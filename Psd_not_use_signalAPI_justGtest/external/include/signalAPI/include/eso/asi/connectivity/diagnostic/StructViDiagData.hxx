/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATA_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATA_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/diagnostic/StructViDiagDataMetadata.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief struct diagnostic::ViDiagData.
    */
    struct PROXY_EXPORT ViDiagData
    {
        /**
            data Array Size: unlimited
        */
        CIPtr< CIUInt8Array > data; // optional=True
        uint64_t lastChanged; // optional=False
        CIPtr< asi::connectivity::diagnostic::ViDiagDataMetadata > metadata; // optional=True
        private:
            ViDiagData()
            :
            data(),
            lastChanged(),
            metadata()
            { }
            friend class ViDiagDataFactory;
            friend class CIFactory<ViDiagData>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::ViDiagData> >;
            friend class ipl::vector<ViDiagData>;
            friend class ipl::allocator<ViDiagData>;
#endif
    };

    typedef CIPtrArray<ViDiagData> CIViDiagDataArray;

    /** \brief factory for diagnostic::ViDiagData. */
    class PROXY_EXPORT ViDiagDataFactory  : CIFactory<ViDiagData> {
    public:
        static inline CIPtr<ViDiagData> createViDiagData() {
            return CIFactory<ViDiagData>::createObject();
        }
        static inline void createViDiagData(CIPtr<ViDiagData> & s) {
            CIFactory<ViDiagData>::createObject(s);
        }
        static inline CIPtr<CIViDiagDataArray> createViDiagDataArray(size_t size) {
            return CIFactory<ViDiagData>::createArray(size);
        }
        static inline void createViDiagDataArray(CIPtr<CIViDiagDataArray>& a, size_t size) {
            CIFactory<ViDiagData>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATA_HXX
