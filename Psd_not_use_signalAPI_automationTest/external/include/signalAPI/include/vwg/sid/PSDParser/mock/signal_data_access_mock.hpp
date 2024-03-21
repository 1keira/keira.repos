/**
 * \file signal_data_access_mock.hpp
 *
 * \brief Generated signal data access mock specific for application PSDParser
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

#ifndef VWG_SID_PSDPARSER_MOCK_SIGNAL_DATA_ACCESS_MOCK_HPP_
#define VWG_SID_PSDPARSER_MOCK_SIGNAL_DATA_ACCESS_MOCK_HPP_

// signal api includes
#include <vwg/sid/PSDParser/signal_data_access.hpp>

// standard library includes
#include <cstdint>
#include <memory>
#include <vector>

namespace vwg {
namespace sid {
namespace PSDParser {
namespace mock {

class MinimalMockSignalDataAccessHandler : public ISignalDataAccessHandler {
public:
   void start(std::shared_ptr<ISignalDataListener>, ConnectionStateNotificationCallback) override;

   void suspend() override;
   void resume() override;


   static std::shared_ptr<ISignalDataListener> getListener();

private:
   static std::shared_ptr<ISignalDataListener> pListener;
   static ConnectionStateNotificationCallback cbConnectionState;
};

} /* namespace mock */
} /* namespace PSDParser */
} /* namespace sid */
} /* namespace vwg */

#endif // VWG_SID_PSDPARSER_MOCK_SIGNAL_DATA_ACCESS_MOCK_HPP_
