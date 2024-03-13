/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef COMM_BROKER_INSTANCEID_HXX
#define COMM_BROKER_INSTANCEID_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <comm/broker/StructUUID844412Blob.hxx>

#undef unix

namespace comm
{
namespace broker
{

    /**
         
    \brief Instance id with interface identity key.
    
    */
    struct PROXY_EXPORT InstanceID
    {
        CIPtr< comm::broker::UUID844412Blob > id; // optional=True
        uint32_t handle; // optional=False
        CIPtr< comm::broker::UUID844412Blob > key; // optional=True
        private:
            InstanceID()
            :
            id(),
            handle(),
            key()
            { }
            friend class InstanceIDFactory;
            friend class CIFactory<InstanceID>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<comm::broker::InstanceID> >;
            friend class ipl::vector<InstanceID>;
            friend class ipl::allocator<InstanceID>;
#endif
    };

    typedef CIPtrArray<InstanceID> CIInstanceIDArray;

    /** \brief factory for broker::InstanceID. */
    class PROXY_EXPORT InstanceIDFactory  : CIFactory<InstanceID> {
    public:
        static inline CIPtr<InstanceID> createInstanceID() {
            return CIFactory<InstanceID>::createObject();
        }
        static inline void createInstanceID(CIPtr<InstanceID> & s) {
            CIFactory<InstanceID>::createObject(s);
        }
        static inline CIPtr<CIInstanceIDArray> createInstanceIDArray(size_t size) {
            return CIFactory<InstanceID>::createArray(size);
        }
        static inline void createInstanceIDArray(CIPtr<CIInstanceIDArray>& a, size_t size) {
            CIFactory<InstanceID>::createArray(a, size);
        }
    };
}//namespace comm
}//namespace broker


#endif// COMM_BROKER_INSTANCEID_HXX
