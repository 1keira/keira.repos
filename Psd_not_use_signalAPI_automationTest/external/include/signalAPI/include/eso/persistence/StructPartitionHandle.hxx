/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef PERSISTENCE_PARTITIONHANDLE_HXX
#define PERSISTENCE_PARTITIONHANDLE_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>

#undef unix

namespace persistence
{

    /**
        
        \brief Opaque handle for an open partition
    
    */
    struct PROXY_EXPORT PartitionHandle
    {
        uint32_t index; // optional=False
        private:
            PartitionHandle()
            :
            index()
            { }
            friend class PartitionHandleFactory;
            friend class CIFactory<PartitionHandle>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<persistence::PartitionHandle> >;
            friend class ipl::vector<PartitionHandle>;
            friend class ipl::allocator<PartitionHandle>;
#endif
    };

    typedef CIPtrArray<PartitionHandle> CIPartitionHandleArray;

    /** \brief factory for persistence::PartitionHandle. */
    class PROXY_EXPORT PartitionHandleFactory  : CIFactory<PartitionHandle> {
    public:
        static inline CIPtr<PartitionHandle> createPartitionHandle() {
            return CIFactory<PartitionHandle>::createObject();
        }
        static inline void createPartitionHandle(CIPtr<PartitionHandle> & s) {
            CIFactory<PartitionHandle>::createObject(s);
        }
        static inline CIPtr<CIPartitionHandleArray> createPartitionHandleArray(size_t size) {
            return CIFactory<PartitionHandle>::createArray(size);
        }
        static inline void createPartitionHandleArray(CIPtr<CIPartitionHandleArray>& a, size_t size) {
            CIFactory<PartitionHandle>::createArray(a, size);
        }
    };
}//namespace persistence


#endif// PERSISTENCE_PARTITIONHANDLE_HXX
