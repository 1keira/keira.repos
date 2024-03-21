/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_DATABUFFER_HXX
#define UTIL_DATABUFFER_HXX

#include <ipl_config.h>

#include <common/streams/iostream.hxx>
#include <common/types/memory.hxx>
#include <common/types/new.hxx>
#include <common/CommonError.hxx>
#include <common/align.hxx>
#include <common/Macros.hxx>
#define UNLOCK_UTIL_REFERENCECOUNTER_I_KNOW_WHAT_I_AM_DOING
#include <util/ReferenceCounter.hxx>
#undef UNLOCK_UTIL_REFERENCECOUNTER_I_KNOW_WHAT_I_AM_DOING
#include <util/MutexGuard.hxx>

#include <string.h>

#ifdef DataBuffer
#undef DataBuffer
#endif

namespace util {

    /*!
        \brief Store data locally and on the heap

        This class has a local buffer and uses the heap only if the data
        cannot be stored in the local buffer.
        It can be used in two ways.
        Either as a variable size single buffer or as a manager of a number of
        memory blocks of a given size.

        In the first mode the following methods are available:
        - allocate()
        - deallocate()
        - setAllocationStep()
        - storeData()
        - retrieveData()
        - size()
        - resize()
        - char_str()
        - wchar_str()
        - operator << ()
        - operator < ()
        - compare()
        - operator == ()
        - operator + ()
        - operator = ()
        - capacity()

        In the second mode, the following methods are available:
        - allocChunks()
        - useFreeChunk()
        - releaseChunk()
        - capacity()
    */

