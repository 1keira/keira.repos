/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_SIMDATAINFO_HXX
#define ASI_CONNECTIVITY_AL_SIMDATAINFO_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/al/Definitions.hxx>
#include <asi/connectivity/al/Definitions.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief struct al::SimDataInfo.
    */
    struct PROXY_EXPORT SimDataInfo
    {
        asi::connectivity::al::SimState simState; // optional=False
        asi::connectivity::al::SimType sim_type; // optional=False
        CIPtr< CIString > iccid; // optional=True
        CIPtr< CIString > euiccid; // optional=True
        CIPtr< CIString > imsi; // optional=True
        CIPtr< CIString > serviceProviderName; // optional=True
        CIPtr< CIString > msisdn; // optional=True
        bool serviceProviderNameRetrieved; // optional=False
        private:
            SimDataInfo()
            :
            simState(),
            sim_type(),
            iccid(),
            euiccid(),
            imsi(),
            serviceProviderName(),
            msisdn(),
            serviceProviderNameRetrieved()
            { }
            friend class SimDataInfoFactory;
            friend class CIFactory<SimDataInfo>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::SimDataInfo> >;
            friend class ipl::vector<SimDataInfo>;
            friend class ipl::allocator<SimDataInfo>;
#endif
    };

    typedef CIPtrArray<SimDataInfo> CISimDataInfoArray;

    /** \brief factory for al::SimDataInfo. */
    class PROXY_EXPORT SimDataInfoFactory  : CIFactory<SimDataInfo> {
    public:
        static inline CIPtr<SimDataInfo> createSimDataInfo() {
            return CIFactory<SimDataInfo>::createObject();
        }
        static inline void createSimDataInfo(CIPtr<SimDataInfo> & s) {
            CIFactory<SimDataInfo>::createObject(s);
        }
        static inline CIPtr<CISimDataInfoArray> createSimDataInfoArray(size_t size) {
            return CIFactory<SimDataInfo>::createArray(size);
        }
        static inline void createSimDataInfoArray(CIPtr<CISimDataInfoArray>& a, size_t size) {
            CIFactory<SimDataInfo>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_SIMDATAINFO_HXX
