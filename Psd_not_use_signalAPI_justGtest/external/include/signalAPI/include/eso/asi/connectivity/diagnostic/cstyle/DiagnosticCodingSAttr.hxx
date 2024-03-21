/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceSAttr_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODINGSATTR_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODINGSATTR_CSTYLE_HXX

#include <common/Macros.hxx>
#include <common/types/vector.hxx>
#include <common/types/set.hxx>
#include <osal/Mutex.hxx>
#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
#include <asi/connectivity/diagnostic/cstyle/DiagnosticCodingS.hxx>

namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace cstyle {

    /*!
    \brief  The diagnostic::DiagnosticCoding interface on tthe service side.
    \detail
            A service instance needs to implement this interface.
    */
    class DiagnosticCodingSAttr : public DiagnosticCodingS
    {
        public:
            DiagnosticCodingSAttr ()
            : m_notifications(ipl::UUID(0x2db9342a, 0xfd81, 0x4d35, 0xa883, 0x0f, 0x1c, 0x75, 0x6a, 0xb0, 0x37))
            {}

            virtual ~DiagnosticCodingSAttr();


/*
*************************************************************************************************************
*   getter methods for all attributes for the service application
*************************************************************************************************************
*/
            /*!
            \brief getter for attribute AdaptationValues
            \detail
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const asi::connectivity::diagnostic::cstyle::AdaptationValues* getAdaptationValues();
            /*!
            \brief getter for attribute CodingValues
            \detail
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const asi::connectivity::diagnostic::cstyle::CodingValues* getCodingValues();
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
            \detail
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateAdaptationValues(const asi::connectivity::diagnostic::cstyle::AdaptationValues* AdaptationValues);

            /*!
            \brief
                update call for attribute CodingValues
            \detail
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateCodingValues(const asi::connectivity::diagnostic::cstyle::CodingValues* CodingValues);


        protected:
/*
*************************************************************************************************************
*  implement notification methods from the IDL
*************************************************************************************************************
*/
            /*!
            \brief
                set notification for all attributes
            \detail
                This method is realized by the DiagnosticCodingSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(DiagnosticCodingProxyReply& reply) override;

            /*!
            \brief
                set notification for one attribute
            \detail
                This method is realized by the DiagnosticCodingSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(const uint32_t attributeId, DiagnosticCodingProxyReply& reply) override;

            /*!
            \brief
                set notification for a list of attributes
            \detail
                This method is realized by the DiagnosticCodingSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(const ipl::vector<uint32_t>* attributeId, DiagnosticCodingProxyReply& reply) override;

            /*!
            \brief
                remove notification for all attributes
            \detail
                This method is realized by the DiagnosticCodingSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(DiagnosticCodingProxyReply& reply) override;

            /*!
            \brief
                remove notification for a specific attribute
            \detail
                This method is realized by the DiagnosticCodingSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(const uint32_t attributeId, DiagnosticCodingProxyReply& reply) override;

            /*!
            \brief
                remove notification for a list of attributes
            \detail
                This method is realized by the DiagnosticCodingSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(const ipl::vector<uint32_t>* attributeId, DiagnosticCodingProxyReply& reply) override;

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
            \detail
            This method is realized by the DiagnosticCodingSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getAdaptationValues(DiagnosticCodingProxyReply& reply) override;

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
            \detail
            This method is realized by the DiagnosticCodingSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getCodingValues(DiagnosticCodingProxyReply& reply) override;


/* #################################  private members ###################### */
        private:
            /*!
            \brief
                container for all attributes and related valid flags
            \detail
                it stored on instance of each attribute and a valid flag per attribute
            */
            struct AttributeContainer {
                AttributeContainer() :
                    m_AdaptationValues(nullptr),
                    m_CodingValues(nullptr),

                    m_AdaptationValues_valid (false),
                    m_CodingValues_valid (false)
                    {}
                ~AttributeContainer() {
                    if (m_AdaptationValues)
                        delete m_AdaptationValues;
                    if (m_CodingValues)
                        delete m_CodingValues;
                }
            
                AttributeContainer(const AttributeContainer&)=delete;
                AttributeContainer &operator = (const AttributeContainer &)=delete;
            

                    asi::connectivity::diagnostic::cstyle::AdaptationValues* m_AdaptationValues;
                    asi::connectivity::diagnostic::cstyle::CodingValues* m_CodingValues;

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

} // namespace cstyle
} //namespace asi
} //namespace connectivity
} //namespace diagnostic
#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODINGSATTR_CSTYLE_HXX
