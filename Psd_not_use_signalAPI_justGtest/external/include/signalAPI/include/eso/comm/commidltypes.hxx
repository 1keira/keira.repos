/*****************************************************************************/
/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef COMM_IDL_TYPES_HXX
#define COMM_IDL_TYPES_HXX
/*****************************************************************************/

#include <ipl_config.h>
#include <common/streams/iostream.hxx>
#include <common/types/vector.hxx>
#include <util/UnicodeString.hxx>
#include <util/serializer/IStreamSerializer.hxx>
#include <util/serializer/IStreamDeserializer.hxx>
#include <util/serializer/IStructuredSerializer.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>
#include <util/SharedPtr.hxx>
#include <comm/Error.hxx>
#include <comm/comm_dso.h>

#include <stdlib.h>

/*****************************************************************************/

#ifdef IPL_OS_WIN32
    #if defined (IPL_PROXY_EXPORT)
        #define PROXY_EXPORT __declspec(dllexport)
    #elif defined(IPL_PROXY_IMPORT)
        #define PROXY_EXPORT __declspec(dllimport)
    #else
        #define PROXY_EXPORT
    #endif
#elif defined IPL_OS_INTEGRITY
    #define PROXY_EXPORT
#else
    #if __GNUC__ >= 4
      #define PROXY_EXPORT __attribute__ ((visibility("default")))
    #else
      #define PROXY_EXPORT
    #endif
#endif

#ifdef CIPTR_CNT_AVAILABLE
COMM_EXPORT long getCIPtrCounter(void);
COMM_EXPORT void incCIPtrCounter(void);
#endif

// forward declaration of the CIFactory template class.
template<typename T> class CIFactory;

/*****************************************************************************/

/*!
    \brief Reference counted pointer

    This is basically a typedef for util::SharedPtr.
    You can use it just as you would use a T* except that
    there is no array functionality, i.e. no operator [],
    operator + and operator -.

    For more details on the methods see util::SharedPtr
*/
template <class T>
class CIPtr : public util::SharedPtr<T> {
public:
    CIPtr(const util::SharedPtr<T> &p=nullptr)
    : util::SharedPtr<T>(p) {
#ifdef CIPTR_CNT_AVAILABLE
        incCIPtrCounter();
#endif
    }
    CIPtr(const CIPtr<T> &other)
    : util::SharedPtr<T>(other) {
#ifdef CIPTR_CNT_AVAILABLE
            incCIPtrCounter();
#endif
    }
    CIPtr(T *t)
    : util::SharedPtr<T>(t) {
#ifdef CIPTR_CNT_AVAILABLE
        incCIPtrCounter();
#endif
    }

    CIPtr<T> &operator = (const CIPtr<T> &p) {
        util::SharedPtr<T>::operator=(p);
        return *this;
    }

    CIPtr<T> &operator = (T *p) {
        util::SharedPtr<T>::operator=(p);
        return *this;
    }
};

/*****************************************************************************/

/*!
    \brief Array holding \a T instances

    It's basically a typedef for an ipl::vector<T>.

    It's used as a container for the COMM Transport. By definition these
    containers must not be constructed explicitely by applictions,
    but they must be constructed by using the factory CITypesFactory.

    Because of this it hides all c'tors and can't be instantiated by itself.

    All other methods of the vector are visible and can be called.
*/
template<typename T>
class CIArray: public ipl::vector<T> {
public:
    typedef size_t size_type;

    CIArray<T>& operator=(const CIArray<T>& other) IPL_NOEXCEPT {
        if ( this != &other ) {
            this->ipl::vector<T>::operator=((const ipl::vector<T>&)other);
        }
        return *this;
    }
    private:
    CIArray(size_type capacity=0) IPL_NOEXCEPT { this->resize(capacity); }
    CIArray(const CIArray& other) IPL_NOEXCEPT : ipl::vector<T>(other) {}
    friend class CIFactory<T>;
    friend class CIFactory< CIArray<T> >;
    friend class ipl::vector< CIArray<T> >;
    friend class ipl::allocator< CIArray<T> >;
    friend class CITypesFactory;
    friend class COMMIdlTypesSerializer;

#ifdef HAVE__CONSTRUCT_RVALUE_REFERENCE
    template<class T1, class T2> friend void std::_Construct(T1*, T2&&);
#endif

#ifdef HAVE__CONSTRUCT_LVALUE_REFERENCE
    template<class T1, class T2> friend void std::_Construct(T1*, const T2&);
#endif
};

/*****************************************************************************/

