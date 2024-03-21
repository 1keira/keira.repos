/**
 * \file simple_data_access_pdu.cpp
 *
 * \brief System-API PDU implementation for signal data access
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

// signal api includes
#include <vwg/sid/PSDParser/signal_data_access.hpp>

namespace vwg {
namespace sid {
namespace PSDParser {

// -- Rx PDU PSD_04 with 18 signals

// -- BEGIN: public API for target code

PduStatus RxPdu_PSD_04::getPduStatus() const noexcept { return status; }

std::uint32_t RxPdu_PSD_04::get_PSD_Segment_ID() const noexcept { return PSD_Segment_ID_value; } // 6 bits
std::uint32_t RxPdu_PSD_04::get_PSD_Vorgaenger_Segment_ID() const noexcept { return PSD_Vorgaenger_Segment_ID_value; } // 6 bits
std::uint32_t RxPdu_PSD_04::get_PSD_Segmentlaenge() const noexcept { return PSD_Segmentlaenge_value; } // 7 bits
std::uint32_t RxPdu_PSD_04::get_PSD_Strassenkategorie() const noexcept { return PSD_Strassenkategorie_value; } // 3 bits
std::uint32_t RxPdu_PSD_04::get_PSD_Endkruemmung() const noexcept { return PSD_Endkruemmung_value; } // 8 bits
bool RxPdu_PSD_04::get_PSD_Endkruemmung_Vorz() const noexcept { return PSD_Endkruemmung_Vorz_value; } // 1 bit
std::uint32_t RxPdu_PSD_04::get_PSD_Idenditaets_ID() const noexcept { return PSD_Idenditaets_ID_value; } // 6 bits
bool RxPdu_PSD_04::get_PSD_ADAS_Qualitaet() const noexcept { return PSD_ADAS_Qualitaet_value; } // 1 bit
bool RxPdu_PSD_04::get_PSD_wahrscheinlichster_Pfad() const noexcept { return PSD_wahrscheinlichster_Pfad_value; } // 1 bit
bool RxPdu_PSD_04::get_PSD_Geradester_Pfad() const noexcept { return PSD_Geradester_Pfad_value; } // 1 bit
std::uint32_t RxPdu_PSD_04::get_PSD_Fahrspuren_Anzahl() const noexcept { return PSD_Fahrspuren_Anzahl_value; } // 3 bits
bool RxPdu_PSD_04::get_PSD_Bebauung() const noexcept { return PSD_Bebauung_value; } // 1 bit
bool RxPdu_PSD_04::get_PSD_Segment_Komplett() const noexcept { return PSD_Segment_Komplett_value; } // 1 bit
std::uint32_t RxPdu_PSD_04::get_PSD_Rampe() const noexcept { return PSD_Rampe_value; } // 2 bits
std::uint32_t RxPdu_PSD_04::get_PSD_Anfangskruemmung() const noexcept { return PSD_Anfangskruemmung_value; } // 8 bits
bool RxPdu_PSD_04::get_PSD_Anfangskruemmung_Vorz() const noexcept { return PSD_Anfangskruemmung_Vorz_value; } // 1 bit
bool RxPdu_PSD_04::get_PSD_Abzweigerichtung() const noexcept { return PSD_Abzweigerichtung_value; } // 1 bit
std::uint32_t RxPdu_PSD_04::get_PSD_Abzweigewinkel() const noexcept { return PSD_Abzweigewinkel_value; } // 7 bits

// --   END: public API for target code


// -- BEGIN: private API for internal use only

void RxPdu_PSD_04::PRIVATE_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_PSD_04::PRIVATE_set_PSD_Segment_ID(std::uint32_t value) noexcept { PSD_Segment_ID_value = value; return; } // 6 bits
void RxPdu_PSD_04::PRIVATE_set_PSD_Vorgaenger_Segment_ID(std::uint32_t value) noexcept { PSD_Vorgaenger_Segment_ID_value = value; return; } // 6 bits
void RxPdu_PSD_04::PRIVATE_set_PSD_Segmentlaenge(std::uint32_t value) noexcept { PSD_Segmentlaenge_value = value; return; } // 7 bits
void RxPdu_PSD_04::PRIVATE_set_PSD_Strassenkategorie(std::uint32_t value) noexcept { PSD_Strassenkategorie_value = value; return; } // 3 bits
void RxPdu_PSD_04::PRIVATE_set_PSD_Endkruemmung(std::uint32_t value) noexcept { PSD_Endkruemmung_value = value; return; } // 8 bits
void RxPdu_PSD_04::PRIVATE_set_PSD_Endkruemmung_Vorz(bool value) noexcept { PSD_Endkruemmung_Vorz_value = value; return; } // 1 bit
void RxPdu_PSD_04::PRIVATE_set_PSD_Idenditaets_ID(std::uint32_t value) noexcept { PSD_Idenditaets_ID_value = value; return; } // 6 bits
void RxPdu_PSD_04::PRIVATE_set_PSD_ADAS_Qualitaet(bool value) noexcept { PSD_ADAS_Qualitaet_value = value; return; } // 1 bit
void RxPdu_PSD_04::PRIVATE_set_PSD_wahrscheinlichster_Pfad(bool value) noexcept { PSD_wahrscheinlichster_Pfad_value = value; return; } // 1 bit
void RxPdu_PSD_04::PRIVATE_set_PSD_Geradester_Pfad(bool value) noexcept { PSD_Geradester_Pfad_value = value; return; } // 1 bit
void RxPdu_PSD_04::PRIVATE_set_PSD_Fahrspuren_Anzahl(std::uint32_t value) noexcept { PSD_Fahrspuren_Anzahl_value = value; return; } // 3 bits
void RxPdu_PSD_04::PRIVATE_set_PSD_Bebauung(bool value) noexcept { PSD_Bebauung_value = value; return; } // 1 bit
void RxPdu_PSD_04::PRIVATE_set_PSD_Segment_Komplett(bool value) noexcept { PSD_Segment_Komplett_value = value; return; } // 1 bit
void RxPdu_PSD_04::PRIVATE_set_PSD_Rampe(std::uint32_t value) noexcept { PSD_Rampe_value = value; return; } // 2 bits
void RxPdu_PSD_04::PRIVATE_set_PSD_Anfangskruemmung(std::uint32_t value) noexcept { PSD_Anfangskruemmung_value = value; return; } // 8 bits
void RxPdu_PSD_04::PRIVATE_set_PSD_Anfangskruemmung_Vorz(bool value) noexcept { PSD_Anfangskruemmung_Vorz_value = value; return; } // 1 bit
void RxPdu_PSD_04::PRIVATE_set_PSD_Abzweigerichtung(bool value) noexcept { PSD_Abzweigerichtung_value = value; return; } // 1 bit
void RxPdu_PSD_04::PRIVATE_set_PSD_Abzweigewinkel(std::uint32_t value) noexcept { PSD_Abzweigewinkel_value = value; return; } // 7 bits

// --   END: private API for internal use only


// -- Rx PDU PSD_05 with 14 signals

// -- BEGIN: public API for target code

PduStatus RxPdu_PSD_05::getPduStatus() const noexcept { return status; }

std::uint32_t RxPdu_PSD_05::get_PSD_Pos_Segment_ID() const noexcept { return PSD_Pos_Segment_ID_value; } // 6 bits
std::uint32_t RxPdu_PSD_05::get_PSD_Pos_Segmentlaenge() const noexcept { return PSD_Pos_Segmentlaenge_value; } // 7 bits
std::uint32_t RxPdu_PSD_05::get_PSD_Pos_Inhibitzeit() const noexcept { return PSD_Pos_Inhibitzeit_value; } // 5 bits
bool RxPdu_PSD_05::get_PSD_Pos_Standort_Eindeutig() const noexcept { return PSD_Pos_Standort_Eindeutig_value; } // 1 bit
std::uint32_t RxPdu_PSD_05::get_PSD_Pos_Fehler_Laengsrichtung() const noexcept { return PSD_Pos_Fehler_Laengsrichtung_value; } // 3 bits
std::uint32_t RxPdu_PSD_05::get_PSD_Pos_Fahrspur() const noexcept { return PSD_Pos_Fahrspur_value; } // 3 bits
std::uint32_t RxPdu_PSD_05::get_PSD_Attribut_Segment_ID_05() const noexcept { return PSD_Attribut_Segment_ID_05_value; } // 6 bits
std::uint32_t RxPdu_PSD_05::get_PSD_Attribut_1_ID() const noexcept { return PSD_Attribut_1_ID_value; } // 5 bits
std::uint32_t RxPdu_PSD_05::get_PSD_Attribut_1_Wert() const noexcept { return PSD_Attribut_1_Wert_value; } // 4 bits
std::uint32_t RxPdu_PSD_05::get_PSD_Attribut_1_Offset() const noexcept { return PSD_Attribut_1_Offset_value; } // 7 bits
std::uint32_t RxPdu_PSD_05::get_PSD_Attribut_2_ID() const noexcept { return PSD_Attribut_2_ID_value; } // 5 bits
std::uint32_t RxPdu_PSD_05::get_PSD_Attribut_2_Wert() const noexcept { return PSD_Attribut_2_Wert_value; } // 4 bits
std::uint32_t RxPdu_PSD_05::get_PSD_Attribut_2_Offset() const noexcept { return PSD_Attribut_2_Offset_value; } // 7 bits
bool RxPdu_PSD_05::get_PSD_Attribute_Komplett_05() const noexcept { return PSD_Attribute_Komplett_05_value; } // 1 bit

// --   END: public API for target code


// -- BEGIN: private API for internal use only

void RxPdu_PSD_05::PRIVATE_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_PSD_05::PRIVATE_set_PSD_Pos_Segment_ID(std::uint32_t value) noexcept { PSD_Pos_Segment_ID_value = value; return; } // 6 bits
void RxPdu_PSD_05::PRIVATE_set_PSD_Pos_Segmentlaenge(std::uint32_t value) noexcept { PSD_Pos_Segmentlaenge_value = value; return; } // 7 bits
void RxPdu_PSD_05::PRIVATE_set_PSD_Pos_Inhibitzeit(std::uint32_t value) noexcept { PSD_Pos_Inhibitzeit_value = value; return; } // 5 bits
void RxPdu_PSD_05::PRIVATE_set_PSD_Pos_Standort_Eindeutig(bool value) noexcept { PSD_Pos_Standort_Eindeutig_value = value; return; } // 1 bit
void RxPdu_PSD_05::PRIVATE_set_PSD_Pos_Fehler_Laengsrichtung(std::uint32_t value) noexcept { PSD_Pos_Fehler_Laengsrichtung_value = value; return; } // 3 bits
void RxPdu_PSD_05::PRIVATE_set_PSD_Pos_Fahrspur(std::uint32_t value) noexcept { PSD_Pos_Fahrspur_value = value; return; } // 3 bits
void RxPdu_PSD_05::PRIVATE_set_PSD_Attribut_Segment_ID_05(std::uint32_t value) noexcept { PSD_Attribut_Segment_ID_05_value = value; return; } // 6 bits
void RxPdu_PSD_05::PRIVATE_set_PSD_Attribut_1_ID(std::uint32_t value) noexcept { PSD_Attribut_1_ID_value = value; return; } // 5 bits
void RxPdu_PSD_05::PRIVATE_set_PSD_Attribut_1_Wert(std::uint32_t value) noexcept { PSD_Attribut_1_Wert_value = value; return; } // 4 bits
void RxPdu_PSD_05::PRIVATE_set_PSD_Attribut_1_Offset(std::uint32_t value) noexcept { PSD_Attribut_1_Offset_value = value; return; } // 7 bits
void RxPdu_PSD_05::PRIVATE_set_PSD_Attribut_2_ID(std::uint32_t value) noexcept { PSD_Attribut_2_ID_value = value; return; } // 5 bits
void RxPdu_PSD_05::PRIVATE_set_PSD_Attribut_2_Wert(std::uint32_t value) noexcept { PSD_Attribut_2_Wert_value = value; return; } // 4 bits
void RxPdu_PSD_05::PRIVATE_set_PSD_Attribut_2_Offset(std::uint32_t value) noexcept { PSD_Attribut_2_Offset_value = value; return; } // 7 bits
void RxPdu_PSD_05::PRIVATE_set_PSD_Attribute_Komplett_05(bool value) noexcept { PSD_Attribute_Komplett_05_value = value; return; } // 1 bit

// --   END: private API for internal use only


// -- Rx PDU PSD_06 with 67 signals

// -- BEGIN: public API for target code

PduStatus RxPdu_PSD_06::getPduStatus() const noexcept { return status; }

std::uint32_t RxPdu_PSD_06::get_PSD_06_Mux() const noexcept { return PSD_06_Mux_value; } // 3 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Sys_Segment_ID() const noexcept { return PSD_Sys_Segment_ID_value; } // 6 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Attribut_Segment_ID() const noexcept { return PSD_Attribut_Segment_ID_value; } // 6 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Ges_Segment_ID() const noexcept { return PSD_Ges_Segment_ID_value; } // 6 bits
bool RxPdu_PSD_06::get_PSD_Baum_Laenge_VZ() const noexcept { return PSD_Baum_Laenge_VZ_value; } // 1 bit
std::uint32_t RxPdu_PSD_06::get_PSD_Steigung_1_Segment_ID() const noexcept { return PSD_Steigung_1_Segment_ID_value; } // 6 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Baum_Laenge() const noexcept { return PSD_Baum_Laenge_value; } // 25 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Sys_Laendercode() const noexcept { return PSD_Sys_Laendercode_value; } // 8 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Attribut_3_ID() const noexcept { return PSD_Attribut_3_ID_value; } // 5 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Ges_Offset() const noexcept { return PSD_Ges_Offset_value; } // 7 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Steigung_1_A_Steigung() const noexcept { return PSD_Steigung_1_A_Steigung_value; } // 7 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Attribut_3_Offset() const noexcept { return PSD_Attribut_3_Offset_value; } // 7 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Ges_Geschwindigkeit() const noexcept { return PSD_Ges_Geschwindigkeit_value; } // 5 bits
bool RxPdu_PSD_06::get_PSD_Steigung_1_A_Vorz() const noexcept { return PSD_Steigung_1_A_Vorz_value; } // 1 bit
bool RxPdu_PSD_06::get_PSD_Sys_Geschwindigkeit_Einheit() const noexcept { return PSD_Sys_Geschwindigkeit_Einheit_value; } // 1 bit
std::uint32_t RxPdu_PSD_06::get_PSD_Steigung_1_A_Offset() const noexcept { return PSD_Steigung_1_A_Offset_value; } // 7 bits
bool RxPdu_PSD_06::get_PSD_Sys_Verkehrsrichtung() const noexcept { return PSD_Sys_Verkehrsrichtung_value; } // 1 bit
std::uint32_t RxPdu_PSD_06::get_PSD_Sys_Geometrieguete() const noexcept { return PSD_Sys_Geometrieguete_value; } // 2 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Sys_Mapmatchingguete() const noexcept { return PSD_Sys_Mapmatchingguete_value; } // 2 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Attribut_3_Wert() const noexcept { return PSD_Attribut_3_Wert_value; } // 4 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Ges_Typ() const noexcept { return PSD_Ges_Typ_value; } // 2 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Sys_Alter_Karte() const noexcept { return PSD_Sys_Alter_Karte_value; } // 3 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Ges_Spur_Geschw_Begrenzung() const noexcept { return PSD_Ges_Spur_Geschw_Begrenzung_value; } // 6 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Steigung_1_B_Steigung() const noexcept { return PSD_Steigung_1_B_Steigung_value; } // 7 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Attribut_4_ID() const noexcept { return PSD_Attribut_4_ID_value; } // 5 bits
bool RxPdu_PSD_06::get_PSD_Sys_Zielfuehrung() const noexcept { return PSD_Sys_Zielfuehrung_value; } // 1 bit
std::uint32_t RxPdu_PSD_06::get_PSD_Sys_US_State() const noexcept { return PSD_Sys_US_State_value; } // 6 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Ges_Geschwindigkeit_Gespann() const noexcept { return PSD_Ges_Geschwindigkeit_Gespann_value; } // 2 bits
bool RxPdu_PSD_06::get_PSD_Baum_Breite_VZ() const noexcept { return PSD_Baum_Breite_VZ_value; } // 1 bit
std::uint32_t RxPdu_PSD_06::get_PSD_Attribut_4_Wert() const noexcept { return PSD_Attribut_4_Wert_value; } // 4 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Baum_Breite() const noexcept { return PSD_Baum_Breite_value; } // 24 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Ges_Geschwindigkeit_Witter() const noexcept { return PSD_Ges_Geschwindigkeit_Witter_value; } // 2 bits
bool RxPdu_PSD_06::get_PSD_Steigung_1_B_Vorz() const noexcept { return PSD_Steigung_1_B_Vorz_value; } // 1 bit
std::uint32_t RxPdu_PSD_06::get_PSD_Steigung_1_B_Offset() const noexcept { return PSD_Steigung_1_B_Offset_value; } // 7 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Sys_Quali_Geometrien() const noexcept { return PSD_Sys_Quali_Geometrien_value; } // 3 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Ges_Geschwindigkeit_Tag_Anf() const noexcept { return PSD_Ges_Geschwindigkeit_Tag_Anf_value; } // 3 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Attribut_4_Offset() const noexcept { return PSD_Attribut_4_Offset_value; } // 7 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Sys_Quali_Ortsinfo() const noexcept { return PSD_Sys_Quali_Ortsinfo_value; } // 2 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Ges_Geschwindigkeit_Tag_Ende() const noexcept { return PSD_Ges_Geschwindigkeit_Tag_Ende_value; } // 3 bits
bool RxPdu_PSD_06::get_PSD_Sys_Quali_verfuegbar() const noexcept { return PSD_Sys_Quali_verfuegbar_value; } // 1 bit
bool RxPdu_PSD_06::get_PSD_Sys_Zielfuehrung_geaendert() const noexcept { return PSD_Sys_Zielfuehrung_geaendert_value; } // 1 bit
std::uint32_t RxPdu_PSD_06::get_PSD_Ges_Geschwindigkeit_Std_Anf() const noexcept { return PSD_Ges_Geschwindigkeit_Std_Anf_value; } // 5 bits
bool RxPdu_PSD_06::get_PSD_Steigung_1_Attribute_kompl() const noexcept { return PSD_Steigung_1_Attribute_kompl_value; } // 1 bit
std::uint32_t RxPdu_PSD_06::get_PSD_Sys_Geometrieguete_erweitert() const noexcept { return PSD_Sys_Geometrieguete_erweitert_value; } // 8 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Steigung_2_Segment_ID() const noexcept { return PSD_Steigung_2_Segment_ID_value; } // 6 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Attribut_5_ID() const noexcept { return PSD_Attribut_5_ID_value; } // 5 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Ges_Geschwindigkeit_Std_Ende() const noexcept { return PSD_Ges_Geschwindigkeit_Std_Ende_value; } // 5 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Attribut_5_Offset() const noexcept { return PSD_Attribut_5_Offset_value; } // 7 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Steigung_2_Steigung() const noexcept { return PSD_Steigung_2_Steigung_value; } // 7 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Sys_Quali_sonstige_Attribute() const noexcept { return PSD_Sys_Quali_sonstige_Attribute_value; } // 3 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Ges_Ueberholverbot() const noexcept { return PSD_Ges_Ueberholverbot_value; } // 2 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Sys_Quali_Steigungen() const noexcept { return PSD_Sys_Quali_Steigungen_value; } // 3 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Ges_Wechselverkehrszeichen() const noexcept { return PSD_Ges_Wechselverkehrszeichen_value; } // 3 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Attribut_5_Wert() const noexcept { return PSD_Attribut_5_Wert_value; } // 4 bits
bool RxPdu_PSD_06::get_PSD_Steigung_2_Vorz() const noexcept { return PSD_Steigung_2_Vorz_value; } // 1 bit
std::uint32_t RxPdu_PSD_06::get_PSD_Sys_Quali_Strassenkennz() const noexcept { return PSD_Sys_Quali_Strassenkennz_value; } // 3 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Wechselverkehrszeichen_Typ() const noexcept { return PSD_Wechselverkehrszeichen_Typ_value; } // 2 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Baum_Ausrichtung() const noexcept { return PSD_Baum_Ausrichtung_value; } // 10 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Steigung_2_Offset() const noexcept { return PSD_Steigung_2_Offset_value; } // 7 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Ges_Gesetzlich_Kategorie() const noexcept { return PSD_Ges_Gesetzlich_Kategorie_value; } // 3 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Sys_Quali_Tempolimits() const noexcept { return PSD_Sys_Quali_Tempolimits_value; } // 3 bits
bool RxPdu_PSD_06::get_PSD_Attribute_Komplett_06() const noexcept { return PSD_Attribute_Komplett_06_value; } // 1 bit
std::uint32_t RxPdu_PSD_06::get_PSD_Ges_Gesetzlich_Zusatz() const noexcept { return PSD_Ges_Gesetzlich_Zusatz_value; } // 2 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Sys_Quali_Vorfahrtsregelung() const noexcept { return PSD_Sys_Quali_Vorfahrtsregelung_value; } // 3 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Ges_Verkehrszeichen_Quelle() const noexcept { return PSD_Ges_Verkehrszeichen_Quelle_value; } // 2 bits
bool RxPdu_PSD_06::get_PSD_Steigung_2_Attribute_kompl() const noexcept { return PSD_Steigung_2_Attribute_kompl_value; } // 1 bit
bool RxPdu_PSD_06::get_PSD_Ges_Attribute_Komplett() const noexcept { return PSD_Ges_Attribute_Komplett_value; } // 1 bit

// --   END: public API for target code


// -- BEGIN: private API for internal use only

void RxPdu_PSD_06::PRIVATE_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_PSD_06::PRIVATE_set_PSD_06_Mux(std::uint32_t value) noexcept { PSD_06_Mux_value = value; return; } // 3 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Sys_Segment_ID(std::uint32_t value) noexcept { PSD_Sys_Segment_ID_value = value; return; } // 6 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Attribut_Segment_ID(std::uint32_t value) noexcept { PSD_Attribut_Segment_ID_value = value; return; } // 6 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Ges_Segment_ID(std::uint32_t value) noexcept { PSD_Ges_Segment_ID_value = value; return; } // 6 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Baum_Laenge_VZ(bool value) noexcept { PSD_Baum_Laenge_VZ_value = value; return; } // 1 bit
void RxPdu_PSD_06::PRIVATE_set_PSD_Steigung_1_Segment_ID(std::uint32_t value) noexcept { PSD_Steigung_1_Segment_ID_value = value; return; } // 6 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Baum_Laenge(std::uint32_t value) noexcept { PSD_Baum_Laenge_value = value; return; } // 25 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Sys_Laendercode(std::uint32_t value) noexcept { PSD_Sys_Laendercode_value = value; return; } // 8 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Attribut_3_ID(std::uint32_t value) noexcept { PSD_Attribut_3_ID_value = value; return; } // 5 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Ges_Offset(std::uint32_t value) noexcept { PSD_Ges_Offset_value = value; return; } // 7 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Steigung_1_A_Steigung(std::uint32_t value) noexcept { PSD_Steigung_1_A_Steigung_value = value; return; } // 7 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Attribut_3_Offset(std::uint32_t value) noexcept { PSD_Attribut_3_Offset_value = value; return; } // 7 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Ges_Geschwindigkeit(std::uint32_t value) noexcept { PSD_Ges_Geschwindigkeit_value = value; return; } // 5 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Steigung_1_A_Vorz(bool value) noexcept { PSD_Steigung_1_A_Vorz_value = value; return; } // 1 bit
void RxPdu_PSD_06::PRIVATE_set_PSD_Sys_Geschwindigkeit_Einheit(bool value) noexcept { PSD_Sys_Geschwindigkeit_Einheit_value = value; return; } // 1 bit
void RxPdu_PSD_06::PRIVATE_set_PSD_Steigung_1_A_Offset(std::uint32_t value) noexcept { PSD_Steigung_1_A_Offset_value = value; return; } // 7 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Sys_Verkehrsrichtung(bool value) noexcept { PSD_Sys_Verkehrsrichtung_value = value; return; } // 1 bit
void RxPdu_PSD_06::PRIVATE_set_PSD_Sys_Geometrieguete(std::uint32_t value) noexcept { PSD_Sys_Geometrieguete_value = value; return; } // 2 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Sys_Mapmatchingguete(std::uint32_t value) noexcept { PSD_Sys_Mapmatchingguete_value = value; return; } // 2 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Attribut_3_Wert(std::uint32_t value) noexcept { PSD_Attribut_3_Wert_value = value; return; } // 4 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Ges_Typ(std::uint32_t value) noexcept { PSD_Ges_Typ_value = value; return; } // 2 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Sys_Alter_Karte(std::uint32_t value) noexcept { PSD_Sys_Alter_Karte_value = value; return; } // 3 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Ges_Spur_Geschw_Begrenzung(std::uint32_t value) noexcept { PSD_Ges_Spur_Geschw_Begrenzung_value = value; return; } // 6 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Steigung_1_B_Steigung(std::uint32_t value) noexcept { PSD_Steigung_1_B_Steigung_value = value; return; } // 7 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Attribut_4_ID(std::uint32_t value) noexcept { PSD_Attribut_4_ID_value = value; return; } // 5 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Sys_Zielfuehrung(bool value) noexcept { PSD_Sys_Zielfuehrung_value = value; return; } // 1 bit
void RxPdu_PSD_06::PRIVATE_set_PSD_Sys_US_State(std::uint32_t value) noexcept { PSD_Sys_US_State_value = value; return; } // 6 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Ges_Geschwindigkeit_Gespann(std::uint32_t value) noexcept { PSD_Ges_Geschwindigkeit_Gespann_value = value; return; } // 2 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Baum_Breite_VZ(bool value) noexcept { PSD_Baum_Breite_VZ_value = value; return; } // 1 bit
void RxPdu_PSD_06::PRIVATE_set_PSD_Attribut_4_Wert(std::uint32_t value) noexcept { PSD_Attribut_4_Wert_value = value; return; } // 4 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Baum_Breite(std::uint32_t value) noexcept { PSD_Baum_Breite_value = value; return; } // 24 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Ges_Geschwindigkeit_Witter(std::uint32_t value) noexcept { PSD_Ges_Geschwindigkeit_Witter_value = value; return; } // 2 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Steigung_1_B_Vorz(bool value) noexcept { PSD_Steigung_1_B_Vorz_value = value; return; } // 1 bit
void RxPdu_PSD_06::PRIVATE_set_PSD_Steigung_1_B_Offset(std::uint32_t value) noexcept { PSD_Steigung_1_B_Offset_value = value; return; } // 7 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Sys_Quali_Geometrien(std::uint32_t value) noexcept { PSD_Sys_Quali_Geometrien_value = value; return; } // 3 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Ges_Geschwindigkeit_Tag_Anf(std::uint32_t value) noexcept { PSD_Ges_Geschwindigkeit_Tag_Anf_value = value; return; } // 3 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Attribut_4_Offset(std::uint32_t value) noexcept { PSD_Attribut_4_Offset_value = value; return; } // 7 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Sys_Quali_Ortsinfo(std::uint32_t value) noexcept { PSD_Sys_Quali_Ortsinfo_value = value; return; } // 2 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Ges_Geschwindigkeit_Tag_Ende(std::uint32_t value) noexcept { PSD_Ges_Geschwindigkeit_Tag_Ende_value = value; return; } // 3 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Sys_Quali_verfuegbar(bool value) noexcept { PSD_Sys_Quali_verfuegbar_value = value; return; } // 1 bit
void RxPdu_PSD_06::PRIVATE_set_PSD_Sys_Zielfuehrung_geaendert(bool value) noexcept { PSD_Sys_Zielfuehrung_geaendert_value = value; return; } // 1 bit
void RxPdu_PSD_06::PRIVATE_set_PSD_Ges_Geschwindigkeit_Std_Anf(std::uint32_t value) noexcept { PSD_Ges_Geschwindigkeit_Std_Anf_value = value; return; } // 5 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Steigung_1_Attribute_kompl(bool value) noexcept { PSD_Steigung_1_Attribute_kompl_value = value; return; } // 1 bit
void RxPdu_PSD_06::PRIVATE_set_PSD_Sys_Geometrieguete_erweitert(std::uint32_t value) noexcept { PSD_Sys_Geometrieguete_erweitert_value = value; return; } // 8 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Steigung_2_Segment_ID(std::uint32_t value) noexcept { PSD_Steigung_2_Segment_ID_value = value; return; } // 6 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Attribut_5_ID(std::uint32_t value) noexcept { PSD_Attribut_5_ID_value = value; return; } // 5 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Ges_Geschwindigkeit_Std_Ende(std::uint32_t value) noexcept { PSD_Ges_Geschwindigkeit_Std_Ende_value = value; return; } // 5 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Attribut_5_Offset(std::uint32_t value) noexcept { PSD_Attribut_5_Offset_value = value; return; } // 7 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Steigung_2_Steigung(std::uint32_t value) noexcept { PSD_Steigung_2_Steigung_value = value; return; } // 7 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Sys_Quali_sonstige_Attribute(std::uint32_t value) noexcept { PSD_Sys_Quali_sonstige_Attribute_value = value; return; } // 3 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Ges_Ueberholverbot(std::uint32_t value) noexcept { PSD_Ges_Ueberholverbot_value = value; return; } // 2 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Sys_Quali_Steigungen(std::uint32_t value) noexcept { PSD_Sys_Quali_Steigungen_value = value; return; } // 3 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Ges_Wechselverkehrszeichen(std::uint32_t value) noexcept { PSD_Ges_Wechselverkehrszeichen_value = value; return; } // 3 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Attribut_5_Wert(std::uint32_t value) noexcept { PSD_Attribut_5_Wert_value = value; return; } // 4 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Steigung_2_Vorz(bool value) noexcept { PSD_Steigung_2_Vorz_value = value; return; } // 1 bit
void RxPdu_PSD_06::PRIVATE_set_PSD_Sys_Quali_Strassenkennz(std::uint32_t value) noexcept { PSD_Sys_Quali_Strassenkennz_value = value; return; } // 3 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Wechselverkehrszeichen_Typ(std::uint32_t value) noexcept { PSD_Wechselverkehrszeichen_Typ_value = value; return; } // 2 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Baum_Ausrichtung(std::uint32_t value) noexcept { PSD_Baum_Ausrichtung_value = value; return; } // 10 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Steigung_2_Offset(std::uint32_t value) noexcept { PSD_Steigung_2_Offset_value = value; return; } // 7 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Ges_Gesetzlich_Kategorie(std::uint32_t value) noexcept { PSD_Ges_Gesetzlich_Kategorie_value = value; return; } // 3 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Sys_Quali_Tempolimits(std::uint32_t value) noexcept { PSD_Sys_Quali_Tempolimits_value = value; return; } // 3 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Attribute_Komplett_06(bool value) noexcept { PSD_Attribute_Komplett_06_value = value; return; } // 1 bit
void RxPdu_PSD_06::PRIVATE_set_PSD_Ges_Gesetzlich_Zusatz(std::uint32_t value) noexcept { PSD_Ges_Gesetzlich_Zusatz_value = value; return; } // 2 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Sys_Quali_Vorfahrtsregelung(std::uint32_t value) noexcept { PSD_Sys_Quali_Vorfahrtsregelung_value = value; return; } // 3 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Ges_Verkehrszeichen_Quelle(std::uint32_t value) noexcept { PSD_Ges_Verkehrszeichen_Quelle_value = value; return; } // 2 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Steigung_2_Attribute_kompl(bool value) noexcept { PSD_Steigung_2_Attribute_kompl_value = value; return; } // 1 bit
void RxPdu_PSD_06::PRIVATE_set_PSD_Ges_Attribute_Komplett(bool value) noexcept { PSD_Ges_Attribute_Komplett_value = value; return; } // 1 bit

// --   END: private API for internal use only



} /* namespace PSDParser */
} /* namespace sid */
} /* namespace vwg */
