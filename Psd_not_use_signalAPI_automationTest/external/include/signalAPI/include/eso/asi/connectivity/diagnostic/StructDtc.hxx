/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DTC_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DTC_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief struct diagnostic::Dtc.
    */
    struct PROXY_EXPORT Dtc
    {
        uint32_t code; // optional=False
        asi::connectivity::diagnostic::DtcErrorCondition errorCondition; // optional=False
        private:
            Dtc()
            :
            code(),
            errorCondition()
            { }
            friend class DtcFactory;
            friend class CIFactory<Dtc>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::Dtc> >;
            friend class ipl::vector<Dtc>;
            friend class ipl::allocator<Dtc>;
#endif
    };

    typedef CIPtrArray<Dtc> CIDtcArray;

    /** \brief factory for diagnostic::Dtc. */
    class PROXY_EXPORT DtcFactory  : CIFactory<Dtc> {
    public:
        static inline CIPtr<Dtc> createDtc() {
            return CIFactory<Dtc>::createObject();
        }
        static inline void createDtc(CIPtr<Dtc> & s) {
            CIFactory<Dtc>::createObject(s);
        }
        static inline CIPtr<CIDtcArray> createDtcArray(size_t size) {
            return CIFactory<Dtc>::createArray(size);
        }
        static inline void createDtcArray(CIPtr<CIDtcArray>& a, size_t size) {
            CIFactory<Dtc>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DTC_HXX