/*!
    \brief Array holding CIPtr<T> instances

    It's basically a typedef for an ipl::vector<CIPtr<T>>.

    It's used as a container for the COMM Transport holding a list
    of pointers to instances of classes for the COMM Transport.
    By definition these containers must not be constructed explicitely
    by applictions, but they must be constructed by using the factory
    CITypesFactory or the specialised factories for COMM transport types
    (see class CIFactory<T>).

    It hides all c'tors and can't be instantiated by itself.

    All methods defined in this class overwrite the methods from the base class.
    For a detailed description of these methods see the documentation
    of ipl::vector.
*/
template<typename T>
class CIPtrArray : public ipl::vector<CIPtr<T> >{
public:
    CIPtrArray<T>& operator=(const CIPtrArray<T>& other) IPL_NOEXCEPT {
        if ( this != &other ) {
            this->ipl::vector<CIPtr<T> >::operator=((const ipl::vector<CIPtr<T> >&)other);
        }
        return *this;
    }
private:
    CIPtrArray(size_t capacity=0) IPL_NOEXCEPT  { this->resize(capacity);}
    CIPtrArray(CIPtrArray& other) IPL_NOEXCEPT {}

    friend class CIFactory<T>;
    friend class CIFactory<CIPtrArray>;
    friend class CITypesFactory;
    friend class COMMIdlTypesSerializer;
};

/*****************************************************************************/

/*!
    \brief Unicode String used as container for COMM Transport

    It's used to transfer strings via the COMM Transport. By definition these
    instances must not constructed explicitely by applictions, but they must
    be constructed by using the factory CITypesFactory.

    -    All ctors() are hidden.
    -    methods from the UnicodeString creating a new instance (like operator+ and assignment) can
        not be called, because the create a new instance, which is prevented
    -     All other methods from UnicodeString are visible and can be used by applications

    For more details on the methods see util::UnicodeString
*/
/*COMM_EXPORT*/ class CIString : public util::UnicodeString {
    public:
//         using util::UnicodeString::operator =;  Nope, the warnings settings won't accept that
        CIString &operator = (const util::UnicodeString8 &other) IPL_NOEXCEPT {
            util::UnicodeString::operator = (other);
            return *this;
        }
        CIString &operator = (const util::UnicodeString16 &other) IPL_NOEXCEPT {
            util::UnicodeString::operator = (other);
            return *this;
        }
        CIString &operator = (const CIString &other) IPL_NOEXCEPT {
            util::UnicodeString::operator = (other);
            return *this;
        }

    private:
        CIString (char const * string, util::UnicodeString::Encoding enc) IPL_NOEXCEPT : util::UnicodeString(string, enc) {};
        CIString (const util::UnicodeString8& from) IPL_NOEXCEPT : util::UnicodeString (from) {};
        CIString (const util::UnicodeString16& from) IPL_NOEXCEPT : util::UnicodeString (from) {};
        CIString (const CIString& from) IPL_NOEXCEPT : util::UnicodeString (from) {};
        CIString () IPL_NOEXCEPT : util::UnicodeString() {};

        friend class CITypesFactory;
        friend class CIFactory<CIString>;
};

/*****************************************************************************/

/*!
    \brief    typedef for arrays of simple data types
    
    \{
*/
typedef CIArray<uint8_t>        CIUInt8Array;
typedef CIArray<int8_t>         CIInt8Array;
typedef CIArray<uint16_t>       CIUInt16Array;
typedef CIArray<int16_t>        CIInt16Array;
typedef CIArray<uint32_t>       CIUInt32Array;
typedef CIArray<int32_t>        CIInt32Array;
typedef CIArray<uint64_t>       CIUInt64Array;
typedef CIArray<int64_t>        CIInt64Array;
typedef CIArray<bool>           CIBoolArray;
typedef CIArray<float>          CIFloatArray;
typedef CIArray<double>         CIDoubleArray;
typedef CIPtrArray<CIString>    CIStringArray;
typedef CIPtrArray<ipl::string> CICStringArray;
/*! \} */

/*****************************************************************************/

/*!
    \brief    factory for creating instances of type \a T and
            arrays of instance pointers of type \a T
*/
template<typename T>
class CIFactory {
public:
    /*!
        \brief    create array of instance \e pointers of type \a T

        All instance pointers within the array are to the \c NULL
        by default.
    */
    static inline CIPtr<CIPtrArray<T> > createArray(size_t size = 0) IPL_NOEXCEPT {
        return new (ipl::nothrow) CIPtrArray<T>(size);
    }

