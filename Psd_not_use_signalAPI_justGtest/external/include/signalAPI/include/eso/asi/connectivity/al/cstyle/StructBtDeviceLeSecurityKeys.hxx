/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_BTDEVICELESECURITYKEYS_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_BTDEVICELESECURITYKEYS_CSTYLE_HXX

#include <comm/commidltypes.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{
struct BtDeviceLeSecurityKeys;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::BtDeviceLeSecurityKeys& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::BtDeviceLeSecurityKeys &val);
}
}

namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{

    /**
    \brief struct al::BtDeviceLeSecurityKeys.
    */
    struct PROXY_EXPORT BtDeviceLeSecurityKeys
    {
        public:
            BtDeviceLeSecurityKeys()
            : m_ltkSize()
            , m_ltkEdiv()
            , m_signedCounter()
            , m_signedCounterValid()
            , m_devAddr()
            , m_storedKeys()
            , m_ltkValue(nullptr)
            , m_ltkRand(nullptr)
            , m_csrk(nullptr)
            , m_irk(nullptr)
            { }

            BtDeviceLeSecurityKeys (const BtDeviceLeSecurityKeys& other)
            : m_ltkSize()
            , m_ltkEdiv()
            , m_signedCounter()
            , m_signedCounterValid()
            , m_devAddr()
            , m_storedKeys()
            , m_ltkValue(nullptr)
            , m_ltkRand(nullptr)
            , m_csrk(nullptr)
            , m_irk(nullptr)
            {
              *this = other;
            }

            ~BtDeviceLeSecurityKeys () {
                if (m_ltkValue) {
                    delete m_ltkValue;
                }
                if (m_ltkRand) {
                    delete m_ltkRand;
                }
                if (m_csrk) {
                    delete m_csrk;
                }
                if (m_irk) {
                    delete m_irk;
                }
            }
            bool operator==(const BtDeviceLeSecurityKeys& rhs) const {
                bool equal = true;
                if (m_ltkSize != rhs.m_ltkSize)
                    equal = false;
                if (m_ltkValue == nullptr && rhs.m_ltkValue != nullptr)
                    equal = false;
                else if (m_ltkValue != nullptr && rhs.m_ltkValue == nullptr)
                    equal = false;
                else if ((m_ltkValue != nullptr) && (rhs.m_ltkValue != nullptr) && (*m_ltkValue != *rhs.m_ltkValue))
                    equal = false;
                if (m_ltkEdiv != rhs.m_ltkEdiv)
                    equal = false;
                if (m_ltkRand == nullptr && rhs.m_ltkRand != nullptr)
                    equal = false;
                else if (m_ltkRand != nullptr && rhs.m_ltkRand == nullptr)
                    equal = false;
                else if ((m_ltkRand != nullptr) && (rhs.m_ltkRand != nullptr) && (*m_ltkRand != *rhs.m_ltkRand))
                    equal = false;
                if (m_csrk == nullptr && rhs.m_csrk != nullptr)
                    equal = false;
                else if (m_csrk != nullptr && rhs.m_csrk == nullptr)
                    equal = false;
                else if ((m_csrk != nullptr) && (rhs.m_csrk != nullptr) && (*m_csrk != *rhs.m_csrk))
                    equal = false;
                if (m_signedCounter != rhs.m_signedCounter)
                    equal = false;
                if (m_signedCounterValid != rhs.m_signedCounterValid)
                    equal = false;
                if (m_irk == nullptr && rhs.m_irk != nullptr)
                    equal = false;
                else if (m_irk != nullptr && rhs.m_irk == nullptr)
                    equal = false;
                else if ((m_irk != nullptr) && (rhs.m_irk != nullptr) && (*m_irk != *rhs.m_irk))
                    equal = false;
                if (m_devAddr != rhs.m_devAddr)
                    equal = false;
                if (m_storedKeys != rhs.m_storedKeys)
                    equal = false;
                return equal;
            }
            bool operator!=(const BtDeviceLeSecurityKeys& rhs) const {
                return !operator==(rhs);
            }

            BtDeviceLeSecurityKeys& operator = (const BtDeviceLeSecurityKeys& src) {
                if (this == &src) return *this;
                m_ltkSize = src.m_ltkSize;
                if (m_ltkValue)
                    delete m_ltkValue;
                if (src.m_ltkValue) {
                    m_ltkValue = new (ipl::nothrow)ipl::vector<uint8_t>(*(src.m_ltkValue));
                } else {
                    m_ltkValue = nullptr;
                }
                m_ltkEdiv = src.m_ltkEdiv;
                if (m_ltkRand)
                    delete m_ltkRand;
                if (src.m_ltkRand) {
                    m_ltkRand = new (ipl::nothrow)ipl::vector<uint8_t>(*(src.m_ltkRand));
                } else {
                    m_ltkRand = nullptr;
                }
                if (m_csrk)
                    delete m_csrk;
                if (src.m_csrk) {
                    m_csrk = new (ipl::nothrow)ipl::vector<uint8_t>(*(src.m_csrk));
                } else {
                    m_csrk = nullptr;
                }
                m_signedCounter = src.m_signedCounter;
                m_signedCounterValid = src.m_signedCounterValid;
                if (m_irk)
                    delete m_irk;
                if (src.m_irk) {
                    m_irk = new (ipl::nothrow)ipl::vector<uint8_t>(*(src.m_irk));
                } else {
                    m_irk = nullptr;
                }
                m_devAddr = src.m_devAddr;
                m_storedKeys = src.m_storedKeys;
                return *this;
            }

                void setltkSize(const uint8_t _value) {
                    m_ltkSize = _value;
                }
                uint8_t getltkSize() const {
                    return m_ltkSize;
                }
                void setltkValue(const ipl::vector<uint8_t>* _value) {
                    if (m_ltkValue)
                        delete m_ltkValue;
                    if (_value) {
                        m_ltkValue = new (ipl::nothrow)ipl::vector<uint8_t>(*_value);
                    } else {
                        m_ltkValue = nullptr;
                    }
                }
                const ipl::vector<uint8_t>* getltkValue() const {
                    return m_ltkValue;
                }
                    bool ltkValueValid() const {
                        return m_ltkValue != nullptr;
                    }
                void setltkEdiv(const uint16_t _value) {
                    m_ltkEdiv = _value;
                }
                uint16_t getltkEdiv() const {
                    return m_ltkEdiv;
                }
                void setltkRand(const ipl::vector<uint8_t>* _value) {
                    if (m_ltkRand)
                        delete m_ltkRand;
                    if (_value) {
                        m_ltkRand = new (ipl::nothrow)ipl::vector<uint8_t>(*_value);
                    } else {
                        m_ltkRand = nullptr;
                    }
                }
                const ipl::vector<uint8_t>* getltkRand() const {
                    return m_ltkRand;
                }
                    bool ltkRandValid() const {
                        return m_ltkRand != nullptr;
                    }
                void setcsrk(const ipl::vector<uint8_t>* _value) {
                    if (m_csrk)
                        delete m_csrk;
                    if (_value) {
                        m_csrk = new (ipl::nothrow)ipl::vector<uint8_t>(*_value);
                    } else {
                        m_csrk = nullptr;
                    }
                }
                const ipl::vector<uint8_t>* getcsrk() const {
                    return m_csrk;
                }
                    bool csrkValid() const {
                        return m_csrk != nullptr;
                    }
                void setsignedCounter(const uint32_t _value) {
                    m_signedCounter = _value;
                }
                uint32_t getsignedCounter() const {
                    return m_signedCounter;
                }
                void setsignedCounterValid(const bool _value) {
                    m_signedCounterValid = _value;
                }
                bool getsignedCounterValid() const {
                    return m_signedCounterValid;
                }
                void setirk(const ipl::vector<uint8_t>* _value) {
                    if (m_irk)
                        delete m_irk;
                    if (_value) {
                        m_irk = new (ipl::nothrow)ipl::vector<uint8_t>(*_value);
                    } else {
                        m_irk = nullptr;
                    }
                }
                const ipl::vector<uint8_t>* getirk() const {
                    return m_irk;
                }
                    bool irkValid() const {
                        return m_irk != nullptr;
                    }
                void setdevAddr(const uint64_t _value) {
                    m_devAddr = _value;
                }
                uint64_t getdevAddr() const {
                    return m_devAddr;
                }
                void setstoredKeys(const uint8_t _value) {
                    m_storedKeys = _value;
                }
                uint8_t getstoredKeys() const {
                    return m_storedKeys;
                }


        uint8_t m_ltkSize;
        /**
            LTK value (up to 128-bit) in Little Endian format
        */
        /**
            LTK value (up to 128-bit) in Little Endian format
        */
        uint16_t m_ltkEdiv;
        /**
            CSRK value (128-bit) in Little Endian format
        */
        /**
            CSRK value (128-bit) in Little Endian format
        */
        uint32_t m_signedCounter;
        /**
            Last received signed counter value
        */
        /**
            Last received signed counter value
        */
        bool m_signedCounterValid;
        /**
            IRK value (128-bit) in Little Endian format
        */
        /**
            IRK value (128-bit) in Little Endian format
        */
        uint64_t m_devAddr;
        /**
            Describes the LE security keys (LTK, CSRK, and IRK) stored in this record
        */
        /**
            Describes the LE security keys (LTK, CSRK, and IRK) stored in this record
        */
        uint8_t m_storedKeys;
    private:
        /**
            LTK key size (7-16 bytes)
            ltkValue Array Size [min,max]: [16,16]
        */
        ipl::vector<uint8_t>* m_ltkValue;
        /**
            Encryption Diversifier identifying LTK (16-bit)
            ltkRand Array Size [min,max]: [8,8]
        */
        ipl::vector<uint8_t>* m_ltkRand;
        /**
            Random number identifying LTK (64-bit) in Little Endian format
            csrk Array Size [min,max]: [16,16]
        */
        ipl::vector<uint8_t>* m_csrk;
        /**
            Value in signedCounter is valid
            irk Array Size [min,max]: [16,16]
        */
        ipl::vector<uint8_t>* m_irk;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::BtDeviceLeSecurityKeys& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::BtDeviceLeSecurityKeys &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_BTDEVICELESECURITYKEYS_CSTYLE_HXX
