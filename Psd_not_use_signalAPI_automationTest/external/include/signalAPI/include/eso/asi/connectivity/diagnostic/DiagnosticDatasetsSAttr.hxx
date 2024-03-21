/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceSAttr_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETSSATTR_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETSSATTR_HXX

#include <common/Macros.hxx>
#include <common/types/vector.hxx>
#include <common/types/set.hxx>
#include <osal/Mutex.hxx>
#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>
#include <asi/connectivity/diagnostic/DiagnosticDatasetsS.hxx>

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /*!
    \brief  The diagnostic::DiagnosticDatasets interface on tthe service side.
    \details
            A service instance needs to implement this interface.
    */
    class DiagnosticDatasetsSAttr : public DiagnosticDatasetsS
    {
        public:
            DiagnosticDatasetsSAttr ()
            : m_notifications(ipl::UUID(0x3f21104a, 0x6ae2, 0x11e7, 0x894d, 0xcb, 0x47, 0xd4, 0xf4, 0x83, 0x19))
            {}

            ~DiagnosticDatasetsSAttr() override;

/*
*************************************************************************************************************
*   getter methods for all attributes for the service application
*************************************************************************************************************
*/
            /*!
            \brief getter for attribute DatasetParameters
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< CIPtrArray< asi::connectivity::diagnostic::DatasetParameter > > getDatasetParameters();
        protected:
/*
*************************************************************************************************************
* IDL defined setter methods to be implemented by the service application
*************************************************************************************************************
*/

/*****************************************************************************
* attribute update for the service application
******************************************************************************/
        public:
            /*!
            \brief
                update call for attribute DatasetParameters
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateDatasetParameters(const CIPtr< CIPtrArray< asi::connectivity::diagnostic::DatasetParameter > >& DatasetParameters);


        protected:
/*
*************************************************************************************************************
*  implement notification methods from the IDL
*************************************************************************************************************
*/
            /*!
            \brief
                set notification for all attributes
            \details
                This method is realized by the DiagnosticDatasetsSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(DiagnosticDatasetsProxyReply& reply) override final;

            /*!
            \brief
                set notification for one attribute
            \details
                This method is realized by the DiagnosticDatasetsSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(const uint32_t attributeId, DiagnosticDatasetsProxyReply& reply) override final;

            /*!
            \brief
                set notification for a list of attributes
            \details
                This method is realized by the DiagnosticDatasetsSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(const CIPtr< CIUInt32Array >& attributeId, DiagnosticDatasetsProxyReply& reply) override final;

            /*!
            \brief
                remove notification for all attributes
            \details
                This method is realized by the DiagnosticDatasetsSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(DiagnosticDatasetsProxyReply& reply) override final;

            /*!
            \brief
                remove notification for a specific attribute
            \details
                This method is realized by the DiagnosticDatasetsSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(const uint32_t attributeId, DiagnosticDatasetsProxyReply& reply) override final;

            /*!
            \brief
                remove notification for a list of attributes
            \details
                This method is realized by the DiagnosticDatasetsSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(const CIPtr< CIUInt32Array >& attributeId, DiagnosticDatasetsProxyReply& reply) override final;

/*
*************************************************************************************************************
* implement setter methods from the IDL
*************************************************************************************************************
*/

/*
*************************************************************************************************************
* implement getter methods from the IDL
*************************************************************************************************************
*/
            /*!
            \brief
            getter for the attribute DatasetParameters
            getDatasetParameters Method ID: 3
            \details
            This method is realized by the DiagnosticDatasetsSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getDatasetParameters(DiagnosticDatasetsProxyReply& reply) override final;


/* #################################  private members ###################### */
        private:
            /*!
            \brief
                container for all attributes and related valid flags
            \details
                it stored on instance of each attribute and a valid flag per attribute
            */
            struct AttributeContainer {
                AttributeContainer() :
                    m_DatasetParameters_valid (false)
                {}
                    
                AttributeContainer(const AttributeContainer&)=delete;
                AttributeContainer &operator = (const AttributeContainer &)=delete;

                CIPtr< CIPtrArray< asi::connectivity::diagnostic::DatasetParameter > > m_DatasetParameters;
                bool m_DatasetParameters_valid;
            };
            /*!
            \brief
                send an update of the attribute value from the cache to the given reply proxy
            \param[in] attribute_Id
                related id of the attribute the update shall be send
            \param[in] proxy
                reply proxy to call the related update method
            */
            void sendAttributeUpdate (uint32_t attribute_id, DiagnosticDatasetsProxyReply& proxy, bool lock=true);

            //! the container of all attributes
            AttributeContainer                      m_attributes;
            //! the notification matrix
            comm::AttributeNotificationContainer    m_notifications;
            //! mutex to secure the attribute container
            osal::Mutex                             m_mtx;
    };

} //namespace asi
} //namespace connectivity
} //namespace diagnostic
#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETSSATTR_HXX
