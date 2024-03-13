/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_SIMPLEPAIRINGINFORMATION_HXX
#define ASI_CONNECTIVITY_AL_SIMPLEPAIRINGINFORMATION_HXX

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
    \brief struct al::SimplePairingInformation.
    */
    struct PROXY_EXPORT SimplePairingInformation
    {
        bool isSimplePairingActive; // optional=False
        int32_t method; // optional=False
        int32_t deviceCapability; // optional=False
        CIPtr< CIString > pin; // optional=True
        private:
            SimplePairingInformation()
            :
            isSimplePairingActive(),
            method(),
            deviceCapability(),
            pin()
            { }
            friend class SimplePairingInformationFactory;
            friend class CIFactory<SimplePairingInformation>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::SimplePairingInformation> >;
            friend class ipl::vector<SimplePairingInformation>;
            friend class ipl::allocator<SimplePairingInformation>;
#endif
    };

    typedef CIPtrArray<SimplePairingInformation> CISimplePairingInformationArray;

    /** \brief factory for al::SimplePairingInformation. */
    class PROXY_EXPORT SimplePairingInformationFactory  : CIFactory<SimplePairingInformation> {
    public:
        static inline CIPtr<SimplePairingInformation> createSimplePairingInformation() {
            return CIFactory<SimplePairingInformation>::createObject();
        }
        static inline void createSimplePairingInformation(CIPtr<SimplePairingInformation> & s) {
            CIFactory<SimplePairingInformation>::createObject(s);
        }
        static inline CIPtr<CISimplePairingInformationArray> createSimplePairingInformationArray(size_t size) {
            return CIFactory<SimplePairingInformation>::createArray(size);
        }
        static inline void createSimplePairingInformationArray(CIPtr<CISimplePairingInformationArray>& a, size_t size) {
            CIFactory<SimplePairingInformation>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_SIMPLEPAIRINGINFORMATION_HXX
