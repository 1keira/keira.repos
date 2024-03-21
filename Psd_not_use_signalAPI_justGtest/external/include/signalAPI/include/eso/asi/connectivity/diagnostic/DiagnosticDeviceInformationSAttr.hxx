/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceSAttr_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATIONSATTR_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATIONSATTR_HXX

#include <common/Macros.hxx>
#include <common/types/vector.hxx>
#include <common/types/set.hxx>
#include <osal/Mutex.hxx>
#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>
#include <asi/connectivity/diagnostic/DiagnosticDeviceInformationS.hxx>

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /*!
    \brief  The diagnostic::DiagnosticDeviceInformation interface on tthe service side.
    \details
            A service instance needs to implement this interface.
    */
    class DiagnosticDeviceInformationSAttr : public DiagnosticDeviceInformationS
    {
        public:
            DiagnosticDeviceInformationSAttr ()
            : m_notifications(ipl::UUID(0xbf16aad9, 0x5d12, 0x4dea, 0x9cef, 0xb5, 0xdf, 0xfe, 0x37, 0x02, 0x80))
            {}

            ~DiagnosticDeviceInformationSAttr() override;

/*
*************************************************************************************************************
*   getter methods for all attributes for the service application
*************************************************************************************************************
*/
            /*!
            \brief getter for attribute OverallSoftwareVersion
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< CIString > getOverallSoftwareVersion();
            /*!
            \brief getter for attribute CompanionSoftwareVersion
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< CIString > getCompanionSoftwareVersion();
            /*!
            \brief getter for attribute HardwareVersion
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< CIString > getHardwareVersion();
            /*!
            \brief getter for attribute SerialNumber
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< CIString > getSerialNumber();
            /*!
            \brief getter for attribute SparePartNumber
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< CIString > getSparePartNumber();
            /*!
            \brief getter for attribute HardwarePartNumber
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< CIString > getHardwarePartNumber();
            /*!
            \brief getter for attribute HardwareVariant
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            uint16_t getHardwareVariant();
            /*!
            \brief getter for attribute AssemblyInformation
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            uint32_t getAssemblyInformation();
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
                update call for attribute OverallSoftwareVersion
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateOverallSoftwareVersion(const CIPtr< CIString >& OverallSoftwareVersion);

            /*!
            \brief
                update call for attribute CompanionSoftwareVersion
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateCompanionSoftwareVersion(const CIPtr< CIString >& CompanionSoftwareVersion);

            /*!
            \brief
                update call for attribute HardwareVersion
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateHardwareVersion(const CIPtr< CIString >& HardwareVersion);

            /*!
            \brief
                update call for attribute SerialNumber
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateSerialNumber(const CIPtr< CIString >& SerialNumber);

            /*!
            \brief
                update call for attribute SparePartNumber
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateSparePartNumber(const CIPtr< CIString >& SparePartNumber);

            /*!
            \brief
                update call for attribute HardwarePartNumber
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateHardwarePartNumber(const CIPtr< CIString >& HardwarePartNumber);

            /*!
            \brief
                update call for attribute HardwareVariant
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateHardwareVariant(const uint16_t HardwareVariant);

            /*!
            \brief
                update call for attribute AssemblyInformation
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateAssemblyInformation(const uint32_t AssemblyInformation);


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
                This method is realized by the DiagnosticDeviceInformationSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(DiagnosticDeviceInformationProxyReply& reply) override final;

            /*!
            \brief
                set notification for one attribute
            \details
                This method is realized by the DiagnosticDeviceInformationSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(const uint32_t attributeId, DiagnosticDeviceInformationProxyReply& reply) override final;

            /*!
            \brief
                set notification for a list of attributes
            \details
                This method is realized by the DiagnosticDeviceInformationSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(const CIPtr< CIUInt32Array >& attributeId, DiagnosticDeviceInformationProxyReply& reply) override final;

            /*!
            \brief
                remove notification for all attributes
            \details
                This method is realized by the DiagnosticDeviceInformationSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(DiagnosticDeviceInformationProxyReply& reply) override final;

            /*!
            \brief
                remove notification for a specific attribute
            \details
                This method is realized by the DiagnosticDeviceInformationSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(const uint32_t attributeId, DiagnosticDeviceInformationProxyReply& reply) override final;

            /*!
            \brief
                remove notification for a list of attributes
            \details
                This method is realized by the DiagnosticDeviceInformationSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(const CIPtr< CIUInt32Array >& attributeId, DiagnosticDeviceInformationProxyReply& reply) override final;

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

/* #################################  private members ###################### */
        private:
            /*!
            \brief
                container for all attributes and related valid flags
            \details
                it stored on instance of each attribute and a valid flag per attribute
            */
            struct AttributeContainer {
                AttributeContainer() :                    m_HardwareVariant(),
                    m_AssemblyInformation(),

                    m_OverallSoftwareVersion_valid (false),
                    m_CompanionSoftwareVersion_valid (false),
                    m_HardwareVersion_valid (false),
                    m_SerialNumber_valid (false),
                    m_SparePartNumber_valid (false),
                    m_HardwarePartNumber_valid (false),
                    m_HardwareVariant_valid (false),
                    m_AssemblyInformation_valid (false)
                {}
                    
                AttributeContainer(const AttributeContainer&)=delete;
                AttributeContainer &operator = (const AttributeContainer &)=delete;

                CIPtr< CIString > m_OverallSoftwareVersion;
                CIPtr< CIString > m_CompanionSoftwareVersion;
                CIPtr< CIString > m_HardwareVersion;
                CIPtr< CIString > m_SerialNumber;
                CIPtr< CIString > m_SparePartNumber;
                CIPtr< CIString > m_HardwarePartNumber;
                uint16_t m_HardwareVariant;
                uint32_t m_AssemblyInformation;
                bool m_OverallSoftwareVersion_valid;
                bool m_CompanionSoftwareVersion_valid;
                bool m_HardwareVersion_valid;
                bool m_SerialNumber_valid;
                bool m_SparePartNumber_valid;
                bool m_HardwarePartNumber_valid;
                bool m_HardwareVariant_valid;
                bool m_AssemblyInformation_valid;
            };
            /*!
            \brief
                send an update of the attribute value from the cache to the given reply proxy
            \param[in] attribute_Id
                related id of the attribute the update shall be send
            \param[in] proxy
                reply proxy to call the related update method
            */
            void sendAttributeUpdate (uint32_t attribute_id, DiagnosticDeviceInformationProxyReply& proxy, bool lock=true);

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
#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATIONSATTR_HXX
