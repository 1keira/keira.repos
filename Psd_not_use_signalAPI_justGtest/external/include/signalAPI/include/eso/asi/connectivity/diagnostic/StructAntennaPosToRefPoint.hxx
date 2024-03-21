/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_ANTENNAPOSTOREFPOINT_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_ANTENNAPOSTOREFPOINT_HXX

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
    \brief struct diagnostic::AntennaPosToRefPoint.
    */
    struct PROXY_EXPORT AntennaPosToRefPoint
    {
        uint16_t directionX; // optional=False
        uint16_t directionY; // optional=False
        uint16_t directionZ; // optional=False
        private:
            AntennaPosToRefPoint()
            :
            directionX(),
            directionY(),
            directionZ()
            { }
            friend class AntennaPosToRefPointFactory;
            friend class CIFactory<AntennaPosToRefPoint>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::AntennaPosToRefPoint> >;
            friend class ipl::vector<AntennaPosToRefPoint>;
            friend class ipl::allocator<AntennaPosToRefPoint>;
#endif
    };

    typedef CIPtrArray<AntennaPosToRefPoint> CIAntennaPosToRefPointArray;

    /** \brief factory for diagnostic::AntennaPosToRefPoint. */
    class PROXY_EXPORT AntennaPosToRefPointFactory  : CIFactory<AntennaPosToRefPoint> {
    public:
        static inline CIPtr<AntennaPosToRefPoint> createAntennaPosToRefPoint() {
            return CIFactory<AntennaPosToRefPoint>::createObject();
        }
        static inline void createAntennaPosToRefPoint(CIPtr<AntennaPosToRefPoint> & s) {
            CIFactory<AntennaPosToRefPoint>::createObject(s);
        }
        static inline CIPtr<CIAntennaPosToRefPointArray> createAntennaPosToRefPointArray(size_t size) {
            return CIFactory<AntennaPosToRefPoint>::createArray(size);
        }
        static inline void createAntennaPosToRefPointArray(CIPtr<CIAntennaPosToRefPointArray>& a, size_t size) {
            CIFactory<AntennaPosToRefPoint>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_ANTENNAPOSTOREFPOINT_HXX
