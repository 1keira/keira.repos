/**
 * \file simple_data_access_handler.cpp
 *
 * \brief System-API handler implementation for signal data access to supplier framework of ESO
 *
 * Code generator version: 0.8.8
 * Generator input:
 * - Data definition:      E3_1_1_UNECE_E3V_VLAN_Connect_KMatrix_Module_V15.04.00.03F_20221220_BAm_P02.xlsx
 * - Config file:          ./config/PSDParser.yaml
 * - Config file version:  0.8/demo_config
 * - Config description:   here goes some description
 * - Platform description: here goes some description
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

// eso adapter of signal api includes
#include "signal_data_access_handler.hpp"

// eso framework includes
#include <asi/sid/psdparser/IntPSDParserReply.hxx>
#include <FrameworkInitialization.hxx>

// system api and foundation library includes
#include <ara/log/logging.hpp>
#include <vwg/fnd/logging.hpp>

// standard library includes
#include <cstdint>

namespace vwg {
namespace sid {
namespace PSDParser {
namespace eso {

// immediately log error and return from void function if condition met
#define ERROR_AND_RETURN_IF(cond) \
if (cond) { \
   /* this is a same-thread reentrant invocation that is prohibited */\
   FND_LOG_ERROR(logger, "directly called interface while in callback (reentrant call)"); \
   return; \
}


// HINT: data_port = "ConMod_V2X_CPUPort"
SignalDataAccessHandler::SignalDataAccessHandler()
   : logger(ara::log::CreateLogger("sidPSDParser", myName))
   , state(HandlerState::kNotStarted)
   , isCallbackActive(false)
{
   FND_LOG_DEBUG(logger, "SignalDataAccessHandler::SignalDataAccessHandler: ctor");
}

SignalDataAccessHandler::~SignalDataAccessHandler() {
   // nothing to do here:
   // * we can not sensibly do any asynchronous disconnect or the like
   // * owned objects, if referenced, are referenced via smart pointers
}

void SignalDataAccessHandler::notifyConnectionState(ConnectionState st) {
   isCallbackActive = true; // to later detect reentrance; supposed to be already under lock, that nothing can intercept the next line
   if (cbConnectionState /*is callable*/) { 
      FND_LOG_DEBUG(logger, "SignalDataAccessHandler::notifyConnectionState: cbConnectionState(), state = ", (int)st);
      cbConnectionState(st); 
   }
   isCallbackActive = false;
}

void SignalDataAccessHandler::start(std::shared_ptr<ISignalDataListener> _pListener, ConnectionStateNotificationCallback cb) {
   std::lock_guard<MyMutexType> lck(mx); // synchronized event action
   
   // guard to only pass if not already started
   if (state != HandlerState::kNotStarted) {
      FND_LOG_ERROR(logger, "start called more than once");
      return;
   }
   
   pListener = std::move(_pListener);
   cbConnectionState = std::move(cb);
   FND_LOG_DEBUG(logger, "SignalDataAccessHandler::start: listener = ", (size_t)pListener.get());

   state = HandlerState::kConnect;

   // show headline
   FND_LOG_INFO(logger, "start " , myName);
   FND_LOG_INFO(logger, "Code generator version: 0.8.8");
   FND_LOG_INFO(logger, "Generator input:");
   FND_LOG_INFO(logger, "- Data definition:      E3_1_1_UNECE_E3V_VLAN_Connect_KMatrix_Module_V15.04.00.03F_20221220_BAm_P02.xlsx");
   FND_LOG_INFO(logger, "- Config file:          ./config/PSDParser.yaml");
   FND_LOG_INFO(logger, "- Config file version:  0.8/demo_config");
   FND_LOG_INFO(logger, "- Config description:   here goes some description");
   FND_LOG_INFO(logger, "Generator output:");
   FND_LOG_INFO(logger, "- C++ API version:      0.8");

   notifyConnectionState(ConnectionState::kConnecting);

   // ESO comm initialization
   FND_LOG_DEBUG(logger, "SignalDataAccessHandler::start: init::initFramework()");
   init::initFramework();

   // TODO: how to manage proxies of different interfaces
   //FOREACH(Interface intf : interfaceList) {
   startProxy(/*intf*/);
   //}
}

