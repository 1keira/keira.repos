/*****************************************************************************/
/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
    $Id$
*/
/*****************************************************************************/
#ifndef PERSISTENCE_COMMON_HXX
#define PERSISTENCE_COMMON_HXX
/*****************************************************************************/

// #include <ipl_config.h>

#include <common/error/Error.hxx>
#include <common/streams/sstream.hxx>
#include <tracing/tracing.hxx>
#include <comm/commidltypes.hxx>  // for repr parameters
#include <util/UnicodeString8.hxx>  // for repr parameters
#include <util/UnicodeString16.hxx>  // for repr parameters
#include <util/config/Values.hxx>

#ifdef ERROR
#undef ERROR  // Window$ strikes again...
#endif

/*****************************************************************************/

#ifdef FW_PERSISTENCE_KERNELTRACES
#include <osal/KernelTrace.hxx>
#ifndef KERNELTRACE_S
#define KERNELTRACE_S(event_id, string)       ::osal::kernel::TraceEventString(event_id, string)
#endif
#ifndef KERNELTRACE_I
#define KERNELTRACE_I(event_id, data0, data1) ::osal::kernel::TraceEventInt(event_id, data0, data1)
#endif
#ifndef KERNELTRACE_B
#define KERNELTRACE_B(event_id, buf, len)     ::osal::kernel::TraceEventBuffer(event_id, buf, len);
#endif
#else
#ifndef KERNELTRACE_S
#define KERNELTRACE_S(event_id, string)       do { /* NOP */ } while(0)
#endif
#ifndef KERNELTRACE_I
#define KERNELTRACE_I(event_id, data0, data1) do { /* NOP */ } while(0)
#endif
#ifndef KERNELTRACE_B
#define KERNELTRACE_B(event_id, buf, len)     do { /* NOP */ } while(0)
#endif
#endif

/*****************************************************************************/

//IPL_TRACE_DECLARE_CHANNEL_EXTERN(FW_PERSISTENCE_SERVICE);  // normal traces
IPL_TRACE_DECLARE_CHANNEL_EXTERN(FW_PERSISTENCE_CONFIG);  // config parsers only
IPL_TRACE_DECLARE_CHANNEL_EXTERN(FW_PERSISTENCE_FLUSH);  // flush tracing only!

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/

    //! \brief Parent of all persistence errors
    extern ipl::ErrorType ERROR;
    //! \brief Parent of all persistence errors of "no such entry" style
    extern ipl::ErrorType NOT_FOUND;
    //! \brief Parent of all persistence errors of "mismatch" style, e.g. type or version mismatch
    extern ipl::ErrorType MISMATCH;
    //! \brief Parent of all persistence errors of "improper use" style, e.g. writing outside a transaction
    extern ipl::ErrorType USAGE;
    //! \brief Parent of all retryable persistence errors
    extern ipl::ErrorType BUSY;
    //! \brief Parent of all persistence errors of "timeout" style, e.g. some backend didn't answer
    extern ipl::ErrorType TIMEOUT;

/*****************************************************************************/

//    //! \brief Convenience for output
//    inline ipl::string repr(const CIString &s)
//    {
//        ipl::string o="\"";
//        o+=s.utf8().char_str();
//        o+="\"";
//        return o;
//    }

//     //! \brief Convenience for output
//     inline ipl::string repr(const util::UnicodeString8 &s)
//     {
//         ipl::string o="\"";
//         o+=s.utf8().char_str();
//         o+="\"";
//         return o;
//     }
// 
//     //! \brief Convenience for output
//     inline ipl::string repr(const util::UnicodeString16 &s)
//     {
//         ipl::string o="\"";
//         o+=s.utf8().char_str();
//         o+="\"";
//         return o;
//     }
// 
//     //! \brief Convenience for output
//     inline ipl::string repr(const CIUInt32Array &a)
//     {
//         ipl::ostringstream s;
//         s << "[";
//         for(unsigned i=0; i<a.size(); i++) {
//             if(i) s << ", ";
//             s << a[i];
//         }
//         s << "]";
//         return s.str();
//     }
// 
//     //! \brief Convenience for output
//     inline ipl::string repr(const CIUInt8Array &a)
//     {
//         static char hex[]={'0', '1', '2', '3', '4', '5', '6', '7',
//                            '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
//         ipl::ostringstream s;
//         s << "[";
//         for(unsigned i=0; i<a.size(); i++) {
//             if(i) s << ", ";
//             s << hex[a[i] >> 4] << hex[a[i] & 0x0f];
//         }
//         s << "]";
//         return s.str();
//     }
// 
//     //! \brief Convenience for output
//     inline ipl::string repr(bool f)
//     {
//         return f? "true" : "false";
//     }
// 
//     //! \brief Convenience for output
//     ipl::string repr(const util::config::Value &v);
// 
//     //! \brief Convenience for output
//     template <typename T>
//     inline ipl::string repr(const CIArray<T> &a)
//     {
//         ipl::ostringstream s;
//         s << "[";
//         for(unsigned i=0; i<a.size(); i++) {
//             if(i) s << ", ";
//             s << repr(a[i]);
//         }
//         s << "]";
//         return s.str();
//     }
// 
//     //! \brief Convenience for output
//     template <typename T>
//     inline ipl::string repr(const CIPtrArray<T> &a)
//     {
//         ipl::ostringstream s;
//         s << "[";
//         for(unsigned i=0; i<a.size(); i++) {
//             if(i) s << ", ";
//             s << repr(*a[i]);
//         }
//         s << "]";
//         return s.str();
//     }
// 
//     //! \brief Convenience for output
//     template <typename T>
//     inline ipl::string repr(const CIPtr<T> &p)
//     {
//         ipl::ostringstream o;
//         if(p.retrieve()==NULL)
//             o << "NULL";
//         else
//             o << repr(*p.retrieve());
//         return o.str();
//     }

//    class PartitionHandle;
//    //! \brief Convenience for output
//    ipl::string repr(const PartitionHandle &h);

/*****************************************************************************/

}  // end of namespace persistence

/*****************************************************************************/
#endif
