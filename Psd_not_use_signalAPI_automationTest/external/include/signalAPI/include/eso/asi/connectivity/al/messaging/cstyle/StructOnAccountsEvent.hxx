/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_ONACCOUNTSEVENT_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_ONACCOUNTSEVENT_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/messaging/cstyle/StructMapAccount.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace al
{
namespace messaging
{
namespace  cstyle
{
struct OnAccountsEvent;
}
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::messaging::cstyle::OnAccountsEvent& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::messaging::cstyle::OnAccountsEvent &val);
}
}

namespace asi
{
namespace connectivity
{
namespace al
{
namespace messaging
{
namespace  cstyle
{

    /**
        *
    * Describes the arguments of onAccounts.
    
    */
    struct PROXY_EXPORT OnAccountsEvent
    {
        public:
            OnAccountsEvent()
            : m_accounts(nullptr)
            { }

            OnAccountsEvent (const OnAccountsEvent& other)
            : m_accounts(nullptr)
            {
              *this = other;
            }

            ~OnAccountsEvent () {
                if (m_accounts) {
                    delete m_accounts;
                }
            }
            bool operator==(const OnAccountsEvent& rhs) const {
                bool equal = true;
                if (m_accounts == nullptr && rhs.m_accounts != nullptr)
                    equal = false;
                else if (m_accounts != nullptr && rhs.m_accounts == nullptr)
                    equal = false;
                else if ((m_accounts != nullptr) && (rhs.m_accounts != nullptr) && (*m_accounts != *rhs.m_accounts))
                    equal = false;
                return equal;
            }
            bool operator!=(const OnAccountsEvent& rhs) const {
                return !operator==(rhs);
            }

            OnAccountsEvent& operator = (const OnAccountsEvent& src) {
                if (this == &src) return *this;
                if (m_accounts)
                    delete m_accounts;
                if (src.m_accounts) {
                    m_accounts = new (ipl::nothrow)ipl::vector< asi::connectivity::al::messaging::cstyle::MapAccount >(*(src.m_accounts));
                } else {
                    m_accounts = nullptr;
                }
                return *this;
            }

                void setaccounts(const ipl::vector< asi::connectivity::al::messaging::cstyle::MapAccount >* _value) {
                    if (m_accounts)
                        delete m_accounts;
                    if (_value) {
                        m_accounts = new (ipl::nothrow)ipl::vector< asi::connectivity::al::messaging::cstyle::MapAccount >(*_value);
                    } else {
                        m_accounts = nullptr;
                    }
                }
                const ipl::vector< asi::connectivity::al::messaging::cstyle::MapAccount >* getaccounts() const {
                    return m_accounts;
                }
                    bool accountsValid() const {
                        return m_accounts != nullptr;
                    }


    private:
        /**
            * Accounts.
            accounts Array Size: unlimited
        */
        ipl::vector< asi::connectivity::al::messaging::cstyle::MapAccount >* m_accounts;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::messaging::cstyle::OnAccountsEvent& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::messaging::cstyle::OnAccountsEvent &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al
}//namespace messaging

#endif// ASI_CONNECTIVITY_AL_MESSAGING_ONACCOUNTSEVENT_CSTYLE_HXX
