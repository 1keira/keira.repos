/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_PRODUCTIONMODE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_PRODUCTIONMODE_HXX

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
    \brief struct diagnostic::ProductionMode.
    */
    struct PROXY_EXPORT ProductionMode
    {
        bool isOnForBt; // optional=False
        bool isOnForMobNet; // optional=False
        bool isOnForWlan; // optional=False
        private:
            ProductionMode()
            :
            isOnForBt(),
            isOnForMobNet(),
            isOnForWlan()
            { }
            friend class ProductionModeFactory;
            friend class CIFactory<ProductionMode>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::ProductionMode> >;
            friend class ipl::vector<ProductionMode>;
            friend class ipl::allocator<ProductionMode>;
#endif
    };

    typedef CIPtrArray<ProductionMode> CIProductionModeArray;

    /** \brief factory for diagnostic::ProductionMode. */
    class PROXY_EXPORT ProductionModeFactory  : CIFactory<ProductionMode> {
    public:
        static inline CIPtr<ProductionMode> createProductionMode() {
            return CIFactory<ProductionMode>::createObject();
        }
        static inline void createProductionMode(CIPtr<ProductionMode> & s) {
            CIFactory<ProductionMode>::createObject(s);
        }
        static inline CIPtr<CIProductionModeArray> createProductionModeArray(size_t size) {
            return CIFactory<ProductionMode>::createArray(size);
        }
        static inline void createProductionModeArray(CIPtr<CIProductionModeArray>& a, size_t size) {
            CIFactory<ProductionMode>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_PRODUCTIONMODE_HXX