void SignalDataAccessHandler::simulateResponse() {

   // simulate automatic response from ESO subsystem
   // {
   //    FND_LOG_INFO(logger, "emulate sending of PDU PSD_04 in handler");
   //    asi::sid::psdparser::PSD04Struct pdu;
   //    pdu.PSD_Segment_ID = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Vorgaenger_Segment_ID = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Segmentlaenge = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Strassenkategorie = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Endkruemmung = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Endkruemmung_Vorz = (bool)0xBBU; 
   //    pdu.PSD_Idenditaets_ID = (std::uint32_t)0xBBU; 
   //    pdu.PSD_ADAS_Qualitaet = (bool)0xBBU; 
   //    pdu.PSD_wahrscheinlichster_Pfad = (bool)0xBBU; 
   //    pdu.PSD_Geradester_Pfad = (bool)0xBBU; 
   //    pdu.PSD_Fahrspuren_Anzahl = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Bebauung = (bool)0xBBU; 
   //    pdu.PSD_Segment_Komplett = (bool)0xBBU; 
   //    pdu.PSD_Rampe = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Anfangskruemmung = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Anfangskruemmung_Vorz = (bool)0xBBU; 
   //    pdu.PSD_Abzweigerichtung = (bool)0xBBU; 
   //    pdu.PSD_Abzweigewinkel = (std::uint32_t)0xBBU; 
   //    pdu.pdustate = asi::sid::psdparser::ePduState_Valid;
   //    updatePSD_04(pdu, true);
   // }

   // {
   //    FND_LOG_INFO(logger, "emulate sending of PDU PSD_05 in handler");
   //    asi::sid::psdparser::PSD05Struct pdu;
   //    pdu.PSD_Pos_Segment_ID = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Pos_Segmentlaenge = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Pos_Inhibitzeit = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Pos_Standort_Eindeutig = (bool)0xBBU; 
   //    pdu.PSD_Pos_Fehler_Laengsrichtung = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Pos_Fahrspur = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Attribut_Segment_ID_05 = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Attribut_1_ID = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Attribut_1_Wert = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Attribut_1_Offset = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Attribut_2_ID = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Attribut_2_Wert = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Attribut_2_Offset = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Attribute_Komplett_05 = (bool)0xBBU; 
   //    pdu.pdustate = asi::sid::psdparser::ePduState_Valid;
   //    updatePSD_05(pdu, true);
   // }

   // {
   //    FND_LOG_INFO(logger, "emulate sending of PDU PSD_06 in handler");
   //    asi::sid::psdparser::PSD06Struct pdu;
   //    pdu.PSD_06_Mux = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Sys_Segment_ID = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Attribut_Segment_ID = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Ges_Segment_ID = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Baum_Laenge_VZ = (bool)0xBBU; 
   //    pdu.PSD_Steigung_1_Segment_ID = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Baum_Laenge = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Sys_Laendercode = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Attribut_3_ID = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Ges_Offset = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Steigung_1_A_Steigung = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Attribut_3_Offset = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Ges_Geschwindigkeit = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Steigung_1_A_Vorz = (bool)0xBBU; 
   //    pdu.PSD_Sys_Geschwindigkeit_Einheit = (bool)0xBBU; 
   //    pdu.PSD_Steigung_1_A_Offset = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Sys_Verkehrsrichtung = (bool)0xBBU; 
   //    pdu.PSD_Sys_Geometrieguete = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Sys_Mapmatchingguete = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Attribut_3_Wert = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Ges_Typ = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Sys_Alter_Karte = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Ges_Spur_Geschw_Begrenzung = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Steigung_1_B_Steigung = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Attribut_4_ID = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Sys_Zielfuehrung = (bool)0xBBU; 
   //    pdu.PSD_Sys_US_State = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Ges_Geschwindigkeit_Gespann = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Baum_Breite_VZ = (bool)0xBBU; 
   //    pdu.PSD_Attribut_4_Wert = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Baum_Breite = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Ges_Geschwindigkeit_Witter = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Steigung_1_B_Vorz = (bool)0xBBU; 
   //    pdu.PSD_Steigung_1_B_Offset = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Sys_Quali_Geometrien = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Ges_Geschwindigkeit_Tag_Anf = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Attribut_4_Offset = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Sys_Quali_Ortsinfo = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Ges_Geschwindigkeit_Tag_Ende = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Sys_Quali_verfuegbar = (bool)0xBBU; 
   //    pdu.PSD_Sys_Zielfuehrung_geaendert = (bool)0xBBU; 
   //    pdu.PSD_Ges_Geschwindigkeit_Std_Anf = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Steigung_1_Attribute_kompl = (bool)0xBBU; 
   //    pdu.PSD_Sys_Geometrieguete_erweitert = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Steigung_2_Segment_ID = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Attribut_5_ID = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Ges_Geschwindigkeit_Std_Ende = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Attribut_5_Offset = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Steigung_2_Steigung = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Sys_Quali_sonstige_Attribute = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Ges_Ueberholverbot = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Sys_Quali_Steigungen = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Ges_Wechselverkehrszeichen = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Attribut_5_Wert = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Steigung_2_Vorz = (bool)0xBBU; 
   //    pdu.PSD_Sys_Quali_Strassenkennz = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Wechselverkehrszeichen_Typ = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Baum_Ausrichtung = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Steigung_2_Offset = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Ges_Gesetzlich_Kategorie = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Sys_Quali_Tempolimits = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Attribute_Komplett_06 = (bool)0xBBU; 
   //    pdu.PSD_Ges_Gesetzlich_Zusatz = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Sys_Quali_Vorfahrtsregelung = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Ges_Verkehrszeichen_Quelle = (std::uint32_t)0xBBU; 
   //    pdu.PSD_Steigung_2_Attribute_kompl = (bool)0xBBU; 
   //    pdu.PSD_Ges_Attribute_Komplett = (bool)0xBBU; 
   //    pdu.pdustate = asi::sid::psdparser::ePduState_Valid;
   //    updatePSD_06(pdu, true);
   // }
}

