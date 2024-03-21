/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_TEMPERATUREINFO_HXX
#define ASI_CONNECTIVITY_AL_TEMPERATUREINFO_HXX

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
         Temperatures in 1/100 °C (e.g. 3753 means 37,53°C) 
    */
    struct PROXY_EXPORT TemperatureInfo
    {
        asi::connectivity::al::NadTempThresholdLevel level; // optional=False
        int32_t temperature1; // optional=False
        int32_t temperature2; // optional=False
        private:
            TemperatureInfo()
            :
            level(),
            temperature1(),
            temperature2()
            { }
            friend class TemperatureInfoFactory;
            friend class CIFactory<TemperatureInfo>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::TemperatureInfo> >;
            friend class ipl::vector<TemperatureInfo>;
            friend class ipl::allocator<TemperatureInfo>;
#endif
    };

    typedef CIPtrArray<TemperatureInfo> CITemperatureInfoArray;

    /** \brief factory for al::TemperatureInfo. */
    class PROXY_EXPORT TemperatureInfoFactory  : CIFactory<TemperatureInfo> {
    public:
        static inline CIPtr<TemperatureInfo> createTemperatureInfo() {
            return CIFactory<TemperatureInfo>::createObject();
        }
        static inline void createTemperatureInfo(CIPtr<TemperatureInfo> & s) {
            CIFactory<TemperatureInfo>::createObject(s);
        }
        static inline CIPtr<CITemperatureInfoArray> createTemperatureInfoArray(size_t size) {
            return CIFactory<TemperatureInfo>::createArray(size);
        }
        static inline void createTemperatureInfoArray(CIPtr<CITemperatureInfoArray>& a, size_t size) {
            CIFactory<TemperatureInfo>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_TEMPERATUREINFO_HXX
