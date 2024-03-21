/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_MOBILETELECOMMUNICATIONSTANDARD_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_MOBILETELECOMMUNICATIONSTANDARD_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief struct diagnostic::MobileTelecommunicationStandard.
    */
    struct PROXY_EXPORT MobileTelecommunicationStandard
    {
        bool is2gOn; // optional=False
        bool is3gOn; // optional=False
        bool is4gOn; // optional=False
        bool is4gCaOn; // optional=False
        bool is5gNsaOn; // optional=False
        bool is5gSaCaOn; // optional=False
        bool is5gSaOn; // optional=False
        bool isMsdViaSipOn; // optional=False
        bool isSoundRefSignalOn; // optional=False
        bool isVoLteOn; // optional=False
        bool isVoNrOn; // optional=False
        private:
            MobileTelecommunicationStandard()
            :
            is2gOn(),
            is3gOn(),
            is4gOn(),
            is4gCaOn(),
            is5gNsaOn(),
            is5gSaCaOn(),
            is5gSaOn(),
            isMsdViaSipOn(),
            isSoundRefSignalOn(),
            isVoLteOn(),
            isVoNrOn()
            { }
            friend class MobileTelecommunicationStandardFactory;
            friend class CIFactory<MobileTelecommunicationStandard>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::MobileTelecommunicationStandard> >;
            friend class ipl::vector<MobileTelecommunicationStandard>;
            friend class ipl::allocator<MobileTelecommunicationStandard>;
#endif
    };

    typedef CIPtrArray<MobileTelecommunicationStandard> CIMobileTelecommunicationStandardArray;

    /** \brief factory for diagnostic::MobileTelecommunicationStandard. */
    class PROXY_EXPORT MobileTelecommunicationStandardFactory  : CIFactory<MobileTelecommunicationStandard> {
    public:
        static inline CIPtr<MobileTelecommunicationStandard> createMobileTelecommunicationStandard() {
            return CIFactory<MobileTelecommunicationStandard>::createObject();
        }
        static inline void createMobileTelecommunicationStandard(CIPtr<MobileTelecommunicationStandard> & s) {
            CIFactory<MobileTelecommunicationStandard>::createObject(s);
        }
        static inline CIPtr<CIMobileTelecommunicationStandardArray> createMobileTelecommunicationStandardArray(size_t size) {
            return CIFactory<MobileTelecommunicationStandard>::createArray(size);
        }
        static inline void createMobileTelecommunicationStandardArray(CIPtr<CIMobileTelecommunicationStandardArray>& a, size_t size) {
            CIFactory<MobileTelecommunicationStandard>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_MOBILETELECOMMUNICATIONSTANDARD_HXX