    /*!
        \brief    create array of \e instances of type \a T

        All instances within the array are default constructed.
    */
    static inline CIPtr<CIArray<T> > createObjectArray(size_t size = 0) IPL_NOEXCEPT {
        return new (ipl::nothrow) CIArray<T>(size);
    }

    /*!
        \brief    create array of instance \e pointers of type \a T

        All instance pointers within the array are to the \c NULL
        by default.
    */
    static inline void createArray(CIPtr<CIPtrArray<T> >& a, size_t size = 0) IPL_NOEXCEPT {
        a = new (ipl::nothrow) CIPtrArray<T>(size);
    }

    /*!
        \brief    create array of \e instances of type \a T

        All instances within the array are default constructed.
    */
    static inline void createObjectArray(CIPtr<CIArray<T> >& a, size_t size = 0) IPL_NOEXCEPT {
        a = new (ipl::nothrow) CIArray<T>(size);
    }

    /*!
        \brief    create instance of type \a T
    */
    static inline CIPtr<T> createObject() IPL_NOEXCEPT {
        return CIPtr<T> (new (ipl::nothrow) T());
    }

    /*!
        \brief    create instance of type \a T
    */
    static inline void createObject(CIPtr<T>&  s) IPL_NOEXCEPT {
        s = new (ipl::nothrow) T();
    }
};

/*****************************************************************************/

/*!
    \brief    factory for arrays of standard data types, array of strings and
            string instances
*/
class COMM_EXPORT CITypesFactory {
    
public:
    /*!
        \brief create an empty string
        \errorindicator
                return value is a NULL pointer within the CIPtr

        \errors    ipl::CommonError -> ipl::OUT_OF_MEMORY
    */
    static CIPtr<CIString> createString () IPL_NOEXCEPT;

    /*!
        \brief create an empty string
        \errorindicator
                parameter s is a NULL pointer within the CIPtr

        \errors    ipl::CommonError -> ipl::OUT_OF_MEMORY
    */
    static void createString (CIPtr<CIString>& s) IPL_NOEXCEPT;

    /*!
        \brief create an string based on given char pointer content and encoding
        \errorindicator
                return value is a NULL pointer within the CIPtr

        \errors    ipl::CommonError -> ipl::OUT_OF_MEMORY
    */
    static CIPtr<CIString>
    createString (char const * string,
                  const util::UnicodeString::Encoding enc) IPL_NOEXCEPT;

    /*!
        \brief create an string based on another string
        \errorindicator
                return value is a NULL pointer within the CIPtr

        \errors    ipl::CommonError -> ipl::OUT_OF_MEMORY
    */
    static CIPtr<CIString>
    createString (const util::UnicodeString8& from) IPL_NOEXCEPT;

    /*!
        \brief create an string based on another string
        \errorindicator
                return value is a NULL pointer within the CIPtr

        \errors    ipl::CommonError -> ipl::OUT_OF_MEMORY
    */
    static CIPtr<CIString>
    createString (const util::UnicodeString16& from) IPL_NOEXCEPT;

    /*!
        \brief create an array of uint8_t values.

        \return    created instance in the CIPtr.

        \errorindicator
                return value is a NULL pointer within the CIPtr

        \errors    ipl::CommonError -> ipl::OUT_OF_MEMORY
    */
    static CIPtr<CIUInt8Array> createUInt8Array (size_t size = 0) IPL_NOEXCEPT;

    /*!
        \brief create an array of int8_t values.

        \return    created instance in the CIPtr.

        \errorindicator
                return value is a NULL pointer within the CIPtr

        \errors    ipl::CommonError -> ipl::OUT_OF_MEMORY
    */
    static CIPtr<CIInt8Array> createInt8Array (size_t size = 0) IPL_NOEXCEPT;

    /*!
        \brief create an array of uint16_t values.

        \return    created instance in the CIPtr.

        \errorindicator
                return value is a NULL pointer within the CIPtr

        \errors    ipl::CommonError -> ipl::OUT_OF_MEMORY
    */
    static CIPtr<CIUInt16Array> createUInt16Array (size_t size = 0) IPL_NOEXCEPT;

    /*!
        \brief    create an array of int16_t values.

        \return    created instance in the CIPtr.

        \errorindicator
                return value is a NULL pointer within the CIPtr

        \errors    ipl::CommonError -> ipl::OUT_OF_MEMORY
    */
    static CIPtr<CIInt16Array> createInt16Array (size_t size = 0) IPL_NOEXCEPT;

    /*!
        \brief    create an array of uint32_t values.

        \return    created instance in the CIPtr.

        \errorindicator
                return value is a NULL pointer within the CIPtr

        \errors    ipl::CommonError -> ipl::OUT_OF_MEMORY
    */
    static CIPtr<CIUInt32Array> createUInt32Array (size_t size = 0) IPL_NOEXCEPT;

