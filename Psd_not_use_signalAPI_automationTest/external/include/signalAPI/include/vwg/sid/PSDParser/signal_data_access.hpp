/**
 * \file signal_data_access.hpp
 *
 * \brief Generated signal data access API specific for application PSDParser
 *
 * Code generator version: 0.8.8
 * Generator input:
 * - Data definition:      E3_1_1_UNECE_E3V_VLAN_Connect_KMatrix_Module_V15.04.00.03F_20221220_BAm_P02.xlsx
 * - Config file:          ./config/PSDParser.yaml
 * - Config file version:  0.8/demo_config
 * - Config description:   here goes some description
 * Generator output:
 * - C++ API version:      0.8
 *
 * \copyright 2023 CARIAD SE, All rights reserved.
 * 
 * NOTICE:
 * 
 * All the information and materials contained herein, including the
 * intellectual and technical concepts, are the property of CARIAD SE and may
 * be covered by patents, patents in process, and are protected by trade
 * secret and/or copyright law.
 * 
 * The copyright notice above does not evidence any actual or intended
 * publication or disclosure of this source code, which includes information
 * and materials that are confidential and/or proprietary and trade secrets of
 * CARIAD SE.
 * 
 * Any reproduction, dissemination, modification, distribution, public
 * performance, public display of or any other use of this source code and/or
 * any other information and/or material contained herein without the prior
 * written consent of CARIAD SE is strictly prohibited and in violation of
 * applicable laws.
 * 
 * The receipt or possession of this source code and/or related information
 * does not convey or imply any rights to reproduce, disclose or distribute
 * its contents or to manufacture, use or sell anything that it may describe
 * in whole or in part.
 */

#ifndef VWG_SID_PSDPARSER_SIGNAL_DATA_ACCESS_HPP_
#define VWG_SID_PSDPARSER_SIGNAL_DATA_ACCESS_HPP_

// standard library includes
#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

namespace vwg {
namespace sid {
namespace PSDParser {

enum class PduStatus {
   kValid,           // PDU data are valid and up-to-date
   kTimedOut,        // PDU reception timed out unexpectedly
   kTempNotValid,    // PDU receives no updates due to bus not active or Clamp15 off
   kNotReceivedYet,  // PDU was not yet received on this device, signal data are device-local initial data
   kNotValid,        // PDU data are not valid
};

// The RxPdu_xxx instance are provided to the applications by the calls to the
// respective listener function (see the documentation of the
// ISignalDataListener class below).
//
// The data type for each signal is automatically determined from the number
// of bits of the signal as defined in the data definition.  Any extra bits
// will be set to zero.  For a signal with n bits therefore only the bits 2^0
// .. 2^(n-1) may hold non-zero values.  This also applies for signal values
// of type vector<std::uint8_t>: The byte at vector index 0 holds the bits 2^0
// .. 2^7, the byte at index 1 holds the bits 2^8 .. 2^15 etc.
//
// In the target code, these instances are provided to the applications for
// reading only.  For test code, writing is also possible via the dedicated
// setter methods.  This way, test code can create RxPdu_xxx instances with
// test data and send it to the application via the listener instance.

class RxPdu_PSD_04 final {

   // -- BEGIN: public API for target code

public:
   RxPdu_PSD_04() = default; // default ctor
   ~RxPdu_PSD_04() = default; // default dtor
   RxPdu_PSD_04(RxPdu_PSD_04 const &) = default; // default copy ctor
   RxPdu_PSD_04(RxPdu_PSD_04 &&) = default; // default move ctor
   RxPdu_PSD_04 & operator=(RxPdu_PSD_04 const &) = default; // default copy assignment
   RxPdu_PSD_04 & operator=(RxPdu_PSD_04 &&) = default; // default move assignment

   PduStatus getPduStatus() const noexcept;

   std::uint32_t get_PSD_Segment_ID() const noexcept; // 6 bits
   std::uint32_t get_PSD_Vorgaenger_Segment_ID() const noexcept; // 6 bits
   std::uint32_t get_PSD_Segmentlaenge() const noexcept; // 7 bits
   std::uint32_t get_PSD_Strassenkategorie() const noexcept; // 3 bits
   std::uint32_t get_PSD_Endkruemmung() const noexcept; // 8 bits
   bool get_PSD_Endkruemmung_Vorz() const noexcept; // 1 bit
   std::uint32_t get_PSD_Idenditaets_ID() const noexcept; // 6 bits
   bool get_PSD_ADAS_Qualitaet() const noexcept; // 1 bit
   bool get_PSD_wahrscheinlichster_Pfad() const noexcept; // 1 bit
   bool get_PSD_Geradester_Pfad() const noexcept; // 1 bit
   std::uint32_t get_PSD_Fahrspuren_Anzahl() const noexcept; // 3 bits
   bool get_PSD_Bebauung() const noexcept; // 1 bit
   bool get_PSD_Segment_Komplett() const noexcept; // 1 bit
   std::uint32_t get_PSD_Rampe() const noexcept; // 2 bits
   std::uint32_t get_PSD_Anfangskruemmung() const noexcept; // 8 bits
   bool get_PSD_Anfangskruemmung_Vorz() const noexcept; // 1 bit
   bool get_PSD_Abzweigerichtung() const noexcept; // 1 bit
   std::uint32_t get_PSD_Abzweigewinkel() const noexcept; // 7 bits

   // --   END: public API for target code


   // -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING
public:
   void FOR_TESTING_setPduStatus(PduStatus status) noexcept;

