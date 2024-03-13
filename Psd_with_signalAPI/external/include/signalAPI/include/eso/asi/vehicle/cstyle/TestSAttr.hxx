/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceSAttr_hxx.tmpl
*/
#ifndef ASI_VEHICLE_TESTSATTR_CSTYLE_HXX
#define ASI_VEHICLE_TESTSATTR_CSTYLE_HXX

#include <common/Macros.hxx>
#include <common/types/vector.hxx>
#include <common/types/set.hxx>
#include <osal/Mutex.hxx>
#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/vehicle/cstyle/Definitions.hxx>
#include <asi/vehicle/cstyle/TestS.hxx>

namespace asi
{
namespace vehicle
{
namespace cstyle {

    /*!
    \brief  The vehicle::Test interface on tthe service side.
    \detail
            A service instance needs to implement this interface.
    */
    class TestSAttr : public TestS
    {
        public:
            TestSAttr ()
            : m_notifications(ipl::UUID(0xc10ac01f, 0x3f55, 0x5440, 0xb401, 0xd4, 0x07, 0x4d, 0x86, 0x02, 0xbe))
            {}

            virtual ~TestSAttr();


/*
*************************************************************************************************************
*   getter methods for all attributes for the service application
*************************************************************************************************************
*/
            /*!
            \brief getter for attribute Klemmen_Status_01
            \detail
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const asi::vehicle::cstyle::KlemmenStatus01Struct* getKlemmen_Status_01();
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
                update call for attribute Klemmen_Status_01
            \detail
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateKlemmen_Status_01(const asi::vehicle::cstyle::KlemmenStatus01Struct* Klemmen_Status_01);


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
                This method is realized by the TestSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(TestProxyReply& reply) override;

            /*!
            \brief
                set notification for one attribute
            \detail
                This method is realized by the TestSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(const uint32_t attributeId, TestProxyReply& reply) override;

            /*!
            \brief
                set notification for a list of attributes
            \detail
                This method is realized by the TestSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(const ipl::vector<uint32_t>* attributeId, TestProxyReply& reply) override;

            /*!
            \brief
                remove notification for all attributes
            \detail
                This method is realized by the TestSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(TestProxyReply& reply) override;

            /*!
            \brief
                remove notification for a specific attribute
            \detail
                This method is realized by the TestSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(const uint32_t attributeId, TestProxyReply& reply) override;

            /*!
            \brief
                remove notification for a list of attributes
            \detail
                This method is realized by the TestSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(const ipl::vector<uint32_t>* attributeId, TestProxyReply& reply) override;

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
            getter for the attribute Klemmen_Status_01
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * ZAS_Kl_15:
         *   * E3_1_1_UNECE: Klemmen_Status_01.ZAS_Kl_15
         * > KlemmenStatus01Struct.ZAS_Kl_15 [uint64]:
         *   Based on:
         *     * ZAS_Kl_15: Klemme 15: Zuendung (SW-Kl.15)
         *   Used Constants:
         *     0: eZASKl15_Aus
         *     1: eZASKl15_Ein
         * > KlemmenStatus01Struct.pdustate [uint64]:
         *   Based on:
         *     ZAS_Kl_15 SignalState
         *   Used Constants:
         *     0: ePdustate_NotExisting
         *     1: ePdustate_Valid
         *     2: ePdustate_TempNotValid
         *     3: ePdustate_TimeoutNotValidNotFiltered
         *     4: ePdustate_NeverReceived
         *     5: ePdustate_TimeoutNotValidFiltered
         *     15: ePdustate_Invalid
         ***
            getKlemmen_Status_01 Method ID: 3
            \detail
            This method is realized by the TestSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getKlemmen_Status_01(TestProxyReply& reply) override;


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
                    m_Klemmen_Status_01(nullptr),

                    m_Klemmen_Status_01_valid (false)
                    {}
                ~AttributeContainer() {
                    if (m_Klemmen_Status_01)
                        delete m_Klemmen_Status_01;
                }
            
                AttributeContainer(const AttributeContainer&)=delete;
                AttributeContainer &operator = (const AttributeContainer &)=delete;
            

                    asi::vehicle::cstyle::KlemmenStatus01Struct* m_Klemmen_Status_01;

                    bool m_Klemmen_Status_01_valid;
            };

            /*!
            \brief
                send an update of the attribute value from the cache to the given reply proxy
            \param[in] attribute_Id
                related id of the attribute the update shall be send
            \param[in] proxy
                reply proxy to call the related update method
            */
            void sendAttributeUpdate (uint32_t attribute_id, TestProxyReply& proxy, bool lock=true);

            //! the container of all attributes
            AttributeContainer                      m_attributes;
            //! the notification matrix
            comm::AttributeNotificationContainer    m_notifications;
            //! mutex to secure the attribute container
            osal::Mutex                             m_mtx;
    };

} // namespace cstyle
} //namespace asi
} //namespace vehicle
#endif// ASI_VEHICLE_TESTSATTR_CSTYLE_HXX