bool SignalDataAccessHandler::startProxy (/*Interface intf*/) {
   bool res = false; // failure by default

   // CREATE
   FND_LOG_DEBUG(logger, "SignalDataAccessHandler::startProxy: asi::sid::psdparser::IntPSDParserProxy::IntPSDParserProxy(), asi::sid::psdparser::INTPSDPARSER_INSTANCE_ID = ", asi::sid::psdparser::INTPSDPARSER_INSTANCE_ID);
   pProxy = std::make_unique<asi::sid::psdparser::IntPSDParserProxy /*as Interface*/>(asi::sid::psdparser::INTPSDPARSER_INSTANCE_ID, *this /*as Reply*/, this /* as LifecycleListener*/);

   // CONNECT
   FND_LOG_DEBUG(logger, "SignalDataAccessHandler::startProxy: IntPSDParserProxy.connect()");
   if (pProxy->connect()) {
      // TODO: on error; when to retry?
      pProxy = nullptr;
      FND_LOG_ERROR(logger, "proxy connection error");
   }
   else {
      res = true; // success
      FND_LOG_DEBUG(logger, "SignalDataAccessHandler::startProxy: IntPSDParserProxy.connect() successful, proxy = ", (size_t)pProxy.get());
   }

   return res;
}

struct DisconnectionInfo {
   SignalDataAccessHandler *handler;
   asi::sid::psdparser::IntPSDParserProxy *proxy;
};

// typedef void (*ProxyReleasedFct)(void* ctx, const comm::Proxy& proxy);
static void onDisconnect(void *data, const comm::Proxy &sr) {
   DisconnectionInfo *pDi = static_cast<DisconnectionInfo *>(data);
   pDi->handler->disconnected(pDi->proxy, sr);
   delete pDi;
}

void SignalDataAccessHandler::suspend() {
   std::lock_guard<MyMutexType> lck(mx); // synchronized event action
   ERROR_AND_RETURN_IF(isCallbackActive);

   if (state == HandlerState::kConnect) {
      state = HandlerState::kDisconnect;
      notifyConnectionState(ConnectionState::kDisconnecting);
      // TODO: once we have more proxies, there will be a sequence of disconnect calls.
      Proxy *proxyPlainPtr = pProxy.get();
      proxiesToBeDisconnected.push_back(std::move(pProxy));
      DisconnectionInfo *pDiProxy = new DisconnectionInfo{this, proxyPlainPtr};
      FND_LOG_DEBUG(logger, "SignalDataAccessHandler::suspend: IntPSDParserProxy.disconnectAndNotify(), proxy = ", (size_t)pDiProxy);
      proxyPlainPtr->disconnectAndNotify(onDisconnect, pDiProxy);
   }
   else if (state == HandlerState::kDisconnect) {
      FND_LOG_WARN(logger, "suspend called while already disconnecting");
   }
   else { // state == HandlerState::kNotStarted
      FND_LOG_ERROR(logger, "nothing to suspend since not started");
   }
}

void SignalDataAccessHandler::resume() {
   std::lock_guard<MyMutexType> lck(mx); // synchronized event action
   ERROR_AND_RETURN_IF(isCallbackActive);
   FND_LOG_DEBUG(logger, "SignalDataAccessHandler::resume");
   
   if (state == HandlerState::kNotStarted) {
      FND_LOG_ERROR(logger, "nothing to resume since not started");
   }
   else if (state == HandlerState::kDisconnect) {
      notifyConnectionState(ConnectionState::kConnecting);
      // TODO: how to manage proxies of different interfaces
      //FOREACH(Interface intf : interfaceList) {
      startProxy(/*intf*/);
      //}
   }
   else {
      FND_LOG_ERROR(logger, "nothing to resume since already started");
   }
}


static bool convertPduStatusFromEsoToSid(std::uint64_t pduState, PduStatus &result) {
   using namespace asi::sid::psdparser;

   switch (pduState) {
      // Plausible values:
      case ePdustate_Valid:                        result = PduStatus::kValid;            break;
      case ePdustate_TempNotValid:                 result = PduStatus::kTempNotValid;     break;
      case ePdustate_NeverReceived:                result = PduStatus::kNotReceivedYet;   break;
      case ePdustate_Invalid:                      result = PduStatus::kNotValid;         break;
      case ePdustate_TimeoutNotValidNotFiltered:   result = PduStatus::kTimedOut;         break;
      case ePdustate_TimeoutNotValidFiltered:      result = PduStatus::kTimedOut;         break;

      // Implausible values:
      case ePdustate_NotExisting:                  result = PduStatus::kNotValid;         return false;
      default:                                     result = PduStatus::kNotValid;         return false;
   }

   return true;
}