    /*!
        \brief    create an array of int32_t values.

        \return    created instance in the CIPtr.

        \errorindicator
                return value is a NULL pointer within the CIPtr

        \errors    ipl::CommonError -> ipl::OUT_OF_MEMORY
    */
    static CIPtr<CIInt32Array> createInt32Array (size_t size = 0) IPL_NOEXCEPT;

    /*!
        \brief     create an array of uint64_t values.

        \return    created instance in the CIPtr.

        \errorindicator
                return value is a NULL pointer within the CIPtr

        \errors    ipl::CommonError -> ipl::OUT_OF_MEMORY
    */
    static CIPtr<CIUInt64Array> createUInt64Array (size_t size = 0) IPL_NOEXCEPT;

    /*!
        \brief    create an array of int64_t values.

        \return    created instance in the CIPtr.

        \errorindicator
                return value is a NULL pointer within the CIPtr

        \errors    ipl::CommonError -> ipl::OUT_OF_MEMORY
    */
    static CIPtr<CIInt64Array> createInt64Array (size_t size = 0) IPL_NOEXCEPT;

    /*!
        \brief    create an array of float values.

        \return    created instance in the CIPtr.

        \errorindicator
                return value is a NULL pointer within the CIPtr

        \errors    ipl::CommonError -> ipl::OUT_OF_MEMORY
    */
    static CIPtr<CIFloatArray> createFloatArray (size_t size = 0) IPL_NOEXCEPT;

    /*!
        \brief    create an array of double values.

        \return    created instance in the CIPtr.

        \errorindicator
                return value is a NULL pointer within the CIPtr

        \errors    ipl::CommonError -> ipl::OUT_OF_MEMORY
    */
    static CIPtr<CIDoubleArray> createDoubleArray (size_t size = 0) IPL_NOEXCEPT;

    /*!
        \brief    create an array of bool values.

        \return    created instance in the CIPtr.

        \errorindicator
                return value is a NULL pointer within the CIPtr

        \errors    ipl::CommonError -> ipl::OUT_OF_MEMORY
    */
    static CIPtr<CIBoolArray> createBoolArray (size_t size = 0) IPL_NOEXCEPT;

    /*!
        \brief    create an array of CIString instance pointers. All pointers are set to NULL.

        \return    created instance in the CIPtr.

        \errorindicator
                return value is a NULL pointer within the CIPtr

        \errors    ipl::CommonError -> ipl::OUT_OF_MEMORY
    */
    static CIPtr<CIStringArray> createStringArray (size_t size = 0) IPL_NOEXCEPT;

    /*!
        \brief    create an array of ipl::string instance pointers. All pointers are set to NULL.

        \return    created instance in the CIPtr.

        \errorindicator
                return value is a NULL pointer within the CIPtr

        \errors    ipl::CommonError -> ipl::OUT_OF_MEMORY
    */
    static CIPtr<CICStringArray> createCStringArray (size_t size = 0) IPL_NOEXCEPT;
};

/*****************************************************************************/

namespace comm {
    //! \brief c++ binding for idl data types
    namespace idl {

/*****************************************************************************/

        template<typename T>
        bool compare (const CIPtr<T>& s1, const CIPtr<T>& s2) IPL_NOEXCEPT;

        template<typename T>
        bool compare (const CIPtr<CIPtrArray<T> >& s1,
                      const CIPtr<CIPtrArray<T> >& s2) IPL_NOEXCEPT {
            if (!s1 && !s2)
                return true;
            if ((s1 && !s2) || (!s1 && s2))
                return false;
            if (s1->size() != s2->size())
                return false;
            for (size_t cnt = 0; cnt < s1->size(); cnt++) {
                if (!compare ((*s1)[cnt], (*s2)[cnt]))
                    return false;
            }
            return true;
        }

        template<typename T>
        bool compare (const CIPtr<CIArray<T> >& s1,
                      const CIPtr<CIArray<T> >& s2) IPL_NOEXCEPT {
            if (!s1 && !s2)
                return true;
            if ((s1 && !s2) || (!s1 && s2))
                return false;
            if (s1->size() != s2->size())
                return false;
            for (size_t cnt = 0; cnt < s1->size(); cnt++) {
                if ((*s1)[cnt] != (*s2)[cnt])
                    return false;
            }
            return true;
        }

        template<>
        COMM_EXPORT bool compare (const CIPtr<CIString>& s1,
                                  const CIPtr<CIString>& s2) IPL_NOEXCEPT;

/*****************************************************************************/

