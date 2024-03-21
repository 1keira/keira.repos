/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceSAttr_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_INTV2XSTACKSATTR_HXX
#define ASI_SID_V2XSTACK_INTV2XSTACKSATTR_HXX

#include <common/Macros.hxx>
#include <common/types/vector.hxx>
#include <common/types/set.hxx>
#include <osal/Mutex.hxx>
#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/sid/v2xstack/Definitions.hxx>
#include <asi/sid/v2xstack/IntV2XStackS.hxx>

namespace asi
{
namespace sid
{
namespace v2xstack
{

    /*!
    \brief  The v2xstack::IntV2XStack interface on tthe service side.
    \details
            A service instance needs to implement this interface.
    */
    class IntV2XStackSAttr : public IntV2XStackS
    {
        public:
            IntV2XStackSAttr ()
            : m_notifications(ipl::UUID(0x14b60cbe, 0x515f, 0x5af6, 0xb6aa, 0x49, 0x36, 0x77, 0xf0, 0x7d, 0xd9))
            {}

            ~IntV2XStackSAttr() override;

/*
*************************************************************************************************************
*   getter methods for all attributes for the service application
*************************************************************************************************************
*/
            /*!
            \brief getter for attribute ESC50
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::sid::v2xstack::ESC50Struct > getESC50();
            /*!
            \brief getter for attribute EBKV03Auth
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::sid::v2xstack::EBKV03AuthStruct > getEBKV03Auth();
            /*!
            \brief getter for attribute ESC51Auth
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::sid::v2xstack::ESC51AuthStruct > getESC51Auth();
            /*!
            \brief getter for attribute ESP21
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::sid::v2xstack::ESP21Struct > getESP21();
            /*!
            \brief getter for attribute LichtAnf01
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::sid::v2xstack::LichtAnf01Struct > getLichtAnf01();
            /*!
            \brief getter for attribute Lichtvorne01
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::sid::v2xstack::Lichtvorne01Struct > getLichtvorne01();
            /*!
            \brief getter for attribute Blinkmodi02
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::sid::v2xstack::Blinkmodi02Struct > getBlinkmodi02();
            /*!
            \brief getter for attribute VMM02Auth
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::sid::v2xstack::VMM02AuthStruct > getVMM02Auth();
            /*!
            \brief getter for attribute ESP24
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::sid::v2xstack::ESP24Struct > getESP24();
            /*!
            \brief getter for attribute Motor14
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::sid::v2xstack::Motor14Struct > getMotor14();
            /*!
            \brief getter for attribute LWI01
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::sid::v2xstack::LWI01Struct > getLWI01();
            /*!
            \brief getter for attribute Getriebe11
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::sid::v2xstack::Getriebe11Struct > getGetriebe11();
            /*!
            \brief getter for attribute KlemmenStatus01
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::sid::v2xstack::KlemmenStatus01Struct > getKlemmenStatus01();
            /*!
            \brief getter for attribute Personalisierung01
            \details
            can be used by the service application to retrieve the current
            attribute value from the cache
            */
            const CIPtr< asi::sid::v2xstack::Personalisierung01Struct > getPersonalisierung01();
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
                update call for attribute ESC50
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateESC50(const CIPtr< asi::sid::v2xstack::ESC50Struct >& ESC50);

            /*!
            \brief
                update call for attribute EBKV03Auth
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateEBKV03Auth(const CIPtr< asi::sid::v2xstack::EBKV03AuthStruct >& EBKV03Auth);

            /*!
            \brief
                update call for attribute ESC51Auth
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateESC51Auth(const CIPtr< asi::sid::v2xstack::ESC51AuthStruct >& ESC51Auth);

            /*!
            \brief
                update call for attribute ESP21
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateESP21(const CIPtr< asi::sid::v2xstack::ESP21Struct >& ESP21);

            /*!
            \brief
                update call for attribute LichtAnf01
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateLichtAnf01(const CIPtr< asi::sid::v2xstack::LichtAnf01Struct >& LichtAnf01);

            /*!
            \brief
                update call for attribute Lichtvorne01
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateLichtvorne01(const CIPtr< asi::sid::v2xstack::Lichtvorne01Struct >& Lichtvorne01);

            /*!
            \brief
                update call for attribute Blinkmodi02
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateBlinkmodi02(const CIPtr< asi::sid::v2xstack::Blinkmodi02Struct >& Blinkmodi02);

            /*!
            \brief
                update call for attribute VMM02Auth
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateVMM02Auth(const CIPtr< asi::sid::v2xstack::VMM02AuthStruct >& VMM02Auth);

            /*!
            \brief
                update call for attribute ESP24
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateESP24(const CIPtr< asi::sid::v2xstack::ESP24Struct >& ESP24);

            /*!
            \brief
                update call for attribute Motor14
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateMotor14(const CIPtr< asi::sid::v2xstack::Motor14Struct >& Motor14);

            /*!
            \brief
                update call for attribute LWI01
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateLWI01(const CIPtr< asi::sid::v2xstack::LWI01Struct >& LWI01);

            /*!
            \brief
                update call for attribute Getriebe11
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateGetriebe11(const CIPtr< asi::sid::v2xstack::Getriebe11Struct >& Getriebe11);

            /*!
            \brief
                update call for attribute KlemmenStatus01
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updateKlemmenStatus01(const CIPtr< asi::sid::v2xstack::KlemmenStatus01Struct >& KlemmenStatus01);

            /*!
            \brief
                update call for attribute Personalisierung01
            \details
                The value is copied into the cache,
                it's marked as VALID and
                an update is send to all notified clients

            **/
            void updatePersonalisierung01(const CIPtr< asi::sid::v2xstack::Personalisierung01Struct >& Personalisierung01);


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
                This method is realized by the IntV2XStackSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(IntV2XStackProxyReply& reply) override final;

