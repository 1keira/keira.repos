/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_MAPATTACHMENTS_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_MAPATTACHMENTS_HXX

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
        
    * Definition of a MAP attachment intended for pushing
    
    */
    struct PROXY_EXPORT MapAttachments
    {
        CIPtr< CIString > local_path; // optional=True
        bool rfc822_encoded_mimepart; // optional=False
        CIPtr< CIString > display_name; // optional=True
        CIPtr< CIString > content_type; // optional=True
        private:
            MapAttachments()
            :
            local_path(),
            rfc822_encoded_mimepart(),
            display_name(),
            content_type()
            { }
            friend class MapAttachmentsFactory;
            friend class CIFactory<MapAttachments>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::messaging::MapAttachments> >;
            friend class ipl::vector<MapAttachments>;
            friend class ipl::allocator<MapAttachments>;
#endif
    };

    typedef CIPtrArray<MapAttachments> CIMapAttachmentsArray;

    /** \brief factory for messaging::MapAttachments. */
    class PROXY_EXPORT MapAttachmentsFactory  : CIFactory<MapAttachments> {
    public:
        static inline CIPtr<MapAttachments> createMapAttachments() {
            return CIFactory<MapAttachments>::createObject();
        }
        static inline void createMapAttachments(CIPtr<MapAttachments> & s) {
            CIFactory<MapAttachments>::createObject(s);
        }
        static inline CIPtr<CIMapAttachmentsArray> createMapAttachmentsArray(size_t size) {
            return CIFactory<MapAttachments>::createArray(size);
        }
        static inline void createMapAttachmentsArray(CIPtr<CIMapAttachmentsArray>& a, size_t size) {
            CIFactory<MapAttachments>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al
}//namespace messaging


#endif// ASI_CONNECTIVITY_AL_MESSAGING_MAPATTACHMENTS_HXX
