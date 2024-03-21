/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_TIMESTAMP_HXX
#define ASI_CONNECTIVITY_AL_TIMESTAMP_HXX

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
    \brief struct al::Timestamp.
    */
    struct PROXY_EXPORT Timestamp
    {
        int16_t year; // optional=False
        int16_t month; // optional=False
        int16_t day; // optional=False
        int16_t hours; // optional=False
        int16_t minutes; // optional=False
        int16_t seconds; // optional=False
        private:
            Timestamp()
            :
            year(-1),
            month(-1),
            day(-1),
            hours(-1),
            minutes(-1),
            seconds(-1)
            { }
            friend class TimestampFactory;
            friend class CIFactory<Timestamp>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::Timestamp> >;
            friend class ipl::vector<Timestamp>;
            friend class ipl::allocator<Timestamp>;
#endif
    };

    typedef CIPtrArray<Timestamp> CITimestampArray;

    /** \brief factory for al::Timestamp. */
    class PROXY_EXPORT TimestampFactory  : CIFactory<Timestamp> {
    public:
        static inline CIPtr<Timestamp> createTimestamp() {
            return CIFactory<Timestamp>::createObject();
        }
        static inline void createTimestamp(CIPtr<Timestamp> & s) {
            CIFactory<Timestamp>::createObject(s);
        }
        static inline CIPtr<CITimestampArray> createTimestampArray(size_t size) {
            return CIFactory<Timestamp>::createArray(size);
        }
        static inline void createTimestampArray(CIPtr<CITimestampArray>& a, size_t size) {
            CIFactory<Timestamp>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_TIMESTAMP_HXX
