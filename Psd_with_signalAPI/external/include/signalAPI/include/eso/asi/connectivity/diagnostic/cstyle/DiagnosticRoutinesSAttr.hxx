/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceSAttr_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICROUTINESSATTR_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICROUTINESSATTR_CSTYLE_HXX

#include <common/Macros.hxx>
#include <common/types/vector.hxx>
#include <common/types/set.hxx>
#include <osal/Mutex.hxx>
#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
#include <asi/connectivity/diagnostic/cstyle/DiagnosticRoutinesS.hxx>

namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace cstyle {

    /*!
    \brief  The diagnostic::DiagnosticRoutines interface on tthe service side.
    \detail
            A service instance needs to implement this interface.
    */
    class DiagnosticRoutinesSAttr : public DiagnosticRoutinesS
    {
        public:
            DiagnosticRoutinesSAttr ()
            : m_notifications(ipl::UUID(0x34ae4f9a, 0x5d74, 0x11e7, 0xb43b, 0x6f, 0xa6, 0x3a, 0xcc, 0x8a, 0x2f))
            {}

            virtual ~DiagnosticRoutinesSAttr();


/*
*************************************************************************************************************
*   getter methods for all attributes for the service application
*************************************************************************************************************
*/
            /*!
            \brief getter for attribute RoutineRequest
            \detail
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const asi::connectivity::diagnostic::cstyle::RoutineRequestInfo* getRoutineRequest();
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
                update call for attribute RoutineRequest
            \detail
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateRoutineRequest(const asi::connectivity::diagnostic::cstyle::RoutineRequestInfo* RoutineRequest);


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
                This method is realized by the DiagnosticRoutinesSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(DiagnosticRoutinesProxyReply& reply) override;

            /*!
            \brief
                set notification for one attribute
            \detail
                This method is realized by the DiagnosticRoutinesSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(const uint32_t attributeId, DiagnosticRoutinesProxyReply& reply) override;

            /*!
            \brief
                set notification for a list of attributes
            \detail
                This method is realized by the DiagnosticRoutinesSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(const ipl::vector<uint32_t>* attributeId, DiagnosticRoutinesProxyReply& reply) override;

            /*!
            \brief
                remove notification for all attributes
            \detail
                This method is realized by the DiagnosticRoutinesSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(DiagnosticRoutinesProxyReply& reply) override;

            /*!
            \brief
                remove notification for a specific attribute
            \detail
                This method is realized by the DiagnosticRoutinesSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(const uint32_t attributeId, DiagnosticRoutinesProxyReply& reply) override;

            /*!
            \brief
                remove notification for a list of attributes
            \detail
                This method is realized by the DiagnosticRoutinesSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(const ipl::vector<uint32_t>* attributeId, DiagnosticRoutinesProxyReply& reply) override;

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
            getter for the attribute RoutineRequest
            getRoutineRequest Method ID: 3
            \detail
            This method is realized by the DiagnosticRoutinesSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getRoutineRequest(DiagnosticRoutinesProxyReply& reply) override;


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
                    m_RoutineRequest(nullptr),

                    m_RoutineRequest_valid (false)
                    {}
                ~AttributeContainer() {
                    if (m_RoutineRequest)
                        delete m_RoutineRequest;
                }
            
                AttributeContainer(const AttributeContainer&)=delete;
                AttributeContainer &operator = (const AttributeContainer &)=delete;
            

                    asi::connectivity::diagnostic::cstyle::RoutineRequestInfo* m_RoutineRequest;

                    bool m_RoutineRequest_valid;
            };

            /*!
            \brief
                send an update of the attribute value from the cache to the given reply proxy
            \param[in] attribute_Id
                related id of the attribute the update shall be send
            \param[in] proxy
                reply proxy to call the related update method
            */
            void sendAttributeUpdate (uint32_t attribute_id, DiagnosticRoutinesProxyReply& proxy, bool lock=true);

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
#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICROUTINESSATTR_CSTYLE_HXX
