/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATAMETADATA_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATAMETADATA_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief struct diagnostic::ViDiagDataMetadata.
    */
    struct PROXY_EXPORT ViDiagDataMetadata
    {
        uint32_t id; // optional=False
        bool isModifiable; // optional=False
        bool isReadOnly; // optional=False
        uint32_t maxLength; // optional=False
        uint32_t minLength; // optional=False
        asi::connectivity::diagnostic::DiagDataType type; // optional=False
        private:
            ViDiagDataMetadata()
            :
            id(),
            isModifiable(),
            isReadOnly(),
            maxLength(),
            minLength(),
            type()
            { }
            friend class ViDiagDataMetadataFactory;
            friend class CIFactory<ViDiagDataMetadata>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::ViDiagDataMetadata> >;
            friend class ipl::vector<ViDiagDataMetadata>;
            friend class ipl::allocator<ViDiagDataMetadata>;
#endif
    };

    typedef CIPtrArray<ViDiagDataMetadata> CIViDiagDataMetadataArray;

    /** \brief factory for diagnostic::ViDiagDataMetadata. */
    class PROXY_EXPORT ViDiagDataMetadataFactory  : CIFactory<ViDiagDataMetadata> {
    public:
        static inline CIPtr<ViDiagDataMetadata> createViDiagDataMetadata() {
            return CIFactory<ViDiagDataMetadata>::createObject();
        }
        static inline void createViDiagDataMetadata(CIPtr<ViDiagDataMetadata> & s) {
            CIFactory<ViDiagDataMetadata>::createObject(s);
        }
        static inline CIPtr<CIViDiagDataMetadataArray> createViDiagDataMetadataArray(size_t size) {
            return CIFactory<ViDiagDataMetadata>::createArray(size);
        }
        static inline void createViDiagDataMetadataArray(CIPtr<CIViDiagDataMetadataArray>& a, size_t size) {
            CIFactory<ViDiagDataMetadata>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATAMETADATA_HXX
