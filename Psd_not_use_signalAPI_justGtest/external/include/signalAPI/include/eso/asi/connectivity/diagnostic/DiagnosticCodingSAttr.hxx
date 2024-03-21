/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceSAttr_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODINGSATTR_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODINGSATTR_HXX

#include <common/Macros.hxx>
#include <common/types/vector.hxx>
#include <common/types/set.hxx>
#include <osal/Mutex.hxx>
#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>
#include <asi/connectivity/diagnostic/DiagnosticCodingS.hxx>

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /*!
    \brief  The diagnostic::DiagnosticCoding interface on tthe service side.
    \details
            A service instance needs to implement this interface.
    */
    class DiagnosticCodingSAttr : public DiagnosticCodingS
    {
        public:
            DiagnosticCodingSAttr ()
            : m_notifications(ipl::UUID(0x2db9342a, 0xfd81, 0x4d35, 0xa883, 0x0f, 0x1c, 0x75, 0x6a, 0xb0, 0x37))
            {}

            ~DiagnosticCodingSAttr() override;

/*
*************************************************************************************************************
*   getter methods for all attributes for the service application
*************************************************************************************************************
*/
            /*!
            \brief getter for attribute AdaptationValues
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::connectivity::diagnostic::AdaptationValues > getAdaptationValues();
            /*!
            \brief getter for attribute CodingValues
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::connectivity::diagnostic::CodingValues > getCodingValues();
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
                update call for attribute AdaptationValues
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateAdaptationValues(const CIPtr< asi::connectivity::diagnostic::AdaptationValues >& AdaptationValues);

            /*!
            \brief
                update call for attribute CodingValues
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateCodingValues(const CIPtr< asi::connectivity::diagnostic::CodingValues >& CodingValues);


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
                This method is realized by the DiagnosticCodingSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(DiagnosticCodingProxyReply& reply) override final;

            /*!
            \brief
                set notification for one attribute
            \details
                This method is realized by the DiagnosticCodingSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(const uint32_t attributeId, DiagnosticCodingProxyReply& reply) override final;

            /*!
            \brief
                set notification for a list of attributes
            \details
                This method is realized by the DiagnosticCodingSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(const CIPtr< CIUInt32Array >& attributeId, DiagnosticCodingProxyReply& reply) override final;

            /*!
            \brief
                remove notification for all attributes
            \details
                This method is realized by the DiagnosticCodingSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(DiagnosticCodingProxyReply& reply) override final;

            /*!
            \brief
                remove notification for a specific attribute
            \details
                This method is realized by the DiagnosticCodingSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(const uint32_t attributeId, DiagnosticCodingProxyReply& reply) override final;

            /*!
            \brief
                remove notification for a list of attributes
            \details
                This method is realized by the DiagnosticCodingSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(const CIPtr< CIUInt32Array >& attributeId, DiagnosticCodingProxyReply& reply) override final;

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
            getter for the attribute AdaptationValues
            getAdaptationValues Method ID: 3
            \details
            This method is realized by the DiagnosticCodingSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getAdaptationValues(DiagnosticCodingProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute CodingValues
            \details
            *
         * Delivers coding values received from IOC (either on startup or when
         * a value has been changed)
         *
         * @param CodingValues - Contains values of all coding parameters
         
            getCodingValues Method ID: 4
            \details
            This method is realized by the DiagnosticCodingSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getCodingValues(DiagnosticCodingProxyReply& reply) override final;


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
                    m_AdaptationValues_valid (false),
                    m_CodingValues_valid (false)
                {}
                    
                AttributeContainer(const AttributeContainer&)=delete;
                AttributeContainer &operator = (const AttributeContainer &)=delete;

                CIPtr< asi::connectivity::diagnostic::AdaptationValues > m_AdaptationValues;
                CIPtr< asi::connectivity::diagnostic::CodingValues > m_CodingValues;
                bool m_AdaptationValues_valid;
                bool m_CodingValues_valid;
            };
            /*!
            \brief
                send an update of the attribute value from the cache to the given reply proxy
            \param[in] attribute_Id
                related id of the attribute the update shall be send
            \param[in] proxy
                reply proxy to call the related update method
            */
            void sendAttributeUpdate (uint32_t attribute_id, DiagnosticCodingProxyReply& proxy, bool lock=true);

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
#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODINGSATTR_HXX