// propagate receive PDU PSD_04
void SignalDataAccessHandler::updatePSD_04(const CIPtr< asi::sid::psdparser::PSD04Struct >& pdu, const bool valid) {
   static const std::string pduName{"PDU PSD_04"};
   FND_LOG_DEBUG(logger, "SignalDataAccessHandler::updatePSD_04");

   if (!valid) {
      FND_LOG_ERROR(logger, "Received PDU update marked invalid for ", pduName);
      return;
   }

   PduStatus pduState;
   if (!convertPduStatusFromEsoToSid(pdu->pdustate, pduState)) {
      FND_LOG_ERROR(logger, "Received PDU update has implausible state ", pdu->pdustate, " for ", pduName);
      return;
   }

   auto pdu_out = RxPdu_PSD_04();
   
   pdu_out.PRIVATE_set_PSD_Segment_ID(pdu->PSD_Segment_ID_Raw);
   pdu_out.PRIVATE_set_PSD_Vorgaenger_Segment_ID(pdu->PSD_Vorgaenger_Segment_ID_Raw);
   pdu_out.PRIVATE_set_PSD_Segmentlaenge(pdu->PSD_Segmentlaenge_Raw);
   pdu_out.PRIVATE_set_PSD_Strassenkategorie(pdu->PSD_Strassenkategorie_Raw);
   pdu_out.PRIVATE_set_PSD_Endkruemmung(pdu->PSD_Endkruemmung_Raw);
   pdu_out.PRIVATE_set_PSD_Endkruemmung_Vorz(pdu->PSD_Endkruemmung_Vorz_Raw);
   pdu_out.PRIVATE_set_PSD_Idenditaets_ID(pdu->PSD_Idenditaets_ID_Raw);
   pdu_out.PRIVATE_set_PSD_ADAS_Qualitaet(pdu->PSD_ADAS_Qualitaet_Raw);
   pdu_out.PRIVATE_set_PSD_wahrscheinlichster_Pfad(pdu->PSD_wahrscheinlichster_Pfad_Raw);
   pdu_out.PRIVATE_set_PSD_Geradester_Pfad(pdu->PSD_Geradester_Pfad_Raw);
   pdu_out.PRIVATE_set_PSD_Fahrspuren_Anzahl(pdu->PSD_Fahrspuren_Anzahl_Raw);
   pdu_out.PRIVATE_set_PSD_Bebauung(pdu->PSD_Bebauung_Raw);
   pdu_out.PRIVATE_set_PSD_Segment_Komplett(pdu->PSD_Segment_Komplett_Raw);
   pdu_out.PRIVATE_set_PSD_Rampe(pdu->PSD_Rampe_Raw);
   pdu_out.PRIVATE_set_PSD_Anfangskruemmung(pdu->PSD_Anfangskruemmung_Raw);
   pdu_out.PRIVATE_set_PSD_Anfangskruemmung_Vorz(pdu->PSD_Anfangskruemmung_Vorz_Raw);
   pdu_out.PRIVATE_set_PSD_Abzweigerichtung(pdu->PSD_Abzweigerichtung_Raw);
   pdu_out.PRIVATE_set_PSD_Abzweigewinkel(pdu->PSD_Abzweigewinkel_Raw);
   
   pdu_out.PRIVATE_setPduStatus(pduState);
   
   FND_LOG_INFO(logger, "propagating incoming ", pduName, " to listener");
   // pManipulator->manipulate(const&)
   FND_LOG_DEBUG(logger, "SignalDataAccessHandler::updatePSD_04: SignalDataListener->receivedPdu_PSD_04, listener = ", (size_t)pListener.get());
   pListener->receivedPdu_PSD_04(pdu_out);
}

