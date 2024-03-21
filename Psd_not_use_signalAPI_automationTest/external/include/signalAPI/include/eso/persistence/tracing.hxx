/*****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Martin Stein
*/
/*****************************************************************************/
/*!
    \file
    \brief Convenience for tracing within the persistence service

    Besides auto-including the tracing, we provide a bunch of
    functions here that convert assorted datatypes into a string representation
    suited for trace output.
*/
/*****************************************************************************/
#ifndef PERSISTENCE_TRACING_HXX
#define PERSISTENCE_TRACING_HXX
/*****************************************************************************/

#include <ipl_config.h>

#include <common/tracing/tracing.hxx>
#include <common/streams/sstream.hxx>
#include <comm/commidltypes.hxx>
#include <util/UnicodeString8.hxx>
#include <util/UnicodeString16.hxx>
#include <util/config/Values.hxx>
#include <persistence/Blob.hxx>

#include <persistence/IPersistenceAS.hxx>  // for RequestStatus

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/

    //! \brief Convenience for output
    inline ipl::string repr(const util::UnicodeString8 &s) IPL_NOEXCEPT
    {
        ipl::ostringstream o;
        o << "\"";
        o << s;
        o << "\"";
        return o.str();
    }

    //! \brief Convenience for output
    inline ipl::string repr(const util::UnicodeString16 &s) IPL_NOEXCEPT
    {
        ipl::ostringstream o;
        o << "\"";
        o << s;
        o << "\"";
        return o.str();
    }

    //! \brief Convenience for output
    ipl::string repr(const CIUInt32Array &a) IPL_NOEXCEPT;

    //! \brief Convenience for output
    ipl::string repr(const CIUInt8Array &a) IPL_NOEXCEPT;

    //! \brief Convenience for output
    ipl::string repr(const Blob &b) IPL_NOEXCEPT;

    //! \brief Convenience for output
    inline ipl::string repr(int64_t i) IPL_NOEXCEPT
    {
        ipl::ostringstream o;
        o << i;
        return o.str();
    }

    //! \brief Convenience for output
    inline ipl::string repr(uint64_t i) IPL_NOEXCEPT
    {
        ipl::ostringstream o;
        o << i;
        return o.str();
    }

    //! \brief Convenience for output
    inline ipl::string repr(int32_t i) IPL_NOEXCEPT
    {
        ipl::ostringstream o;
        o << i;
        return o.str();
    }

    //! \brief Convenience for output
    inline ipl::string repr(uint32_t i) IPL_NOEXCEPT
    {
        ipl::ostringstream o;
        o << i;
        return o.str();
    }

    //! \brief Convenience for output
    inline ipl::string repr(bool f) IPL_NOEXCEPT
    {
        return f? "true" : "false";
    }

    //! \brief Convenience for output
    inline ipl::string repr(const RequestStatus &s) IPL_NOEXCEPT
    {
        return repr((uint32_t)s);
    }

    //! \brief Convenience for output
    ipl::string repr(const util::config::Value &v) IPL_NOEXCEPT;

    // forwards for repr(const CIPtr<T> &p)
    template <typename T> ipl::string repr(const CIArray<T> &a) IPL_NOEXCEPT;
    template <typename T> ipl::string repr(const CIPtrArray<T> &a) IPL_NOEXCEPT;

//    //! \brief Convenience for output
//    template <typename T>
//    ipl::string repr(const CIPtr<T> &p) IPL_NOEXCEPT
//    {
//        ipl::ostringstream o;
//        if(p.retrieve()==NULL)
//            o << "NULL";
//        else
//            o << repr(*p.retrieve());
//        return o.str();
//    }

    //! \brief Convenience for output
    template <typename T>
    ipl::string repr(const util::SharedPtr<T> &p) IPL_NOEXCEPT
    {
        if(p.retrieve()==NULL)
            return "NULL";
        else
            return repr(*p/*.retrieve()*/);
    }

    //! \brief Convenience for output
    template <typename T>
    ipl::string repr(const CIArray<T> &a) IPL_NOEXCEPT
    {
        ipl::ostringstream s;
        s << "[";
        for(unsigned i=0; i<a.size(); i++) {
            if(i) s << ", ";
            s << repr(a[i]);
        }
        s << "]";
        return s.str();
    }

//    //! \brief Convenience for output
//    template <typename T>
//    inline ipl::string repr(CIArray<T> &a) IPL_NOEXCEPT
//    {
//        return repr((const CIArray<T> &)a);
//    }

    //! \brief Convenience for output
    template <typename T>
    ipl::string repr(const CIPtrArray<T> &a) IPL_NOEXCEPT
    {
        ipl::ostringstream s;
        s << "[";
        for(unsigned i=0; i<a.size(); i++) {
            if(i) s << ", ";
            s << repr(a[i]);
        }
        s << "]";
        return s.str();
    }

//    //! \brief Convenience for output
//    template <typename T>
//    inline ipl::string repr(CIPtrArray<T> &a) IPL_NOEXCEPT
//    {
//        return repr((const CIArray<T> &)a);
//    }

//    //! \brief Convenience for output
//    ipl::string repr(const Engine::Name &n) IPL_NOEXCEPT;

/*****************************************************************************/

}  // end of namespace persistence

/*****************************************************************************/
#endif
