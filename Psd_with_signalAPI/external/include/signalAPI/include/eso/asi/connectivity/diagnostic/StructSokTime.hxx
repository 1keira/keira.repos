/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_SOKTIME_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_SOKTIME_HXX

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
    \brief struct diagnostic::SokTime.
    */
    struct PROXY_EXPORT SokTime
    {
        uint64_t currentTime; // optional=False
        bool isJitterExceeded; // optional=False
        bool isTimeValid; // optional=False
        private:
            SokTime()
            :
            currentTime(),
            isJitterExceeded(),
            isTimeValid()
            { }
            friend class SokTimeFactory;
            friend class CIFactory<SokTime>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::SokTime> >;
            friend class ipl::vector<SokTime>;
            friend class ipl::allocator<SokTime>;
#endif
    };

    typedef CIPtrArray<SokTime> CISokTimeArray;

    /** \brief factory for diagnostic::SokTime. */
    class PROXY_EXPORT SokTimeFactory  : CIFactory<SokTime> {
    public:
        static inline CIPtr<SokTime> createSokTime() {
            return CIFactory<SokTime>::createObject();
        }
        static inline void createSokTime(CIPtr<SokTime> & s) {
            CIFactory<SokTime>::createObject(s);
        }
        static inline CIPtr<CISokTimeArray> createSokTimeArray(size_t size) {
            return CIFactory<SokTime>::createArray(size);
        }
        static inline void createSokTimeArray(CIPtr<CISokTimeArray>& a, size_t size) {
            CIFactory<SokTime>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_SOKTIME_HXX