    template<int LOCAL_STORAGE=8> class DataBuffer {

        friend ipl::ostream &operator << (ipl::ostream &out, DataBuffer<> &db) IPL_NOEXCEPT;

    public:

        enum Flags{
            HEAP_STORAGE = 1,
            CHUNK_USAGE = 2,
            USERFLAG1 = 4,
            USERFLAG2 = 8
        };

        DataBuffer() IPL_NOEXCEPT: m_error(false), m_valid(true), m_flags(0), m_size(0),
            m_chunksize(8), m_mutex(osal::Mutex::RECURSIVE) {}

        /*!
            \brief Fill new DataBuffer with \a value

            \errors
                see allocate()
            \errorindicator
                hasError()
        */
        DataBuffer(uint_fast32_t num_bytes, uint8_t value) IPL_NOEXCEPT: m_error(false),
            m_valid(false), m_flags(0), m_size(0), m_chunksize(8),
            m_mutex(osal::Mutex::RECURSIVE) {

            if(allocate(num_bytes)<0) { return; } // BRANCH_COVERAGE_UNTESTABLE
            for(uint_fast32_t i=0; i<num_bytes; i++)
                if(storeData(&value, m_size, 1)<0) // BRANCH_COVERAGE_UNTESTABLE
                    return;
            m_valid=true;
        }

        DataBuffer(DataBuffer<LOCAL_STORAGE> const &other) IPL_NOEXCEPT: m_error(false),
            m_valid(true), m_flags(0), m_size(0), m_chunksize(other.m_chunksize),
            m_mutex(osal::Mutex::RECURSIVE)
        {
            util::MutexGuard lock(other.m_mutex);
            if(other.m_flags & static_cast<uint8_t>(HEAP_STORAGE)) {
                m_heap.m_allocated=other.m_heap.m_allocated;
                m_heap.m_refcounter=other.m_heap.m_refcounter;
                m_heap.m_refcounter->ref();
            } else
                memcpy(m_buffer, other.m_buffer, LOCAL_STORAGE);

            m_flags=other.m_flags;
            if(other.m_flags & static_cast<uint8_t>(CHUNK_USAGE)) {
                uint_fast32_t numChunks=other.m_heap.m_allocated/other.m_chunksize;
                uint_fast32_t numStatus=numChunks/8;
                if(numStatus*8<numChunks) numStatus+=1;
                
                m_chunkstates=new(ipl::nothrow) uint8_t[numStatus];                
                if(!m_chunkstates) { // BRANCH_COVERAGE_UNTESTABLE
                    ipl_raise(ipl::CommonError, ipl::OUT_OF_MEMORY);
                    m_error=true;
                    return;
                }

                for(uint_fast32_t i=0; i<numStatus; i++)
                    m_chunkstates[i]=other.m_chunkstates[i];
            } else
                m_size=other.m_size;
        }

        virtual ~DataBuffer() IPL_NOEXCEPT {
            util::MutexGuard lock(m_mutex);

            if(m_flags & static_cast<uint8_t>(HEAP_STORAGE))
                if(m_heap.m_refcounter->unref()==1)  // last one
                    delete m_heap.m_refcounter;
            if(m_flags & static_cast<uint8_t>(CHUNK_USAGE))
                delete[] m_chunkstates;
        }

        /*!
            \brief Ensure that the buffer can store at least \a bytes

            The memory is allocated either on the local buffer or on the heap.
            If \a bytes is less than the memory that was allocated previously,
            the buffersize stays the same.

            \return
                > 0 if the existing memory suffices,
                0 if it had to be allocated,
                < 0 if an error occured.
            \errors
                ipl::CommonError with ID OUT_OF_MEMORY
            \errorindicator
                via hasError(), via return value
        */
        int_fast8_t allocate(uint_fast32_t bytes) IPL_NOEXCEPT {
            util::MutexGuard lock(m_mutex);
            m_error=false;

            if(m_flags & static_cast<uint8_t>(HEAP_STORAGE)) {
                // do we need more memory?
                if(bytes<=m_heap.m_allocated) return 1;

                //resize heap storage
                //allocate a little more space to minimize reallocs
                uint32_t chunk = (uint32_t)(bytes/m_chunksize*m_chunksize);
                if (chunk<bytes) chunk += (uint32_t) m_chunksize;
                uint32_t *tmp=new(ipl::nothrow) uint32_t[chunk];
                if(tmp==NULL) { // BRANCH_COVERAGE_UNTESTABLE
                    ipl_raise(ipl::CommonError, ipl::OUT_OF_MEMORY);
                    m_error=true;
                    return -1;
                }

                //update
                // non-copyable, hence monkey-patch:
                RefCounter *new_heap_pointer=new(ipl::nothrow) RefCounter;                
                if(!new_heap_pointer) { // BRANCH_COVERAGE_UNTESTABLE
                    m_error=true;
                    ipl_raise(ipl::CommonError, ipl::OUT_OF_MEMORY);
                    delete[] tmp;
                    return -1;
                }
                
                //copy old data
                memcpy(tmp, m_heap.m_refcounter->get(), m_size);

                if(m_heap.m_refcounter->unref()==1)
                    delete m_heap.m_refcounter;
                new_heap_pointer->setObject(tmp);
                m_heap.m_refcounter=new_heap_pointer;
                m_heap.m_allocated=chunk;
            } else {
                // fits into local buffer
                if(bytes<=LOCAL_STORAGE) return 1;

                // put into heap storage
                //allocate a little more space to minimize reallocs
                uint32_t chunk = (uint32_t)(bytes/m_chunksize*m_chunksize);
                if (chunk<bytes) chunk += (uint32_t) m_chunksize;
                uint32_t *tmp=new(ipl::nothrow) uint32_t[chunk];
                if(tmp==NULL) { // BRANCH_COVERAGE_UNTESTABLE
                    ipl_raise(ipl::CommonError, ipl::OUT_OF_MEMORY);
                    m_error=true;
                    return -1;
                }
                
                // non-copyable, hence monkey-patch:
                RefCounter *reftmp=new(ipl::nothrow) RefCounter;
                if(!reftmp) { // BRANCH_COVERAGE_UNTESTABLE
                    m_error=true;
                    ipl_raise(ipl::CommonError, ipl::OUT_OF_MEMORY);
                    delete[] tmp;
                    return -1;
                }
                
                m_flags|=static_cast<uint8_t>(HEAP_STORAGE);
                //copy old data
                memcpy(tmp, m_buffer, m_size);

                //store the allocation data
                m_heap.m_refcounter=reftmp;
                m_heap.m_refcounter->setObject(tmp);
                m_heap.m_allocated=chunk;
            }

            return 0;
        }

        /*!
            \brief Reduc the size of the allocated buffer to \a bytes.

            The memory is allocated either on the local buffer or on the heap.
            If \a bytes is greater than the memory that was allocated
            previously, the buffersize stays the same.
            If \a bytes is less than the buffer size, the buffer is truncated
            to \a bytes.

            \errors
                see allocate(), allocation may fail due to the need to copy data from old
                buffer into new one, thus one intermediate buffer is needed.
            \errorindicator
                hasError()
        */
        void deallocate(uint_fast32_t bytes) IPL_NOEXCEPT {
            util::MutexGuard lock(m_mutex);
            m_error=false;

            if(!(m_flags & static_cast<uint8_t>(HEAP_STORAGE))) return;
            if(bytes>=m_heap.m_allocated) return;

            //resize heap storage
            //allocate a little more space to minimize reallocs
            uint32_t chunk=bytes/sizeof(uint32_t)*sizeof(uint32_t);
            if(chunk<bytes) chunk+=sizeof(uint32_t);
            uint32_t *tmp=new(ipl::nothrow) uint32_t[chunk];
            if(tmp==NULL) { // BRANCH_COVERAGE_UNTESTABLE
                m_error=true;
                ipl_raise( ipl::CommonError, ipl::OUT_OF_MEMORY );
                return;
            }

            //truncate
            if(bytes<m_size) m_size=bytes;

            //copy old data
            memcpy(tmp, m_heap.m_refcounter->get(), m_size);
            //update
            if(m_heap.m_refcounter->unref()==1)
                delete m_heap.m_refcounter;
            // non-copyable, hence monkey-patch:
            RefCounter *new_heap_pointer=new(ipl::nothrow) RefCounter;
            if(!new_heap_pointer) { // BRANCH_COVERAGE_UNTESTABLE
                m_error=true;
                ipl_raise(ipl::CommonError, ipl::OUT_OF_MEMORY);
                return;
            }
            new_heap_pointer->setObject(tmp);
            m_heap.m_refcounter=new_heap_pointer;
            m_heap.m_allocated=chunk;
        }

        /*!
            \brief Allocate a number of chunks

            If called on an already existing DataBuffer with different
            chunksize the buffer becomes invalid.

            \errors
                see allocate()
            \errorindicator
                hasError()
        */
        void allocChunks(uint_fast32_t num_chunks, uint_fast16_t chunksize=0) IPL_NOEXCEPT {
            util::MutexGuard lock(m_mutex);
            m_error=false;

            IPL_ASSERT(num_chunks*chunksize>LOCAL_STORAGE);
            if(allocate(num_chunks*chunksize)<0) return; // BRANCH_COVERAGE_UNTESTABLE

            //only one bit is needed per chunk as status register
            uint_fast32_t numStatusBytes=num_chunks/8;
            if(numStatusBytes*8<num_chunks) numStatusBytes+=1;
            m_chunkstates=new(ipl::nothrow) uint8_t[numStatusBytes];
            if(!m_chunkstates) { // BRANCH_COVERAGE_UNTESTABLE
                m_error=true;
                ipl_raise(ipl::CommonError, ipl::OUT_OF_MEMORY);
                return;
            }

            memset(m_chunkstates, 0, numStatusBytes);
            m_flags|=static_cast<uint8_t>(CHUNK_USAGE);
            m_chunksize=chunksize;
        }

        /*!
            \brief Copy \a datasize bytes of \a data into the buffer at \a position,
            reallocating if necessary

            \return
                > 0 if new memory was allocated during the storage process,
                0 if not,
                < 0 on error
            \errors
                see allocate()
            \errorindicator
                via hasError(), via return value
        */
        int_fast8_t storeData(const uint8_t *data, uint32_t position,
                              uint32_t datasize) IPL_NOEXCEPT {
            util::MutexGuard lock(m_mutex);
            m_error=false;

            if(m_flags & static_cast<uint8_t>(HEAP_STORAGE))
                m_heap.m_refcounter=m_heap.m_refcounter->copyIfNeccessary((m_heap.m_allocated>>2));
            int_fast8_t enoughMem=allocate(position+datasize);
            if(enoughMem<0) return enoughMem; // BRANCH_COVERAGE_UNTESTABLE

            uint8_t* memory = getDataPointer(position);
            memcpy(memory, data, datasize);
            m_size = (m_size > position+datasize) ? m_size : (position+datasize);
            return (enoughMem == 0);
        }

        //! \brief Get pointer to stored data
        const uint8_t *retrieveData() const IPL_NOEXCEPT { return getDataPointer(0); }

        //! \brief Get buffer size (in bytes)
        uint32_t size() const IPL_NOEXCEPT { return m_size; }

        //! \brief Get actually allocated buffer size (in bytes) -- may be more than size()
        uint32_t capacity() const IPL_NOEXCEPT {
            util::MutexGuard lock(m_mutex);
            if(m_flags & HEAP_STORAGE)
                return m_heap.m_allocated;
            else
                return LOCAL_STORAGE;
        }

        //! \brief Compare buffer content as byte strings
        virtual bool operator<(const DataBuffer& db) const IPL_NOEXCEPT {
            util::MutexGuard lock(m_mutex);

            uint32_t commonSize=(m_size<db.size())? m_size : db.size();
            int cmp=memcmp(retrieveData(), db.retrieveData(), commonSize);
            //in the common length, both are equal
            if(cmp==0) return m_size < db.size();
            return cmp < 0;
        }

        //! \brief Compare buffer content as byte strings
        bool operator <= (const DataBuffer &other) const IPL_NOEXCEPT {
            util::MutexGuard lock(m_mutex);
            return *this<other || *this==other;
        }
        //! \brief Compare buffer content as byte strings
        bool operator > (const DataBuffer &other) const IPL_NOEXCEPT { return !(*this<=other); }
        //! \brief Compare buffer content as byte strings
        bool operator >= (const DataBuffer &other) const IPL_NOEXCEPT { return !(*this<other); }
        /*!
            \brief Compare buffer content as byte strings

            \return
                >0 if *this>db,
                0  if *this==db,
                <0 if *this<db
        */
        virtual int32_t compare(const DataBuffer &db) const IPL_NOEXCEPT {
            util::MutexGuard lock(m_mutex);

            uint32_t commonSize=(m_size < db.size())? m_size : db.size();
            int cmp=memcmp(retrieveData(), db.retrieveData(), commonSize);
            //in the common length, both are equal
            if(cmp==0) {
                if(m_size<db.size())
                    return -1;
                else if(m_size>db.size())
                    return 1;
                return 0;
            }
            return cmp;
        }

        //! \brief Compare buffer content as byte strings
        bool operator == (const DataBuffer &db) const IPL_NOEXCEPT {
            util::MutexGuard lock(m_mutex);

            //different lengths can't be equal
            if(m_size!=db.m_size) return false;
            return memcmp(retrieveData(), db.retrieveData(), m_size)==0;
        }

        //! \brief Compare buffer content as byte strings
        bool operator != (const DataBuffer &other) const IPL_NOEXCEPT { return !operator == (other); }

        //! \brief Concatenate *this and \a db
        virtual DataBuffer<LOCAL_STORAGE> operator + (const DataBuffer &db) const IPL_NOEXCEPT {
            util::MutexGuard lock(m_mutex);

            DataBuffer<LOCAL_STORAGE> ret(*this);
            ret.storeData(db.retrieveData(), m_size, db.m_size);

            // if operation failed storeData has already set error state
            return ret;
        }

        DataBuffer<LOCAL_STORAGE>& operator=(const DataBuffer &db) IPL_NOEXCEPT {
            util::MutexGuard lock1(&m_mutex<&db.m_mutex? m_mutex : db.m_mutex);
            util::MutexGuard lock2(&m_mutex<&db.m_mutex? db.m_mutex : m_mutex);

            if(this==&db) return *this;
            //deallocate the old one
            if(m_flags & static_cast<uint8_t>(HEAP_STORAGE))
                if(m_heap.m_refcounter->unref()==1)
                    delete m_heap.m_refcounter;
            //set the new one
            m_flags=db.m_flags;
            m_size=db.m_size;
            if(db.m_flags & static_cast<uint8_t>(HEAP_STORAGE)) {
                m_heap.m_refcounter=db.m_heap.m_refcounter;
                if(m_heap.m_refcounter->ref()==0) {
                    // lost a race, the other side already got unrefed
                    // save your butt, reinit as empty
                    m_heap.m_allocated=0;
                    m_flags=0;
                    m_size=0;
                    return *this;
                }
                m_heap.m_allocated=db.m_heap.m_allocated;
            } else
                memcpy(m_buffer, db.m_buffer, LOCAL_STORAGE);
            return *this;
        }

        //! \brief Change size(), reallocating if necessary
        void resize(uint32_t newsize) IPL_NOEXCEPT {
            util::MutexGuard lock(m_mutex);

            if(m_flags & static_cast<uint8_t>(HEAP_STORAGE))
                m_heap.m_refcounter=m_heap.m_refcounter->copyIfNeccessary((m_heap.m_allocated>>2));
            if(allocate(newsize)<0) // BRANCH_COVERAGE_UNTESTABLE
                return;
            m_size=newsize;
        }

        /*!
            \brief Allocate a chunk

            The buffer must be in chunk mode, i.e. call allocChunks() before.
        */
        uint8_t *useFreeChunk() IPL_NOEXCEPT {
            util::MutexGuard lock(m_mutex);

            //search status list for free chunk
            if(m_flags & static_cast<uint8_t>(CHUNK_USAGE)) {
                uint32_t numChunks = (uint32_t)(m_heap.m_allocated/m_chunksize);
                uint32_t numStatus=numChunks/8;
                if(numStatus*8<numChunks) numStatus+=1;
                for(uint32_t i=0; i<numStatus; i++)
                    for(unsigned int j=0; j<8; j++) {
                        uint8_t usedmask=(uint8_t)(1u<<j);
                        if(!(m_chunkstates[i] & usedmask)) {
                            // free chunk found
                            m_chunkstates[i]|=usedmask;
                            uint32_t pos = (uint32_t) (m_chunksize*(i*8+j));
                            return (uint8_t*)m_heap.m_refcounter->get()+pos;
                        }
                    }
            }
            return NULL;
        }

        //! \brief Deallocate \a chunk allocated by useFreeChunkl() earlier
        void releaseChunk(uint8_t* chunk) IPL_NOEXCEPT {
            util::MutexGuard lock(m_mutex);

            if(m_flags & static_cast<uint8_t>(CHUNK_USAGE)) {
                uint32_t pos=(uint32_t)((chunk-(uint8_t*)m_heap.m_refcounter->get())/m_chunksize);
                //get status byte offset
                int32_t offset=pos/8;
                uint8_t bit=(uint8_t)(pos-(uint32_t)(offset*8));
                m_chunkstates[offset]&=(uint8_t)~(1u<<bit);
            }
        }

        /*!
            \brief Get a pointer to the data
            <strong>without any guarantees about zero-termination</strong>
        */
        const char *char_str() const IPL_NOEXCEPT { return (char const*)retrieveData(); }

        /*!
            \brief Get a pointer to the data
            <strong>without any guarantees about zero-termination</strong>
        */
        const wchar_t *wchar_str() const IPL_NOEXCEPT { return ipl::cast_without_warning<wchar_t const*>(retrieveData()); }

        //! \brief Set internal allocation granularity
        void setAllocationStep(uint16_t stepsize) IPL_NOEXCEPT {
            util::MutexGuard lock(m_mutex);
            m_chunksize=stepsize;
        }

        bool hasError() const IPL_NOEXCEPT { return m_error; }
        bool isValid() const IPL_NOEXCEPT { return m_valid; }

    protected:

        typedef ReferenceCounter<uint32_t, true> RefCounter;

        uint8_t *getDataPointer(int_fast32_t offset) const IPL_NOEXCEPT {
            util::MutexGuard lock(m_mutex);
            if(m_flags & static_cast<uint8_t>(HEAP_STORAGE))
                return reinterpret_cast<uint8_t*>(m_heap.m_refcounter->get())+offset;
            else
                return const_cast<uint8_t*>(m_buffer+offset);
        }

        bool m_error;
        bool m_valid;
        uint8_t m_flags;

        union {
            //! \brief The size of the stored data in bytes
            uint32_t m_size;
            //! \brief The pointer to the chunk status data
            uint8_t *m_chunkstates;
        };

        union {
            //! \brief The local data buffer
            uint8_t m_buffer[LOCAL_STORAGE];

            struct {
                //! \brief The pointer to the heap
                RefCounter *m_refcounter;
                //! \brief The allocated memory in bytes
                uint32_t m_allocated;
            } m_heap;
        };

        //! \brief Alloc granularity, in chunk mode size of one chunk
        uint_fast16_t m_chunksize;
        osal::Mutex m_mutex;
    };

    ipl::ostream &operator << (ipl::ostream &out, DataBuffer<> &db) IPL_NOEXCEPT;

} // end namespace

#endif
