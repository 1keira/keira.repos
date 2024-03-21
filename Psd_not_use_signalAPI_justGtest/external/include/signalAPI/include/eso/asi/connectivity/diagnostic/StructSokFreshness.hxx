/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_SOKFRESHNESS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_SOKFRESHNESS_HXX

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
    \brief struct diagnostic::SokFreshness.
    */
    struct PROXY_EXPORT SokFreshness
    {
        uint8_t activeCounterValue; // optional=False
        uint16_t consumedCounterValues; // optional=False
        bool isActive; // optional=False
        uint16_t pduId; // optional=False
        uint64_t timestampOfLastSuccessfulVerification; // optional=False
        private:
            SokFreshness()
            :
            activeCounterValue(),
            consumedCounterValues(),
            isActive(),
            pduId(),
            timestampOfLastSuccessfulVerification()
            { }
            friend class SokFreshnessFactory;
            friend class CIFactory<SokFreshness>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::SokFreshness> >;
            friend class ipl::vector<SokFreshness>;
            friend class ipl::allocator<SokFreshness>;
#endif
    };

    typedef CIPtrArray<SokFreshness> CISokFreshnessArray;

    /** \brief factory for diagnostic::SokFreshness. */
    class PROXY_EXPORT SokFreshnessFactory  : CIFactory<SokFreshness> {
    public:
        static inline CIPtr<SokFreshness> createSokFreshness() {
            return CIFactory<SokFreshness>::createObject();
        }
        static inline void createSokFreshness(CIPtr<SokFreshness> & s) {
            CIFactory<SokFreshness>::createObject(s);
        }
        static inline CIPtr<CISokFreshnessArray> createSokFreshnessArray(size_t size) {
            return CIFactory<SokFreshness>::createArray(size);
        }
        static inline void createSokFreshnessArray(CIPtr<CISokFreshnessArray>& a, size_t size) {
            CIFactory<SokFreshness>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_SOKFRESHNESS_HXX
