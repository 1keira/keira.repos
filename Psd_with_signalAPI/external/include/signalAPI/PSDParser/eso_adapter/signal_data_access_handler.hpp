/**
 * \file simple_data_access_handler.hpp
 *
 * \brief System-API handler declaration for signal data access to supplier framework of ESO
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

#ifndef ESO_ADAPTER_HPP
#define ESO_ADAPTER_HPP

// signal api includes
#include <vwg/sid/PSDParser/signal_data_access.hpp>

// eso framework includes
#include <asi/sid/psdparser/IntPSDParserProxy.hxx>
#include <asi/sid/psdparser/IntPSDParserReply.hxx>

// system api and foundation library includes
#include <ara/log/logging.hpp>

// standard library includes
#include <memory>
#include <mutex>
#include <vector>

namespace vwg {
namespace sid {
namespace PSDParser {
namespace eso {

enum class HandlerState {
   kNotStarted,  // Target State: Disconnected
   kConnect,       // Target State: Connected
   kDisconnect     // Target State: Disconnected
};

using Proxy = asi::sid::psdparser::IntPSDParserProxy;

class SignalDataAccessHandler : public ISignalDataAccessHandler, public asi::sid::psdparser::IntPSDParserReply, public comm::LifecycleListener {
public:
   SignalDataAccessHandler();
   virtual ~SignalDataAccessHandler();

   void start(std::shared_ptr<ISignalDataListener>, ConnectionStateNotificationCallback) override;
   void suspend() override;
   void resume() override;


   void updatePSD_04(const CIPtr< asi::sid::psdparser::PSD04Struct >& pdu, const bool valid) override;
   void updatePSD_05(const CIPtr< asi::sid::psdparser::PSD05Struct >& pdu, const bool valid) override;
   void updatePSD_06(const CIPtr< asi::sid::psdparser::PSD06Struct >& pdu, const bool valid) override;


   void alive(comm::Lifecycle*, const comm::ServiceEvent&) override;
   void dead(comm::Lifecycle*, const comm::ServiceEvent&) override;

   void disconnected(asi::sid::psdparser::IntPSDParserProxy *disconnectedProxy, const comm::Proxy &sr); // TODO: virtual?  Added in analogy to alive and dead, but is not part of any adopted interface

private:
   using MyMutexType = std::recursive_mutex;

   const std::string myName = "ESO adapter for Signal Data API for application PSDParser";
   const int AGENT_STARTER_TIMEOUT = 1; // TODO: learn right type and value
   ara::log::Logger &logger;
   std::shared_ptr<ISignalDataListener> pListener = nullptr;
   std::unique_ptr<Proxy> pProxy = nullptr;
   std::vector<std::unique_ptr<Proxy>> proxiesToBeDisconnected;
   ConnectionStateNotificationCallback cbConnectionState;
   HandlerState state;
   bool isCallbackActive; // reentrancy marker
   MyMutexType mx; // to entirely protect event operations

   void simulateResponse();
   bool startProxy ();
   void notifyConnectionState(ConnectionState st);
};

} /* namespace eso */
} /* namespace PSDParser */
} /* namespace sid */
} /* namespace vwg */

#endif // ESO_ADAPTER_HPP