// propagate receive PDU PSD_05
void SignalDataAccessHandler::updatePSD_05(const CIPtr< asi::sid::psdparser::PSD05Struct >& pdu, const bool valid) {
   static const std::string pduName{"PDU PSD_05"};
   FND_LOG_DEBUG(logger, "SignalDataAccessHandler::updatePSD_05");

   if (!valid) {
      FND_LOG_ERROR(logger, "Received PDU update marked invalid for ", pduName);
      return;
   }

   PduStatus pduState;
   if (!convertPduStatusFromEsoToSid(pdu->pdustate, pduState)) {
      FND_LOG_ERROR(logger, "Received PDU update has implausible state ", pdu->pdustate, " for ", pduName);
      return;
   }

   auto pdu_out = RxPdu_PSD_05();
   
   pdu_out.PRIVATE_set_PSD_Pos_Segment_ID(pdu->PSD_Pos_Segment_ID_Raw);
   pdu_out.PRIVATE_set_PSD_Pos_Segmentlaenge(pdu->PSD_Pos_Segmentlaenge_Raw);
   pdu_out.PRIVATE_set_PSD_Pos_Inhibitzeit(pdu->PSD_Pos_Inhibitzeit_Raw);
   pdu_out.PRIVATE_set_PSD_Pos_Standort_Eindeutig(pdu->PSD_Pos_Standort_Eindeutig_Raw);
   pdu_out.PRIVATE_set_PSD_Pos_Fehler_Laengsrichtung(pdu->PSD_Pos_Fehler_Laengsrichtung_Raw);
   pdu_out.PRIVATE_set_PSD_Pos_Fahrspur(pdu->PSD_Pos_Fahrspur_Raw);
   pdu_out.PRIVATE_set_PSD_Attribut_Segment_ID_05(pdu->PSD_Attribut_Segment_ID_05_Raw);
   pdu_out.PRIVATE_set_PSD_Attribut_1_ID(pdu->PSD_Attribut_1_ID_Raw);
   pdu_out.PRIVATE_set_PSD_Attribut_1_Wert(pdu->PSD_Attribut_1_Wert_Raw);
   pdu_out.PRIVATE_set_PSD_Attribut_1_Offset(pdu->PSD_Attribut_1_Offset_Raw);
   pdu_out.PRIVATE_set_PSD_Attribut_2_ID(pdu->PSD_Attribut_2_ID_Raw);
   pdu_out.PRIVATE_set_PSD_Attribut_2_Wert(pdu->PSD_Attribut_2_Wert_Raw);
   pdu_out.PRIVATE_set_PSD_Attribut_2_Offset(pdu->PSD_Attribut_2_Offset_Raw);
   pdu_out.PRIVATE_set_PSD_Attribute_Komplett_05(pdu->PSD_Attribute_Komplett_05_Raw);
   
   pdu_out.PRIVATE_setPduStatus(pduState);
   
   FND_LOG_INFO(logger, "propagating incoming ", pduName, " to listener");
   // pManipulator->manipulate(const&)
   FND_LOG_DEBUG(logger, "SignalDataAccessHandler::updatePSD_05: SignalDataListener->receivedPdu_PSD_05, listener = ", (size_t)pListener.get());
   pListener->receivedPdu_PSD_05(pdu_out);
}

