/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceReply_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_INTLHWAPPREPLY_CSTYLE_HXX
#define ASI_SID_LHWAPP_INTLHWAPPREPLY_CSTYLE_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/sid/lhwapp/cstyle/StructAirbag01Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructBlinkmodi02Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructDaempfer01Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructESC50Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructESP21Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructESP24Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructESP30Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructHVK01Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructMotor18Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructMotor41Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructPOSGNSSDR01Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructPSD04Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructPSD05Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructPSD06Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructRKA01Struct.hxx>
#include <asi/sid/lhwapp/cstyle/Definitions.hxx>

namespace asi
{
namespace sid
{
namespace lhwapp
{
namespace cstyle
{

    /**
    \brief  Declaration of the reply interface, which must be implemented by any user of this interface
    **/
    class IntLHWAppReply {

    public:
    // List of reply methods
            /**
            \brief
            reply for the attribute Airbag01
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * AB_Crash_Int:
         *   * E3_1_1_UNECE: Airbag_01.AB_Crash_Int
         * > Airbag01Struct.AB_Crash_Int_Raw [uint8]:
         *   Based on:
         *     * AB_Crash_Int: Crash_Intensität_1 = fahrzeugabhängige Reaktionen im
         *       Crash Crash_Intensität_2 = fahrzeugabhängige Reaktionen im Crash
         *       Crash_Intensität_3 = fahrzeugabhängige Reaktionen im Crash  Die
         *       jeweiligen fahrzeugabhängigen Reaktionen im Crash sind in einem
         *       separaten Doors Modul im Airbag-SG beschrieben.  Die Information
         *       bleibt bei jeder Schwellwert-überschreitung für ~10 s bestehen
         *       (Achtung: Energiereserve bei abgetrennter Batterie reicht worstcase
         *       nur für 150 ms)
         * > Airbag01Struct.PduState [uint64]:
         *   Based on:
         *     AB_Crash_Int SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            updateAirbag01 Method ID: 21
            **/
        virtual void updateAirbag01(
            const asi::sid::lhwapp::cstyle::Airbag01Struct* Airbag01,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute Blinkmodi02
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * BM_Recas:
         *   * E3_1_1_UNECE: Blinkmodi_02.BM_Recas
         * BM_Crash:
         *   * E3_1_1_UNECE: Blinkmodi_02.BM_Crash
         * BM_Warnblinken:
         *   * E3_1_1_UNECE: Blinkmodi_02.BM_Warnblinken
         * BM_Not_Bremsung:
         *   * E3_1_1_UNECE: Blinkmodi_02.BM_Not_Bremsung
         * > Blinkmodi02Struct.BM_Recas_Raw [bool]:
         *   Based on:
         *     * BM_Recas: Blinkermodus RECAS  (RearEndCollisionAlertSignal)
         * > Blinkmodi02Struct.BM_Crash_Raw [bool]:
         *   Based on:
         *     * BM_Crash: Status Crashblinken
         * > Blinkmodi02Struct.BM_Warnblinken_Raw [bool]:
         *   Based on:
         *     * BM_Warnblinken: Warnblinken
         * > Blinkmodi02Struct.BM_Not_Bremsung_Raw [bool]:
         *   Based on:
         *     * BM_Not_Bremsung: Das Signal BM_Not_Bremsung  zeigt an,  ob ein
         *       Warnblinken aufgrund einer vom Bremssystem signalisierten Notbremsung
         *       aktiv ist
         * > Blinkmodi02Struct.PduState [uint64]:
         *   Based on:
         *     BM_Recas SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            updateBlinkmodi02 Method ID: 22
            **/
        virtual void updateBlinkmodi02(
            const asi::sid::lhwapp::cstyle::Blinkmodi02Struct* Blinkmodi02,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute Daempfer01
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * DR_Gelbe_Warnlampe:
         *   * E3_1_1_UNECE: Daempfer_01.DR_Gelbe_Warnlampe
         * > Daempfer01Struct.DR_Gelbe_Warnlampe_Raw [uint8]:
         *   Based on:
         *     * DR_Gelbe_Warnlampe: Bit wird gesetzt, wenn während des Betriebes ein
         *       Fehler erkannt wird
         * > Daempfer01Struct.PduState [uint64]:
         *   Based on:
         *     DR_Gelbe_Warnlampe SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            updateDaempfer01 Method ID: 23
            **/
        virtual void updateDaempfer01(
            const asi::sid::lhwapp::cstyle::Daempfer01Struct* Daempfer01,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute ESC50
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
            updateESC50 Method ID: 24
            **/
        virtual void updateESC50(
            const asi::sid::lhwapp::cstyle::ESC50Struct* ESC50,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute ESP21
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * ESP_v_Signal:
         *   * E3_1_1_UNECE: ESP_21.ESP_v_Signal
         * ESP_QBit_v_Signal:
         *   * E3_1_1_UNECE: ESP_21.ESP_QBit_v_Signal
         * ABS_Bremsung:
         *   * E3_1_1_UNECE: ESP_21.ABS_Bremsung
         * ASR_Anf:
         *   * E3_1_1_UNECE: ESP_21.ASR_Anf
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
            updateESP21 Method ID: 25
            **/
        virtual void updateESP21(
            const asi::sid::lhwapp::cstyle::ESP21Struct* ESP21,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute ESP24
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
            updateESP24 Method ID: 26
            **/
        virtual void updateESP24(
            const asi::sid::lhwapp::cstyle::ESP24Struct* ESP24,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute ESP30
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * RLE_Anzeigen:
         *   * E3_1_1_UNECE: ESP_30.RLE_Anzeigen
         * > ESP30Struct.RLE_Anzeigen_Raw [uint8]:
         *   Based on:
         *     * RLE_Anzeigen: Anzeigen für die Radlöseerkennung
         * > ESP30Struct.PduState [uint64]:
         *   Based on:
         *     RLE_Anzeigen SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            updateESP30 Method ID: 27
            **/
        virtual void updateESP30(
            const asi::sid::lhwapp::cstyle::ESP30Struct* ESP30,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute HVK01
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * HVK_HV_Netz_Warnungen:
         *   * E3_1_1_UNECE: HVK_01.HVK_HV_Netz_Warnungen
         * > HVK01Struct.HVK_HV_Netz_Warnungen_Raw [uint8]:
         *   Based on:
         *     * HVK_HV_Netz_Warnungen: Anforderung Warnung/Fehler HV-System im Kombi
         *       0: Keine Warnung/Init 1:Anforderung_Anzeige_Warnung_HV-Netz (gelbes
         *       Symbol) 2:Anforderung_Anzeige_Fehler_HV-Netz (rotes Symbol)
         *       3:Anforderung_Anzeige_Warnung_Kein_Wiederstart_möglich
         * > HVK01Struct.PduState [uint64]:
         *   Based on:
         *     HVK_HV_Netz_Warnungen SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            updateHVK01 Method ID: 28
            **/
        virtual void updateHVK01(
            const asi::sid::lhwapp::cstyle::HVK01Struct* HVK01,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute Motor18
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * MO_EPCL:
         *   * E3_1_1_UNECE: Motor_18.MO_EPCL
         * > Motor18Struct.MO_EPCL_Raw [uint8]:
         *   Based on:
         *     * MO_EPCL: Die Anforderung der EPC-Lampe vom MSG ans Kombi soll durch
         *       das Bus-Signal MO_EPCL gemäß folgender Logik erfolgen: MO_EPCL = 0 dez
         *       -> EPC Lampe aus, kein Text MO_EPCL = 1 dez -> gelbe EPC-Symbolik,
         *       Text „Antrieb: Störung! Bitte Service aufsuchen“ MO_EPCL = 2 dez ->
         *       gelbe EPC-Symbolik, Text „Antrieb: Achtung! Fahrleistung begrenzt“
         *       MO_EPCL = 3 dez -> rote EPC-Symbolik, Text „Antrieb: Störung! Fahrzeug
         *       sicher abstellen“
         * > Motor18Struct.PduState [uint64]:
         *   Based on:
         *     MO_EPCL SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            updateMotor18 Method ID: 29
            **/
        virtual void updateMotor18(
            const asi::sid::lhwapp::cstyle::Motor18Struct* Motor18,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute Motor_41
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * MO_EM_Ueberhitzungswarnung:
         *   * E3_1_1_UNECE: Motor_41.MO_EM_Ueberhitzungswarnung
         * FDR_Warnung_ALR:
         *   * E3_1_1_UNECE: Motor_41.FDR_Warnung_ALR
         * > Motor41Struct.MO_EM_Ueberhitzungswarnung_Raw [uint8]:
         *   Based on:
         *     * MO_EM_Ueberhitzungswarnung: Der elektrische Antrieb ist aufgrund eines
         *       Fehlers oder dauerhaft sehr hoher Drehzahl überhitzt
         * > Motor41Struct.FDR_Warnung_ALR_Raw [uint8]:
         *   Based on:
         *     * FDR_Warnung_ALR: Warnmeldungen der Allradverteilung
         * > Motor41Struct.PduState [uint64]:
         *   Based on:
         *     MO_EM_Ueberhitzungswarnung SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            updateMotor_41 Method ID: 30
            **/
        virtual void updateMotor_41(
            const asi::sid::lhwapp::cstyle::Motor41Struct* Motor_41,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute POSGNSSDR01
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * POS_GNSS_DR_Breite_Ortung:
         *   * E3_1_1_UNECE: POS_GNSS_DR_01.POS_GNSS_DR_Breite_Ortung
         * POS_GNSS_DR_Guete_E_GrH_Ausr:
         *   * E3_1_1_UNECE: POS_GNSS_DR_01.POS_GNSS_DR_Guete_E_GrH_Ausr
         * POS_GNSS_DR_Guete_E_GrHalbachse:
         *   * E3_1_1_UNECE: POS_GNSS_DR_01.POS_GNSS_DR_Guete_E_GrHalbachse
         * POS_GNSS_DR_Guete_E_KlHalbachse:
         *   * E3_1_1_UNECE: POS_GNSS_DR_01.POS_GNSS_DR_Guete_E_KlHalbachse
         * POS_GNSS_DR_Laenge_Ortung:
         *   * E3_1_1_UNECE: POS_GNSS_DR_01.POS_GNSS_DR_Laenge_Ortung
         * POS_GNSS_DR_Ausrichtung_Geschw:
         *   * E3_1_1_UNECE: POS_GNSS_DR_01.POS_GNSS_DR_Ausrichtung_Geschw
         * POS_GNSS_DR_Guete_Ausricht_Gesch:
         *   * E3_1_1_UNECE: POS_GNSS_DR_01.POS_GNSS_DR_Guete_Ausricht_Gesch
         * > POSGNSSDR01Struct.POS_GNSS_DR_Breite_Ortung_Raw [uint64]:
         *   Based on:
         *     * POS_GNSS_DR_Breite_Ortung: Breitengrad des Ortungsergebnisses
         *       entsprechend der DR-Position des GNSS-Moduls
         * > POSGNSSDR01Struct.POS_GNSS_DR_Breite_Ortung_SignalState [uint64]:
         *   Based on:
         *     * POS_GNSS_DR_Breite_Ortung: Breitengrad des Ortungsergebnisses
         *       entsprechend der DR-Position des GNSS-Moduls
         *   Used Constants:
         *     0: eSignalState_Valid
         *     1: eSignalState_Init
         *     2: eSignalState_Error
         * > POSGNSSDR01Struct.POS_GNSS_DR_Guete_E_GrH_Ausr_Raw [uint16]:
         *   Based on:
         *     * POS_GNSS_DR_Guete_E_GrH_Ausr: Ausrichtung der großen Halbachse der
         *       horizontalen Fehlerellipse (für die horizontale Positionsgüte)
         *       bezüglich der DR-Position des GNSS-Moduls
         * > POSGNSSDR01Struct.POS_GNSS_DR_Guete_E_GrH_Ausr_SignalState [uint64]:
         *   Based on:
         *     * POS_GNSS_DR_Guete_E_GrH_Ausr: Ausrichtung der großen Halbachse der
         *       horizontalen Fehlerellipse (für die horizontale Positionsgüte)
         *       bezüglich der DR-Position des GNSS-Moduls
         *   Used Constants:
         *     0: eSignalState_Valid
         *     1: eSignalState_Init
         *     2: eSignalState_Error
         * > POSGNSSDR01Struct.POS_GNSS_DR_Guete_E_GrHalbachse_Raw [uint16]:
         *   Based on:
         *     * POS_GNSS_DR_Guete_E_GrHalbachse: Länge der großen Halbachse der
         *       horizontalen Fehlerellipse (für die horizontale Positionsgüte)
         *       bezüglich der DR-Position des GNSS-Moduls
         * > POSGNSSDR01Struct.POS_GNSS_DR_Guete_E_GrHalbachse_SignalState [uint64]:
         *   Based on:
         *     * POS_GNSS_DR_Guete_E_GrHalbachse: Länge der großen Halbachse der
         *       horizontalen Fehlerellipse (für die horizontale Positionsgüte)
         *       bezüglich der DR-Position des GNSS-Moduls
         *   Used Constants:
         *     0: eSignalState_Valid
         *     1: eSignalState_Init
         *     2: eSignalState_Error
         * > POSGNSSDR01Struct.POS_GNSS_DR_Guete_E_KlHalbachse_Raw [uint16]:
         *   Based on:
         *     * POS_GNSS_DR_Guete_E_KlHalbachse: Länge der kleinen Halbachse der
         *       horizontalen Fehlerellipse (für die horizontale Positionsgüte)
         *       bezüglich der DR-Position des GNSS-Moduls
         * > POSGNSSDR01Struct.POS_GNSS_DR_Guete_E_KlHalbachse_SignalState [uint64]:
         *   Based on:
         *     * POS_GNSS_DR_Guete_E_KlHalbachse: Länge der kleinen Halbachse der
         *       horizontalen Fehlerellipse (für die horizontale Positionsgüte)
         *       bezüglich der DR-Position des GNSS-Moduls
         *   Used Constants:
         *     0: eSignalState_Valid
         *     1: eSignalState_Init
         *     2: eSignalState_Error
         * > POSGNSSDR01Struct.POS_GNSS_DR_Laenge_Ortung_Raw [uint64]:
         *   Based on:
         *     * POS_GNSS_DR_Laenge_Ortung: Längengrad des Ortungsergebnisses
         *       entsprechend der DR-Position des GNSS-Moduls
         * > POSGNSSDR01Struct.POS_GNSS_DR_Laenge_Ortung_SignalState [uint64]:
         *   Based on:
         *     * POS_GNSS_DR_Laenge_Ortung: Längengrad des Ortungsergebnisses
         *       entsprechend der DR-Position des GNSS-Moduls
         *   Used Constants:
         *     0: eSignalState_Valid
         *     1: eSignalState_Init
         *     2: eSignalState_Error
         * > POSGNSSDR01Struct.POS_GNSS_DR_Ausrichtung_Geschw_Raw [uint16]:
         *   Based on:
         *     * POS_GNSS_DR_Ausrichtung_Geschw: Ausrichtung des Ortungsergebnisses in
         *       Richtung des Geschwindigkeitsvektors entsprechend der DR-Position des
         *       GNSS-Moduls
         * > POSGNSSDR01Struct.POS_GNSS_DR_Ausrichtung_Geschw_SignalState [uint64]:
         *   Based on:
         *     * POS_GNSS_DR_Ausrichtung_Geschw: Ausrichtung des Ortungsergebnisses in
         *       Richtung des Geschwindigkeitsvektors entsprechend der DR-Position des
         *       GNSS-Moduls
         *   Used Constants:
         *     0: eSignalState_Valid
         *     1: eSignalState_Init
         *     2: eSignalState_Error
         * > POSGNSSDR01Struct.POS_GNSS_DR_Guete_Ausricht_Gesch_Raw [uint16]:
         *   Based on:
         *     * POS_GNSS_DR_Guete_Ausricht_Gesch: Güte der Ausrichtung des
         *       Ortungsergebnisses in Richtung des Geschwindigkeitsvektors
         *       entsprechend der DR-Position des GNSS-Moduls
         * > POSGNSSDR01Struct.POS_GNSS_DR_Guete_Ausricht_Gesch_SignalState [uint64]:
         *   Based on:
         *     * POS_GNSS_DR_Guete_Ausricht_Gesch: Güte der Ausrichtung des
         *       Ortungsergebnisses in Richtung des Geschwindigkeitsvektors
         *       entsprechend der DR-Position des GNSS-Moduls
         *   Used Constants:
         *     0: eSignalState_Valid
         *     1: eSignalState_Init
         *     2: eSignalState_Error
         * > POSGNSSDR01Struct.PduState [uint64]:
         *   Based on:
         *     POS_GNSS_DR_Breite_Ortung SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            updatePOSGNSSDR01 Method ID: 31
            **/
        virtual void updatePOSGNSSDR01(
            const asi::sid::lhwapp::cstyle::POSGNSSDR01Struct* POSGNSSDR01,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute PSD04
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * PSD_Endkruemmung_Vorz:
         *   * E3_1_1_UNECE: PSD_04.PSD_Endkruemmung_Vorz
         * PSD_wahrscheinlichster_Pfad:
         *   * E3_1_1_UNECE: PSD_04.PSD_wahrscheinlichster_Pfad
         * PSD_Geradester_Pfad:
         *   * E3_1_1_UNECE: PSD_04.PSD_Geradester_Pfad
         * PSD_Segment_Komplett:
         *   * E3_1_1_UNECE: PSD_04.PSD_Segment_Komplett
         * PSD_Anfangskruemmung:
         *   * E3_1_1_UNECE: PSD_04.PSD_Anfangskruemmung
         * PSD_Anfangskruemmung_Vorz:
         *   * E3_1_1_UNECE: PSD_04.PSD_Anfangskruemmung_Vorz
         * PSD_Abzweigerichtung:
         *   * E3_1_1_UNECE: PSD_04.PSD_Abzweigerichtung
         * PSD_Abzweigewinkel:
         *   * E3_1_1_UNECE: PSD_04.PSD_Abzweigewinkel
         * PSD_Segment_ID:
         *   * E3_1_1_UNECE: PSD_04.PSD_Segment_ID
         * PSD_Vorgaenger_Segment_ID:
         *   * E3_1_1_UNECE: PSD_04.PSD_Vorgaenger_Segment_ID
         * PSD_Segmentlaenge:
         *   * E3_1_1_UNECE: PSD_04.PSD_Segmentlaenge
         * PSD_Strassenkategorie:
         *   * E3_1_1_UNECE: PSD_04.PSD_Strassenkategorie
         * PSD_Endkruemmung:
         *   * E3_1_1_UNECE: PSD_04.PSD_Endkruemmung
         * > PSD04Struct.PSD_Endkruemmung_Vorz_Raw [bool]:
         *   Based on:
         *     * PSD_Endkruemmung_Vorz:
         * > PSD04Struct.PSD_wahrscheinlichster_Pfad_Raw [bool]:
         *   Based on:
         *     * PSD_wahrscheinlichster_Pfad: Identifiziert den vom Navigationssystem
         *       berechneten wahrscheinlichsten Pfad des Fahrzeuges
         * > PSD04Struct.PSD_Geradester_Pfad_Raw [bool]:
         *   Based on:
         *     * PSD_Geradester_Pfad: Segment ist Teil des geradesten Pfades
         * > PSD04Struct.PSD_Segment_Komplett_Raw [bool]:
         *   Based on:
         *     * PSD_Segment_Komplett: Zeigt, ob alle Attribute für das Segment
         *       übertragen worden sind
         * > PSD04Struct.PSD_Anfangskruemmung_Raw [uint8]:
         *   Based on:
         *     * PSD_Anfangskruemmung: Startkrümmung der Klothoide des übermittelten
         *       abzweigenden Streckensegments.  1/(1+0.155 * x^2) {1/m}"
         * > PSD04Struct.PSD_Anfangskruemmung_SignalState [uint64]:
         *   Based on:
         *     * PSD_Anfangskruemmung: Startkrümmung der Klothoide des übermittelten
         *       abzweigenden Streckensegments.  1/(1+0.155 * x^2) {1/m}"
         *   Used Constants:
         *     0: eSignalState_Valid
         *     16: eSignalState_Reserved
         * > PSD04Struct.PSD_Anfangskruemmung_Vorz_Raw [bool]:
         *   Based on:
         *     * PSD_Anfangskruemmung_Vorz: Vorzeichen für die Startkrümmung bei
         *       Abzweigungen
         * > PSD04Struct.PSD_Abzweigerichtung_Raw [bool]:
         *   Based on:
         *     * PSD_Abzweigerichtung: Richtung, in der die Abzweigung von der
         *       Hauptroute abzweigt
         * > PSD04Struct.PSD_Abzweigewinkel_Raw [uint8]:
         *   Based on:
         *     * PSD_Abzweigewinkel: Winkel, unter dem die Abzweigung von der
         *       Hauptroute abzweigt
         * > PSD04Struct.PSD_Segment_ID_Raw [uint8]:
         *   Based on:
         *     * PSD_Segment_ID: Identifier des prädiktiven Streckensegments
         * > PSD04Struct.PSD_Segment_ID_SignalState [uint64]:
         *   Based on:
         *     * PSD_Segment_ID: Identifier des prädiktiven Streckensegments
         *   Used Constants:
         *     0: eSignalState_Valid
         *     2: eSignalState_Error
         *     11: eSignalState_NotAvailable
         * > PSD04Struct.PSD_Vorgaenger_Segment_ID_Raw [uint8]:
         *   Based on:
         *     * PSD_Vorgaenger_Segment_ID: An dem Streckensegment mit diesem
         *       Identifier schließt sich das neue Segment mit der ID
         *       "PSD_01_Segment_ID" an
         * > PSD04Struct.PSD_Vorgaenger_Segment_ID_SignalState [uint64]:
         *   Based on:
         *     * PSD_Vorgaenger_Segment_ID: An dem Streckensegment mit diesem
         *       Identifier schließt sich das neue Segment mit der ID
         *       "PSD_01_Segment_ID" an
         *   Used Constants:
         *     0: eSignalState_Valid
         *     2: eSignalState_Error
         *     11: eSignalState_NotAvailable
         * > PSD04Struct.PSD_Segmentlaenge_Raw [uint8]:
         *   Based on:
         *     * PSD_Segmentlaenge: Gesamtlänge des prädiktiven Streckensegments
         * > PSD04Struct.PSD_Strassenkategorie_Raw [uint8]:
         *   Based on:
         *     * PSD_Strassenkategorie: Klassifizierung der Straße des beschriebenen
         *       Segments
         * > PSD04Struct.PSD_Endkruemmung_Raw [uint8]:
         *   Based on:
         *     * PSD_Endkruemmung: "Endkrümmung der Klotoide des übermittelten
         *       Streckensegments. Die Anfangskrümmung des folgenden Streckensegments
         *       entspricht der Endkrümmung dieses Segments. Krümmung = 1/(1+0.155 *
         *       x²) [1/m]
         * > PSD04Struct.PSD_Endkruemmung_SignalState [uint64]:
         *   Based on:
         *     * PSD_Endkruemmung: "Endkrümmung der Klotoide des übermittelten
         *       Streckensegments. Die Anfangskrümmung des folgenden Streckensegments
         *       entspricht der Endkrümmung dieses Segments. Krümmung = 1/(1+0.155 *
         *       x²) [1/m]
         *   Used Constants:
         *     0: eSignalState_Valid
         *     16: eSignalState_Reserved
         * > PSD04Struct.PduState [uint64]:
         *   Based on:
         *     PSD_Endkruemmung_Vorz SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            updatePSD04 Method ID: 32
            **/
        virtual void updatePSD04(
            const asi::sid::lhwapp::cstyle::PSD04Struct* PSD04,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute PSD05
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * PSD_Pos_Segment_ID:
         *   * E3_1_1_UNECE: PSD_05.PSD_Pos_Segment_ID
         * PSD_Pos_Segmentlaenge:
         *   * E3_1_1_UNECE: PSD_05.PSD_Pos_Segmentlaenge
         * PSD_Pos_Standort_Eindeutig:
         *   * E3_1_1_UNECE: PSD_05.PSD_Pos_Standort_Eindeutig
         * PSD_Pos_Fehler_Laengsrichtung:
         *   * E3_1_1_UNECE: PSD_05.PSD_Pos_Fehler_Laengsrichtung
         * PSD_Attribut_1_ID:
         *   * E3_1_1_UNECE: PSD_05.PSD_Attribut_1_ID
         * PSD_Attribut_1_Wert:
         *   * E3_1_1_UNECE: PSD_05.PSD_Attribut_1_Wert
         * PSD_Attribut_2_ID:
         *   * E3_1_1_UNECE: PSD_05.PSD_Attribut_2_ID
         * PSD_Attribut_2_Wert:
         *   * E3_1_1_UNECE: PSD_05.PSD_Attribut_2_Wert
         * > PSD05Struct.PSD_Pos_Segment_ID_Raw [uint8]:
         *   Based on:
         *     * PSD_Pos_Segment_ID: Identifier des Streckensegments, auf dem sich das
         *       Fahrzeug aktuell befindet
         * > PSD05Struct.PSD_Pos_Segment_ID_SignalState [uint64]:
         *   Based on:
         *     * PSD_Pos_Segment_ID: Identifier des Streckensegments, auf dem sich das
         *       Fahrzeug aktuell befindet
         *   Used Constants:
         *     0: eSignalState_Valid
         *     2: eSignalState_Error
         *     11: eSignalState_NotAvailable
         * > PSD05Struct.PSD_Pos_Segmentlaenge_Raw [uint8]:
         *   Based on:
         *     * PSD_Pos_Segmentlaenge: Verbleibende Länge des Streckensegments, auf
         *       dem sich das Fahrzeug aktuell befindet
         * > PSD05Struct.PSD_Pos_Standort_Eindeutig_Raw [bool]:
         *   Based on:
         *     * PSD_Pos_Standort_Eindeutig: Ist die Position des Fahrzeugs eindeutig
         *       dem aktuelle Segment zugeordnet, oder gibt es fahrbare alternative
         *       Segmente, die bei akteller GPS-Position ebenfalls als aktuelles
         *       Segment möglich wären
         * > PSD05Struct.PSD_Pos_Fehler_Laengsrichtung_Raw [uint8]:
         *   Based on:
         *     * PSD_Pos_Fehler_Laengsrichtung: Laengsfehler der Positionierung
         * > PSD05Struct.PSD_Attribut_1_ID_Raw [uint8]:
         *   Based on:
         *     * PSD_Attribut_1_ID: Identifier des ersten Attributes
         * > PSD05Struct.PSD_Attribut_1_ID_SignalState [uint64]:
         *   Based on:
         *     * PSD_Attribut_1_ID: Identifier des ersten Attributes
         *   Used Constants:
         *     0: eSignalState_Valid
         *     11: eSignalState_NotAvailable
         * > PSD05Struct.PSD_Attribut_1_Wert_Raw [uint8]:
         *   Based on:
         *     * PSD_Attribut_1_Wert: Wert des ersten Attributes
         * > PSD05Struct.PSD_Attribut_2_ID_Raw [uint8]:
         *   Based on:
         *     * PSD_Attribut_2_ID: Identifier des zweiten Attributes
         * > PSD05Struct.PSD_Attribut_2_ID_SignalState [uint64]:
         *   Based on:
         *     * PSD_Attribut_2_ID: Identifier des zweiten Attributes
         *   Used Constants:
         *     0: eSignalState_Valid
         *     11: eSignalState_NotAvailable
         * > PSD05Struct.PSD_Attribut_2_Wert_Raw [uint8]:
         *   Based on:
         *     * PSD_Attribut_2_Wert: Wert des zweiten Attributes
         * > PSD05Struct.PduState [uint64]:
         *   Based on:
         *     PSD_Pos_Segment_ID SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            updatePSD05 Method ID: 33
            **/
        virtual void updatePSD05(
            const asi::sid::lhwapp::cstyle::PSD05Struct* PSD05,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute PSD06
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * PSD_06_Mux:
         *   * E3_1_1_UNECE: PSD_06.PSD_06_Mux
         * PSD_Attribut_5_ID:
         *   * E3_1_1_UNECE: PSD_06.PSD_Attribut_5_ID
         * PSD_Attribut_3_Wert:
         *   * E3_1_1_UNECE: PSD_06.PSD_Attribut_3_Wert
         * PSD_Attribut_5_Wert:
         *   * E3_1_1_UNECE: PSD_06.PSD_Attribut_5_Wert
         * PSD_Attribut_4_ID:
         *   * E3_1_1_UNECE: PSD_06.PSD_Attribut_4_ID
         * PSD_Attribut_4_Wert:
         *   * E3_1_1_UNECE: PSD_06.PSD_Attribut_4_Wert
         * PSD_Attribut_Segment_ID:
         *   * E3_1_1_UNECE: PSD_06.PSD_Attribut_Segment_ID
         * PSD_Attribut_3_ID:
         *   * E3_1_1_UNECE: PSD_06.PSD_Attribut_3_ID
         * > PSD06Struct.PSD_06_Mux_Raw [uint8]:
         *   Based on:
         *     * PSD_06_Mux: Multiplex Zähler für die PSD_06-Botschaft. Die
         *       unterschiedlichen Muxe folgen keiner festen Reihenfolge. Je nach
         *       Inhalt des PSD-Protokolls an der aktuellen Position werden jeweils die
         *       notwendigen PSD6-Botschaften gesendet
         * > PSD06Struct.PSD_Attribut_5_ID_Raw [uint8]:
         *   Based on:
         *     * PSD_Attribut_5_ID: Typ von Attribut 5
         * > PSD06Struct.PSD_Attribut_5_ID_SignalState [uint64]:
         *   Based on:
         *     * PSD_Attribut_5_ID: Typ von Attribut 5
         *   Used Constants:
         *     0: eSignalState_Valid
         *     11: eSignalState_NotAvailable
         * > PSD06Struct.PSD_Attribut_3_Wert_Raw [uint8]:
         *   Based on:
         *     * PSD_Attribut_3_Wert: Wert des dritten Attributes
         * > PSD06Struct.PSD_Attribut_5_Wert_Raw [uint8]:
         *   Based on:
         *     * PSD_Attribut_5_Wert: Wert von Attribut 5
         * > PSD06Struct.PSD_Attribut_4_ID_Raw [uint8]:
         *   Based on:
         *     * PSD_Attribut_4_ID: Typ von Attribut 4
         * > PSD06Struct.PSD_Attribut_4_ID_SignalState [uint64]:
         *   Based on:
         *     * PSD_Attribut_4_ID: Typ von Attribut 4
         *   Used Constants:
         *     0: eSignalState_Valid
         *     11: eSignalState_NotAvailable
         * > PSD06Struct.PSD_Attribut_4_Wert_Raw [uint8]:
         *   Based on:
         *     * PSD_Attribut_4_Wert: Wert von Attribut 4
         * > PSD06Struct.PSD_Attribut_Segment_ID_Raw [uint8]:
         *   Based on:
         *     * PSD_Attribut_Segment_ID: Identifier des Streckensegments,für das die
         *       weiteren Attribute in der Botschaft gültig sind
         * > PSD06Struct.PSD_Attribut_Segment_ID_SignalState [uint64]:
         *   Based on:
         *     * PSD_Attribut_Segment_ID: Identifier des Streckensegments,für das die
         *       weiteren Attribute in der Botschaft gültig sind
         *   Used Constants:
         *     0: eSignalState_Valid
         *     2: eSignalState_Error
         *     11: eSignalState_NotAvailable
         * > PSD06Struct.PSD_Attribut_3_ID_Raw [uint8]:
         *   Based on:
         *     * PSD_Attribut_3_ID: Identifier des dritten Attributes
         * > PSD06Struct.PSD_Attribut_3_ID_SignalState [uint64]:
         *   Based on:
         *     * PSD_Attribut_3_ID: Identifier des dritten Attributes
         *   Used Constants:
         *     0: eSignalState_Valid
         *     11: eSignalState_NotAvailable
         * > PSD06Struct.PduState [uint64]:
         *   Based on:
         *     PSD_06_Mux SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            updatePSD06 Method ID: 34
            **/
        virtual void updatePSD06(
            const asi::sid::lhwapp::cstyle::PSD06Struct* PSD06,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute RKA01
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * RKA_FMVSS138_Lampe:
         *   * E3_1_1_UNECE: RKA_01.RKA_FMVSS138_Lampe
         * RKA_Warnungen_02:
         *   * E3_1_1_UNECE: RKA_01.RKA_Warnungen_02
         * > RKA01Struct.RKA_FMVSS138_Lampe_Raw [bool]:
         *   Based on:
         *     * RKA_FMVSS138_Lampe: Kein Einsatz RKA im D4 Hybrid
         * > RKA01Struct.RKA_Warnungen_02_Raw [uint8]:
         *   Based on:
         *     * RKA_Warnungen_02: Ansteuerung der Warnungen (Texte, Töne, Lampen) im
         *       Kombi für Funktion RKA+  Kein Einsatz RKA im D4 Hybrid
         * > RKA01Struct.PduState [uint64]:
         *   Based on:
         *     RKA_FMVSS138_Lampe SignalState
         *   Used Constants:
         *     0: ePduState_NotExisting
         *     1: ePduState_Valid
         *     2: ePduState_TempNotValid
         *     3: ePduState_TimeoutNotValidNotFiltered
         *     4: ePduState_NeverReceived
         *     5: ePduState_TimeoutNotValidFiltered
         *     15: ePduState_Invalid
         ***
            updateRKA01 Method ID: 35
            **/
        virtual void updateRKA01(
            const asi::sid::lhwapp::cstyle::RKA01Struct* RKA01,
            const bool isValid
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        */
        virtual void clientConnected(uint32_t count) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        */
        virtual void clientDisconnected(uint32_t count) {}

        // call ids
        void
        updateAirbag01CallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IntLHWAppReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 21;
            ce.assign(inst, mid);
        }

        void
        updateBlinkmodi02CallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IntLHWAppReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 22;
            ce.assign(inst, mid);
        }

        void
        updateDaempfer01CallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IntLHWAppReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 23;
            ce.assign(inst, mid);
        }

        void
        updateESC50CallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IntLHWAppReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 24;
            ce.assign(inst, mid);
        }

        void
        updateESP21CallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IntLHWAppReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 25;
            ce.assign(inst, mid);
        }

        void
        updateESP24CallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IntLHWAppReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 26;
            ce.assign(inst, mid);
        }

        void
        updateESP30CallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IntLHWAppReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 27;
            ce.assign(inst, mid);
        }

        void
        updateHVK01CallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IntLHWAppReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 28;
            ce.assign(inst, mid);
        }

        void
        updateMotor18CallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IntLHWAppReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 29;
            ce.assign(inst, mid);
        }

        void
        updateMotor_41CallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IntLHWAppReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 30;
            ce.assign(inst, mid);
        }

        void
        updatePOSGNSSDR01CallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IntLHWAppReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 31;
            ce.assign(inst, mid);
        }

        void
        updatePSD04CallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IntLHWAppReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 32;
            ce.assign(inst, mid);
        }

        void
        updatePSD05CallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IntLHWAppReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 33;
            ce.assign(inst, mid);
        }

        void
        updatePSD06CallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IntLHWAppReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 34;
            ce.assign(inst, mid);
        }

        void
        updateRKA01CallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IntLHWAppReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 35;
            ce.assign(inst, mid);
        }


        virtual ~IntLHWAppReply() {}
    };

} // namespace cstyle
}//namespace asi
}//namespace sid
}//namespace lhwapp

#endif// ASI_SID_LHWAPP_INTLHWAPPREPLY_CSTYLE_HXX
