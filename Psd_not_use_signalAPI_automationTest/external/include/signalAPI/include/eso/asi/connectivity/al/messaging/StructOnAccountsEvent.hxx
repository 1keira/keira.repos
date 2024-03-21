/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_ONACCOUNTSEVENT_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_ONACCOUNTSEVENT_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/al/messaging/StructMapAccount.hxx>

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
    * Describes the arguments of onAccounts.
    
    */
    struct PROXY_EXPORT OnAccountsEvent
    {
        /**
            * Accounts.
            accounts Array Size: unlimited
        */
        CIPtr< CIPtrArray< asi::connectivity::al::messaging::MapAccount > > accounts; // optional=True
        private:
            OnAccountsEvent()
            :
            accounts()
            { }
            friend class OnAccountsEventFactory;
            friend class CIFactory<OnAccountsEvent>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::messaging::OnAccountsEvent> >;
            friend class ipl::vector<OnAccountsEvent>;
            friend class ipl::allocator<OnAccountsEvent>;
#endif
    };

    typedef CIPtrArray<OnAccountsEvent> CIOnAccountsEventArray;

    /** \brief factory for messaging::OnAccountsEvent. */
    class PROXY_EXPORT OnAccountsEventFactory  : CIFactory<OnAccountsEvent> {
    public:
        static inline CIPtr<OnAccountsEvent> createOnAccountsEvent() {
            return CIFactory<OnAccountsEvent>::createObject();
        }
        static inline void createOnAccountsEvent(CIPtr<OnAccountsEvent> & s) {
            CIFactory<OnAccountsEvent>::createObject(s);
        }
        static inline CIPtr<CIOnAccountsEventArray> createOnAccountsEventArray(size_t size) {
            return CIFactory<OnAccountsEvent>::createArray(size);
        }
        static inline void createOnAccountsEventArray(CIPtr<CIOnAccountsEventArray>& a, size_t size) {
            CIFactory<OnAccountsEvent>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al
}//namespace messaging


#endif// ASI_CONNECTIVITY_AL_MESSAGING_ONACCOUNTSEVENT_HXX