// propagate receive PDU PSD_06
void SignalDataAccessHandler::updatePSD_06(const CIPtr< asi::sid::psdparser::PSD06Struct >& pdu, const bool valid) {
   static const std::string pduName{"PDU PSD_06"};
   FND_LOG_DEBUG(logger, "SignalDataAccessHandler::updatePSD_06");

   if (!valid) {
      FND_LOG_ERROR(logger, "Received PDU update marked invalid for ", pduName);
      return;
   }

   PduStatus pduState;
   if (!convertPduStatusFromEsoToSid(pdu->pdustate, pduState)) {
      FND_LOG_ERROR(logger, "Received PDU update has implausible state ", pdu->pdustate, " for ", pduName);
      return;
   }

   auto pdu_out = RxPdu_PSD_06();
   
   pdu_out.PRIVATE_set_PSD_06_Mux(pdu->PSD_06_Mux_Raw);
   pdu_out.PRIVATE_set_PSD_Sys_Segment_ID(pdu->PSD_Sys_Segment_ID_Raw);
   pdu_out.PRIVATE_set_PSD_Attribut_Segment_ID(pdu->PSD_Attribut_Segment_ID_Raw);
   pdu_out.PRIVATE_set_PSD_Ges_Segment_ID(pdu->PSD_Ges_Segment_ID_Raw);
   pdu_out.PRIVATE_set_PSD_Baum_Laenge_VZ(pdu->PSD_Baum_Laenge_VZ_Raw);
   pdu_out.PRIVATE_set_PSD_Steigung_1_Segment_ID(pdu->PSD_Steigung_1_Segment_ID_Raw);
   pdu_out.PRIVATE_set_PSD_Baum_Laenge(pdu->PSD_Baum_Laenge_Raw);
   pdu_out.PRIVATE_set_PSD_Sys_Laendercode(pdu->PSD_Sys_Laendercode_Raw);
   pdu_out.PRIVATE_set_PSD_Attribut_3_ID(pdu->PSD_Attribut_3_ID_Raw);
   pdu_out.PRIVATE_set_PSD_Ges_Offset(pdu->PSD_Ges_Offset_Raw);
   pdu_out.PRIVATE_set_PSD_Steigung_1_A_Steigung(pdu->PSD_Steigung_1_A_Steigung_Raw);
   pdu_out.PRIVATE_set_PSD_Attribut_3_Offset(pdu->PSD_Attribut_3_Offset_Raw);
   pdu_out.PRIVATE_set_PSD_Ges_Geschwindigkeit(pdu->PSD_Ges_Geschwindigkeit_Raw);
   pdu_out.PRIVATE_set_PSD_Steigung_1_A_Vorz(pdu->PSD_Steigung_1_A_Vorz_Raw);
   pdu_out.PRIVATE_set_PSD_Sys_Geschwindigkeit_Einheit(pdu->PSD_Sys_Geschwindigkeit_Einheit_Raw);
   pdu_out.PRIVATE_set_PSD_Steigung_1_A_Offset(pdu->PSD_Steigung_1_A_Offset_Raw);
   pdu_out.PRIVATE_set_PSD_Sys_Verkehrsrichtung(pdu->PSD_Sys_Verkehrsrichtung_Raw);
   pdu_out.PRIVATE_set_PSD_Sys_Geometrieguete(pdu->PSD_Sys_Geometrieguete_Raw);
   pdu_out.PRIVATE_set_PSD_Sys_Mapmatchingguete(pdu->PSD_Sys_Mapmatchingguete_Raw);
   pdu_out.PRIVATE_set_PSD_Attribut_3_Wert(pdu->PSD_Attribut_3_Wert_Raw);
   pdu_out.PRIVATE_set_PSD_Ges_Typ(pdu->PSD_Ges_Typ_Raw);
   pdu_out.PRIVATE_set_PSD_Sys_Alter_Karte(pdu->PSD_Sys_Alter_Karte_Raw);
   pdu_out.PRIVATE_set_PSD_Ges_Spur_Geschw_Begrenzung(pdu->PSD_Ges_Spur_Geschw_Begrenzung_Raw);
   pdu_out.PRIVATE_set_PSD_Steigung_1_B_Steigung(pdu->PSD_Steigung_1_B_Steigung_Raw);
   pdu_out.PRIVATE_set_PSD_Attribut_4_ID(pdu->PSD_Attribut_4_ID_Raw);
   pdu_out.PRIVATE_set_PSD_Sys_Zielfuehrung(pdu->PSD_Sys_Zielfuehrung_Raw);
   pdu_out.PRIVATE_set_PSD_Sys_US_State(pdu->PSD_Sys_US_State_Raw);
   pdu_out.PRIVATE_set_PSD_Ges_Geschwindigkeit_Gespann(pdu->PSD_Ges_Geschwindigkeit_Gespann_Raw);
   pdu_out.PRIVATE_set_PSD_Baum_Breite_VZ(pdu->PSD_Baum_Breite_VZ_Raw);
   pdu_out.PRIVATE_set_PSD_Attribut_4_Wert(pdu->PSD_Attribut_4_Wert_Raw);
   pdu_out.PRIVATE_set_PSD_Baum_Breite(pdu->PSD_Baum_Breite_Raw);
   pdu_out.PRIVATE_set_PSD_Ges_Geschwindigkeit_Witter(pdu->PSD_Ges_Geschwindigkeit_Witter_Raw);
   pdu_out.PRIVATE_set_PSD_Steigung_1_B_Vorz(pdu->PSD_Steigung_1_B_Vorz_Raw);
   pdu_out.PRIVATE_set_PSD_Steigung_1_B_Offset(pdu->PSD_Steigung_1_B_Offset_Raw);
   pdu_out.PRIVATE_set_PSD_Sys_Quali_Geometrien(pdu->PSD_Sys_Quali_Geometrien_Raw);
   pdu_out.PRIVATE_set_PSD_Ges_Geschwindigkeit_Tag_Anf(pdu->PSD_Ges_Geschwindigkeit_Tag_Anf_Raw);
   pdu_out.PRIVATE_set_PSD_Attribut_4_Offset(pdu->PSD_Attribut_4_Offset_Raw);
   pdu_out.PRIVATE_set_PSD_Sys_Quali_Ortsinfo(pdu->PSD_Sys_Quali_Ortsinfo_Raw);
   pdu_out.PRIVATE_set_PSD_Ges_Geschwindigkeit_Tag_Ende(pdu->PSD_Ges_Geschwindigkeit_Tag_Ende_Raw);
   pdu_out.PRIVATE_set_PSD_Sys_Quali_verfuegbar(pdu->PSD_Sys_Quali_verfuegbar_Raw);
   pdu_out.PRIVATE_set_PSD_Sys_Zielfuehrung_geaendert(pdu->PSD_Sys_Zielfuehrung_geaendert_Raw);
   pdu_out.PRIVATE_set_PSD_Ges_Geschwindigkeit_Std_Anf(pdu->PSD_Ges_Geschwindigkeit_Std_Anf_Raw);
   pdu_out.PRIVATE_set_PSD_Steigung_1_Attribute_kompl(pdu->PSD_Steigung_1_Attribute_kompl_Raw);
   pdu_out.PRIVATE_set_PSD_Sys_Geometrieguete_erweitert(pdu->PSD_Sys_Geometrieguete_erweitert_Raw);
   pdu_out.PRIVATE_set_PSD_Steigung_2_Segment_ID(pdu->PSD_Steigung_2_Segment_ID_Raw);
   pdu_out.PRIVATE_set_PSD_Attribut_5_ID(pdu->PSD_Attribut_5_ID_Raw);
   pdu_out.PRIVATE_set_PSD_Ges_Geschwindigkeit_Std_Ende(pdu->PSD_Ges_Geschwindigkeit_Std_Ende_Raw);
   pdu_out.PRIVATE_set_PSD_Attribut_5_Offset(pdu->PSD_Attribut_5_Offset_Raw);
   pdu_out.PRIVATE_set_PSD_Steigung_2_Steigung(pdu->PSD_Steigung_2_Steigung_Raw);
   pdu_out.PRIVATE_set_PSD_Sys_Quali_sonstige_Attribute(pdu->PSD_Sys_Quali_sonstige_Attribute_Raw);
   pdu_out.PRIVATE_set_PSD_Ges_Ueberholverbot(pdu->PSD_Ges_Ueberholverbot_Raw);
   pdu_out.PRIVATE_set_PSD_Sys_Quali_Steigungen(pdu->PSD_Sys_Quali_Steigungen_Raw);
   pdu_out.PRIVATE_set_PSD_Ges_Wechselverkehrszeichen(pdu->PSD_Ges_Wechselverkehrszeichen_Raw);
   pdu_out.PRIVATE_set_PSD_Attribut_5_Wert(pdu->PSD_Attribut_5_Wert_Raw);
   pdu_out.PRIVATE_set_PSD_Steigung_2_Vorz(pdu->PSD_Steigung_2_Vorz_Raw);
   pdu_out.PRIVATE_set_PSD_Sys_Quali_Strassenkennz(pdu->PSD_Sys_Quali_Strassenkennz_Raw);
   pdu_out.PRIVATE_set_PSD_Wechselverkehrszeichen_Typ(pdu->PSD_Wechselverkehrszeichen_Typ_Raw);
   pdu_out.PRIVATE_set_PSD_Baum_Ausrichtung(pdu->PSD_Baum_Ausrichtung_Raw);
   pdu_out.PRIVATE_set_PSD_Steigung_2_Offset(pdu->PSD_Steigung_2_Offset_Raw);
   pdu_out.PRIVATE_set_PSD_Ges_Gesetzlich_Kategorie(pdu->PSD_Ges_Gesetzlich_Kategorie_Raw);
   pdu_out.PRIVATE_set_PSD_Sys_Quali_Tempolimits(pdu->PSD_Sys_Quali_Tempolimits_Raw);
   pdu_out.PRIVATE_set_PSD_Attribute_Komplett_06(pdu->PSD_Attribute_Komplett_06_Raw);
   pdu_out.PRIVATE_set_PSD_Ges_Gesetzlich_Zusatz(pdu->PSD_Ges_Gesetzlich_Zusatz_Raw);
   pdu_out.PRIVATE_set_PSD_Sys_Quali_Vorfahrtsregelung(pdu->PSD_Sys_Quali_Vorfahrtsregelung_Raw);
   pdu_out.PRIVATE_set_PSD_Ges_Verkehrszeichen_Quelle(pdu->PSD_Ges_Verkehrszeichen_Quelle_Raw);
   pdu_out.PRIVATE_set_PSD_Steigung_2_Attribute_kompl(pdu->PSD_Steigung_2_Attribute_kompl_Raw);
   pdu_out.PRIVATE_set_PSD_Ges_Attribute_Komplett(pdu->PSD_Ges_Attribute_Komplett_Raw);
   
   pdu_out.PRIVATE_setPduStatus(pduState);
   
   FND_LOG_INFO(logger, "propagating incoming ", pduName, " to listener");
   // pManipulator->manipulate(const&)
   FND_LOG_DEBUG(logger, "SignalDataAccessHandler::updatePSD_06: SignalDataListener->receivedPdu_PSD_06, listener = ", (size_t)pListener.get());
   pListener->receivedPdu_PSD_06(pdu_out);
}