   void FOR_TESTING_set_PSD_Segment_ID(std::uint32_t) noexcept; // 6 bits
   void FOR_TESTING_set_PSD_Vorgaenger_Segment_ID(std::uint32_t) noexcept; // 6 bits
   void FOR_TESTING_set_PSD_Segmentlaenge(std::uint32_t) noexcept; // 7 bits
   void FOR_TESTING_set_PSD_Strassenkategorie(std::uint32_t) noexcept; // 3 bits
   void FOR_TESTING_set_PSD_Endkruemmung(std::uint32_t) noexcept; // 8 bits
   void FOR_TESTING_set_PSD_Endkruemmung_Vorz(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Idenditaets_ID(std::uint32_t) noexcept; // 6 bits
   void FOR_TESTING_set_PSD_ADAS_Qualitaet(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_wahrscheinlichster_Pfad(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Geradester_Pfad(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Fahrspuren_Anzahl(std::uint32_t) noexcept; // 3 bits
   void FOR_TESTING_set_PSD_Bebauung(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Segment_Komplett(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Rampe(std::uint32_t) noexcept; // 2 bits
   void FOR_TESTING_set_PSD_Anfangskruemmung(std::uint32_t) noexcept; // 8 bits
   void FOR_TESTING_set_PSD_Anfangskruemmung_Vorz(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Abzweigerichtung(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Abzweigewinkel(std::uint32_t) noexcept; // 7 bits
#endif // VWG_SID_CLIENT_TESTING

   // --   END: public API for testing & mocking purposes only


   // -- BEGIN: private API for internal use only

   void PRIVATE_setPduStatus(PduStatus status) noexcept;

   void PRIVATE_set_PSD_Segment_ID(std::uint32_t) noexcept; // 6 bits
   void PRIVATE_set_PSD_Vorgaenger_Segment_ID(std::uint32_t) noexcept; // 6 bits
   void PRIVATE_set_PSD_Segmentlaenge(std::uint32_t) noexcept; // 7 bits
   void PRIVATE_set_PSD_Strassenkategorie(std::uint32_t) noexcept; // 3 bits
   void PRIVATE_set_PSD_Endkruemmung(std::uint32_t) noexcept; // 8 bits
   void PRIVATE_set_PSD_Endkruemmung_Vorz(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Idenditaets_ID(std::uint32_t) noexcept; // 6 bits
   void PRIVATE_set_PSD_ADAS_Qualitaet(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_wahrscheinlichster_Pfad(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Geradester_Pfad(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Fahrspuren_Anzahl(std::uint32_t) noexcept; // 3 bits
   void PRIVATE_set_PSD_Bebauung(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Segment_Komplett(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Rampe(std::uint32_t) noexcept; // 2 bits
   void PRIVATE_set_PSD_Anfangskruemmung(std::uint32_t) noexcept; // 8 bits
   void PRIVATE_set_PSD_Anfangskruemmung_Vorz(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Abzweigerichtung(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Abzweigewinkel(std::uint32_t) noexcept; // 7 bits

private:
   PduStatus status = PduStatus::kNotValid;
   std::uint32_t PSD_Segment_ID_value;
   std::uint32_t PSD_Vorgaenger_Segment_ID_value;
   std::uint32_t PSD_Segmentlaenge_value;
   std::uint32_t PSD_Strassenkategorie_value;
   std::uint32_t PSD_Endkruemmung_value;
   bool PSD_Endkruemmung_Vorz_value;
   std::uint32_t PSD_Idenditaets_ID_value;
   bool PSD_ADAS_Qualitaet_value;
   bool PSD_wahrscheinlichster_Pfad_value;
   bool PSD_Geradester_Pfad_value;
   std::uint32_t PSD_Fahrspuren_Anzahl_value;
   bool PSD_Bebauung_value;
   bool PSD_Segment_Komplett_value;
   std::uint32_t PSD_Rampe_value;
   std::uint32_t PSD_Anfangskruemmung_value;
   bool PSD_Anfangskruemmung_Vorz_value;
   bool PSD_Abzweigerichtung_value;
   std::uint32_t PSD_Abzweigewinkel_value;

   // --   END: private API for internal use only
};

class RxPdu_PSD_05 final {

   // -- BEGIN: public API for target code

public:
   RxPdu_PSD_05() = default; // default ctor
   ~RxPdu_PSD_05() = default; // default dtor
   RxPdu_PSD_05(RxPdu_PSD_05 const &) = default; // default copy ctor
   RxPdu_PSD_05(RxPdu_PSD_05 &&) = default; // default move ctor
   RxPdu_PSD_05 & operator=(RxPdu_PSD_05 const &) = default; // default copy assignment
   RxPdu_PSD_05 & operator=(RxPdu_PSD_05 &&) = default; // default move assignment

   PduStatus getPduStatus() const noexcept;

   std::uint32_t get_PSD_Pos_Segment_ID() const noexcept; // 6 bits
   std::uint32_t get_PSD_Pos_Segmentlaenge() const noexcept; // 7 bits
   std::uint32_t get_PSD_Pos_Inhibitzeit() const noexcept; // 5 bits
   bool get_PSD_Pos_Standort_Eindeutig() const noexcept; // 1 bit
   std::uint32_t get_PSD_Pos_Fehler_Laengsrichtung() const noexcept; // 3 bits
   std::uint32_t get_PSD_Pos_Fahrspur() const noexcept; // 3 bits
   std::uint32_t get_PSD_Attribut_Segment_ID_05() const noexcept; // 6 bits
   std::uint32_t get_PSD_Attribut_1_ID() const noexcept; // 5 bits
   std::uint32_t get_PSD_Attribut_1_Wert() const noexcept; // 4 bits
   std::uint32_t get_PSD_Attribut_1_Offset() const noexcept; // 7 bits
   std::uint32_t get_PSD_Attribut_2_ID() const noexcept; // 5 bits
   std::uint32_t get_PSD_Attribut_2_Wert() const noexcept; // 4 bits
   std::uint32_t get_PSD_Attribut_2_Offset() const noexcept; // 7 bits
   bool get_PSD_Attribute_Komplett_05() const noexcept; // 1 bit

   // --   END: public API for target code


   // -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING
public:
   void FOR_TESTING_setPduStatus(PduStatus status) noexcept;

   void FOR_TESTING_set_PSD_Pos_Segment_ID(std::uint32_t) noexcept; // 6 bits
   void FOR_TESTING_set_PSD_Pos_Segmentlaenge(std::uint32_t) noexcept; // 7 bits
   void FOR_TESTING_set_PSD_Pos_Inhibitzeit(std::uint32_t) noexcept; // 5 bits
   void FOR_TESTING_set_PSD_Pos_Standort_Eindeutig(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Pos_Fehler_Laengsrichtung(std::uint32_t) noexcept; // 3 bits
   void FOR_TESTING_set_PSD_Pos_Fahrspur(std::uint32_t) noexcept; // 3 bits
   void FOR_TESTING_set_PSD_Attribut_Segment_ID_05(std::uint32_t) noexcept; // 6 bits
   void FOR_TESTING_set_PSD_Attribut_1_ID(std::uint32_t) noexcept; // 5 bits
   void FOR_TESTING_set_PSD_Attribut_1_Wert(std::uint32_t) noexcept; // 4 bits
   void FOR_TESTING_set_PSD_Attribut_1_Offset(std::uint32_t) noexcept; // 7 bits
   void FOR_TESTING_set_PSD_Attribut_2_ID(std::uint32_t) noexcept; // 5 bits
   void FOR_TESTING_set_PSD_Attribut_2_Wert(std::uint32_t) noexcept; // 4 bits
   void FOR_TESTING_set_PSD_Attribut_2_Offset(std::uint32_t) noexcept; // 7 bits
   void FOR_TESTING_set_PSD_Attribute_Komplett_05(bool) noexcept; // 1 bit
#endif // VWG_SID_CLIENT_TESTING

   // --   END: public API for testing & mocking purposes only


   // -- BEGIN: private API for internal use only

   void PRIVATE_setPduStatus(PduStatus status) noexcept;

   void PRIVATE_set_PSD_Pos_Segment_ID(std::uint32_t) noexcept; // 6 bits
   void PRIVATE_set_PSD_Pos_Segmentlaenge(std::uint32_t) noexcept; // 7 bits
   void PRIVATE_set_PSD_Pos_Inhibitzeit(std::uint32_t) noexcept; // 5 bits
   void PRIVATE_set_PSD_Pos_Standort_Eindeutig(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Pos_Fehler_Laengsrichtung(std::uint32_t) noexcept; // 3 bits
   void PRIVATE_set_PSD_Pos_Fahrspur(std::uint32_t) noexcept; // 3 bits
   void PRIVATE_set_PSD_Attribut_Segment_ID_05(std::uint32_t) noexcept; // 6 bits
   void PRIVATE_set_PSD_Attribut_1_ID(std::uint32_t) noexcept; // 5 bits
   void PRIVATE_set_PSD_Attribut_1_Wert(std::uint32_t) noexcept; // 4 bits
   void PRIVATE_set_PSD_Attribut_1_Offset(std::uint32_t) noexcept; // 7 bits
   void PRIVATE_set_PSD_Attribut_2_ID(std::uint32_t) noexcept; // 5 bits
   void PRIVATE_set_PSD_Attribut_2_Wert(std::uint32_t) noexcept; // 4 bits
   void PRIVATE_set_PSD_Attribut_2_Offset(std::uint32_t) noexcept; // 7 bits
   void PRIVATE_set_PSD_Attribute_Komplett_05(bool) noexcept; // 1 bit

private:
   PduStatus status = PduStatus::kNotValid;
   std::uint32_t PSD_Pos_Segment_ID_value;
   std::uint32_t PSD_Pos_Segmentlaenge_value;
   std::uint32_t PSD_Pos_Inhibitzeit_value;
   bool PSD_Pos_Standort_Eindeutig_value;
   std::uint32_t PSD_Pos_Fehler_Laengsrichtung_value;
   std::uint32_t PSD_Pos_Fahrspur_value;
   std::uint32_t PSD_Attribut_Segment_ID_05_value;
   std::uint32_t PSD_Attribut_1_ID_value;
   std::uint32_t PSD_Attribut_1_Wert_value;
   std::uint32_t PSD_Attribut_1_Offset_value;
   std::uint32_t PSD_Attribut_2_ID_value;
   std::uint32_t PSD_Attribut_2_Wert_value;
   std::uint32_t PSD_Attribut_2_Offset_value;
   bool PSD_Attribute_Komplett_05_value;

   // --   END: private API for internal use only
};

class RxPdu_PSD_06 final {

   // -- BEGIN: public API for target code

public:
   RxPdu_PSD_06() = default; // default ctor
   ~RxPdu_PSD_06() = default; // default dtor
   RxPdu_PSD_06(RxPdu_PSD_06 const &) = default; // default copy ctor
   RxPdu_PSD_06(RxPdu_PSD_06 &&) = default; // default move ctor
   RxPdu_PSD_06 & operator=(RxPdu_PSD_06 const &) = default; // default copy assignment
   RxPdu_PSD_06 & operator=(RxPdu_PSD_06 &&) = default; // default move assignment

   PduStatus getPduStatus() const noexcept;

   std::uint32_t get_PSD_06_Mux() const noexcept; // 3 bits
   std::uint32_t get_PSD_Sys_Segment_ID() const noexcept; // 6 bits
   std::uint32_t get_PSD_Attribut_Segment_ID() const noexcept; // 6 bits
   std::uint32_t get_PSD_Ges_Segment_ID() const noexcept; // 6 bits
   bool get_PSD_Baum_Laenge_VZ() const noexcept; // 1 bit
   std::uint32_t get_PSD_Steigung_1_Segment_ID() const noexcept; // 6 bits
   std::uint32_t get_PSD_Baum_Laenge() const noexcept; // 25 bits
   std::uint32_t get_PSD_Sys_Laendercode() const noexcept; // 8 bits
   std::uint32_t get_PSD_Attribut_3_ID() const noexcept; // 5 bits
   std::uint32_t get_PSD_Ges_Offset() const noexcept; // 7 bits
   std::uint32_t get_PSD_Steigung_1_A_Steigung() const noexcept; // 7 bits
   std::uint32_t get_PSD_Attribut_3_Offset() const noexcept; // 7 bits
   std::uint32_t get_PSD_Ges_Geschwindigkeit() const noexcept; // 5 bits
   bool get_PSD_Steigung_1_A_Vorz() const noexcept; // 1 bit
   bool get_PSD_Sys_Geschwindigkeit_Einheit() const noexcept; // 1 bit
   std::uint32_t get_PSD_Steigung_1_A_Offset() const noexcept; // 7 bits
   bool get_PSD_Sys_Verkehrsrichtung() const noexcept; // 1 bit
   std::uint32_t get_PSD_Sys_Geometrieguete() const noexcept; // 2 bits
   std::uint32_t get_PSD_Sys_Mapmatchingguete() const noexcept; // 2 bits
   std::uint32_t get_PSD_Attribut_3_Wert() const noexcept; // 4 bits
   std::uint32_t get_PSD_Ges_Typ() const noexcept; // 2 bits
   std::uint32_t get_PSD_Sys_Alter_Karte() const noexcept; // 3 bits
   std::uint32_t get_PSD_Ges_Spur_Geschw_Begrenzung() const noexcept; // 6 bits
   std::uint32_t get_PSD_Steigung_1_B_Steigung() const noexcept; // 7 bits
   std::uint32_t get_PSD_Attribut_4_ID() const noexcept; // 5 bits
   bool get_PSD_Sys_Zielfuehrung() const noexcept; // 1 bit
   std::uint32_t get_PSD_Sys_US_State() const noexcept; // 6 bits
   std::uint32_t get_PSD_Ges_Geschwindigkeit_Gespann() const noexcept; // 2 bits
   bool get_PSD_Baum_Breite_VZ() const noexcept; // 1 bit
   std::uint32_t get_PSD_Attribut_4_Wert() const noexcept; // 4 bits
   std::uint32_t get_PSD_Baum_Breite() const noexcept; // 24 bits
   std::uint32_t get_PSD_Ges_Geschwindigkeit_Witter() const noexcept; // 2 bits
   bool get_PSD_Steigung_1_B_Vorz() const noexcept; // 1 bit
   std::uint32_t get_PSD_Steigung_1_B_Offset() const noexcept; // 7 bits
   std::uint32_t get_PSD_Sys_Quali_Geometrien() const noexcept; // 3 bits
   std::uint32_t get_PSD_Ges_Geschwindigkeit_Tag_Anf() const noexcept; // 3 bits
   std::uint32_t get_PSD_Attribut_4_Offset() const noexcept; // 7 bits
   std::uint32_t get_PSD_Sys_Quali_Ortsinfo() const noexcept; // 2 bits
   std::uint32_t get_PSD_Ges_Geschwindigkeit_Tag_Ende() const noexcept; // 3 bits
   bool get_PSD_Sys_Quali_verfuegbar() const noexcept; // 1 bit
   bool get_PSD_Sys_Zielfuehrung_geaendert() const noexcept; // 1 bit
   std::uint32_t get_PSD_Ges_Geschwindigkeit_Std_Anf() const noexcept; // 5 bits
   bool get_PSD_Steigung_1_Attribute_kompl() const noexcept; // 1 bit
   std::uint32_t get_PSD_Sys_Geometrieguete_erweitert() const noexcept; // 8 bits
   std::uint32_t get_PSD_Steigung_2_Segment_ID() const noexcept; // 6 bits
   std::uint32_t get_PSD_Attribut_5_ID() const noexcept; // 5 bits
   std::uint32_t get_PSD_Ges_Geschwindigkeit_Std_Ende() const noexcept; // 5 bits
   std::uint32_t get_PSD_Attribut_5_Offset() const noexcept; // 7 bits
   std::uint32_t get_PSD_Steigung_2_Steigung() const noexcept; // 7 bits
   std::uint32_t get_PSD_Sys_Quali_sonstige_Attribute() const noexcept; // 3 bits
   std::uint32_t get_PSD_Ges_Ueberholverbot() const noexcept; // 2 bits
   std::uint32_t get_PSD_Sys_Quali_Steigungen() const noexcept; // 3 bits
   std::uint32_t get_PSD_Ges_Wechselverkehrszeichen() const noexcept; // 3 bits
   std::uint32_t get_PSD_Attribut_5_Wert() const noexcept; // 4 bits
   bool get_PSD_Steigung_2_Vorz() const noexcept; // 1 bit
   std::uint32_t get_PSD_Sys_Quali_Strassenkennz() const noexcept; // 3 bits
   std::uint32_t get_PSD_Wechselverkehrszeichen_Typ() const noexcept; // 2 bits
   std::uint32_t get_PSD_Baum_Ausrichtung() const noexcept; // 10 bits
   std::uint32_t get_PSD_Steigung_2_Offset() const noexcept; // 7 bits
   std::uint32_t get_PSD_Ges_Gesetzlich_Kategorie() const noexcept; // 3 bits
   std::uint32_t get_PSD_Sys_Quali_Tempolimits() const noexcept; // 3 bits
   bool get_PSD_Attribute_Komplett_06() const noexcept; // 1 bit
   std::uint32_t get_PSD_Ges_Gesetzlich_Zusatz() const noexcept; // 2 bits
   std::uint32_t get_PSD_Sys_Quali_Vorfahrtsregelung() const noexcept; // 3 bits
   std::uint32_t get_PSD_Ges_Verkehrszeichen_Quelle() const noexcept; // 2 bits
   bool get_PSD_Steigung_2_Attribute_kompl() const noexcept; // 1 bit
   bool get_PSD_Ges_Attribute_Komplett() const noexcept; // 1 bit

   // --   END: public API for target code


   // -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING
public:
   void FOR_TESTING_setPduStatus(PduStatus status) noexcept;

   void FOR_TESTING_set_PSD_06_Mux(std::uint32_t) noexcept; // 3 bits
   void FOR_TESTING_set_PSD_Sys_Segment_ID(std::uint32_t) noexcept; // 6 bits
   void FOR_TESTING_set_PSD_Attribut_Segment_ID(std::uint32_t) noexcept; // 6 bits
   void FOR_TESTING_set_PSD_Ges_Segment_ID(std::uint32_t) noexcept; // 6 bits
   void FOR_TESTING_set_PSD_Baum_Laenge_VZ(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Steigung_1_Segment_ID(std::uint32_t) noexcept; // 6 bits
   void FOR_TESTING_set_PSD_Baum_Laenge(std::uint32_t) noexcept; // 25 bits
   void FOR_TESTING_set_PSD_Sys_Laendercode(std::uint32_t) noexcept; // 8 bits
   void FOR_TESTING_set_PSD_Attribut_3_ID(std::uint32_t) noexcept; // 5 bits
   void FOR_TESTING_set_PSD_Ges_Offset(std::uint32_t) noexcept; // 7 bits
   void FOR_TESTING_set_PSD_Steigung_1_A_Steigung(std::uint32_t) noexcept; // 7 bits
   void FOR_TESTING_set_PSD_Attribut_3_Offset(std::uint32_t) noexcept; // 7 bits
   void FOR_TESTING_set_PSD_Ges_Geschwindigkeit(std::uint32_t) noexcept; // 5 bits
   void FOR_TESTING_set_PSD_Steigung_1_A_Vorz(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Sys_Geschwindigkeit_Einheit(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Steigung_1_A_Offset(std::uint32_t) noexcept; // 7 bits
   void FOR_TESTING_set_PSD_Sys_Verkehrsrichtung(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Sys_Geometrieguete(std::uint32_t) noexcept; // 2 bits
   void FOR_TESTING_set_PSD_Sys_Mapmatchingguete(std::uint32_t) noexcept; // 2 bits
   void FOR_TESTING_set_PSD_Attribut_3_Wert(std::uint32_t) noexcept; // 4 bits
   void FOR_TESTING_set_PSD_Ges_Typ(std::uint32_t) noexcept; // 2 bits
   void FOR_TESTING_set_PSD_Sys_Alter_Karte(std::uint32_t) noexcept; // 3 bits
   void FOR_TESTING_set_PSD_Ges_Spur_Geschw_Begrenzung(std::uint32_t) noexcept; // 6 bits
   void FOR_TESTING_set_PSD_Steigung_1_B_Steigung(std::uint32_t) noexcept; // 7 bits
   void FOR_TESTING_set_PSD_Attribut_4_ID(std::uint32_t) noexcept; // 5 bits
   void FOR_TESTING_set_PSD_Sys_Zielfuehrung(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Sys_US_State(std::uint32_t) noexcept; // 6 bits
   void FOR_TESTING_set_PSD_Ges_Geschwindigkeit_Gespann(std::uint32_t) noexcept; // 2 bits
   void FOR_TESTING_set_PSD_Baum_Breite_VZ(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Attribut_4_Wert(std::uint32_t) noexcept; // 4 bits
   void FOR_TESTING_set_PSD_Baum_Breite(std::uint32_t) noexcept; // 24 bits
   void FOR_TESTING_set_PSD_Ges_Geschwindigkeit_Witter(std::uint32_t) noexcept; // 2 bits
   void FOR_TESTING_set_PSD_Steigung_1_B_Vorz(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Steigung_1_B_Offset(std::uint32_t) noexcept; // 7 bits
   void FOR_TESTING_set_PSD_Sys_Quali_Geometrien(std::uint32_t) noexcept; // 3 bits
   void FOR_TESTING_set_PSD_Ges_Geschwindigkeit_Tag_Anf(std::uint32_t) noexcept; // 3 bits
   void FOR_TESTING_set_PSD_Attribut_4_Offset(std::uint32_t) noexcept; // 7 bits
   void FOR_TESTING_set_PSD_Sys_Quali_Ortsinfo(std::uint32_t) noexcept; // 2 bits
   void FOR_TESTING_set_PSD_Ges_Geschwindigkeit_Tag_Ende(std::uint32_t) noexcept; // 3 bits
   void FOR_TESTING_set_PSD_Sys_Quali_verfuegbar(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Sys_Zielfuehrung_geaendert(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Ges_Geschwindigkeit_Std_Anf(std::uint32_t) noexcept; // 5 bits
   void FOR_TESTING_set_PSD_Steigung_1_Attribute_kompl(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Sys_Geometrieguete_erweitert(std::uint32_t) noexcept; // 8 bits
   void FOR_TESTING_set_PSD_Steigung_2_Segment_ID(std::uint32_t) noexcept; // 6 bits
   void FOR_TESTING_set_PSD_Attribut_5_ID(std::uint32_t) noexcept; // 5 bits
   void FOR_TESTING_set_PSD_Ges_Geschwindigkeit_Std_Ende(std::uint32_t) noexcept; // 5 bits
   void FOR_TESTING_set_PSD_Attribut_5_Offset(std::uint32_t) noexcept; // 7 bits
   void FOR_TESTING_set_PSD_Steigung_2_Steigung(std::uint32_t) noexcept; // 7 bits
   void FOR_TESTING_set_PSD_Sys_Quali_sonstige_Attribute(std::uint32_t) noexcept; // 3 bits
   void FOR_TESTING_set_PSD_Ges_Ueberholverbot(std::uint32_t) noexcept; // 2 bits
   void FOR_TESTING_set_PSD_Sys_Quali_Steigungen(std::uint32_t) noexcept; // 3 bits
   void FOR_TESTING_set_PSD_Ges_Wechselverkehrszeichen(std::uint32_t) noexcept; // 3 bits
   void FOR_TESTING_set_PSD_Attribut_5_Wert(std::uint32_t) noexcept; // 4 bits
   void FOR_TESTING_set_PSD_Steigung_2_Vorz(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Sys_Quali_Strassenkennz(std::uint32_t) noexcept; // 3 bits
   void FOR_TESTING_set_PSD_Wechselverkehrszeichen_Typ(std::uint32_t) noexcept; // 2 bits
   void FOR_TESTING_set_PSD_Baum_Ausrichtung(std::uint32_t) noexcept; // 10 bits
   void FOR_TESTING_set_PSD_Steigung_2_Offset(std::uint32_t) noexcept; // 7 bits
   void FOR_TESTING_set_PSD_Ges_Gesetzlich_Kategorie(std::uint32_t) noexcept; // 3 bits
   void FOR_TESTING_set_PSD_Sys_Quali_Tempolimits(std::uint32_t) noexcept; // 3 bits
   void FOR_TESTING_set_PSD_Attribute_Komplett_06(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Ges_Gesetzlich_Zusatz(std::uint32_t) noexcept; // 2 bits
   void FOR_TESTING_set_PSD_Sys_Quali_Vorfahrtsregelung(std::uint32_t) noexcept; // 3 bits
   void FOR_TESTING_set_PSD_Ges_Verkehrszeichen_Quelle(std::uint32_t) noexcept; // 2 bits
   void FOR_TESTING_set_PSD_Steigung_2_Attribute_kompl(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Ges_Attribute_Komplett(bool) noexcept; // 1 bit
#endif // VWG_SID_CLIENT_TESTING

   // --   END: public API for testing & mocking purposes only


   // -- BEGIN: private API for internal use only

   void PRIVATE_setPduStatus(PduStatus status) noexcept;

   void PRIVATE_set_PSD_06_Mux(std::uint32_t) noexcept; // 3 bits
   void PRIVATE_set_PSD_Sys_Segment_ID(std::uint32_t) noexcept; // 6 bits
   void PRIVATE_set_PSD_Attribut_Segment_ID(std::uint32_t) noexcept; // 6 bits
   void PRIVATE_set_PSD_Ges_Segment_ID(std::uint32_t) noexcept; // 6 bits
   void PRIVATE_set_PSD_Baum_Laenge_VZ(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Steigung_1_Segment_ID(std::uint32_t) noexcept; // 6 bits
   void PRIVATE_set_PSD_Baum_Laenge(std::uint32_t) noexcept; // 25 bits
   void PRIVATE_set_PSD_Sys_Laendercode(std::uint32_t) noexcept; // 8 bits
   void PRIVATE_set_PSD_Attribut_3_ID(std::uint32_t) noexcept; // 5 bits
   void PRIVATE_set_PSD_Ges_Offset(std::uint32_t) noexcept; // 7 bits
   void PRIVATE_set_PSD_Steigung_1_A_Steigung(std::uint32_t) noexcept; // 7 bits
   void PRIVATE_set_PSD_Attribut_3_Offset(std::uint32_t) noexcept; // 7 bits
   void PRIVATE_set_PSD_Ges_Geschwindigkeit(std::uint32_t) noexcept; // 5 bits
   void PRIVATE_set_PSD_Steigung_1_A_Vorz(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Sys_Geschwindigkeit_Einheit(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Steigung_1_A_Offset(std::uint32_t) noexcept; // 7 bits
   void PRIVATE_set_PSD_Sys_Verkehrsrichtung(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Sys_Geometrieguete(std::uint32_t) noexcept; // 2 bits
   void PRIVATE_set_PSD_Sys_Mapmatchingguete(std::uint32_t) noexcept; // 2 bits
   void PRIVATE_set_PSD_Attribut_3_Wert(std::uint32_t) noexcept; // 4 bits
   void PRIVATE_set_PSD_Ges_Typ(std::uint32_t) noexcept; // 2 bits
   void PRIVATE_set_PSD_Sys_Alter_Karte(std::uint32_t) noexcept; // 3 bits
   void PRIVATE_set_PSD_Ges_Spur_Geschw_Begrenzung(std::uint32_t) noexcept; // 6 bits
   void PRIVATE_set_PSD_Steigung_1_B_Steigung(std::uint32_t) noexcept; // 7 bits
   void PRIVATE_set_PSD_Attribut_4_ID(std::uint32_t) noexcept; // 5 bits
   void PRIVATE_set_PSD_Sys_Zielfuehrung(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Sys_US_State(std::uint32_t) noexcept; // 6 bits
   void PRIVATE_set_PSD_Ges_Geschwindigkeit_Gespann(std::uint32_t) noexcept; // 2 bits
   void PRIVATE_set_PSD_Baum_Breite_VZ(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Attribut_4_Wert(std::uint32_t) noexcept; // 4 bits
   void PRIVATE_set_PSD_Baum_Breite(std::uint32_t) noexcept; // 24 bits
   void PRIVATE_set_PSD_Ges_Geschwindigkeit_Witter(std::uint32_t) noexcept; // 2 bits
   void PRIVATE_set_PSD_Steigung_1_B_Vorz(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Steigung_1_B_Offset(std::uint32_t) noexcept; // 7 bits
   void PRIVATE_set_PSD_Sys_Quali_Geometrien(std::uint32_t) noexcept; // 3 bits
   void PRIVATE_set_PSD_Ges_Geschwindigkeit_Tag_Anf(std::uint32_t) noexcept; // 3 bits
   void PRIVATE_set_PSD_Attribut_4_Offset(std::uint32_t) noexcept; // 7 bits
   void PRIVATE_set_PSD_Sys_Quali_Ortsinfo(std::uint32_t) noexcept; // 2 bits
   void PRIVATE_set_PSD_Ges_Geschwindigkeit_Tag_Ende(std::uint32_t) noexcept; // 3 bits
   void PRIVATE_set_PSD_Sys_Quali_verfuegbar(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Sys_Zielfuehrung_geaendert(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Ges_Geschwindigkeit_Std_Anf(std::uint32_t) noexcept; // 5 bits
   void PRIVATE_set_PSD_Steigung_1_Attribute_kompl(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Sys_Geometrieguete_erweitert(std::uint32_t) noexcept; // 8 bits
   void PRIVATE_set_PSD_Steigung_2_Segment_ID(std::uint32_t) noexcept; // 6 bits
   void PRIVATE_set_PSD_Attribut_5_ID(std::uint32_t) noexcept; // 5 bits
   void PRIVATE_set_PSD_Ges_Geschwindigkeit_Std_Ende(std::uint32_t) noexcept; // 5 bits
   void PRIVATE_set_PSD_Attribut_5_Offset(std::uint32_t) noexcept; // 7 bits
   void PRIVATE_set_PSD_Steigung_2_Steigung(std::uint32_t) noexcept; // 7 bits
   void PRIVATE_set_PSD_Sys_Quali_sonstige_Attribute(std::uint32_t) noexcept; // 3 bits
   void PRIVATE_set_PSD_Ges_Ueberholverbot(std::uint32_t) noexcept; // 2 bits
   void PRIVATE_set_PSD_Sys_Quali_Steigungen(std::uint32_t) noexcept; // 3 bits
   void PRIVATE_set_PSD_Ges_Wechselverkehrszeichen(std::uint32_t) noexcept; // 3 bits
   void PRIVATE_set_PSD_Attribut_5_Wert(std::uint32_t) noexcept; // 4 bits
   void PRIVATE_set_PSD_Steigung_2_Vorz(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Sys_Quali_Strassenkennz(std::uint32_t) noexcept; // 3 bits
   void PRIVATE_set_PSD_Wechselverkehrszeichen_Typ(std::uint32_t) noexcept; // 2 bits
   void PRIVATE_set_PSD_Baum_Ausrichtung(std::uint32_t) noexcept; // 10 bits
   void PRIVATE_set_PSD_Steigung_2_Offset(std::uint32_t) noexcept; // 7 bits
   void PRIVATE_set_PSD_Ges_Gesetzlich_Kategorie(std::uint32_t) noexcept; // 3 bits
   void PRIVATE_set_PSD_Sys_Quali_Tempolimits(std::uint32_t) noexcept; // 3 bits
   void PRIVATE_set_PSD_Attribute_Komplett_06(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Ges_Gesetzlich_Zusatz(std::uint32_t) noexcept; // 2 bits
   void PRIVATE_set_PSD_Sys_Quali_Vorfahrtsregelung(std::uint32_t) noexcept; // 3 bits
   void PRIVATE_set_PSD_Ges_Verkehrszeichen_Quelle(std::uint32_t) noexcept; // 2 bits
   void PRIVATE_set_PSD_Steigung_2_Attribute_kompl(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Ges_Attribute_Komplett(bool) noexcept; // 1 bit

private:
   PduStatus status = PduStatus::kNotValid;
   std::uint32_t PSD_06_Mux_value;
   std::uint32_t PSD_Sys_Segment_ID_value;
   std::uint32_t PSD_Attribut_Segment_ID_value;
   std::uint32_t PSD_Ges_Segment_ID_value;
   bool PSD_Baum_Laenge_VZ_value;
   std::uint32_t PSD_Steigung_1_Segment_ID_value;
   std::uint32_t PSD_Baum_Laenge_value;
   std::uint32_t PSD_Sys_Laendercode_value;
   std::uint32_t PSD_Attribut_3_ID_value;
   std::uint32_t PSD_Ges_Offset_value;
   std::uint32_t PSD_Steigung_1_A_Steigung_value;
   std::uint32_t PSD_Attribut_3_Offset_value;
   std::uint32_t PSD_Ges_Geschwindigkeit_value;
   bool PSD_Steigung_1_A_Vorz_value;
   bool PSD_Sys_Geschwindigkeit_Einheit_value;
   std::uint32_t PSD_Steigung_1_A_Offset_value;
   bool PSD_Sys_Verkehrsrichtung_value;
   std::uint32_t PSD_Sys_Geometrieguete_value;
   std::uint32_t PSD_Sys_Mapmatchingguete_value;
   std::uint32_t PSD_Attribut_3_Wert_value;
   std::uint32_t PSD_Ges_Typ_value;
   std::uint32_t PSD_Sys_Alter_Karte_value;
   std::uint32_t PSD_Ges_Spur_Geschw_Begrenzung_value;
   std::uint32_t PSD_Steigung_1_B_Steigung_value;
   std::uint32_t PSD_Attribut_4_ID_value;
   bool PSD_Sys_Zielfuehrung_value;
   std::uint32_t PSD_Sys_US_State_value;
   std::uint32_t PSD_Ges_Geschwindigkeit_Gespann_value;
   bool PSD_Baum_Breite_VZ_value;
   std::uint32_t PSD_Attribut_4_Wert_value;
   std::uint32_t PSD_Baum_Breite_value;
   std::uint32_t PSD_Ges_Geschwindigkeit_Witter_value;
   bool PSD_Steigung_1_B_Vorz_value;
   std::uint32_t PSD_Steigung_1_B_Offset_value;
   std::uint32_t PSD_Sys_Quali_Geometrien_value;
   std::uint32_t PSD_Ges_Geschwindigkeit_Tag_Anf_value;
   std::uint32_t PSD_Attribut_4_Offset_value;
   std::uint32_t PSD_Sys_Quali_Ortsinfo_value;
   std::uint32_t PSD_Ges_Geschwindigkeit_Tag_Ende_value;
   bool PSD_Sys_Quali_verfuegbar_value;
   bool PSD_Sys_Zielfuehrung_geaendert_value;
   std::uint32_t PSD_Ges_Geschwindigkeit_Std_Anf_value;
   bool PSD_Steigung_1_Attribute_kompl_value;
   std::uint32_t PSD_Sys_Geometrieguete_erweitert_value;
   std::uint32_t PSD_Steigung_2_Segment_ID_value;
   std::uint32_t PSD_Attribut_5_ID_value;
   std::uint32_t PSD_Ges_Geschwindigkeit_Std_Ende_value;
   std::uint32_t PSD_Attribut_5_Offset_value;
   std::uint32_t PSD_Steigung_2_Steigung_value;
   std::uint32_t PSD_Sys_Quali_sonstige_Attribute_value;
   std::uint32_t PSD_Ges_Ueberholverbot_value;
   std::uint32_t PSD_Sys_Quali_Steigungen_value;
   std::uint32_t PSD_Ges_Wechselverkehrszeichen_value;
   std::uint32_t PSD_Attribut_5_Wert_value;
   bool PSD_Steigung_2_Vorz_value;
   std::uint32_t PSD_Sys_Quali_Strassenkennz_value;
   std::uint32_t PSD_Wechselverkehrszeichen_Typ_value;
   std::uint32_t PSD_Baum_Ausrichtung_value;
   std::uint32_t PSD_Steigung_2_Offset_value;
   std::uint32_t PSD_Ges_Gesetzlich_Kategorie_value;
   std::uint32_t PSD_Sys_Quali_Tempolimits_value;
   bool PSD_Attribute_Komplett_06_value;
   std::uint32_t PSD_Ges_Gesetzlich_Zusatz_value;
   std::uint32_t PSD_Sys_Quali_Vorfahrtsregelung_value;
   std::uint32_t PSD_Ges_Verkehrszeichen_Quelle_value;
   bool PSD_Steigung_2_Attribute_kompl_value;
   bool PSD_Ges_Attribute_Komplett_value;

   // --   END: private API for internal use only
};

// The ISignalDataListener class is only defined as an interface and has to be
// implemented by the client code.  For each PDU that the application wants
// to receive the interface holds an receivedPdu_xxx method.
//
// A receivedPdu_xxx method will be called...
//
//   a) after the SignalDataAccessHandler is started: The framework will
//      provide all PDU data initially, because afterwards only updates will
//      be received.  The data that is received in this phase may be partition
//      local default data for some PDUs, if those PDUs have at this time not
//      actually been received from the car network.  This would be reflected
//      by a PduStatus of kNotYetReceived in the respective RxPdu_xxx
//      instance.
//
//   b) when the PduStatus for this PDU has changed.  For example, if the
//      platform software does not receive the PDU from the car network for
//      some time, then the PduStatus will change to kTimedOut, and this
//      change will be communicated to the application via receivedPdu_xxx.
//
//   c) when the platform receives the PDU, and one of the signal values that
//      the application is subscribed to has changed.  In this case, the
//      platform will provide an update with all changed signals (but possibly
//      also with unchanged ones) to the application.

class ISignalDataListener {
public:
   virtual ~ISignalDataListener() = default;

   virtual void receivedPdu_PSD_04 (RxPdu_PSD_04 const &) = 0;
   virtual void receivedPdu_PSD_05 (RxPdu_PSD_05 const &) = 0;
   virtual void receivedPdu_PSD_06 (RxPdu_PSD_06 const &) = 0;
};

// For sending PDU data, applications only have to provide updates of their
// data to the framework.  All further aspects related to the sending of PDUs
// are handled by the framework: The framework will, for example, take care of
// ensuring PDUs are sent out cyclically on the car network with the defined
// cycle time.
//
// TxPdu_xxx classes are for providing updates of PDU signal data to the
// framework.  Each class holds a default constructor and setter methods for
// the signals.
//
// The set of signals in a TxPdu_xxx class is not necessarily the complete set
// of signals of the PDU: An application may only be responsible for the
// sending of a subset of the PDU's signals.  In such a case the TxPdu_xxx
// class that is part of the API for this application will also only contain
// setters for those signals that this application is responsible for.
//
// Having two applications configured as senders for the same signal has
// undefined behaviour.
//
// Before sending out an instance of a TxPdu_xxx class from within one
// application, all signal values of that PDU that the application is
// responsible for must have been set.  In other words, after creation of a
// TxPdu_xxx instance and before sending this instance, all setter methods
// must have been called.  There is no defined default value for a signal
// within a TxPdu_xxx instance.
//
// TBD: For PDUs with multiplexed signals some special rules may have to be
// added here.  Please contact the responsibles for this API when you have to
// deal with multiplexed signals for sending.
//
// The attempt to send out an TxPdu_xxx instance where not all signal values
// that this application is responsible for have been set has undefined
// behaviour.
//
// The argument provided to a setter method for a signal shall not use more
// bits than defined in the respective data definition for that signal.  Any
// extra bits must be set to zero.  For a signal with n bits therefore only
// the bits 2^0 .. 2^(n-1) may hold non-zero values.  This also applies for
// signal values of type vector<std::uint8_t>: The byte at vector index 0
// holds the bits 2^0 .. 2^7, the byte at index 1 holds the bits 2^8 .. 2^15
// etc.
//
// Calling a setter method with an argument that uses more bits than allowed
// has undefined behaviour.


enum class ConnectionState {
   kConnecting,
   kConnected,
   kDisconnecting,
   kDisconnected
};

using ConnectionStateNotificationCallback = std::function<void (ConnectionState) noexcept>; // shall not block

class ISignalDataAccessHandler {
public:
   virtual ~ISignalDataAccessHandler() = default;

   /**
    * Start the underlying communication with the partition's signal
    * communication framework.  It is not allowed for applications to call
    * this method more than once.
    *
    * Implementation note: This shall intentionally not be done by or from
    * within the constructor, but in the separate start method: As this most
    * likely includes concurrent activities we want to be sure it is done
    * after the ISignalDataAccessHandler object is fully constructed.  This
    * shall avoid potential race conditions where a partly constructed object
    * is accessed.
    * 
    * The referenced listener object is expected to be valid allover the 
    * runtime (infinite lifetime). Neighter shall it be destroyed while system 
    * is suspending nor shall it refer to any resource that is not available 
    * anymore when system suspend is initiated.
    */
   virtual void start(std::shared_ptr<ISignalDataListener>, ConnectionStateNotificationCallback) = 0;

   [[deprecated]] void start(std::shared_ptr<ISignalDataListener> p) {
      ConnectionStateNotificationCallback cb = [](ConnectionState) noexcept ->void {};
      this->start(p, cb);
   }

   /**
    * Suspend the communication as part of a preparation for shutdown or
    * suspend to RAM.
    */
   virtual void suspend() = 0;

   /**
    * Resume the communication after suspend.
    */
   virtual void resume() = 0;

};

/**
 * The following function will return the singleton instance of
 * vwg::sid::PSDParser::ISignalDataAccessHandler.
 */
ISignalDataAccessHandler & getSignalDataAccessHandler();

[[deprecated]]
inline std::unique_ptr<ISignalDataAccessHandler> createSignalDataAccessHandler() {
   return std::unique_ptr<ISignalDataAccessHandler>(&getSignalDataAccessHandler());
}

} /* namespace PSDParser */
} /* namespace sid */
} /* namespace vwg */

#endif // VWG_SID_PSDPARSER_SIGNAL_DATA_ACCESS_HPP_
