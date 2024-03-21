/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_SIMDATACONFIG_HXX
#define ASI_CONNECTIVITY_AL_SIMDATACONFIG_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief struct al::SimDataConfig.
    */
    struct PROXY_EXPORT SimDataConfig
    {
        int32_t dataConnectionId; // optional=False
        CIPtr< CIString > apn; // optional=True
        CIPtr< CIString > login; // optional=True
        CIPtr< CIString > password; // optional=True
        private:
            SimDataConfig()
            :
            dataConnectionId(),
            apn(),
            login(),
            password()
            { }
            friend class SimDataConfigFactory;
            friend class CIFactory<SimDataConfig>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::SimDataConfig> >;
            friend class ipl::vector<SimDataConfig>;
            friend class ipl::allocator<SimDataConfig>;
#endif
    };

    typedef CIPtrArray<SimDataConfig> CISimDataConfigArray;

    /** \brief factory for al::SimDataConfig. */
    class PROXY_EXPORT SimDataConfigFactory  : CIFactory<SimDataConfig> {
    public:
        static inline CIPtr<SimDataConfig> createSimDataConfig() {
            return CIFactory<SimDataConfig>::createObject();
        }
        static inline void createSimDataConfig(CIPtr<SimDataConfig> & s) {
            CIFactory<SimDataConfig>::createObject(s);
        }
        static inline CIPtr<CISimDataConfigArray> createSimDataConfigArray(size_t size) {
            return CIFactory<SimDataConfig>::createArray(size);
        }
        static inline void createSimDataConfigArray(CIPtr<CISimDataConfigArray>& a, size_t size) {
            CIFactory<SimDataConfig>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_SIMDATACONFIG_HXX