void SignalDataAccessHandler::alive(comm::Lifecycle* lc, const comm::ServiceEvent&) {
   std::lock_guard<MyMutexType> lck(mx); // synchronized event action
   ERROR_AND_RETURN_IF(isCallbackActive);
   FND_LOG_DEBUG(logger, "SignalDataAccessHandler::alive: proxy = ", (size_t)lc);

   if (state == HandlerState::kConnect) { // connection established
      // Finalize setup of the proxy that has come to life
      bool proxyFound = false; // if we use the eso API correctly, we must find a proxy
      // TODO: later to be checked for each proxy
      if (*pProxy.get() == lc) {
         proxyFound = true;
         FND_LOG_INFO(logger, "IntPSDParserProxy alive");
         FND_LOG_DEBUG(logger, "SignalDataAccessHandler::alive: IntPSDParserProxy->setNotification()");
         // TODO: loop over all notifications relevant for this proxy - maybe just "all" is fine for us?
         if((*pProxy)->setNotification(/*for all*/)) {
            FND_LOG_ERROR(logger, "setNotification for proxy failed finally");
         }
      }
      if (!proxyFound) {
         // Most likely we are not using the ESO APIs properly...
         FND_LOG_ERROR(logger, "alive called but no matching proxy found");
      }

      // If now all proxies are connected, inform the client
      bool allProxiesAreConnected = true;
      // TODO: once we have more proxies, there will be a sequence of if statements.
      if (!pProxy->isAlive()) {
         allProxiesAreConnected = false;
      }
      if (allProxiesAreConnected) {
         notifyConnectionState(ConnectionState::kConnected); // this call may immediately trigger a check of `isCallbackActive` when directly advancing to other event like `sendX()`
      }

      simulateResponse();
   }
   else if (state == HandlerState::kDisconnect) {
      // race condition: This must be an alive call that was somehow delayed from the time we were in HandlerState::kConnect.  Log, but otherwise ignore
      FND_LOG_INFO(logger, "proxy alive called although target is to be disconnected");
   }
   else { // state == HandlerState::kNotStarted
      // this is impossible
   }
}