            /*!
            \brief
                set notification for one attribute
            \details
                This method is realized by the IntV2XStackSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(const uint32_t attributeId, IntV2XStackProxyReply& reply) override final;

            /*!
            \brief
                set notification for a list of attributes
            \details
                This method is realized by the IntV2XStackSAttr implementation
                and must not be overwritten by the service application
            */
            void setNotification(const CIPtr< CIUInt32Array >& attributeId, IntV2XStackProxyReply& reply) override final;

            /*!
            \brief
                remove notification for all attributes
            \details
                This method is realized by the IntV2XStackSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(IntV2XStackProxyReply& reply) override final;

            /*!
            \brief
                remove notification for a specific attribute
            \details
                This method is realized by the IntV2XStackSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(const uint32_t attributeId, IntV2XStackProxyReply& reply) override final;

            /*!
            \brief
                remove notification for a list of attributes
            \details
                This method is realized by the IntV2XStackSAttr implementation
                and must not be overwritten by the service application
            */
            void clearNotification(const CIPtr< CIUInt32Array >& attributeId, IntV2XStackProxyReply& reply) override final;

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
            getter for the attribute ESC50
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * ESP_QBit_Gierrate:
         *   * E3_1_1_UNECE: ESC_50.ESP_QBit_Gierrate
         * ESP_QBit_Laengsbeschl:
         *   * E3_1_1_UNECE: ESC_50.ESP_QBit_Laengsbeschl
         * ESP_QBit_Querb:
         *   * E3_1_1_UNECE: ESC_50.ESP_QBit_Querb
         * ESP_Querbeschleunigung:
         *   * E3_1_1_UNECE: ESC_50.ESP_Querbeschleunigung
         * ESP_Eingr_HL:
         *   * E3_1_1_UNECE: ESC_50.ESP_Eingr_HL
         * ESP_Eingr_HR:
         *   * E3_1_1_UNECE: ESC_50.ESP_Eingr_HR
         * ESP_Eingr_VL:
         *   * E3_1_1_UNECE: ESC_50.ESP_Eingr_VL
         * ESP_Eingr_VR:
         *   * E3_1_1_UNECE: ESC_50.ESP_Eingr_VR
         * ESP_Laengsbeschl:
         *   * E3_1_1_UNECE: ESC_50.ESP_Laengsbeschl
         * ESP_Gierrate:
         *   * E3_1_1_UNECE: ESC_50.ESP_Gierrate
         * ESP_VZ_Gierrate:
         *   * E3_1_1_UNECE: ESC_50.ESP_VZ_Gierrate
         * ESP_Notbremsanzeige:
         *   * E3_1_1_UNECE: ESC_50.ESP_Notbremsanzeige
         * ESP_Fahrer_bremst:
         *   * E3_1_1_UNECE: ESC_50.ESP_Fahrer_bremst
         * > ESC50Struct.ESP_QBit_Gierrate_Raw [bool]:
         *   Based on:
         *     * ESP_QBit_Gierrate: QBit der Gierrate. Gesetzt bei Ersatzwert, Init
         *       oder Fehler
         * > ESC50Struct.ESP_QBit_Laengsbeschl_Raw [bool]:
         *   Based on:
         *     * ESP_QBit_Laengsbeschl: QBit der Längsbeschleunigung. Gesetzt bei
         *       Ersatzwert, Init oder Fehler
         * > ESC50Struct.ESP_QBit_Querb_Raw [bool]:
         *   Based on:
         *     * ESP_QBit_Querb: QBit der Querbeschleunigung. Gesetzt bei Ersatzwert,
         *       Init oder Fehler
         * > ESC50Struct.ESP_Querbeschleunigung_Raw [uint8]:
         *   Based on:
         *     * ESP_Querbeschleunigung: Beschleunigungswert in y-Achse  MLB:
         *       Gemessener Wert 0xFF = Fehler (wie bereits im Wertebereich
         *       spezifizert) Bei ESP-Abschaltung durch modellgestützte Überwachung
         *       wird das Signal weiterhin ausgegeben. Im AU64x und AU57x erfolgt die
         *       Bereitstellung der Sensorwerte durch SARA-SG!  MQB: Sensorrohwert
         *       Querbeschleunigung Bei ESP gemessene Größe, bei ABS errechnet
         *       (ungenauer Ersatzwert)
         * > ESC50Struct.ESP_Querbeschleunigung_SignalState [uint64]:
         *   Based on:
         *     * ESP_Querbeschleunigung: Beschleunigungswert in y-Achse  MLB:
         *       Gemessener Wert 0xFF = Fehler (wie bereits im Wertebereich
         *       spezifizert) Bei ESP-Abschaltung durch modellgestützte Überwachung
         *       wird das Signal weiterhin ausgegeben. Im AU64x und AU57x erfolgt die
         *       Bereitstellung der Sensorwerte durch SARA-SG!  MQB: Sensorrohwert
         *       Querbeschleunigung Bei ESP gemessene Größe, bei ABS errechnet
         *       (ungenauer Ersatzwert)
         *   Used Constants:
         *     0: eSignalState_Valid
         *     2: eSignalState_Error
         * > ESC50Struct.ESP_Eingr_HL_Raw [bool]:
         *   Based on:
         *     * ESP_Eingr_HL: wird von QSP und Neigungsanzeige verwendet  Flag wird
         *       vom ESP gesetzt, sobald aufgrund eines ESP-Eingriffs am Rad aktiv
         *       Druck aufgebaut wird. Frühestens mit öffnen des Ventils und spätestens
         *       bei einem Bremsmoment von 100Nm. Flag bleibt solange gesetzt wie ein
         *       Bremsmoment von mehr als 100Nm anliegt. QSP berücksichtigt diese
         *       Information zur Berechnung der eigenen v_ref
         * > ESC50Struct.ESP_Eingr_HR_Raw [bool]:
         *   Based on:
         *     * ESP_Eingr_HR: wird von QSP und Neigungsanzeige verwendet  Flag wird
         *       vom ESP gesetzt, sobald aufgrund eines ESP-Eingriffs am Rad aktiv
         *       Druck aufgebaut wird. Frühestens mit öffnen des Ventils und spätestens
         *       bei einem Bremsmoment von 100Nm. Flag bleibt solange gesetzt wie ein
         *       Bremsmoment von mehr als 100Nm anliegt. QSP berücksichtigt diese
         *       Information zur Berechnung der eigenen v_ref
         * > ESC50Struct.ESP_Eingr_VL_Raw [bool]:
         *   Based on:
         *     * ESP_Eingr_VL: wird von QSP und Neigungsanzeige verwendet  Flag wird
         *       vom ESP gesetzt, sobald aufgrund eines ESP-Eingriffs am Rad aktiv
         *       Druck aufgebaut wird. Frühestens mit öffnen des Ventils und spätestens
         *       bei einem Bremsmoment von 100Nm. Flag bleibt solange gesetzt wie ein
         *       Bremsmoment von mehr als 100Nm anliegt. QSP berücksichtigt diese
         *       Information zur Berechnung der eigenen v_ref
         * > ESC50Struct.ESP_Eingr_VR_Raw [bool]:
         *   Based on:
         *     * ESP_Eingr_VR: wird von QSP und Neigungsanzeige verwendet  Flag wird
         *       vom ESP gesetzt, sobald aufgrund eines ESP-Eingriffs am Rad aktiv
         *       Druck aufgebaut wird. Frühestens mit öffnen des Ventils und spätestens
         *       bei einem Bremsmoment von 100Nm. Flag bleibt solange gesetzt wie ein
         *       Bremsmoment von mehr als 100Nm anliegt. QSP berücksichtigt diese
         *       Information zur Berechnung der eigenen v_ref
         * > ESC50Struct.ESP_Laengsbeschl_Raw [uint16]:
         *   Based on:
         *     * ESP_Laengsbeschl: Beschleunigungswert in x-Achse  MLB: Im AU64x und
         *       AU57x erfolgt die Bereitstellung der Sensorwerte durch SARA-SG! Im
         *       AU64x und AU57x wird bei ESP-Abschaltung durch modellgestützte
         *       Überwachung das Signal weiterhin ausgegeben.  MQB: reines ABS schickt
         *       0x3FE für "nicht vorhanden"
         * > ESC50Struct.ESP_Laengsbeschl_SignalState [uint64]:
         *   Based on:
         *     * ESP_Laengsbeschl: Beschleunigungswert in x-Achse  MLB: Im AU64x und
         *       AU57x erfolgt die Bereitstellung der Sensorwerte durch SARA-SG! Im
         *       AU64x und AU57x wird bei ESP-Abschaltung durch modellgestützte
         *       Überwachung das Signal weiterhin ausgegeben.  MQB: reines ABS schickt
         *       0x3FE für "nicht vorhanden"
         *   Used Constants:
         *     0: eSignalState_Valid
         *     2: eSignalState_Error
         *     11: eSignalState_NotAvailable
         * > ESC50Struct.ESP_Gierrate_Raw [uint16]:
         *   Based on:
         *     * ESP_Gierrate: Winkelgeschwindigkeit um die z-Achse, ESP_VZ_Gierrate &
         *       ESP_QBit_Gierrate beachten !!!  MLB: gemessener Wert tatsächliche
         *       Auflösung Bosch ESP: 0,27 Grad/s  Ab AU64x Auflösung wie die
         *       tatsächliche Skalierung 0,01. Im AU64x und AU57x wird bei ESP-
         *       Abschaltung durch modellgestützte Überwachung das Signal weiterhin
         *       ausgegeben. Signalgüte abhängig vom QBit-Gierrate. Ab AU64x erfolgt
         *       die Bereitstellung der Sensorwerte durch SARA-SG!  MQB: Rohwert der
         *       gemessenen Gierrate
         * > ESC50Struct.ESP_Gierrate_SignalState [uint64]:
         *   Based on:
         *     * ESP_Gierrate: Winkelgeschwindigkeit um die z-Achse, ESP_VZ_Gierrate &
         *       ESP_QBit_Gierrate beachten !!!  MLB: gemessener Wert tatsächliche
         *       Auflösung Bosch ESP: 0,27 Grad/s  Ab AU64x Auflösung wie die
         *       tatsächliche Skalierung 0,01. Im AU64x und AU57x wird bei ESP-
         *       Abschaltung durch modellgestützte Überwachung das Signal weiterhin
         *       ausgegeben. Signalgüte abhängig vom QBit-Gierrate. Ab AU64x erfolgt
         *       die Bereitstellung der Sensorwerte durch SARA-SG!  MQB: Rohwert der
         *       gemessenen Gierrate
         *   Used Constants:
         *     0: eSignalState_Valid
         *     2: eSignalState_Error
         * > ESC50Struct.ESP_VZ_Gierrate_Raw [bool]:
         *   Based on:
         *     * ESP_VZ_Gierrate: Vorzeichen der Gierrate
         * > ESC50Struct.ESP_Notbremsanzeige_Raw [bool]:
         *   Based on:
         *     * ESP_Notbremsanzeige: ABS/ASR oder ESP hat Notbremssituation erkannt.
         *       Weiterführende Informationen im Lastenheft spezifiziert und in der
         *       entsprechenden Fachabteilung zu erfragen
         * > ESC50Struct.ESP_Fahrer_bremst_Raw [bool]:
         *   Based on:
         *     * ESP_Fahrer_bremst: Bit wird gesetzt beim Überschreiten der
         *       Bremsdruckschwelle  Weiterführende Informationen im Lastenheft
         *       spezifiziert und in der entsprechenden Fachabteilung zu erfragen
         * > ESC50Struct.PduState [uint64]:
         *   Based on:
         *     ESP_QBit_Gierrate SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            getESC50 Method ID: 5
            \details
            This method is realized by the IntV2XStackSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getESC50(IntV2XStackProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute EBKV03Auth
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * EBKV_QBit_Fahrer_bremst:
         *   * E3_1_1_UNECE: EBKV_03_Auth.EBKV_QBit_Fahrer_bremst
         * EBKV_Fahrer_bremst:
         *   * E3_1_1_UNECE: EBKV_03_Auth.EBKV_Fahrer_bremst
         * > EBKV03AuthStruct.EBKV_QBit_Fahrer_bremst_Raw [bool]:
         *   Based on:
         *     * EBKV_QBit_Fahrer_bremst:
         * > EBKV03AuthStruct.EBKV_Fahrer_bremst_Raw [bool]:
         *   Based on:
         *     * EBKV_Fahrer_bremst: Fahrer will bremsen (Eintreterkennung). Wird
         *       benötigt, um ACC oder GRA abzuschalten
         * > EBKV03AuthStruct.PduState [uint64]:
         *   Based on:
         *     EBKV_QBit_Fahrer_bremst SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            getEBKV03Auth Method ID: 4
            \details
            This method is realized by the IntV2XStackSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getEBKV03Auth(IntV2XStackProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute ESC51Auth
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * ESP_HR_Bremsmoment:
         *   * E3_1_1_UNECE: ESC_51_Auth.ESP_HR_Bremsmoment
         * ESP_VR_Bremsmoment:
         *   * E3_1_1_UNECE: ESC_51_Auth.ESP_VR_Bremsmoment
         * ESP_VL_Bremsmoment:
         *   * E3_1_1_UNECE: ESC_51_Auth.ESP_VL_Bremsmoment
         * ESP_HL_Bremsmoment:
         *   * E3_1_1_UNECE: ESC_51_Auth.ESP_HL_Bremsmoment
         * > ESC51AuthStruct.ESP_HR_Bremsmoment_Raw [uint8]:
         *   Based on:
         *     * ESP_HR_Bremsmoment: Bremsmoment HR Ausgabe nach LAH: Ausgabe der
         *       internen Radbremsmomente / Radbremsdrücke / durch das ESP
         * > ESC51AuthStruct.ESP_HR_Bremsmoment_SignalState [uint64]:
         *   Based on:
         *     * ESP_HR_Bremsmoment: Bremsmoment HR Ausgabe nach LAH: Ausgabe der
         *       internen Radbremsmomente / Radbremsdrücke / durch das ESP
         *   Used Constants:
         *     0: eSignalState_Valid
         *     1: eSignalState_Init
         *     2: eSignalState_Error
         * > ESC51AuthStruct.ESP_VR_Bremsmoment_Raw [uint8]:
         *   Based on:
         *     * ESP_VR_Bremsmoment: Bremsmoment VR Ausgabe nach LAH: Ausgabe der
         *       internen Radbremsmomente / Radbremsdrücke / durch das ESP
         * > ESC51AuthStruct.ESP_VR_Bremsmoment_SignalState [uint64]:
         *   Based on:
         *     * ESP_VR_Bremsmoment: Bremsmoment VR Ausgabe nach LAH: Ausgabe der
         *       internen Radbremsmomente / Radbremsdrücke / durch das ESP
         *   Used Constants:
         *     0: eSignalState_Valid
         *     1: eSignalState_Init
         *     2: eSignalState_Error
         * > ESC51AuthStruct.ESP_VL_Bremsmoment_Raw [uint8]:
         *   Based on:
         *     * ESP_VL_Bremsmoment: Bremsmoment VL Ausgabe nach LAH: Ausgabe der
         *       internen Radbremsmomente / Radbremsdrücke / durch das ESP
         * > ESC51AuthStruct.ESP_VL_Bremsmoment_SignalState [uint64]:
         *   Based on:
         *     * ESP_VL_Bremsmoment: Bremsmoment VL Ausgabe nach LAH: Ausgabe der
         *       internen Radbremsmomente / Radbremsdrücke / durch das ESP
         *   Used Constants:
         *     0: eSignalState_Valid
         *     1: eSignalState_Init
         *     2: eSignalState_Error
         * > ESC51AuthStruct.ESP_HL_Bremsmoment_Raw [uint8]:
         *   Based on:
         *     * ESP_HL_Bremsmoment: Bremsmoment HL Ausgabe nach LAH: Ausgabe der
         *       internen Radbremsmomente / Radbremsdrücke / durch das ESP
         * > ESC51AuthStruct.ESP_HL_Bremsmoment_SignalState [uint64]:
         *   Based on:
         *     * ESP_HL_Bremsmoment: Bremsmoment HL Ausgabe nach LAH: Ausgabe der
         *       internen Radbremsmomente / Radbremsdrücke / durch das ESP
         *   Used Constants:
         *     0: eSignalState_Valid
         *     1: eSignalState_Init
         *     2: eSignalState_Error
         * > ESC51AuthStruct.PduState [uint64]:
         *   Based on:
         *     ESP_HR_Bremsmoment SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            getESC51Auth Method ID: 6
            \details
            This method is realized by the IntV2XStackSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getESC51Auth(IntV2XStackProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute ESP21
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * ESP_v_Signal:
         *   * E3_1_1_UNECE: ESP_21.ESP_v_Signal
         * ASR_Tastung_passiv:
         *   * E3_1_1_UNECE: ESP_21.ASR_Tastung_passiv
         * ESP_Tastung_passiv:
         *   * E3_1_1_UNECE: ESP_21.ESP_Tastung_passiv
         * ESP_Systemstatus:
         *   * E3_1_1_UNECE: ESP_21.ESP_Systemstatus
         * ESP_QBit_v_Signal:
         *   * E3_1_1_UNECE: ESP_21.ESP_QBit_v_Signal
         * ABS_Bremsung:
         *   * E3_1_1_UNECE: ESP_21.ABS_Bremsung
         * ASR_Anf:
         *   * E3_1_1_UNECE: ESP_21.ASR_Anf
         * EDS_Eingriff:
         *   * E3_1_1_UNECE: ESP_21.EDS_Eingriff
         * ESP_Eingriff:
         *   * E3_1_1_UNECE: ESP_21.ESP_Eingriff
         * > ESP21Struct.ESP_v_Signal_Raw [uint16]:
         *   Based on:
         *     * ESP_v_Signal: Geschwindigkeitssignal vom ABS/ASR oder ESP. Mittelwert
         *       der angetriebenen Räder. Bei MSR oder ABS Eingriffen wird die ABS-
         *       Referenzgeschwindigkeit für >= 200ms eingespiegelt (Zeit wird mit
         *       Aktiv-Flanke der Funktionsbits getriggert)  MQB: Bei Frontantrieb und
         *       gesteuertem Allrad (Haldex) Mittelwert der Vorderräder
         * > ESP21Struct.ESP_v_Signal_SignalState [uint64]:
         *   Based on:
         *     * ESP_v_Signal: Geschwindigkeitssignal vom ABS/ASR oder ESP. Mittelwert
         *       der angetriebenen Räder. Bei MSR oder ABS Eingriffen wird die ABS-
         *       Referenzgeschwindigkeit für >= 200ms eingespiegelt (Zeit wird mit
         *       Aktiv-Flanke der Funktionsbits getriggert)  MQB: Bei Frontantrieb und
         *       gesteuertem Allrad (Haldex) Mittelwert der Vorderräder
         *   Used Constants:
         *     0: eSignalState_Valid
         *     1: eSignalState_Init
         *     2: eSignalState_Error
         *     26: eSignalState_Undervoltage
         * > ESP21Struct.ASR_Tastung_passiv_Raw [bool]:
         *   Based on:
         *     * ASR_Tastung_passiv: ASR deaktiviert oder Schwellen geändert
         *       (projektabhängig) Weiterführende Informationen im Lastenheft
         *       spezifiziert und in der entsprechenden Fachabteilung zu erfragen
         * > ESP21Struct.ESP_Tastung_passiv_Raw [bool]:
         *   Based on:
         *     * ESP_Tastung_passiv: ESP deaktiviert oder Schwellen geändert
         *       (projektabhängig) Weiterführende Informationen im Lastenheft
         *       spezifiziert und in der entsprechenden Fachabteilung zu erfragen
         * > ESP21Struct.ESP_Systemstatus_Raw [bool]:
         *   Based on:
         *     * ESP_Systemstatus: Fehler steht für Stillegung ESP mit Fehlereintrag.
         *       MLB: Flag wird bei Unterspannung im Stand bis einmalig 6km/h (AU48x)
         *       oder 10 km/h (AU641, AU57x) überschritten nicht gesetzt (Ausblendung
         *       Startvorgang) Im AU64x, AU57x gilt ESP D4 Funktionsanforderungen
         *       (DOORS-Modul)
         * > ESP21Struct.ESP_QBit_v_Signal_Raw [bool]:
         *   Based on:
         *     * ESP_QBit_v_Signal: Geschwindigkeit wird vom ABS/ASR oder ESP aus
         *       Ersatzwerten errechnet, wenn Bit gesetzt ist. Güte des Signals ist
         *       verändert
         * > ESP21Struct.ABS_Bremsung_Raw [bool]:
         *   Based on:
         *     * ABS_Bremsung: Antiblockiersystem, Bit zeigt auch Druckabbau an (z.B.
         *       ESP hat zuviel Druck aufgebaut oder ungebremste Regelung auf
         *       Bahnübergang) Weiterführende Informationen im Lastenheft spezifiziert
         *       und in der entsprechenden Fachabteilung zu erfragen
         * > ESP21Struct.ASR_Anf_Raw [bool]:
         *   Based on:
         *     * ASR_Anf: MLB: Die Momentenanforderung "ASR_MSR_Moment_schnell" und
         *       "ASR_Moment_langsam" sind auszuführen MQB: Die Momentenanforderung
         *       "BR_Eingriffsmoment" ist auszuführen
         * > ESP21Struct.EDS_Eingriff_Raw [bool]:
         *   Based on:
         *     * EDS_Eingriff: Elektronische Differentialsperre
         * > ESP21Struct.ESP_Eingriff_Raw [bool]:
         *   Based on:
         *     * ESP_Eingriff: Eingriff des Fahrdynamikreglers
         * > ESP21Struct.PduState [uint64]:
         *   Based on:
         *     ESP_v_Signal SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            getESP21 Method ID: 7
            \details
            This method is realized by the IntV2XStackSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getESP21(IntV2XStackProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute LichtAnf01
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * BCM1_Nebellicht_Anf:
         *   * E3_1_1_UNECE: Licht_Anf_01.BCM1_Nebellicht_Anf
         * BCM1_Parklicht_li_Anf:
         *   * E3_1_1_UNECE: Licht_Anf_01.BCM1_Parklicht_li_Anf
         * BCM1_Parklicht_re_Anf:
         *   * E3_1_1_UNECE: Licht_Anf_01.BCM1_Parklicht_re_Anf
         * BCM1_Nebelschluss_Fzg_Anf:
         *   * E3_1_1_UNECE: Licht_Anf_01.BCM1_Nebelschluss_Fzg_Anf
         * BCM1_Tagfahrlicht_Anf:
         *   * E3_1_1_UNECE: Licht_Anf_01.BCM1_Tagfahrlicht_Anf
         * BCM1_Abblendlicht_Anf:
         *   * E3_1_1_UNECE: Licht_Anf_01.BCM1_Abblendlicht_Anf
         * BCM1_Fernlicht_Anf:
         *   * E3_1_1_UNECE: Licht_Anf_01.BCM1_Fernlicht_Anf
         * > LichtAnf01Struct.BCM1_Nebellicht_Anf_Raw [bool]:
         *   Based on:
         *     * BCM1_Nebellicht_Anf: Anforderung Nebellicht
         * > LichtAnf01Struct.BCM1_Parklicht_li_Anf_Raw [bool]:
         *   Based on:
         *     * BCM1_Parklicht_li_Anf: Anforderung: Parklicht links (Sollzustand)
         * > LichtAnf01Struct.BCM1_Parklicht_re_Anf_Raw [bool]:
         *   Based on:
         *     * BCM1_Parklicht_re_Anf: Anforderung: Parklicht rechts (Sollzustand)
         * > LichtAnf01Struct.BCM1_Nebelschluss_Fzg_Anf_Raw [bool]:
         *   Based on:
         *     * BCM1_Nebelschluss_Fzg_Anf: Anforderung: Nebelschlusslicht Fahrzeug
         *       (Sollzustand)
         * > LichtAnf01Struct.BCM1_Tagfahrlicht_Anf_Raw [bool]:
         *   Based on:
         *     * BCM1_Tagfahrlicht_Anf: Anforderung: Tagfahrlicht (Sollzustand)
         * > LichtAnf01Struct.BCM1_Abblendlicht_Anf_Raw [bool]:
         *   Based on:
         *     * BCM1_Abblendlicht_Anf: Anforderung Abblendlicht
         * > LichtAnf01Struct.BCM1_Fernlicht_Anf_Raw [bool]:
         *   Based on:
         *     * BCM1_Fernlicht_Anf: Anforderung Fernlicht
         * > LichtAnf01Struct.PduState [uint64]:
         *   Based on:
         *     BCM1_Nebellicht_Anf SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            getLichtAnf01 Method ID: 12
            \details
            This method is realized by the IntV2XStackSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getLichtAnf01(IntV2XStackProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute Lichtvorne01
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * LV_AFL_aktiv_Anzeige:
         *   * E3_1_1_UNECE: Licht_vorne_01.LV_AFL_aktiv_Anzeige
         * > Lichtvorne01Struct.LV_AFL_aktiv_Anzeige_Raw [bool]:
         *   Based on:
         *     * LV_AFL_aktiv_Anzeige: Anzeige AFL-Funktion
         * > Lichtvorne01Struct.PduState [uint64]:
         *   Based on:
         *     LV_AFL_aktiv_Anzeige SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            getLichtvorne01 Method ID: 13
            \details
            This method is realized by the IntV2XStackSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getLichtvorne01(IntV2XStackProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute Blinkmodi02
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * BM_Warnblinken:
         *   * E3_1_1_UNECE: Blinkmodi_02.BM_Warnblinken
         * BM_links:
         *   * E3_1_1_UNECE: Blinkmodi_02.BM_links
         * BM_rechts:
         *   * E3_1_1_UNECE: Blinkmodi_02.BM_rechts
         * > Blinkmodi02Struct.BM_Warnblinken_Raw [bool]:
         *   Based on:
         *     * BM_Warnblinken: Warnblinken
         * > Blinkmodi02Struct.BM_links_Raw [bool]:
         *   Based on:
         *     * BM_links: Richtungsblinken links
         * > Blinkmodi02Struct.BM_rechts_Raw [bool]:
         *   Based on:
         *     * BM_rechts: Richtungsblinken rechts
         * > Blinkmodi02Struct.PduState [uint64]:
         *   Based on:
         *     BM_Warnblinken SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            getBlinkmodi02 Method ID: 3
            \details
            This method is realized by the IntV2XStackSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getBlinkmodi02(IntV2XStackProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute VMM02Auth
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * HMS_aktives_System:
         *   * E3_1_1_UNECE: VMM_02_Auth.HMS_aktives_System
         * > VMM02AuthStruct.HMS_aktives_System_Raw [uint8]:
         *   Based on:
         *     * HMS_aktives_System: Zeigt an, von welchem System die Anforderung
         *       gerade umgesetzt wird
         * > VMM02AuthStruct.PduState [uint64]:
         *   Based on:
         *     HMS_aktives_System SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            getVMM02Auth Method ID: 16
            \details
            This method is realized by the IntV2XStackSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getVMM02Auth(IntV2XStackProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute ESP24
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * ESP_Lampe:
         *   * E3_1_1_UNECE: ESP_24.ESP_Lampe
         * ABS_Lampe:
         *   * E3_1_1_UNECE: ESP_24.ABS_Lampe
         * BK_Lampe_02:
         *   * E3_1_1_UNECE: ESP_24.BK_Lampe_02
         * > ESP24Struct.ESP_Lampe_Raw [bool]:
         *   Based on:
         *     * ESP_Lampe: Zustand der Fahrdynamikregelungslampe (MLB: ASR und/oder
         *       ESP, MQB: nur ESP)  Weiterführende Informationen im Lastenheft
         *       spezifiziert und in der entsprechenden Fachabteilung zu erfragen
         * > ESP24Struct.ABS_Lampe_Raw [bool]:
         *   Based on:
         *     * ABS_Lampe: Sicherheitswarnlampe  Weiterführende Informationen im
         *       Lastenheft spezifiziert und in der entsprechenden Fachabteilung zu
         *       erfragen
         * > ESP24Struct.BK_Lampe_02_Raw [uint8]:
         *   Based on:
         *     * BK_Lampe_02: Typ1_ein_statisch signalisiert EBV-Ausfall MQB: wird auch
         *       bei HBV-Ausfall verwendet.  Typ1_ein_statisch: wird bei AUDI für
         *       Aktivierung der roten BKL ohne Text und Akustik verwendet (z.B.
         *       Lampenaufprüfung). Typ2_ein_statisch: signalisiert elektrischen Fehler
         *       ohne Ausfall HBV oder EBV  Weiterführende Informationen im Lastenheft
         *       spezifiziert und in der entsprechenden Fachabteilung zu erfragen
         * > ESP24Struct.PduState [uint64]:
         *   Based on:
         *     ESP_Lampe SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            getESP24 Method ID: 8
            \details
            This method is realized by the IntV2XStackSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getESP24(IntV2XStackProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute Motor14
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * MO_Fahrer_bremst:
         *   * E3_1_1_UNECE: Motor_14.MO_Fahrer_bremst
         * MO_QBit_Fahrer_bremst:
         *   * E3_1_1_UNECE: Motor_14.MO_QBit_Fahrer_bremst
         * > Motor14Struct.MO_Fahrer_bremst_Raw [bool]:
         *   Based on:
         *     * MO_Fahrer_bremst: Redundante Bremsinformation vom Motor.  MLB: AUDI
         *       D4: Zykluszeit: 10ms (siehe Zykluszeit schnell/Cycletime Fast) Im AUDI
         *       B8 wird in diesem Bit der Wert der ESP-CAN-Information
         *       "ESP_Fahrer_bremst" ausgegeben.  Achtung: Reduktion der Zykluszeit
         *       Motor_03 auf 10ms geplant. Projektabhängig soll künftig mit 10ms
         *       gesendet werden. Empfänger die in weiteren Konzern-Projekten
         *       eingesetzt werden müssen dazu beide Zykluszeiten (10/20ms)
         *       unterstützen. Empfänger muss in diesem Fall für die Timeoutdiagnose
         *       und CAN-Messwerteblöcke mit 20ms auslegen
         * > Motor14Struct.MO_QBit_Fahrer_bremst_Raw [bool]:
         *   Based on:
         *     * MO_QBit_Fahrer_bremst: MLB: AUDI D4: Zykluszeit: 10ms (siehe
         *       Zykluszeit schnell/Cycletime Fast)  Achtung: Reduktion der Zykluszeit
         *       Motor_03 auf 10ms geplant. Projektabhängig soll künftig mit 10ms
         *       gesendet werden. Empfänger die in weiteren Konzern-Projekten
         *       eingesetzt werden müssen dazu beide Zykluszeiten (10/20ms)
         *       unterstützen. Empfänger muss in diesem Fall für die Timeoutdiagnose
         *       und CAN-Messwerteblöcke mit 20ms auslegen
         * > Motor14Struct.PduState [uint64]:
         *   Based on:
         *     MO_Fahrer_bremst SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            getMotor14 Method ID: 14
            \details
            This method is realized by the IntV2XStackSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getMotor14(IntV2XStackProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute LWI01
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * LWI_Lenkradwinkel:
         *   * E3_1_1_UNECE: LWI_01.LWI_Lenkradwinkel
         * LWI_VZ_Lenkradwinkel:
         *   * E3_1_1_UNECE: LWI_01.LWI_VZ_Lenkradwinkel
         * LWI_QBit_Lenkradwinkel:
         *   * E3_1_1_UNECE: LWI_01.LWI_QBit_Lenkradwinkel
         * > LWI01Struct.LWI_Lenkradwinkel_Raw [uint16]:
         *   Based on:
         *     * LWI_Lenkradwinkel: Wertebereich = +/- 800 Grad Auflösung = 0,1 Grad
         *       ACHTUNG: spezifizierte Interne Auflösung des Sensors beträgt aber nur
         *       Schrittweite 0,5 Grad!  Hinweis: MLB: Zusätzlich gestellte Winkel bei
         *       Dynamiklenkung beachten ! MQB: Nicht konstante Lenkübersetzung bei
         *       Progressivlenkung beachten. Signal bei Progressivlenkung auf den
         *       Lenkhub bezogen
         * > LWI01Struct.LWI_Lenkradwinkel_SignalState [uint64]:
         *   Based on:
         *     * LWI_Lenkradwinkel: Wertebereich = +/- 800 Grad Auflösung = 0,1 Grad
         *       ACHTUNG: spezifizierte Interne Auflösung des Sensors beträgt aber nur
         *       Schrittweite 0,5 Grad!  Hinweis: MLB: Zusätzlich gestellte Winkel bei
         *       Dynamiklenkung beachten ! MQB: Nicht konstante Lenkübersetzung bei
         *       Progressivlenkung beachten. Signal bei Progressivlenkung auf den
         *       Lenkhub bezogen
         *   Used Constants:
         *     0: eSignalState_Valid
         *     1: eSignalState_Init
         *     2: eSignalState_Error
         * > LWI01Struct.LWI_VZ_Lenkradwinkel_Raw [bool]:
         *   Based on:
         *     * LWI_VZ_Lenkradwinkel: Vorzeichen Lenkradwinkel gemäss DIN70000;
         *       Nullstellung = +0
         * > LWI01Struct.LWI_QBit_Lenkradwinkel_Raw [bool]:
         *   Based on:
         *     * LWI_QBit_Lenkradwinkel: Das QBit wird auch bei nicht abgeglichenem
         *       Lenkradwinkelsensor gesetzt
         * > LWI01Struct.PduState [uint64]:
         *   Based on:
         *     LWI_Lenkradwinkel SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            getLWI01 Method ID: 11
            \details
            This method is realized by the IntV2XStackSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getLWI01(IntV2XStackProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute Getriebe11
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * GE_Fahrstufe:
         *   * E3_1_1_UNECE: Getriebe_11.GE_Fahrstufe
         * > Getriebe11Struct.GE_Fahrstufe_Raw [uint8]:
         *   Based on:
         *     * GE_Fahrstufe: Fahrprogramm des Getriebes  Hinweis: Zwischenstellung
         *       "0x0" darf nur für Zustandswechsel P/R, R/N, N/D ausgegeben werden,
         *       nicht für D/S oder D/Tippgasse wegen Abschaltkriterium GRA/ACC
         * > Getriebe11Struct.PduState [uint64]:
         *   Based on:
         *     GE_Fahrstufe SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            getGetriebe11 Method ID: 9
            \details
            This method is realized by the IntV2XStackSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getGetriebe11(IntV2XStackProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute KlemmenStatus01
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * ZAS_Kl_15:
         *   * E3_1_1_UNECE: Klemmen_Status_01.ZAS_Kl_15
         * > KlemmenStatus01Struct.ZAS_Kl_15_Raw [bool]:
         *   Based on:
         *     * ZAS_Kl_15: Klemme 15: Zuendung (SW-Kl.15)
         * > KlemmenStatus01Struct.PduState [uint64]:
         *   Based on:
         *     ZAS_Kl_15 SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            getKlemmenStatus01 Method ID: 10
            \details
            This method is realized by the IntV2XStackSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getKlemmenStatus01(IntV2XStackProxyReply& reply) override final;

            /*!
            \brief
            getter for the attribute Personalisierung01
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * Perso_Steuerung:
         *   * E3_1_1_UNECE: Personalisierung_01.Perso_Steuerung
         * Perso_Steuerungsparameter:
         *   * E3_1_1_UNECE: Personalisierung_01.Perso_Steuerungsparameter
         * Perso_Status:
         *   * E3_1_1_UNECE: Personalisierung_01.Perso_Status
         * Perso_Kontonummer:
         *   * E3_1_1_UNECE: Personalisierung_01.Perso_Kontonummer
         * > Personalisierung01Struct.Perso_Steuerung_Raw [uint8]:
         *   Based on:
         *     * Perso_Steuerung: Signal gibt einen Steuerungsbefehl an die
         *       Funktionsteilnehmer der Personalisierung. Nicht für AU736 und AU49x
         * > Personalisierung01Struct.Perso_Steuerungsparameter_Raw [uint8]:
         *   Based on:
         *     * Perso_Steuerungsparameter: Signal gibt einen Parameter zum
         *       Steuerungsbefehl (Signal Perso_Steuerung) für die Personalisierung an.
         *       Nicht für AU736 und AU49x
         * > Personalisierung01Struct.Perso_Status_Raw [uint8]:
         *   Based on:
         *     * Perso_Status: Codierstatus der Personalisierung Nicht für AU736 und
         *       AU49x
         * > Personalisierung01Struct.Perso_Kontonummer_Raw [uint8]:
         *   Based on:
         *     * Perso_Kontonummer: Signal gibt die jewels aktuelle Kontonummer für die
         *       Personalisierung an. Nicht für AU736 und AU48x
         * > Personalisierung01Struct.PduState [uint64]:
         *   Based on:
         *     Perso_Steuerung SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            getPersonalisierung01 Method ID: 15
            \details
            This method is realized by the IntV2XStackSAttr implementation
            and must not be overwritten by the service application.
            The request is answered out from the cache and the service application
            is not informed
            */
            void getPersonalisierung01(IntV2XStackProxyReply& reply) override final;


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
                    m_ESC50_valid (false),
                    m_EBKV03Auth_valid (false),
                    m_ESC51Auth_valid (false),
                    m_ESP21_valid (false),
                    m_LichtAnf01_valid (false),
                    m_Lichtvorne01_valid (false),
                    m_Blinkmodi02_valid (false),
                    m_VMM02Auth_valid (false),
                    m_ESP24_valid (false),
                    m_Motor14_valid (false),
                    m_LWI01_valid (false),
                    m_Getriebe11_valid (false),
                    m_KlemmenStatus01_valid (false),
                    m_Personalisierung01_valid (false)
                {}
                    
                AttributeContainer(const AttributeContainer&)=delete;
                AttributeContainer &operator = (const AttributeContainer &)=delete;

                CIPtr< asi::sid::v2xstack::ESC50Struct > m_ESC50;
                CIPtr< asi::sid::v2xstack::EBKV03AuthStruct > m_EBKV03Auth;
                CIPtr< asi::sid::v2xstack::ESC51AuthStruct > m_ESC51Auth;
                CIPtr< asi::sid::v2xstack::ESP21Struct > m_ESP21;
                CIPtr< asi::sid::v2xstack::LichtAnf01Struct > m_LichtAnf01;
                CIPtr< asi::sid::v2xstack::Lichtvorne01Struct > m_Lichtvorne01;
                CIPtr< asi::sid::v2xstack::Blinkmodi02Struct > m_Blinkmodi02;
                CIPtr< asi::sid::v2xstack::VMM02AuthStruct > m_VMM02Auth;
                CIPtr< asi::sid::v2xstack::ESP24Struct > m_ESP24;
                CIPtr< asi::sid::v2xstack::Motor14Struct > m_Motor14;
                CIPtr< asi::sid::v2xstack::LWI01Struct > m_LWI01;
                CIPtr< asi::sid::v2xstack::Getriebe11Struct > m_Getriebe11;
                CIPtr< asi::sid::v2xstack::KlemmenStatus01Struct > m_KlemmenStatus01;
                CIPtr< asi::sid::v2xstack::Personalisierung01Struct > m_Personalisierung01;
                bool m_ESC50_valid;
                bool m_EBKV03Auth_valid;
                bool m_ESC51Auth_valid;
                bool m_ESP21_valid;
                bool m_LichtAnf01_valid;
                bool m_Lichtvorne01_valid;
                bool m_Blinkmodi02_valid;
                bool m_VMM02Auth_valid;
                bool m_ESP24_valid;
                bool m_Motor14_valid;
                bool m_LWI01_valid;
                bool m_Getriebe11_valid;
                bool m_KlemmenStatus01_valid;
                bool m_Personalisierung01_valid;
            };
            /*!
            \brief
                send an update of the attribute value from the cache to the given reply proxy
            \param[in] attribute_Id
                related id of the attribute the update shall be send
            \param[in] proxy
                reply proxy to call the related update method
            */
            void sendAttributeUpdate (uint32_t attribute_id, IntV2XStackProxyReply& proxy, bool lock=true);

            //! the container of all attributes
            AttributeContainer                      m_attributes;
            //! the notification matrix
            comm::AttributeNotificationContainer    m_notifications;
            //! mutex to secure the attribute container
            osal::Mutex                             m_mtx;
    };

} //namespace asi
} //namespace sid
} //namespace v2xstack
#endif// ASI_SID_V2XSTACK_INTV2XSTACKSATTR_HXX
