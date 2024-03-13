/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DATASETPARAMETER_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DATASETPARAMETER_HXX

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
    \brief struct diagnostic::DatasetParameter.
    */
    struct PROXY_EXPORT DatasetParameter
    {
        CIPtr< CIString > key; // optional=True
        CIPtr< CIString > value; // optional=True
        private:
            DatasetParameter()
            :
            key(),
            value()
            { }
            friend class DatasetParameterFactory;
            friend class CIFactory<DatasetParameter>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::DatasetParameter> >;
            friend class ipl::vector<DatasetParameter>;
            friend class ipl::allocator<DatasetParameter>;
#endif
    };

    typedef CIPtrArray<DatasetParameter> CIDatasetParameterArray;

    /** \brief factory for diagnostic::DatasetParameter. */
    class PROXY_EXPORT DatasetParameterFactory  : CIFactory<DatasetParameter> {
    public:
        static inline CIPtr<DatasetParameter> createDatasetParameter() {
            return CIFactory<DatasetParameter>::createObject();
        }
        static inline void createDatasetParameter(CIPtr<DatasetParameter> & s) {
            CIFactory<DatasetParameter>::createObject(s);
        }
        static inline CIPtr<CIDatasetParameterArray> createDatasetParameterArray(size_t size) {
            return CIFactory<DatasetParameter>::createArray(size);
        }
        static inline void createDatasetParameterArray(CIPtr<CIDatasetParameterArray>& a, size_t size) {
            CIFactory<DatasetParameter>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DATASETPARAMETER_HXX