// NOTE: Assumption is that a dead proxy doesn't require a disconnect and can be destroyed immediately
void SignalDataAccessHandler::dead(comm::Lifecycle* lc, const comm::ServiceEvent&) {
   std::lock_guard<MyMutexType> lck(mx); // synchronized event action
   ERROR_AND_RETURN_IF(isCallbackActive);

   FND_LOG_DEBUG(logger, "SignalDataAccessHandler::dead: proxy = ", (size_t)lc);

   if (state == HandlerState::kConnect) {
      notifyConnectionState(ConnectionState::kConnecting); // TODO: how to detect an immediate call to `sendX()` afterwards?

      // TODO: later to be checked for each proxy
      if (*pProxy.get() == lc) {
         // TODO: add information about which proxy died
         FND_LOG_WARN(logger, "IntPSDParserProxy died unexpectedly, trying to reconnect");
         // ESO comm resume/resolve (re-init part 1)
         pProxy = nullptr;
         // ESO comm initialization (re-init part 2)
         startProxy(/*Interface intf*/);
      }
   }
   else if (state == HandlerState::kDisconnect) {
      // race condition: This must be a call to dead that was somehow delayed from the time we were in HandlerState::kConnect.  Log, but otherwise ignore
      FND_LOG_INFO(logger, "proxy dead called while disconnecting");
   }
   else { // state == HandlerState::kNotStarted
      // this is impossible
   }
}

// TODO: add more explanation about pointer usage and memory management
void SignalDataAccessHandler::disconnected(asi::sid::psdparser::IntPSDParserProxy *disconnectedProxy, const comm::Proxy &sr) {
   std::lock_guard<MyMutexType> lck(mx); // synchronized event action
   ERROR_AND_RETURN_IF(isCallbackActive);
   FND_LOG_DEBUG(logger, "SignalDataAccessHandler::disconnected: proxy = ", (size_t)disconnectedProxy);

   // Remove proxy from the set proxiesToBeDisconnected.
   size_t pos = 0;
   while (pos < proxiesToBeDisconnected.size() && proxiesToBeDisconnected[pos].get() != disconnectedProxy) {
      ++pos;
   }
   if (pos < proxiesToBeDisconnected.size()) {
      FND_LOG_INFO(logger, "proxy disconnected"); // can we somehow give details about the proxy?
      disconnectedProxy = nullptr; // raw pointer only for identification of unique_ptr
      proxiesToBeDisconnected.erase(proxiesToBeDisconnected.begin() + pos);
   }
   else {
      // race condition: disconnectAndNotify was called on a proxy that became dead afterwards
      FND_LOG_WARN(logger, "disconnected called but no matching proxy found");
   }

   if (state == HandlerState::kConnect) {
      // race condition: This must be a call to disconnected that was somehow delayed from the time we were in HandlerState::kDisconnect.
      FND_LOG_WARN(logger, "proxy disconnected called while connecting");
   }
   else if (state == HandlerState::kDisconnect) { // connection teared down as requested
      if (proxiesToBeDisconnected.empty()) {
         notifyConnectionState(ConnectionState::kDisconnected);
      }
   }
   else { // state == HandlerState::kNotStarted
      // this is impossible
   }
}

} /* namespace eso */
} /* namespace PSDParser */
} /* namespace sid */
} /* namespace vwg */
