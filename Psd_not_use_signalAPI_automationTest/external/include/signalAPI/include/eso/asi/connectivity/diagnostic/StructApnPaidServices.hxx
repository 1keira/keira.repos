/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_APNPAIDSERVICES_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_APNPAIDSERVICES_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/diagnostic/StructApnConfig.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief struct diagnostic::ApnPaidServices.
    */
    struct PROXY_EXPORT ApnPaidServices
    {
        CIPtr< asi::connectivity::diagnostic::ApnConfig > customerPaid; // optional=True
        CIPtr< asi::connectivity::diagnostic::ApnConfig > vwPaid; // optional=True
        private:
            ApnPaidServices()
            :
            customerPaid(),
            vwPaid()
            { }
            friend class ApnPaidServicesFactory;
            friend class CIFactory<ApnPaidServices>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::ApnPaidServices> >;
            friend class ipl::vector<ApnPaidServices>;
            friend class ipl::allocator<ApnPaidServices>;
#endif
    };

    typedef CIPtrArray<ApnPaidServices> CIApnPaidServicesArray;

    /** \brief factory for diagnostic::ApnPaidServices. */
    class PROXY_EXPORT ApnPaidServicesFactory  : CIFactory<ApnPaidServices> {
    public:
        static inline CIPtr<ApnPaidServices> createApnPaidServices() {
            return CIFactory<ApnPaidServices>::createObject();
        }
        static inline void createApnPaidServices(CIPtr<ApnPaidServices> & s) {
            CIFactory<ApnPaidServices>::createObject(s);
        }
        static inline CIPtr<CIApnPaidServicesArray> createApnPaidServicesArray(size_t size) {
            return CIFactory<ApnPaidServices>::createArray(size);
        }
        static inline void createApnPaidServicesArray(CIPtr<CIApnPaidServicesArray>& a, size_t size) {
            CIFactory<ApnPaidServices>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_APNPAIDSERVICES_HXX
