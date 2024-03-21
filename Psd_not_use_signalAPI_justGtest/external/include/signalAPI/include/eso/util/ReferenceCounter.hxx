/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UNLOCK_UTIL_REFERENCECOUNTER_I_KNOW_WHAT_I_AM_DOING
#error Do not use util::ReferenceCounter. Use util::SharedPtr or build the functionality yourself.
#endif

#ifndef UTIL_REFERENCECOUNTER_HXX
#define UTIL_REFERENCECOUNTER_HXX

#include <ipl_config.h>

#include <common/stdint.h>
#include <common/streams/iostream.hxx>
#include <common/Macros.hxx>
#include <common/align.hxx>
#include <common/types/memory.hxx>
#include <common/NonCopyable.hxx>

#include <osal/AtomicCounter.hxx>

namespace util {

    /*!
        \brief Don't use!

        Crude reference counting for objects and arrays.
    */

    template<typename T, bool IS_ARRAY = false>
    class ReferenceCounter: public ipl::NonCopyable {

    public:

//         typedef osal::AtomicCounterType Count;

        ReferenceCounter() IPL_NOEXCEPT: m_object(NULL), m_counter(0) {}

        /*!
            \brief Initialize with \a object which must me allocated by new
        */
        ReferenceCounter(T *object) IPL_NOEXCEPT: m_object(object), m_counter(1) {}

        ~ReferenceCounter() IPL_NOEXCEPT {
            if(m_counter.getCurrentCount() != 0) // BRANCH_COVERAGE_UNTESTABLE
                ipl::cerr << "Warning: ReferenceCounter destroyed while not all"
                             " counted objects were unrefed! Maybe a bug in your Code?"
                          << ipl::endl;
        }

        /*!
            \brief Assign \a object
        */
        void setObject(T *object) IPL_NOEXCEPT
        {
            if(ref()>0) {
                unref();
                ipl::cerr << "non empty RefCounter set tried";
            } else {
                m_object=object;
            }
        }

        //! \brief Increment the reference
        osal::AtomicCounterType ref() IPL_NOEXCEPT { return m_counter.increment(); }

        //! \brief Decrement the reference
        osal::AtomicCounterType unref() IPL_NOEXCEPT {
            if (m_counter.getCurrentCount()>0) {
                osal::AtomicCounterType count=m_counter.decrement();
                if(count==1) {
                    //last reference gone
                    if(IS_ARRAY)
                        delete[] m_object;
                    else
                        delete m_object;
                    m_object=NULL;
                }
                return count;
            } else{
                ipl::cerr << "Tried to unref an already deleted or non-existing object.";
                return 0;
            }
        }

        //! \brief <strong>Do not use</strong>
        osal::AtomicCounterType getRefCount() IPL_NOEXCEPT { return m_counter.getCurrentCount(); }

        //! \brief Get a singly-refed buffer, either \a this or a (new-allocated) copy
        ReferenceCounter<T, IS_ARRAY> *copyIfNeccessary(uint32_t num_elems=1) IPL_NOEXCEPT
        {
            if(m_counter.getCurrentCount()>1) {
                // Note: this is not threadsafe!
                ReferenceCounter<T, IS_ARRAY> *ret=NULL;
                while(!ret) {
                    ret=new ReferenceCounter<T, IS_ARRAY>;
                    if(!ret) IPL_OOM("refcounter"); // BRANCH_COVERAGE_UNTESTABLE
                }
                T *newT=NULL;
                if(IS_ARRAY) {
                    while(!newT) {
                        newT=ipl::cast_without_warning<T *>(new unsigned char[num_elems*sizeof(T)]);
                        if(!newT) IPL_OOM("ref-array");
                    }
                    for(uint32_t i=0; i<num_elems; i++)
                        new(newT+i) T(m_object[i]);
                } else {
                    while(!newT) {
                        newT=new T(*m_object);
                        if(!newT) IPL_OOM("ref-obj");
                    }
                }

                ret->setObject(newT);
                // We have copied ourself, so we return an unshared copy.
                // Hence we transfer one reference form this to ret.
                unref();
                return ret;
            } else
                return this;
        }

        //! \brief Get actual data pointer
        T *get() const  IPL_NOEXCEPT{ return m_object; }

    protected:
        T *m_object;
        //! \brief The reference counter
        osal::AtomicCounter m_counter;
    };

}  // end of namespace util

#endif
