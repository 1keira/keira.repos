/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_VEHICLEDIMENSIONS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_VEHICLEDIMENSIONS_HXX

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
    \brief struct diagnostic::VehicleDimensions.
    */
    struct PROXY_EXPORT VehicleDimensions
    {
        uint16_t height; // optional=False
        uint16_t length; // optional=False
        uint16_t width; // optional=False
        private:
            VehicleDimensions()
            :
            height(),
            length(),
            width()
            { }
            friend class VehicleDimensionsFactory;
            friend class CIFactory<VehicleDimensions>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::VehicleDimensions> >;
            friend class ipl::vector<VehicleDimensions>;
            friend class ipl::allocator<VehicleDimensions>;
#endif
    };

    typedef CIPtrArray<VehicleDimensions> CIVehicleDimensionsArray;

    /** \brief factory for diagnostic::VehicleDimensions. */
    class PROXY_EXPORT VehicleDimensionsFactory  : CIFactory<VehicleDimensions> {
    public:
        static inline CIPtr<VehicleDimensions> createVehicleDimensions() {
            return CIFactory<VehicleDimensions>::createObject();
        }
        static inline void createVehicleDimensions(CIPtr<VehicleDimensions> & s) {
            CIFactory<VehicleDimensions>::createObject(s);
        }
        static inline CIPtr<CIVehicleDimensionsArray> createVehicleDimensionsArray(size_t size) {
            return CIFactory<VehicleDimensions>::createArray(size);
        }
        static inline void createVehicleDimensionsArray(CIPtr<CIVehicleDimensionsArray>& a, size_t size) {
            CIFactory<VehicleDimensions>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_VEHICLEDIMENSIONS_HXX