        template <typename T>
        COMM_EXPORT bool deep_copy(const CIPtr<CIPtrArray<T>> &from,
                                   CIPtr<CIPtrArray<T>> &to);
        
        inline bool deep_copy(const        bool &from,        bool &to) { to=from; return false; }
        inline bool deep_copy(const std::vector<bool>::reference from,
                              std::vector<bool>::reference to)          { to=from; return false; }
        inline bool deep_copy(const     uint8_t &from,     uint8_t &to) { to=from; return false; }
        inline bool deep_copy(const      int8_t &from,      int8_t &to) { to=from; return false; }
        inline bool deep_copy(const    uint16_t &from,    uint16_t &to) { to=from; return false; }
        inline bool deep_copy(const     int16_t &from,     int16_t &to) { to=from; return false; }
        inline bool deep_copy(const    uint32_t &from,    uint32_t &to) { to=from; return false; }
        inline bool deep_copy(const     int32_t &from,     int32_t &to) { to=from; return false; }
        inline bool deep_copy(const    uint64_t &from,    uint64_t &to) { to=from; return false; }
        inline bool deep_copy(const     int64_t &from,     int64_t &to) { to=from; return false; }
        inline bool deep_copy(const       float &from,       float &to) { to=from; return false; }
        inline bool deep_copy(const      double &from,      double &to) { to=from; return false; }
        
        COMM_EXPORT bool deep_copy(const CIPtr<CIString> &from,
                                   CIPtr<CIString> &to);
        COMM_EXPORT bool deep_copy(const CIPtr<std::string> &from,
                                   CIPtr<std::string> &to);

        template <typename T>
        /*COMM_EXPORT*/ bool deep_copy(const CIPtr<CIArray<T>> &from,
                                   CIPtr<CIArray<T>> &to)
        {
            if(!from) {
                to=nullptr;
                return false;
            }
            CIFactory<T>::createObjectArray(to, from->size());
            if(!to) return true;
            for(typename CIArray<T>::size_type i=0; i<from->size(); i++)
                if(deep_copy((*from)[i], (*to)[i]))
                    return true;
            return false;
        }
        
        template <typename T>
        /*COMM_EXPORT*/ bool deep_copy(const CIPtr<CIPtrArray<T>> &from,
                                   CIPtr<CIPtrArray<T>> &to)
        {
            if(!from) {
                to=nullptr;
                return false;
            }
            CIFactory<T>::createArray(to, from->size());
            if(!to) return true;
            for(typename CIPtrArray<T>::size_type i=0; i<from->size(); i++)
                if(deep_copy((*from)[i], (*to)[i]))
                    return true;
            return false;
        }
    
/*****************************************************************************/

    }  // end of namespace idl
}  // end of namespace comm

/*****************************************************************************/
// Serializer / Deserializer
/*****************************************************************************/

namespace util {
    namespace serializer {

        /*!
            \brief   structured serialization method for CIPtrArray<T>

            \return    false in case of success, true in case of error

            \errorindicator
                    return value
        */
        template<typename T>
        inline bool serialize (IStructuredSerializer &serializer,
                               const CIPtrArray<T> &array) IPL_NOEXCEPT
        {
            if (serializer.beginArray()) return true;
            for  (const auto& val : array)
            {
                if (!val) {
                    serializer.putEmptyElement();
                } else {
                    if (serializer.beginElement()) return true;
                    if (serialize(serializer, *val)) return true;
                    if (serializer.endElement()) return true;
                }
            }
            return serializer.endArray();
        }

        /*!
            \brief   structured deserialization method for CIPtrArray<T>

            \return    false in case of success, true in case of error

            \errorindicator
                    return value
        */
        template<typename T>
        inline bool deserialize (IStructuredPullDeserializer &s,
                                 CIPtrArray<T>  &arr) IPL_NOEXCEPT
        {
            if (s.beginArray()) return true;
            while (!s.isArrayEnd()) {
                CIPtr<T> elem;
                bool isEmpty =false;
                if (s.getEmptyElement(isEmpty)) return true;
                if (isEmpty) {
                    arr.emplace_back(elem);
                } else {
                    CIFactory<T>::createObject(elem);
                    if (!elem) return true; // BRANCH_COVERAGE_UNTESTABLE
                    if (s.beginElement()) return true;
                    if (deserialize(s, *elem)) return true;
                    arr.emplace_back(elem);
                    if (s.endElement()) return true;
                }
            }
            return s.endArray();
        }

    }  // end of namespace serializer
}  // end of namespace util

/*****************************************************************************/
#endif
