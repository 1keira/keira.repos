/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_BTDEVICELESECURITYKEYS_HXX
#define ASI_CONNECTIVITY_AL_BTDEVICELESECURITYKEYS_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief struct al::BtDeviceLeSecurityKeys.
    */
    struct PROXY_EXPORT BtDeviceLeSecurityKeys
    {
        uint8_t ltkSize; // optional=False
        /**
            LTK key size (7-16 bytes)
            ltkValue Array Size [min,max]: [16,16]
        */
        CIPtr< CIUInt8Array > ltkValue; // optional=True
        /**
            LTK value (up to 128-bit) in Little Endian format
        */
        uint16_t ltkEdiv; // optional=False
        /**
            Encryption Diversifier identifying LTK (16-bit)
            ltkRand Array Size [min,max]: [8,8]
        */
        CIPtr< CIUInt8Array > ltkRand; // optional=True
        /**
            Random number identifying LTK (64-bit) in Little Endian format
            csrk Array Size [min,max]: [16,16]
        */
        CIPtr< CIUInt8Array > csrk; // optional=True
        /**
            CSRK value (128-bit) in Little Endian format
        */
        uint32_t signedCounter; // optional=False
        /**
            Last received signed counter value
        */
        bool signedCounterValid; // optional=False
        /**
            Value in signedCounter is valid
            irk Array Size [min,max]: [16,16]
        */
        CIPtr< CIUInt8Array > irk; // optional=True
        /**
            IRK value (128-bit) in Little Endian format
        */
        uint64_t devAddr; // optional=False
        /**
            Describes the LE security keys (LTK, CSRK, and IRK) stored in this record
        */
        uint8_t storedKeys; // optional=False
        private:
            BtDeviceLeSecurityKeys()
            :
            ltkSize(),
            ltkValue(),
            ltkEdiv(),
            ltkRand(),
            csrk(),
            signedCounter(),
            signedCounterValid(),
            irk(),
            devAddr(),
            storedKeys()
            { }
            friend class BtDeviceLeSecurityKeysFactory;
            friend class CIFactory<BtDeviceLeSecurityKeys>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::BtDeviceLeSecurityKeys> >;
            friend class ipl::vector<BtDeviceLeSecurityKeys>;
            friend class ipl::allocator<BtDeviceLeSecurityKeys>;
#endif
    };

    typedef CIPtrArray<BtDeviceLeSecurityKeys> CIBtDeviceLeSecurityKeysArray;

    /** \brief factory for al::BtDeviceLeSecurityKeys. */
    class PROXY_EXPORT BtDeviceLeSecurityKeysFactory  : CIFactory<BtDeviceLeSecurityKeys> {
    public:
        static inline CIPtr<BtDeviceLeSecurityKeys> createBtDeviceLeSecurityKeys() {
            return CIFactory<BtDeviceLeSecurityKeys>::createObject();
        }
        static inline void createBtDeviceLeSecurityKeys(CIPtr<BtDeviceLeSecurityKeys> & s) {
            CIFactory<BtDeviceLeSecurityKeys>::createObject(s);
        }
        static inline CIPtr<CIBtDeviceLeSecurityKeysArray> createBtDeviceLeSecurityKeysArray(size_t size) {
            return CIFactory<BtDeviceLeSecurityKeys>::createArray(size);
        }
        static inline void createBtDeviceLeSecurityKeysArray(CIPtr<CIBtDeviceLeSecurityKeysArray>& a, size_t size) {
            CIFactory<BtDeviceLeSecurityKeys>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_BTDEVICELESECURITYKEYS_HXX
