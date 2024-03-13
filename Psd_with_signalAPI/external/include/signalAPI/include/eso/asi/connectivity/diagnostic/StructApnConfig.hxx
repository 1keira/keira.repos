/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_APNCONFIG_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_APNCONFIG_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief struct diagnostic::ApnConfig.
    */
    struct PROXY_EXPORT ApnConfig
    {
        CIPtr< CIString > password; // optional=True
        CIPtr< CIString > providerName; // optional=True
        CIPtr< CIString > username; // optional=True
        private:
            ApnConfig()
            :
            password(),
            providerName(),
            username()
            { }
            friend class ApnConfigFactory;
            friend class CIFactory<ApnConfig>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::ApnConfig> >;
            friend class ipl::vector<ApnConfig>;
            friend class ipl::allocator<ApnConfig>;
#endif
    };

    typedef CIPtrArray<ApnConfig> CIApnConfigArray;

    /** \brief factory for diagnostic::ApnConfig. */
    class PROXY_EXPORT ApnConfigFactory  : CIFactory<ApnConfig> {
    public:
        static inline CIPtr<ApnConfig> createApnConfig() {
            return CIFactory<ApnConfig>::createObject();
        }
        static inline void createApnConfig(CIPtr<ApnConfig> & s) {
            CIFactory<ApnConfig>::createObject(s);
        }
        static inline CIPtr<CIApnConfigArray> createApnConfigArray(size_t size) {
            return CIFactory<ApnConfig>::createArray(size);
        }
        static inline void createApnConfigArray(CIPtr<CIApnConfigArray>& a, size_t size) {
            CIFactory<ApnConfig>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_APNCONFIG_HXX
