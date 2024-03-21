/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NETWORK_HXX
#define ASI_CONNECTIVITY_AL_NETWORK_HXX

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
    \brief struct al::Network.
    */
    struct PROXY_EXPORT Network
    {
        CIPtr< CIString > operator_long; // optional=True
        CIPtr< CIString > operator_short; // optional=True
        CIPtr< CIString > operator_numeric; // optional=True
        asi::connectivity::al::NetworkAvailibility availibility; // optional=False
        asi::connectivity::al::NetworkType accessTech; // optional=False
        private:
            Network()
            :
            operator_long(),
            operator_short(),
            operator_numeric(),
            availibility(),
            accessTech()
            { }
            friend class NetworkFactory;
            friend class CIFactory<Network>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::Network> >;
            friend class ipl::vector<Network>;
            friend class ipl::allocator<Network>;
#endif
    };

    typedef CIPtrArray<Network> CINetworkArray;

    /** \brief factory for al::Network. */
    class PROXY_EXPORT NetworkFactory  : CIFactory<Network> {
    public:
        static inline CIPtr<Network> createNetwork() {
            return CIFactory<Network>::createObject();
        }
        static inline void createNetwork(CIPtr<Network> & s) {
            CIFactory<Network>::createObject(s);
        }
        static inline CIPtr<CINetworkArray> createNetworkArray(size_t size) {
            return CIFactory<Network>::createArray(size);
        }
        static inline void createNetworkArray(CIPtr<CINetworkArray>& a, size_t size) {
            CIFactory<Network>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_NETWORK_HXX
