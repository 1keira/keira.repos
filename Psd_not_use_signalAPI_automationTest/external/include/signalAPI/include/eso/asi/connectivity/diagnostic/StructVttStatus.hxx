/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_VTTSTATUS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_VTTSTATUS_HXX

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
    \brief struct diagnostic::VttStatus.
    */
    struct PROXY_EXPORT VttStatus
    {
        bool isActivated; // optional=False
        bool isTransmissionRestricted; // optional=False
        asi::connectivity::diagnostic::VttNetworkStatus networkStatus; // optional=False
        private:
            VttStatus()
            :
            isActivated(),
            isTransmissionRestricted(),
            networkStatus()
            { }
            friend class VttStatusFactory;
            friend class CIFactory<VttStatus>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::VttStatus> >;
            friend class ipl::vector<VttStatus>;
            friend class ipl::allocator<VttStatus>;
#endif
    };

    typedef CIPtrArray<VttStatus> CIVttStatusArray;

    /** \brief factory for diagnostic::VttStatus. */
    class PROXY_EXPORT VttStatusFactory  : CIFactory<VttStatus> {
    public:
        static inline CIPtr<VttStatus> createVttStatus() {
            return CIFactory<VttStatus>::createObject();
        }
        static inline void createVttStatus(CIPtr<VttStatus> & s) {
            CIFactory<VttStatus>::createObject(s);
        }
        static inline CIPtr<CIVttStatusArray> createVttStatusArray(size_t size) {
            return CIFactory<VttStatus>::createArray(size);
        }
        static inline void createVttStatusArray(CIPtr<CIVttStatusArray>& a, size_t size) {
            CIFactory<VttStatus>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_VTTSTATUS_HXX
