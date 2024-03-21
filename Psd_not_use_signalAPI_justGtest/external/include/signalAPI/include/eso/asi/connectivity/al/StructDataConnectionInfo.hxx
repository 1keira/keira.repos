/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_DATACONNECTIONINFO_HXX
#define ASI_CONNECTIVITY_AL_DATACONNECTIONINFO_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/al/Definitions.hxx>
#include <asi/connectivity/al/StructIpInfo.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief struct al::DataConnectionInfo.
    */
    struct PROXY_EXPORT DataConnectionInfo
    {
        int32_t dataConnectionId; // optional=False
        asi::connectivity::al::DataConnectionState state; // optional=False
        CIPtr< CIString > net_interface; // optional=True
        CIPtr< CIString > apn; // optional=True
        CIPtr< asi::connectivity::al::IpInfo > ipv4Info; // optional=True
        CIPtr< asi::connectivity::al::IpInfo > ipv6Info; // optional=True
        private:
            DataConnectionInfo()
            :
            dataConnectionId(),
            state(),
            net_interface(),
            apn(),
            ipv4Info(),
            ipv6Info()
            { }
            friend class DataConnectionInfoFactory;
            friend class CIFactory<DataConnectionInfo>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::DataConnectionInfo> >;
            friend class ipl::vector<DataConnectionInfo>;
            friend class ipl::allocator<DataConnectionInfo>;
#endif
    };

    typedef CIPtrArray<DataConnectionInfo> CIDataConnectionInfoArray;

    /** \brief factory for al::DataConnectionInfo. */
    class PROXY_EXPORT DataConnectionInfoFactory  : CIFactory<DataConnectionInfo> {
    public:
        static inline CIPtr<DataConnectionInfo> createDataConnectionInfo() {
            return CIFactory<DataConnectionInfo>::createObject();
        }
        static inline void createDataConnectionInfo(CIPtr<DataConnectionInfo> & s) {
            CIFactory<DataConnectionInfo>::createObject(s);
        }
        static inline CIPtr<CIDataConnectionInfoArray> createDataConnectionInfoArray(size_t size) {
            return CIFactory<DataConnectionInfo>::createArray(size);
        }
        static inline void createDataConnectionInfoArray(CIPtr<CIDataConnectionInfoArray>& a, size_t size) {
            CIFactory<DataConnectionInfo>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_DATACONNECTIONINFO_HXX
