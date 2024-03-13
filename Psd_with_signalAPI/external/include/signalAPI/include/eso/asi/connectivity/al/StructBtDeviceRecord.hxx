/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_BTDEVICERECORD_HXX
#define ASI_CONNECTIVITY_AL_BTDEVICERECORD_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/al/StructBtDeviceLeSecurityKeys.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief struct al::BtDeviceRecord.
    */
    struct PROXY_EXPORT BtDeviceRecord
    {
        int64_t address; // optional=False
        uint8_t linkKeyType; // optional=False
        /**
            linkKey Array Size: unlimited
        */
        CIPtr< CIUInt8Array > linkKey; // optional=True
        uint8_t pinLen; // optional=False
        uint8_t psRepMode; // optional=False
        uint8_t leLinkKeyType; // optional=False
        CIPtr< asi::connectivity::al::BtDeviceLeSecurityKeys > leLocalKeys; // optional=True
        CIPtr< asi::connectivity::al::BtDeviceLeSecurityKeys > leRemoteKeys; // optional=True
        private:
            BtDeviceRecord()
            :
            address(),
            linkKeyType(),
            linkKey(),
            pinLen(),
            psRepMode(),
            leLinkKeyType(),
            leLocalKeys(),
            leRemoteKeys()
            { }
            friend class BtDeviceRecordFactory;
            friend class CIFactory<BtDeviceRecord>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::BtDeviceRecord> >;
            friend class ipl::vector<BtDeviceRecord>;
            friend class ipl::allocator<BtDeviceRecord>;
#endif
    };

    typedef CIPtrArray<BtDeviceRecord> CIBtDeviceRecordArray;

    /** \brief factory for al::BtDeviceRecord. */
    class PROXY_EXPORT BtDeviceRecordFactory  : CIFactory<BtDeviceRecord> {
    public:
        static inline CIPtr<BtDeviceRecord> createBtDeviceRecord() {
            return CIFactory<BtDeviceRecord>::createObject();
        }
        static inline void createBtDeviceRecord(CIPtr<BtDeviceRecord> & s) {
            CIFactory<BtDeviceRecord>::createObject(s);
        }
        static inline CIPtr<CIBtDeviceRecordArray> createBtDeviceRecordArray(size_t size) {
            return CIFactory<BtDeviceRecord>::createArray(size);
        }
        static inline void createBtDeviceRecordArray(CIPtr<CIBtDeviceRecordArray>& a, size_t size) {
            CIFactory<BtDeviceRecord>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_BTDEVICERECORD_HXX
