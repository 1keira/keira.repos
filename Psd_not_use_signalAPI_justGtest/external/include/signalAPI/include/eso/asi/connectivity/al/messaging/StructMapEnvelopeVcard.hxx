/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_MAPENVELOPEVCARD_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_MAPENVELOPEVCARD_HXX

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
        
    * MAP specifies so called envelope vcards which describe the final recipients using 
    * limited number of vcard fields (e.g. N, TEL, EMAIL)
    
    */
    struct PROXY_EXPORT MapEnvelopeVcard
    {
        CIPtr< CIString > name; // optional=True
        CIPtr< CIString > email; // optional=True
        CIPtr< CIString > tel; // optional=True
        private:
            MapEnvelopeVcard()
            :
            name(),
            email(),
            tel()
            { }
            friend class MapEnvelopeVcardFactory;
            friend class CIFactory<MapEnvelopeVcard>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::messaging::MapEnvelopeVcard> >;
            friend class ipl::vector<MapEnvelopeVcard>;
            friend class ipl::allocator<MapEnvelopeVcard>;
#endif
    };

    typedef CIPtrArray<MapEnvelopeVcard> CIMapEnvelopeVcardArray;

    /** \brief factory for messaging::MapEnvelopeVcard. */
    class PROXY_EXPORT MapEnvelopeVcardFactory  : CIFactory<MapEnvelopeVcard> {
    public:
        static inline CIPtr<MapEnvelopeVcard> createMapEnvelopeVcard() {
            return CIFactory<MapEnvelopeVcard>::createObject();
        }
        static inline void createMapEnvelopeVcard(CIPtr<MapEnvelopeVcard> & s) {
            CIFactory<MapEnvelopeVcard>::createObject(s);
        }
        static inline CIPtr<CIMapEnvelopeVcardArray> createMapEnvelopeVcardArray(size_t size) {
            return CIFactory<MapEnvelopeVcard>::createArray(size);
        }
        static inline void createMapEnvelopeVcardArray(CIPtr<CIMapEnvelopeVcardArray>& a, size_t size) {
            CIFactory<MapEnvelopeVcard>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al
}//namespace messaging


#endif// ASI_CONNECTIVITY_AL_MESSAGING_MAPENVELOPEVCARD_HXX
