/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef COMM_BROKER_UUID844412BLOB_HXX
#define COMM_BROKER_UUID844412BLOB_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>

#undef unix

namespace comm
{
namespace broker
{

    /**
        
    \brief This is a UUID in 8-4-4-4-12 notation.

    When the bytes member is created, the uuid is read left to right, dashes between groups are omitted,
    each group is written most significant bytes first - all written with growing index into bytes.
    
    */
    struct PROXY_EXPORT UUID844412Blob
    {
        /**
            bytes Array Size [min,max]: [32,32]
        */
        CIPtr< CIUInt8Array > bytes; // optional=True
        private:
            UUID844412Blob()
            :
            bytes()
            { }
            friend class UUID844412BlobFactory;
            friend class CIFactory<UUID844412Blob>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<comm::broker::UUID844412Blob> >;
            friend class ipl::vector<UUID844412Blob>;
            friend class ipl::allocator<UUID844412Blob>;
#endif
    };

    typedef CIPtrArray<UUID844412Blob> CIUUID844412BlobArray;

    /** \brief factory for broker::UUID844412Blob. */
    class PROXY_EXPORT UUID844412BlobFactory  : CIFactory<UUID844412Blob> {
    public:
        static inline CIPtr<UUID844412Blob> createUUID844412Blob() {
            return CIFactory<UUID844412Blob>::createObject();
        }
        static inline void createUUID844412Blob(CIPtr<UUID844412Blob> & s) {
            CIFactory<UUID844412Blob>::createObject(s);
        }
        static inline CIPtr<CIUUID844412BlobArray> createUUID844412BlobArray(size_t size) {
            return CIFactory<UUID844412Blob>::createArray(size);
        }
        static inline void createUUID844412BlobArray(CIPtr<CIUUID844412BlobArray>& a, size_t size) {
            CIFactory<UUID844412Blob>::createArray(a, size);
        }
    };
}//namespace comm
}//namespace broker


#endif// COMM_BROKER_UUID844412BLOB_HXX
