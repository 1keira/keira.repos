/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_ANTENNAINFO_HXX
#define ASI_CONNECTIVITY_AL_ANTENNAINFO_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/al/Definitions.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief struct al::AntennaInfo.
    */
    struct PROXY_EXPORT AntennaInfo
    {
        asi::connectivity::al::AntennaState state; // optional=False
        int32_t channel; // optional=False
        private:
            AntennaInfo()
            :
            state(),
            channel()
            { }
            friend class AntennaInfoFactory;
            friend class CIFactory<AntennaInfo>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::AntennaInfo> >;
            friend class ipl::vector<AntennaInfo>;
            friend class ipl::allocator<AntennaInfo>;
#endif
    };

    typedef CIPtrArray<AntennaInfo> CIAntennaInfoArray;

    /** \brief factory for al::AntennaInfo. */
    class PROXY_EXPORT AntennaInfoFactory  : CIFactory<AntennaInfo> {
    public:
        static inline CIPtr<AntennaInfo> createAntennaInfo() {
            return CIFactory<AntennaInfo>::createObject();
        }
        static inline void createAntennaInfo(CIPtr<AntennaInfo> & s) {
            CIFactory<AntennaInfo>::createObject(s);
        }
        static inline CIPtr<CIAntennaInfoArray> createAntennaInfoArray(size_t size) {
            return CIFactory<AntennaInfo>::createArray(size);
        }
        static inline void createAntennaInfoArray(CIPtr<CIAntennaInfoArray>& a, size_t size) {
            CIFactory<AntennaInfo>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_ANTENNAINFO_HXX
