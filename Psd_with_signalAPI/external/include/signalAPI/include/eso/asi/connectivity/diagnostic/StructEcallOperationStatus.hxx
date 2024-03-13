/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_ECALLOPERATIONSTATUS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_ECALLOPERATIONSTATUS_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief struct diagnostic::EcallOperationStatus.
    */
    struct PROXY_EXPORT EcallOperationStatus
    {
        asi::connectivity::diagnostic::EcallDatasetAvailabilityState dsAvailStateLegal; // optional=False
        asi::connectivity::diagnostic::EcallDatasetAvailabilityState dsAvailStatePrivate; // optional=False
        asi::connectivity::diagnostic::EcallDatasetConfigState dsConfigStateLegal; // optional=False
        asi::connectivity::diagnostic::EcallDatasetConfigState dsConfigStatePrivate; // optional=False
        asi::connectivity::diagnostic::EcallFunctionState functionStateLegal; // optional=False
        asi::connectivity::diagnostic::EcallFunctionState functionStatePrivate; // optional=False
        asi::connectivity::diagnostic::EcallLicenseState licenseStateLegal; // optional=False
        asi::connectivity::diagnostic::EcallLicenseState licenseStatePrivate; // optional=False
        asi::connectivity::diagnostic::EcallServiceDisabledReason serviceDisablReasonLegal; // optional=False
        asi::connectivity::diagnostic::EcallServiceDisabledReason serviceDisablReasonPrivate; // optional=False
        asi::connectivity::diagnostic::EcallServiceState serviceStateLegal; // optional=False
        asi::connectivity::diagnostic::EcallServiceState serviceStatePrivate; // optional=False
        private:
            EcallOperationStatus()
            :
            dsAvailStateLegal(),
            dsAvailStatePrivate(),
            dsConfigStateLegal(),
            dsConfigStatePrivate(),
            functionStateLegal(),
            functionStatePrivate(),
            licenseStateLegal(),
            licenseStatePrivate(),
            serviceDisablReasonLegal(),
            serviceDisablReasonPrivate(),
            serviceStateLegal(),
            serviceStatePrivate()
            { }
            friend class EcallOperationStatusFactory;
            friend class CIFactory<EcallOperationStatus>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::EcallOperationStatus> >;
            friend class ipl::vector<EcallOperationStatus>;
            friend class ipl::allocator<EcallOperationStatus>;
#endif
    };

    typedef CIPtrArray<EcallOperationStatus> CIEcallOperationStatusArray;

    /** \brief factory for diagnostic::EcallOperationStatus. */
    class PROXY_EXPORT EcallOperationStatusFactory  : CIFactory<EcallOperationStatus> {
    public:
        static inline CIPtr<EcallOperationStatus> createEcallOperationStatus() {
            return CIFactory<EcallOperationStatus>::createObject();
        }
        static inline void createEcallOperationStatus(CIPtr<EcallOperationStatus> & s) {
            CIFactory<EcallOperationStatus>::createObject(s);
        }
        static inline CIPtr<CIEcallOperationStatusArray> createEcallOperationStatusArray(size_t size) {
            return CIFactory<EcallOperationStatus>::createArray(size);
        }
        static inline void createEcallOperationStatusArray(CIPtr<CIEcallOperationStatusArray>& a, size_t size) {
            CIFactory<EcallOperationStatus>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_ECALLOPERATIONSTATUS_HXX
