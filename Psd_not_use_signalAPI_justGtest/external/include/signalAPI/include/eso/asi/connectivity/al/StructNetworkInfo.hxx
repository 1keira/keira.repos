/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NETWORKINFO_HXX
#define ASI_CONNECTIVITY_AL_NETWORKINFO_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/al/Definitions.hxx>
#include <asi/connectivity/al/Definitions.hxx>
#include <asi/connectivity/al/Definitions.hxx>
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
    \brief struct al::NetworkInfo.
    */
    struct PROXY_EXPORT NetworkInfo
    {
        asi::connectivity::al::RegState regState; // optional=False
        asi::connectivity::al::ServiceDomain domain; // optional=False
        asi::connectivity::al::VolteSupport isVoLTESupported; // optional=False
        asi::connectivity::al::CSRatsSupport is2G3GAvailable; // optional=False
        asi::connectivity::al::NetworkType type; // optional=False
        int32_t signalStrength; // optional=False
        int16_t rsrp; // optional=False
        int8_t rsrq; // optional=False
        int16_t sinr; // optional=False
        int8_t rssi; // optional=False
        int16_t ecio; // optional=False
        CIPtr< CIString > operatorName; // optional=True
        CIPtr< CIString > plmn; // optional=True
        CIPtr< CIString > lac; // optional=True
        CIPtr< CIString > cellId; // optional=True
        private:
            NetworkInfo()
            :
            regState(),
            domain(),
            isVoLTESupported(),
            is2G3GAvailable(),
            type(),
            signalStrength(),
            rsrp(),
            rsrq(),
            sinr(),
            rssi(),
            ecio(),
            operatorName(),
            plmn(),
            lac(),
            cellId()
            { }
            friend class NetworkInfoFactory;
            friend class CIFactory<NetworkInfo>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::NetworkInfo> >;
            friend class ipl::vector<NetworkInfo>;
            friend class ipl::allocator<NetworkInfo>;
#endif
    };

    typedef CIPtrArray<NetworkInfo> CINetworkInfoArray;

    /** \brief factory for al::NetworkInfo. */
    class PROXY_EXPORT NetworkInfoFactory  : CIFactory<NetworkInfo> {
    public:
        static inline CIPtr<NetworkInfo> createNetworkInfo() {
            return CIFactory<NetworkInfo>::createObject();
        }
        static inline void createNetworkInfo(CIPtr<NetworkInfo> & s) {
            CIFactory<NetworkInfo>::createObject(s);
        }
        static inline CIPtr<CINetworkInfoArray> createNetworkInfoArray(size_t size) {
            return CIFactory<NetworkInfo>::createArray(size);
        }
        static inline void createNetworkInfoArray(CIPtr<CINetworkInfoArray>& a, size_t size) {
            CIFactory<NetworkInfo>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_NETWORKINFO_HXX
