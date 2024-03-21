/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NETWORKREJECTINFORMATION_HXX
#define ASI_CONNECTIVITY_AL_NETWORKREJECTINFORMATION_HXX

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
    \brief struct al::NetworkRejectInformation.
    */
    struct PROXY_EXPORT NetworkRejectInformation
    {
        int32_t rejectCause; // optional=False
        CIPtr< CIString > plmn; // optional=True
        asi::connectivity::al::ServiceDomain domain; // optional=False
        asi::connectivity::al::NetworkType rat; // optional=False
        private:
            NetworkRejectInformation()
            :
            rejectCause(),
            plmn(),
            domain(),
            rat()
            { }
            friend class NetworkRejectInformationFactory;
            friend class CIFactory<NetworkRejectInformation>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::NetworkRejectInformation> >;
            friend class ipl::vector<NetworkRejectInformation>;
            friend class ipl::allocator<NetworkRejectInformation>;
#endif
    };

    typedef CIPtrArray<NetworkRejectInformation> CINetworkRejectInformationArray;

    /** \brief factory for al::NetworkRejectInformation. */
    class PROXY_EXPORT NetworkRejectInformationFactory  : CIFactory<NetworkRejectInformation> {
    public:
        static inline CIPtr<NetworkRejectInformation> createNetworkRejectInformation() {
            return CIFactory<NetworkRejectInformation>::createObject();
        }
        static inline void createNetworkRejectInformation(CIPtr<NetworkRejectInformation> & s) {
            CIFactory<NetworkRejectInformation>::createObject(s);
        }
        static inline CIPtr<CINetworkRejectInformationArray> createNetworkRejectInformationArray(size_t size) {
            return CIFactory<NetworkRejectInformation>::createArray(size);
        }
        static inline void createNetworkRejectInformationArray(CIPtr<CINetworkRejectInformationArray>& a, size_t size) {
            CIFactory<NetworkRejectInformation>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_NETWORKREJECTINFORMATION_HXX
