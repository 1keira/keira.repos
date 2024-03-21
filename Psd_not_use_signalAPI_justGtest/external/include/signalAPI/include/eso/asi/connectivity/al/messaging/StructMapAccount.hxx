/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_MAPACCOUNT_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_MAPACCOUNT_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace al
{
namespace messaging
{

    /**
        *
    * Describes a map account.
    
    */
    struct PROXY_EXPORT MapAccount
    {
        /**
            * Device identifier.
        */
        uint32_t deviceId; // optional=False
        /**
            * Account identifier.
        */
        int32_t accountId; // optional=False
        /**
            *
       * Describes the connect state of the account.
       * (true: connected - false: disconnected)
        */
        bool connected; // optional=False
        /**
            * Bitmask of supported features. (ACCOUNT_FEATURE_EMAIL, ACCOUNT_FEATURE_SMS_GSM, ...)
        */
        uint8_t supportedMessageTypes; // optional=False
        uint32_t mapSupportedFeatures; // optional=False
        /**
            * Account name.
        */
        CIPtr< CIString > title; // optional=True
        private:
            MapAccount()
            :
            deviceId(),
            accountId(),
            connected(),
            supportedMessageTypes(),
            mapSupportedFeatures(),
            title()
            { }
            friend class MapAccountFactory;
            friend class CIFactory<MapAccount>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::messaging::MapAccount> >;
            friend class ipl::vector<MapAccount>;
            friend class ipl::allocator<MapAccount>;
#endif
    };

    typedef CIPtrArray<MapAccount> CIMapAccountArray;

    /** \brief factory for messaging::MapAccount. */
    class PROXY_EXPORT MapAccountFactory  : CIFactory<MapAccount> {
    public:
        static inline CIPtr<MapAccount> createMapAccount() {
            return CIFactory<MapAccount>::createObject();
        }
        static inline void createMapAccount(CIPtr<MapAccount> & s) {
            CIFactory<MapAccount>::createObject(s);
        }
        static inline CIPtr<CIMapAccountArray> createMapAccountArray(size_t size) {
            return CIFactory<MapAccount>::createArray(size);
        }
        static inline void createMapAccountArray(CIPtr<CIMapAccountArray>& a, size_t size) {
            CIFactory<MapAccount>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al
}//namespace messaging


#endif// ASI_CONNECTIVITY_AL_MESSAGING_MAPACCOUNT_HXX
