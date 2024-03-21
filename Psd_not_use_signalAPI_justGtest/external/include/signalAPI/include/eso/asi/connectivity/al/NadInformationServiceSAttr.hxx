/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceSAttr_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICESATTR_HXX
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICESATTR_HXX

#include <common/Macros.hxx>
#include <common/types/vector.hxx>
#include <common/types/set.hxx>
#include <osal/Mutex.hxx>
#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/al/Definitions.hxx>
#include <asi/connectivity/al/NadInformationServiceS.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{

    /*!
    \brief  The al::NadInformationService interface on tthe service side.
    \details
            A service instance needs to implement this interface.
        *
    * Clients, which are registered with the NadInformationService,
    * will receive updates of NAD related information.
    * All information will be cached and is read-only from a client perspective.
    */
    class NadInformationServiceSAttr : public NadInformationServiceS
    {
        public:
            NadInformationServiceSAttr ()
            : m_notifications(ipl::UUID(0x627977d9, 0xd125, 0x411c, 0x86d3, 0x4a, 0xaa, 0x7f, 0x89, 0x62, 0x1d))
            {}

            ~NadInformationServiceSAttr() override;

/*
*************************************************************************************************************
*   getter methods for all attributes for the service application
*************************************************************************************************************
*/
            /*!
            \brief getter for attribute AntennaInfo
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< CIPtrArray< asi::connectivity::al::AntennaInfo > > getAntennaInfo();
            /*!
            \brief getter for attribute DataConnectionInfo
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::connectivity::al::DataConnectionInfo > getDataConnectionInfo();
            /*!
            \brief getter for attribute SimDataConfig
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::connectivity::al::SimDataConfig > getSimDataConfig();
            /*!
            \brief getter for attribute NadDeviceInformation
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::connectivity::al::NadDeviceInformation > getNadDeviceInformation();
            /*!
            \brief getter for attribute NetworkRejectInformation
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::connectivity::al::NetworkRejectInformation > getNetworkRejectInformation();
            /*!
            \brief getter for attribute SimDataInfo
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::connectivity::al::SimDataInfo > getSimDataInfo();
            /*!
            \brief getter for attribute TemperatureInfo
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::connectivity::al::TemperatureInfo > getTemperatureInfo();
            /*!
            \brief getter for attribute NetworkInfo
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::connectivity::al::NetworkInfo > getNetworkInfo();
            /*!
            \brief getter for attribute AirplaneMode
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            asi::connectivity::al::AirplaneMode getAirplaneMode();
            /*!
            \brief getter for attribute NadState
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            asi::connectivity::al::NadState getNadState();
            /*!
            \brief getter for attribute JammingState
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            asi::connectivity::al::JammingStatus getJammingState();
            /*!
            \brief getter for attribute DormantMode
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            asi::connectivity::al::DormantMode getDormantMode();
            /*!
            \brief getter for attribute MobileCountryCode
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< CIString > getMobileCountryCode();
            /*!
            \brief getter for attribute MobileNetworkCode
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< CIString > getMobileNetworkCode();
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
                update call for attribute AntennaInfo
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateAntennaInfo(const CIPtr< CIPtrArray< asi::connectivity::al::AntennaInfo > >& AntennaInfo);

            /*!
            \brief
                update call for attribute DataConnectionInfo
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateDataConnectionInfo(const CIPtr< asi::connectivity::al::DataConnectionInfo >& DataConnectionInfo);

            /*!
            \brief
                update call for attribute SimDataConfig
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateSimDataConfig(const CIPtr< asi::connectivity::al::SimDataConfig >& SimDataConfig);

            /*!
            \brief
                update call for attribute DataConnectionStartResult
            \details
                The value is not copied into the cache (it's defined as uncached)
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateDataConnectionStartResult(const CIPtr< asi::connectivity::al::DataConnectionStartResult >& DataConnectionStartResult);

            /*!
            \brief
                update call for attribute NadDeviceInformation
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateNadDeviceInformation(const CIPtr< asi::connectivity::al::NadDeviceInformation >& NadDeviceInformation);

            /*!
            \brief
                update call for attribute NetworkRejectInformation
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateNetworkRejectInformation(const CIPtr< asi::connectivity::al::NetworkRejectInformation >& NetworkRejectInformation);

            /*!
            \brief
                update call for attribute SimDataInfo
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateSimDataInfo(const CIPtr< asi::connectivity::al::SimDataInfo >& SimDataInfo);

            /*!
            \brief
                update call for attribute TemperatureInfo
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateTemperatureInfo(const CIPtr< asi::connectivity::al::TemperatureInfo >& TemperatureInfo);

            /*!
            \brief
                update call for attribute NetworkInfo
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateNetworkInfo(const CIPtr< asi::connectivity::al::NetworkInfo >& NetworkInfo);

            /*!
            \brief
                update call for attribute AirplaneMode
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateAirplaneMode(const asi::connectivity::al::AirplaneMode AirplaneMode);

            /*!
            \brief
                update call for attribute NadState
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateNadState(const asi::connectivity::al::NadState NadState);

            /*!
            \brief
                update call for attribute JammingState
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateJammingState(const asi::connectivity::al::JammingStatus JammingState);

            /*!
            \brief
                update call for attribute DormantMode
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateDormantMode(const asi::connectivity::al::DormantMode DormantMode);

            /*!
            \brief
                update call for attribute MobileCountryCode
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateMobileCountryCode(const CIPtr< CIString >& MobileCountryCode);

            /*!
            \brief
                update call for attribute MobileNetworkCode
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateMobileNetworkCode(const CIPtr< CIString >& MobileNetworkCode);


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
                This method is realized by the NadInformationServiceSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(NadInformationServiceProxyReply& reply) override final;

            /*!
            \brief
                set notification for one attribute
            \details
                This method is realized by the NadInformationServiceSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(const uint32_t attributeId, NadInformationServiceProxyReply& reply) override final;

            /*!
            \brief
                set notification for a list of attributes
            \details
                This method is realized by the NadInformationServiceSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(const CIPtr< CIUInt32Array >& attributeId, NadInformationServiceProxyReply& reply) override final;

            /*!
            \brief
                remove notification for all attributes
            \details
                This method is realized by the NadInformationServiceSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(NadInformationServiceProxyReply& reply) override final;

            /*!
            \brief
                remove notification for a specific attribute
            \details
                This method is realized by the NadInformationServiceSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(const uint32_t attributeId, NadInformationServiceProxyReply& reply) override final;

            /*!
            \brief
                remove notification for a list of attributes
            \details
                This method is realized by the NadInformationServiceSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(const CIPtr< CIUInt32Array >& attributeId, NadInformationServiceProxyReply& reply) override final;

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
            getter for the attribute AntennaInfo
            getAntennaInfo Method ID: 4
            \details
            This method is realized by the NadInformationServiceSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getAntennaInfo(NadInformationServiceProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute DataConnectionInfo
            getDataConnectionInfo Method ID: 5
            \details
            This method is realized by the NadInformationServiceSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getDataConnectionInfo(NadInformationServiceProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute SimDataConfig
            getSimDataConfig Method ID: 13
            \details
            This method is realized by the NadInformationServiceSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getSimDataConfig(NadInformationServiceProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute NadDeviceInformation
            getNadDeviceInformation Method ID: 9
            \details
            This method is realized by the NadInformationServiceSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getNadDeviceInformation(NadInformationServiceProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute NetworkRejectInformation
            getNetworkRejectInformation Method ID: 12
            \details
            This method is realized by the NadInformationServiceSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getNetworkRejectInformation(NadInformationServiceProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute SimDataInfo
            getSimDataInfo Method ID: 14
            \details
            This method is realized by the NadInformationServiceSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getSimDataInfo(NadInformationServiceProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute TemperatureInfo
            getTemperatureInfo Method ID: 15
            \details
            This method is realized by the NadInformationServiceSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getTemperatureInfo(NadInformationServiceProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute NetworkInfo
            getNetworkInfo Method ID: 11
            \details
            This method is realized by the NadInformationServiceSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getNetworkInfo(NadInformationServiceProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute AirplaneMode
            getAirplaneMode Method ID: 3
            \details
            This method is realized by the NadInformationServiceSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getAirplaneMode(NadInformationServiceProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute NadState
            getNadState Method ID: 10
            \details
            This method is realized by the NadInformationServiceSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getNadState(NadInformationServiceProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute JammingState
            getJammingState Method ID: 8
            \details
            This method is realized by the NadInformationServiceSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getJammingState(NadInformationServiceProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute DormantMode
            getDormantMode Method ID: 7
            \details
            This method is realized by the NadInformationServiceSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getDormantMode(NadInformationServiceProxyReply& reply) override final;


/* #################################  private members ###################### */
        private:
            /*!
            \brief
                container for all attributes and related valid flags
            \details
                it stored on instance of each attribute and a valid flag per attribute
            */
            struct AttributeContainer {
                AttributeContainer() :                    m_AirplaneMode(asi::connectivity::al::AIRPLANE_MODE_OFF),
                    m_NadState(asi::connectivity::al::NAD_OFF),
                    m_JammingState(asi::connectivity::al::JAMMING_STATUS_UNKNOWN),
                    m_DormantMode(asi::connectivity::al::DORMANT_MODE_UNKNOWN),

                    m_AntennaInfo_valid (false),
                    m_DataConnectionInfo_valid (false),
                    m_SimDataConfig_valid (false),
                    m_NadDeviceInformation_valid (false),
                    m_NetworkRejectInformation_valid (false),
                    m_SimDataInfo_valid (false),
                    m_TemperatureInfo_valid (false),
                    m_NetworkInfo_valid (false),
                    m_AirplaneMode_valid (false),
                    m_NadState_valid (false),
                    m_JammingState_valid (false),
                    m_DormantMode_valid (false),
                    m_MobileCountryCode_valid (false),
                    m_MobileNetworkCode_valid (false)
                {}
                    
                AttributeContainer(const AttributeContainer&)=delete;
                AttributeContainer &operator = (const AttributeContainer &)=delete;

                CIPtr< CIPtrArray< asi::connectivity::al::AntennaInfo > > m_AntennaInfo;
                CIPtr< asi::connectivity::al::DataConnectionInfo > m_DataConnectionInfo;
                CIPtr< asi::connectivity::al::SimDataConfig > m_SimDataConfig;
                CIPtr< asi::connectivity::al::NadDeviceInformation > m_NadDeviceInformation;
                CIPtr< asi::connectivity::al::NetworkRejectInformation > m_NetworkRejectInformation;
                CIPtr< asi::connectivity::al::SimDataInfo > m_SimDataInfo;
                CIPtr< asi::connectivity::al::TemperatureInfo > m_TemperatureInfo;
                CIPtr< asi::connectivity::al::NetworkInfo > m_NetworkInfo;
                asi::connectivity::al::AirplaneMode m_AirplaneMode;
                asi::connectivity::al::NadState m_NadState;
                asi::connectivity::al::JammingStatus m_JammingState;
                asi::connectivity::al::DormantMode m_DormantMode;
                CIPtr< CIString > m_MobileCountryCode;
                CIPtr< CIString > m_MobileNetworkCode;
                bool m_AntennaInfo_valid;
                bool m_DataConnectionInfo_valid;
                bool m_SimDataConfig_valid;
                bool m_NadDeviceInformation_valid;
                bool m_NetworkRejectInformation_valid;
                bool m_SimDataInfo_valid;
                bool m_TemperatureInfo_valid;
                bool m_NetworkInfo_valid;
                bool m_AirplaneMode_valid;
                bool m_NadState_valid;
                bool m_JammingState_valid;
                bool m_DormantMode_valid;
                bool m_MobileCountryCode_valid;
                bool m_MobileNetworkCode_valid;
            };
            /*!
            \brief
                send an update of the attribute value from the cache to the given reply proxy
            \param[in] attribute_Id
                related id of the attribute the update shall be send
            \param[in] proxy
                reply proxy to call the related update method
            */
            void sendAttributeUpdate (uint32_t attribute_id, NadInformationServiceProxyReply& proxy, bool lock=true);

            //! the container of all attributes
            AttributeContainer                      m_attributes;
            //! the notification matrix
            comm::AttributeNotificationContainer    m_notifications;
            //! mutex to secure the attribute container
            osal::Mutex                             m_mtx;
    };

} //namespace asi
} //namespace connectivity
} //namespace al
#endif// ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICESATTR_HXX
