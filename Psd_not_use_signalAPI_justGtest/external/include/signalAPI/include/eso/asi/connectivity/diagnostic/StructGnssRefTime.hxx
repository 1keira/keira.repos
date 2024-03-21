/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_GNSSREFTIME_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_GNSSREFTIME_HXX

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
    \brief struct diagnostic::GnssRefTime.
    */
    struct PROXY_EXPORT GnssRefTime
    {
        uint8_t day; // optional=False
        uint8_t month; // optional=False
        uint16_t year; // optional=False
        private:
            GnssRefTime()
            :
            day(),
            month(),
            year()
            { }
            friend class GnssRefTimeFactory;
            friend class CIFactory<GnssRefTime>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::GnssRefTime> >;
            friend class ipl::vector<GnssRefTime>;
            friend class ipl::allocator<GnssRefTime>;
#endif
    };

    typedef CIPtrArray<GnssRefTime> CIGnssRefTimeArray;

    /** \brief factory for diagnostic::GnssRefTime. */
    class PROXY_EXPORT GnssRefTimeFactory  : CIFactory<GnssRefTime> {
    public:
        static inline CIPtr<GnssRefTime> createGnssRefTime() {
            return CIFactory<GnssRefTime>::createObject();
        }
        static inline void createGnssRefTime(CIPtr<GnssRefTime> & s) {
            CIFactory<GnssRefTime>::createObject(s);
        }
        static inline CIPtr<CIGnssRefTimeArray> createGnssRefTimeArray(size_t size) {
            return CIFactory<GnssRefTime>::createArray(size);
        }
        static inline void createGnssRefTimeArray(CIPtr<CIGnssRefTimeArray>& a, size_t size) {
            CIFactory<GnssRefTime>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_GNSSREFTIME_HXX
