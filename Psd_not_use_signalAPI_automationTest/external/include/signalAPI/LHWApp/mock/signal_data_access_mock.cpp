/**
 * \file signal_data_access_mock.cpp
 *
 * \brief Generated mock implementation for signal data access API specific for application LHWApp
 *
 * Code generator version: 0.8.8
 * Generator input:
 * - Data definition:      E3_1_1_UNECE_E3V_VLAN_Connect_KMatrix_Module_V15.04.00.03F_20221220_BAm_P02.xlsx
 * - Config file:          ./config/LHWApp.yaml
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

// mock of signal api includes
#include <vwg/sid/LHWApp/mock/signal_data_access_mock.hpp>

// signal api includes
#include <vwg/sid/LHWApp/signal_data_access.hpp>

// standard library includes
#include <iostream>

#if defined(__linux__) && defined(USE_SYSLOG)
#include <syslog.h> // syslog(...)
#include <unistd.h> // gettid()
#else
#include <cstdio>
#define syslog(x,...) {printf(__VA_ARGS__); printf("\n");}
#define gettid() 0
#endif

namespace vwg {
namespace sid {
namespace LHWApp {

// -- Rx PDU Blinkmodi_02 with 4 signals

// -- BEGIN: public API for target code

PduStatus RxPdu_Blinkmodi_02::getPduStatus() const noexcept { return status; }

bool RxPdu_Blinkmodi_02::get_BM_Warnblinken() const noexcept { return BM_Warnblinken_value; } // 1 bit
bool RxPdu_Blinkmodi_02::get_BM_Crash() const noexcept { return BM_Crash_value; } // 1 bit
bool RxPdu_Blinkmodi_02::get_BM_Not_Bremsung() const noexcept { return BM_Not_Bremsung_value; } // 1 bit
bool RxPdu_Blinkmodi_02::get_BM_Recas() const noexcept { return BM_Recas_value; } // 1 bit

// --   END: public API for target code


// -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING

void RxPdu_Blinkmodi_02::FOR_TESTING_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_Blinkmodi_02::FOR_TESTING_set_BM_Warnblinken(bool value) noexcept { BM_Warnblinken_value = value; return; } // 1 bit
void RxPdu_Blinkmodi_02::FOR_TESTING_set_BM_Crash(bool value) noexcept { BM_Crash_value = value; return; } // 1 bit
void RxPdu_Blinkmodi_02::FOR_TESTING_set_BM_Not_Bremsung(bool value) noexcept { BM_Not_Bremsung_value = value; return; } // 1 bit
void RxPdu_Blinkmodi_02::FOR_TESTING_set_BM_Recas(bool value) noexcept { BM_Recas_value = value; return; } // 1 bit

#endif // VWG_SID_CLIENT_TESTING

// --   END: public API for testing & mocking purposes only


// -- BEGIN: private API for internal use only

void RxPdu_Blinkmodi_02::PRIVATE_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_Blinkmodi_02::PRIVATE_set_BM_Warnblinken(bool value) noexcept { BM_Warnblinken_value = value; return; } // 1 bit
void RxPdu_Blinkmodi_02::PRIVATE_set_BM_Crash(bool value) noexcept { BM_Crash_value = value; return; } // 1 bit
void RxPdu_Blinkmodi_02::PRIVATE_set_BM_Not_Bremsung(bool value) noexcept { BM_Not_Bremsung_value = value; return; } // 1 bit
void RxPdu_Blinkmodi_02::PRIVATE_set_BM_Recas(bool value) noexcept { BM_Recas_value = value; return; } // 1 bit

// --   END: private API for internal use only


// -- Rx PDU ESP_21 with 5 signals

// -- BEGIN: public API for target code

PduStatus RxPdu_ESP_21::getPduStatus() const noexcept { return status; }

bool RxPdu_ESP_21::get_ESP_Eingriff() const noexcept { return ESP_Eingriff_value; } // 1 bit
bool RxPdu_ESP_21::get_ASR_Anf() const noexcept { return ASR_Anf_value; } // 1 bit
std::uint32_t RxPdu_ESP_21::get_ESP_v_Signal() const noexcept { return ESP_v_Signal_value; } // 16 bits
bool RxPdu_ESP_21::get_ESP_QBit_v_Signal() const noexcept { return ESP_QBit_v_Signal_value; } // 1 bit
bool RxPdu_ESP_21::get_ABS_Bremsung() const noexcept { return ABS_Bremsung_value; } // 1 bit

// --   END: public API for target code


// -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING

void RxPdu_ESP_21::FOR_TESTING_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_ESP_21::FOR_TESTING_set_ESP_Eingriff(bool value) noexcept { ESP_Eingriff_value = value; return; } // 1 bit
void RxPdu_ESP_21::FOR_TESTING_set_ASR_Anf(bool value) noexcept { ASR_Anf_value = value; return; } // 1 bit
void RxPdu_ESP_21::FOR_TESTING_set_ESP_v_Signal(std::uint32_t value) noexcept { ESP_v_Signal_value = value; return; } // 16 bits
void RxPdu_ESP_21::FOR_TESTING_set_ESP_QBit_v_Signal(bool value) noexcept { ESP_QBit_v_Signal_value = value; return; } // 1 bit
void RxPdu_ESP_21::FOR_TESTING_set_ABS_Bremsung(bool value) noexcept { ABS_Bremsung_value = value; return; } // 1 bit

#endif // VWG_SID_CLIENT_TESTING

// --   END: public API for testing & mocking purposes only


// -- BEGIN: private API for internal use only

void RxPdu_ESP_21::PRIVATE_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_ESP_21::PRIVATE_set_ESP_Eingriff(bool value) noexcept { ESP_Eingriff_value = value; return; } // 1 bit
void RxPdu_ESP_21::PRIVATE_set_ASR_Anf(bool value) noexcept { ASR_Anf_value = value; return; } // 1 bit
void RxPdu_ESP_21::PRIVATE_set_ESP_v_Signal(std::uint32_t value) noexcept { ESP_v_Signal_value = value; return; } // 16 bits
void RxPdu_ESP_21::PRIVATE_set_ESP_QBit_v_Signal(bool value) noexcept { ESP_QBit_v_Signal_value = value; return; } // 1 bit
void RxPdu_ESP_21::PRIVATE_set_ABS_Bremsung(bool value) noexcept { ABS_Bremsung_value = value; return; } // 1 bit

// --   END: private API for internal use only


// -- Rx PDU ESP_24 with 3 signals

// -- BEGIN: public API for target code

PduStatus RxPdu_ESP_24::getPduStatus() const noexcept { return status; }

bool RxPdu_ESP_24::get_ESP_Lampe() const noexcept { return ESP_Lampe_value; } // 1 bit
std::uint32_t RxPdu_ESP_24::get_BK_Lampe_02() const noexcept { return BK_Lampe_02_value; } // 2 bits
std::uint32_t RxPdu_ESP_24::get_ESP_Textanzeigen_03() const noexcept { return ESP_Textanzeigen_03_value; } // 5 bits

// --   END: public API for target code


// -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING

void RxPdu_ESP_24::FOR_TESTING_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_ESP_24::FOR_TESTING_set_ESP_Lampe(bool value) noexcept { ESP_Lampe_value = value; return; } // 1 bit
void RxPdu_ESP_24::FOR_TESTING_set_BK_Lampe_02(std::uint32_t value) noexcept { BK_Lampe_02_value = value; return; } // 2 bits
void RxPdu_ESP_24::FOR_TESTING_set_ESP_Textanzeigen_03(std::uint32_t value) noexcept { ESP_Textanzeigen_03_value = value; return; } // 5 bits

#endif // VWG_SID_CLIENT_TESTING

// --   END: public API for testing & mocking purposes only


// -- BEGIN: private API for internal use only

void RxPdu_ESP_24::PRIVATE_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_ESP_24::PRIVATE_set_ESP_Lampe(bool value) noexcept { ESP_Lampe_value = value; return; } // 1 bit
void RxPdu_ESP_24::PRIVATE_set_BK_Lampe_02(std::uint32_t value) noexcept { BK_Lampe_02_value = value; return; } // 2 bits
void RxPdu_ESP_24::PRIVATE_set_ESP_Textanzeigen_03(std::uint32_t value) noexcept { ESP_Textanzeigen_03_value = value; return; } // 5 bits

// --   END: private API for internal use only


// -- Rx PDU Airbag_01 with 1 signal

// -- BEGIN: public API for target code

PduStatus RxPdu_Airbag_01::getPduStatus() const noexcept { return status; }

std::uint32_t RxPdu_Airbag_01::get_AB_Crash_Int() const noexcept { return AB_Crash_Int_value; } // 3 bits

// --   END: public API for target code


// -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING

void RxPdu_Airbag_01::FOR_TESTING_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_Airbag_01::FOR_TESTING_set_AB_Crash_Int(std::uint32_t value) noexcept { AB_Crash_Int_value = value; return; } // 3 bits

#endif // VWG_SID_CLIENT_TESTING

// --   END: public API for testing & mocking purposes only


// -- BEGIN: private API for internal use only

void RxPdu_Airbag_01::PRIVATE_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_Airbag_01::PRIVATE_set_AB_Crash_Int(std::uint32_t value) noexcept { AB_Crash_Int_value = value; return; } // 3 bits

// --   END: private API for internal use only


// -- Rx PDU Motor_18 with 1 signal

// -- BEGIN: public API for target code

PduStatus RxPdu_Motor_18::getPduStatus() const noexcept { return status; }

std::uint32_t RxPdu_Motor_18::get_MO_EPCL() const noexcept { return MO_EPCL_value; } // 3 bits

// --   END: public API for target code


// -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING

void RxPdu_Motor_18::FOR_TESTING_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_Motor_18::FOR_TESTING_set_MO_EPCL(std::uint32_t value) noexcept { MO_EPCL_value = value; return; } // 3 bits

#endif // VWG_SID_CLIENT_TESTING

// --   END: public API for testing & mocking purposes only


// -- BEGIN: private API for internal use only

void RxPdu_Motor_18::PRIVATE_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_Motor_18::PRIVATE_set_MO_EPCL(std::uint32_t value) noexcept { MO_EPCL_value = value; return; } // 3 bits

// --   END: private API for internal use only


// -- Rx PDU HVK_01 with 1 signal

// -- BEGIN: public API for target code

PduStatus RxPdu_HVK_01::getPduStatus() const noexcept { return status; }

std::uint32_t RxPdu_HVK_01::get_HVK_HV_Netz_Warnungen() const noexcept { return HVK_HV_Netz_Warnungen_value; } // 2 bits

// --   END: public API for target code


// -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING

void RxPdu_HVK_01::FOR_TESTING_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_HVK_01::FOR_TESTING_set_HVK_HV_Netz_Warnungen(std::uint32_t value) noexcept { HVK_HV_Netz_Warnungen_value = value; return; } // 2 bits

#endif // VWG_SID_CLIENT_TESTING

// --   END: public API for testing & mocking purposes only


// -- BEGIN: private API for internal use only

void RxPdu_HVK_01::PRIVATE_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_HVK_01::PRIVATE_set_HVK_HV_Netz_Warnungen(std::uint32_t value) noexcept { HVK_HV_Netz_Warnungen_value = value; return; } // 2 bits

// --   END: private API for internal use only


// -- Rx PDU Daempfer_01 with 1 signal

// -- BEGIN: public API for target code

PduStatus RxPdu_Daempfer_01::getPduStatus() const noexcept { return status; }

std::uint32_t RxPdu_Daempfer_01::get_DR_Gelbe_Warnlampe() const noexcept { return DR_Gelbe_Warnlampe_value; } // 2 bits

// --   END: public API for target code


// -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING

void RxPdu_Daempfer_01::FOR_TESTING_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_Daempfer_01::FOR_TESTING_set_DR_Gelbe_Warnlampe(std::uint32_t value) noexcept { DR_Gelbe_Warnlampe_value = value; return; } // 2 bits

#endif // VWG_SID_CLIENT_TESTING

// --   END: public API for testing & mocking purposes only


// -- BEGIN: private API for internal use only

void RxPdu_Daempfer_01::PRIVATE_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_Daempfer_01::PRIVATE_set_DR_Gelbe_Warnlampe(std::uint32_t value) noexcept { DR_Gelbe_Warnlampe_value = value; return; } // 2 bits

// --   END: private API for internal use only


// -- Rx PDU ESP_30 with 1 signal

// -- BEGIN: public API for target code

PduStatus RxPdu_ESP_30::getPduStatus() const noexcept { return status; }

std::uint32_t RxPdu_ESP_30::get_RLE_Anzeigen() const noexcept { return RLE_Anzeigen_value; } // 3 bits

// --   END: public API for target code


// -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING

void RxPdu_ESP_30::FOR_TESTING_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_ESP_30::FOR_TESTING_set_RLE_Anzeigen(std::uint32_t value) noexcept { RLE_Anzeigen_value = value; return; } // 3 bits

#endif // VWG_SID_CLIENT_TESTING

// --   END: public API for testing & mocking purposes only


// -- BEGIN: private API for internal use only

void RxPdu_ESP_30::PRIVATE_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_ESP_30::PRIVATE_set_RLE_Anzeigen(std::uint32_t value) noexcept { RLE_Anzeigen_value = value; return; } // 3 bits

// --   END: private API for internal use only


// -- Rx PDU Motor_41 with 2 signals

// -- BEGIN: public API for target code

PduStatus RxPdu_Motor_41::getPduStatus() const noexcept { return status; }

std::uint32_t RxPdu_Motor_41::get_FDR_Warnung_ALR() const noexcept { return FDR_Warnung_ALR_value; } // 2 bits
std::uint32_t RxPdu_Motor_41::get_MO_EM_Ueberhitzungswarnung() const noexcept { return MO_EM_Ueberhitzungswarnung_value; } // 2 bits

// --   END: public API for target code


// -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING

void RxPdu_Motor_41::FOR_TESTING_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_Motor_41::FOR_TESTING_set_FDR_Warnung_ALR(std::uint32_t value) noexcept { FDR_Warnung_ALR_value = value; return; } // 2 bits
void RxPdu_Motor_41::FOR_TESTING_set_MO_EM_Ueberhitzungswarnung(std::uint32_t value) noexcept { MO_EM_Ueberhitzungswarnung_value = value; return; } // 2 bits

#endif // VWG_SID_CLIENT_TESTING

// --   END: public API for testing & mocking purposes only


// -- BEGIN: private API for internal use only

void RxPdu_Motor_41::PRIVATE_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_Motor_41::PRIVATE_set_FDR_Warnung_ALR(std::uint32_t value) noexcept { FDR_Warnung_ALR_value = value; return; } // 2 bits
void RxPdu_Motor_41::PRIVATE_set_MO_EM_Ueberhitzungswarnung(std::uint32_t value) noexcept { MO_EM_Ueberhitzungswarnung_value = value; return; } // 2 bits

// --   END: private API for internal use only


// -- Rx PDU RKA_01 with 2 signals

// -- BEGIN: public API for target code

PduStatus RxPdu_RKA_01::getPduStatus() const noexcept { return status; }

bool RxPdu_RKA_01::get_RKA_FMVSS138_Lampe() const noexcept { return RKA_FMVSS138_Lampe_value; } // 1 bit
std::uint32_t RxPdu_RKA_01::get_RKA_Warnungen_02() const noexcept { return RKA_Warnungen_02_value; } // 5 bits

// --   END: public API for target code


// -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING

void RxPdu_RKA_01::FOR_TESTING_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_RKA_01::FOR_TESTING_set_RKA_FMVSS138_Lampe(bool value) noexcept { RKA_FMVSS138_Lampe_value = value; return; } // 1 bit
void RxPdu_RKA_01::FOR_TESTING_set_RKA_Warnungen_02(std::uint32_t value) noexcept { RKA_Warnungen_02_value = value; return; } // 5 bits

#endif // VWG_SID_CLIENT_TESTING

// --   END: public API for testing & mocking purposes only


// -- BEGIN: private API for internal use only

void RxPdu_RKA_01::PRIVATE_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_RKA_01::PRIVATE_set_RKA_FMVSS138_Lampe(bool value) noexcept { RKA_FMVSS138_Lampe_value = value; return; } // 1 bit
void RxPdu_RKA_01::PRIVATE_set_RKA_Warnungen_02(std::uint32_t value) noexcept { RKA_Warnungen_02_value = value; return; } // 5 bits

// --   END: private API for internal use only


// -- Rx PDU ESC_50 with 7 signals

// -- BEGIN: public API for target code

PduStatus RxPdu_ESC_50::getPduStatus() const noexcept { return status; }

std::uint32_t RxPdu_ESC_50::get_ESP_Laengsbeschl() const noexcept { return ESP_Laengsbeschl_value; } // 10 bits
bool RxPdu_ESC_50::get_ESP_QBit_Laengsbeschl() const noexcept { return ESP_QBit_Laengsbeschl_value; } // 1 bit
std::uint32_t RxPdu_ESC_50::get_ESP_Querbeschleunigung() const noexcept { return ESP_Querbeschleunigung_value; } // 8 bits
bool RxPdu_ESC_50::get_ESP_QBit_Querb() const noexcept { return ESP_QBit_Querb_value; } // 1 bit
std::uint32_t RxPdu_ESC_50::get_ESP_Gierrate() const noexcept { return ESP_Gierrate_value; } // 14 bits
bool RxPdu_ESC_50::get_ESP_VZ_Gierrate() const noexcept { return ESP_VZ_Gierrate_value; } // 1 bit
bool RxPdu_ESC_50::get_ESP_QBit_Gierrate() const noexcept { return ESP_QBit_Gierrate_value; } // 1 bit

// --   END: public API for target code


// -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING

void RxPdu_ESC_50::FOR_TESTING_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_ESC_50::FOR_TESTING_set_ESP_Laengsbeschl(std::uint32_t value) noexcept { ESP_Laengsbeschl_value = value; return; } // 10 bits
void RxPdu_ESC_50::FOR_TESTING_set_ESP_QBit_Laengsbeschl(bool value) noexcept { ESP_QBit_Laengsbeschl_value = value; return; } // 1 bit
void RxPdu_ESC_50::FOR_TESTING_set_ESP_Querbeschleunigung(std::uint32_t value) noexcept { ESP_Querbeschleunigung_value = value; return; } // 8 bits
void RxPdu_ESC_50::FOR_TESTING_set_ESP_QBit_Querb(bool value) noexcept { ESP_QBit_Querb_value = value; return; } // 1 bit
void RxPdu_ESC_50::FOR_TESTING_set_ESP_Gierrate(std::uint32_t value) noexcept { ESP_Gierrate_value = value; return; } // 14 bits
void RxPdu_ESC_50::FOR_TESTING_set_ESP_VZ_Gierrate(bool value) noexcept { ESP_VZ_Gierrate_value = value; return; } // 1 bit
void RxPdu_ESC_50::FOR_TESTING_set_ESP_QBit_Gierrate(bool value) noexcept { ESP_QBit_Gierrate_value = value; return; } // 1 bit

#endif // VWG_SID_CLIENT_TESTING

// --   END: public API for testing & mocking purposes only


// -- BEGIN: private API for internal use only

void RxPdu_ESC_50::PRIVATE_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_ESC_50::PRIVATE_set_ESP_Laengsbeschl(std::uint32_t value) noexcept { ESP_Laengsbeschl_value = value; return; } // 10 bits
void RxPdu_ESC_50::PRIVATE_set_ESP_QBit_Laengsbeschl(bool value) noexcept { ESP_QBit_Laengsbeschl_value = value; return; } // 1 bit
void RxPdu_ESC_50::PRIVATE_set_ESP_Querbeschleunigung(std::uint32_t value) noexcept { ESP_Querbeschleunigung_value = value; return; } // 8 bits
void RxPdu_ESC_50::PRIVATE_set_ESP_QBit_Querb(bool value) noexcept { ESP_QBit_Querb_value = value; return; } // 1 bit
void RxPdu_ESC_50::PRIVATE_set_ESP_Gierrate(std::uint32_t value) noexcept { ESP_Gierrate_value = value; return; } // 14 bits
void RxPdu_ESC_50::PRIVATE_set_ESP_VZ_Gierrate(bool value) noexcept { ESP_VZ_Gierrate_value = value; return; } // 1 bit
void RxPdu_ESC_50::PRIVATE_set_ESP_QBit_Gierrate(bool value) noexcept { ESP_QBit_Gierrate_value = value; return; } // 1 bit

// --   END: private API for internal use only


// -- Rx PDU POS_GNSS_DR_01 with 7 signals

// -- BEGIN: public API for target code

PduStatus RxPdu_POS_GNSS_DR_01::getPduStatus() const noexcept { return status; }

std::uint64_t RxPdu_POS_GNSS_DR_01::get_POS_GNSS_DR_Breite_Ortung() const noexcept { return POS_GNSS_DR_Breite_Ortung_value; } // 35 bits
std::uint64_t RxPdu_POS_GNSS_DR_01::get_POS_GNSS_DR_Laenge_Ortung() const noexcept { return POS_GNSS_DR_Laenge_Ortung_value; } // 36 bits
std::uint32_t RxPdu_POS_GNSS_DR_01::get_POS_GNSS_DR_Ausrichtung_Geschw() const noexcept { return POS_GNSS_DR_Ausrichtung_Geschw_value; } // 12 bits
std::uint32_t RxPdu_POS_GNSS_DR_01::get_POS_GNSS_DR_Guete_Ausricht_Gesch() const noexcept { return POS_GNSS_DR_Guete_Ausricht_Gesch_value; } // 11 bits
std::uint32_t RxPdu_POS_GNSS_DR_01::get_POS_GNSS_DR_Guete_E_GrH_Ausr() const noexcept { return POS_GNSS_DR_Guete_E_GrH_Ausr_value; } // 12 bits
std::uint32_t RxPdu_POS_GNSS_DR_01::get_POS_GNSS_DR_Guete_E_GrHalbachse() const noexcept { return POS_GNSS_DR_Guete_E_GrHalbachse_value; } // 15 bits
std::uint32_t RxPdu_POS_GNSS_DR_01::get_POS_GNSS_DR_Guete_E_KlHalbachse() const noexcept { return POS_GNSS_DR_Guete_E_KlHalbachse_value; } // 15 bits

// --   END: public API for target code


// -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING

void RxPdu_POS_GNSS_DR_01::FOR_TESTING_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_POS_GNSS_DR_01::FOR_TESTING_set_POS_GNSS_DR_Breite_Ortung(std::uint64_t value) noexcept { POS_GNSS_DR_Breite_Ortung_value = value; return; } // 35 bits
void RxPdu_POS_GNSS_DR_01::FOR_TESTING_set_POS_GNSS_DR_Laenge_Ortung(std::uint64_t value) noexcept { POS_GNSS_DR_Laenge_Ortung_value = value; return; } // 36 bits
void RxPdu_POS_GNSS_DR_01::FOR_TESTING_set_POS_GNSS_DR_Ausrichtung_Geschw(std::uint32_t value) noexcept { POS_GNSS_DR_Ausrichtung_Geschw_value = value; return; } // 12 bits
void RxPdu_POS_GNSS_DR_01::FOR_TESTING_set_POS_GNSS_DR_Guete_Ausricht_Gesch(std::uint32_t value) noexcept { POS_GNSS_DR_Guete_Ausricht_Gesch_value = value; return; } // 11 bits
void RxPdu_POS_GNSS_DR_01::FOR_TESTING_set_POS_GNSS_DR_Guete_E_GrH_Ausr(std::uint32_t value) noexcept { POS_GNSS_DR_Guete_E_GrH_Ausr_value = value; return; } // 12 bits
void RxPdu_POS_GNSS_DR_01::FOR_TESTING_set_POS_GNSS_DR_Guete_E_GrHalbachse(std::uint32_t value) noexcept { POS_GNSS_DR_Guete_E_GrHalbachse_value = value; return; } // 15 bits
void RxPdu_POS_GNSS_DR_01::FOR_TESTING_set_POS_GNSS_DR_Guete_E_KlHalbachse(std::uint32_t value) noexcept { POS_GNSS_DR_Guete_E_KlHalbachse_value = value; return; } // 15 bits

#endif // VWG_SID_CLIENT_TESTING

// --   END: public API for testing & mocking purposes only


// -- BEGIN: private API for internal use only

void RxPdu_POS_GNSS_DR_01::PRIVATE_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_POS_GNSS_DR_01::PRIVATE_set_POS_GNSS_DR_Breite_Ortung(std::uint64_t value) noexcept { POS_GNSS_DR_Breite_Ortung_value = value; return; } // 35 bits
void RxPdu_POS_GNSS_DR_01::PRIVATE_set_POS_GNSS_DR_Laenge_Ortung(std::uint64_t value) noexcept { POS_GNSS_DR_Laenge_Ortung_value = value; return; } // 36 bits
void RxPdu_POS_GNSS_DR_01::PRIVATE_set_POS_GNSS_DR_Ausrichtung_Geschw(std::uint32_t value) noexcept { POS_GNSS_DR_Ausrichtung_Geschw_value = value; return; } // 12 bits
void RxPdu_POS_GNSS_DR_01::PRIVATE_set_POS_GNSS_DR_Guete_Ausricht_Gesch(std::uint32_t value) noexcept { POS_GNSS_DR_Guete_Ausricht_Gesch_value = value; return; } // 11 bits
void RxPdu_POS_GNSS_DR_01::PRIVATE_set_POS_GNSS_DR_Guete_E_GrH_Ausr(std::uint32_t value) noexcept { POS_GNSS_DR_Guete_E_GrH_Ausr_value = value; return; } // 12 bits
void RxPdu_POS_GNSS_DR_01::PRIVATE_set_POS_GNSS_DR_Guete_E_GrHalbachse(std::uint32_t value) noexcept { POS_GNSS_DR_Guete_E_GrHalbachse_value = value; return; } // 15 bits
void RxPdu_POS_GNSS_DR_01::PRIVATE_set_POS_GNSS_DR_Guete_E_KlHalbachse(std::uint32_t value) noexcept { POS_GNSS_DR_Guete_E_KlHalbachse_value = value; return; } // 15 bits

// --   END: private API for internal use only


// -- Rx PDU PSD_04 with 13 signals

// -- BEGIN: public API for target code

PduStatus RxPdu_PSD_04::getPduStatus() const noexcept { return status; }

std::uint32_t RxPdu_PSD_04::get_PSD_Segment_ID() const noexcept { return PSD_Segment_ID_value; } // 6 bits
std::uint32_t RxPdu_PSD_04::get_PSD_Vorgaenger_Segment_ID() const noexcept { return PSD_Vorgaenger_Segment_ID_value; } // 6 bits
std::uint32_t RxPdu_PSD_04::get_PSD_Segmentlaenge() const noexcept { return PSD_Segmentlaenge_value; } // 7 bits
std::uint32_t RxPdu_PSD_04::get_PSD_Strassenkategorie() const noexcept { return PSD_Strassenkategorie_value; } // 3 bits
std::uint32_t RxPdu_PSD_04::get_PSD_Endkruemmung() const noexcept { return PSD_Endkruemmung_value; } // 8 bits
bool RxPdu_PSD_04::get_PSD_Endkruemmung_Vorz() const noexcept { return PSD_Endkruemmung_Vorz_value; } // 1 bit
bool RxPdu_PSD_04::get_PSD_wahrscheinlichster_Pfad() const noexcept { return PSD_wahrscheinlichster_Pfad_value; } // 1 bit
bool RxPdu_PSD_04::get_PSD_Geradester_Pfad() const noexcept { return PSD_Geradester_Pfad_value; } // 1 bit
bool RxPdu_PSD_04::get_PSD_Segment_Komplett() const noexcept { return PSD_Segment_Komplett_value; } // 1 bit
std::uint32_t RxPdu_PSD_04::get_PSD_Anfangskruemmung() const noexcept { return PSD_Anfangskruemmung_value; } // 8 bits
bool RxPdu_PSD_04::get_PSD_Anfangskruemmung_Vorz() const noexcept { return PSD_Anfangskruemmung_Vorz_value; } // 1 bit
bool RxPdu_PSD_04::get_PSD_Abzweigerichtung() const noexcept { return PSD_Abzweigerichtung_value; } // 1 bit
std::uint32_t RxPdu_PSD_04::get_PSD_Abzweigewinkel() const noexcept { return PSD_Abzweigewinkel_value; } // 7 bits

// --   END: public API for target code


// -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING

void RxPdu_PSD_04::FOR_TESTING_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_PSD_04::FOR_TESTING_set_PSD_Segment_ID(std::uint32_t value) noexcept { PSD_Segment_ID_value = value; return; } // 6 bits
void RxPdu_PSD_04::FOR_TESTING_set_PSD_Vorgaenger_Segment_ID(std::uint32_t value) noexcept { PSD_Vorgaenger_Segment_ID_value = value; return; } // 6 bits
void RxPdu_PSD_04::FOR_TESTING_set_PSD_Segmentlaenge(std::uint32_t value) noexcept { PSD_Segmentlaenge_value = value; return; } // 7 bits
void RxPdu_PSD_04::FOR_TESTING_set_PSD_Strassenkategorie(std::uint32_t value) noexcept { PSD_Strassenkategorie_value = value; return; } // 3 bits
void RxPdu_PSD_04::FOR_TESTING_set_PSD_Endkruemmung(std::uint32_t value) noexcept { PSD_Endkruemmung_value = value; return; } // 8 bits
void RxPdu_PSD_04::FOR_TESTING_set_PSD_Endkruemmung_Vorz(bool value) noexcept { PSD_Endkruemmung_Vorz_value = value; return; } // 1 bit
void RxPdu_PSD_04::FOR_TESTING_set_PSD_wahrscheinlichster_Pfad(bool value) noexcept { PSD_wahrscheinlichster_Pfad_value = value; return; } // 1 bit
void RxPdu_PSD_04::FOR_TESTING_set_PSD_Geradester_Pfad(bool value) noexcept { PSD_Geradester_Pfad_value = value; return; } // 1 bit
void RxPdu_PSD_04::FOR_TESTING_set_PSD_Segment_Komplett(bool value) noexcept { PSD_Segment_Komplett_value = value; return; } // 1 bit
void RxPdu_PSD_04::FOR_TESTING_set_PSD_Anfangskruemmung(std::uint32_t value) noexcept { PSD_Anfangskruemmung_value = value; return; } // 8 bits
void RxPdu_PSD_04::FOR_TESTING_set_PSD_Anfangskruemmung_Vorz(bool value) noexcept { PSD_Anfangskruemmung_Vorz_value = value; return; } // 1 bit
void RxPdu_PSD_04::FOR_TESTING_set_PSD_Abzweigerichtung(bool value) noexcept { PSD_Abzweigerichtung_value = value; return; } // 1 bit
void RxPdu_PSD_04::FOR_TESTING_set_PSD_Abzweigewinkel(std::uint32_t value) noexcept { PSD_Abzweigewinkel_value = value; return; } // 7 bits

#endif // VWG_SID_CLIENT_TESTING

// --   END: public API for testing & mocking purposes only


// -- BEGIN: private API for internal use only

void RxPdu_PSD_04::PRIVATE_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_PSD_04::PRIVATE_set_PSD_Segment_ID(std::uint32_t value) noexcept { PSD_Segment_ID_value = value; return; } // 6 bits
void RxPdu_PSD_04::PRIVATE_set_PSD_Vorgaenger_Segment_ID(std::uint32_t value) noexcept { PSD_Vorgaenger_Segment_ID_value = value; return; } // 6 bits
void RxPdu_PSD_04::PRIVATE_set_PSD_Segmentlaenge(std::uint32_t value) noexcept { PSD_Segmentlaenge_value = value; return; } // 7 bits
void RxPdu_PSD_04::PRIVATE_set_PSD_Strassenkategorie(std::uint32_t value) noexcept { PSD_Strassenkategorie_value = value; return; } // 3 bits
void RxPdu_PSD_04::PRIVATE_set_PSD_Endkruemmung(std::uint32_t value) noexcept { PSD_Endkruemmung_value = value; return; } // 8 bits
void RxPdu_PSD_04::PRIVATE_set_PSD_Endkruemmung_Vorz(bool value) noexcept { PSD_Endkruemmung_Vorz_value = value; return; } // 1 bit
void RxPdu_PSD_04::PRIVATE_set_PSD_wahrscheinlichster_Pfad(bool value) noexcept { PSD_wahrscheinlichster_Pfad_value = value; return; } // 1 bit
void RxPdu_PSD_04::PRIVATE_set_PSD_Geradester_Pfad(bool value) noexcept { PSD_Geradester_Pfad_value = value; return; } // 1 bit
void RxPdu_PSD_04::PRIVATE_set_PSD_Segment_Komplett(bool value) noexcept { PSD_Segment_Komplett_value = value; return; } // 1 bit
void RxPdu_PSD_04::PRIVATE_set_PSD_Anfangskruemmung(std::uint32_t value) noexcept { PSD_Anfangskruemmung_value = value; return; } // 8 bits
void RxPdu_PSD_04::PRIVATE_set_PSD_Anfangskruemmung_Vorz(bool value) noexcept { PSD_Anfangskruemmung_Vorz_value = value; return; } // 1 bit
void RxPdu_PSD_04::PRIVATE_set_PSD_Abzweigerichtung(bool value) noexcept { PSD_Abzweigerichtung_value = value; return; } // 1 bit
void RxPdu_PSD_04::PRIVATE_set_PSD_Abzweigewinkel(std::uint32_t value) noexcept { PSD_Abzweigewinkel_value = value; return; } // 7 bits

// --   END: private API for internal use only


// -- Rx PDU PSD_05 with 8 signals

// -- BEGIN: public API for target code

PduStatus RxPdu_PSD_05::getPduStatus() const noexcept { return status; }

std::uint32_t RxPdu_PSD_05::get_PSD_Pos_Segment_ID() const noexcept { return PSD_Pos_Segment_ID_value; } // 6 bits
std::uint32_t RxPdu_PSD_05::get_PSD_Pos_Segmentlaenge() const noexcept { return PSD_Pos_Segmentlaenge_value; } // 7 bits
bool RxPdu_PSD_05::get_PSD_Pos_Standort_Eindeutig() const noexcept { return PSD_Pos_Standort_Eindeutig_value; } // 1 bit
std::uint32_t RxPdu_PSD_05::get_PSD_Pos_Fehler_Laengsrichtung() const noexcept { return PSD_Pos_Fehler_Laengsrichtung_value; } // 3 bits
std::uint32_t RxPdu_PSD_05::get_PSD_Attribut_1_ID() const noexcept { return PSD_Attribut_1_ID_value; } // 5 bits
std::uint32_t RxPdu_PSD_05::get_PSD_Attribut_1_Wert() const noexcept { return PSD_Attribut_1_Wert_value; } // 4 bits
std::uint32_t RxPdu_PSD_05::get_PSD_Attribut_2_ID() const noexcept { return PSD_Attribut_2_ID_value; } // 5 bits
std::uint32_t RxPdu_PSD_05::get_PSD_Attribut_2_Wert() const noexcept { return PSD_Attribut_2_Wert_value; } // 4 bits

// --   END: public API for target code


// -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING

void RxPdu_PSD_05::FOR_TESTING_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_PSD_05::FOR_TESTING_set_PSD_Pos_Segment_ID(std::uint32_t value) noexcept { PSD_Pos_Segment_ID_value = value; return; } // 6 bits
void RxPdu_PSD_05::FOR_TESTING_set_PSD_Pos_Segmentlaenge(std::uint32_t value) noexcept { PSD_Pos_Segmentlaenge_value = value; return; } // 7 bits
void RxPdu_PSD_05::FOR_TESTING_set_PSD_Pos_Standort_Eindeutig(bool value) noexcept { PSD_Pos_Standort_Eindeutig_value = value; return; } // 1 bit
void RxPdu_PSD_05::FOR_TESTING_set_PSD_Pos_Fehler_Laengsrichtung(std::uint32_t value) noexcept { PSD_Pos_Fehler_Laengsrichtung_value = value; return; } // 3 bits
void RxPdu_PSD_05::FOR_TESTING_set_PSD_Attribut_1_ID(std::uint32_t value) noexcept { PSD_Attribut_1_ID_value = value; return; } // 5 bits
void RxPdu_PSD_05::FOR_TESTING_set_PSD_Attribut_1_Wert(std::uint32_t value) noexcept { PSD_Attribut_1_Wert_value = value; return; } // 4 bits
void RxPdu_PSD_05::FOR_TESTING_set_PSD_Attribut_2_ID(std::uint32_t value) noexcept { PSD_Attribut_2_ID_value = value; return; } // 5 bits
void RxPdu_PSD_05::FOR_TESTING_set_PSD_Attribut_2_Wert(std::uint32_t value) noexcept { PSD_Attribut_2_Wert_value = value; return; } // 4 bits

#endif // VWG_SID_CLIENT_TESTING

// --   END: public API for testing & mocking purposes only


// -- BEGIN: private API for internal use only

void RxPdu_PSD_05::PRIVATE_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_PSD_05::PRIVATE_set_PSD_Pos_Segment_ID(std::uint32_t value) noexcept { PSD_Pos_Segment_ID_value = value; return; } // 6 bits
void RxPdu_PSD_05::PRIVATE_set_PSD_Pos_Segmentlaenge(std::uint32_t value) noexcept { PSD_Pos_Segmentlaenge_value = value; return; } // 7 bits
void RxPdu_PSD_05::PRIVATE_set_PSD_Pos_Standort_Eindeutig(bool value) noexcept { PSD_Pos_Standort_Eindeutig_value = value; return; } // 1 bit
void RxPdu_PSD_05::PRIVATE_set_PSD_Pos_Fehler_Laengsrichtung(std::uint32_t value) noexcept { PSD_Pos_Fehler_Laengsrichtung_value = value; return; } // 3 bits
void RxPdu_PSD_05::PRIVATE_set_PSD_Attribut_1_ID(std::uint32_t value) noexcept { PSD_Attribut_1_ID_value = value; return; } // 5 bits
void RxPdu_PSD_05::PRIVATE_set_PSD_Attribut_1_Wert(std::uint32_t value) noexcept { PSD_Attribut_1_Wert_value = value; return; } // 4 bits
void RxPdu_PSD_05::PRIVATE_set_PSD_Attribut_2_ID(std::uint32_t value) noexcept { PSD_Attribut_2_ID_value = value; return; } // 5 bits
void RxPdu_PSD_05::PRIVATE_set_PSD_Attribut_2_Wert(std::uint32_t value) noexcept { PSD_Attribut_2_Wert_value = value; return; } // 4 bits

// --   END: private API for internal use only


// -- Rx PDU PSD_06 with 7 signals

// -- BEGIN: public API for target code

PduStatus RxPdu_PSD_06::getPduStatus() const noexcept { return status; }

std::uint32_t RxPdu_PSD_06::get_PSD_Attribut_Segment_ID() const noexcept { return PSD_Attribut_Segment_ID_value; } // 6 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Attribut_3_ID() const noexcept { return PSD_Attribut_3_ID_value; } // 5 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Attribut_3_Wert() const noexcept { return PSD_Attribut_3_Wert_value; } // 4 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Attribut_4_ID() const noexcept { return PSD_Attribut_4_ID_value; } // 5 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Attribut_4_Wert() const noexcept { return PSD_Attribut_4_Wert_value; } // 4 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Attribut_5_ID() const noexcept { return PSD_Attribut_5_ID_value; } // 5 bits
std::uint32_t RxPdu_PSD_06::get_PSD_Attribut_5_Wert() const noexcept { return PSD_Attribut_5_Wert_value; } // 4 bits

// --   END: public API for target code


// -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING

void RxPdu_PSD_06::FOR_TESTING_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_PSD_06::FOR_TESTING_set_PSD_Attribut_Segment_ID(std::uint32_t value) noexcept { PSD_Attribut_Segment_ID_value = value; return; } // 6 bits
void RxPdu_PSD_06::FOR_TESTING_set_PSD_Attribut_3_ID(std::uint32_t value) noexcept { PSD_Attribut_3_ID_value = value; return; } // 5 bits
void RxPdu_PSD_06::FOR_TESTING_set_PSD_Attribut_3_Wert(std::uint32_t value) noexcept { PSD_Attribut_3_Wert_value = value; return; } // 4 bits
void RxPdu_PSD_06::FOR_TESTING_set_PSD_Attribut_4_ID(std::uint32_t value) noexcept { PSD_Attribut_4_ID_value = value; return; } // 5 bits
void RxPdu_PSD_06::FOR_TESTING_set_PSD_Attribut_4_Wert(std::uint32_t value) noexcept { PSD_Attribut_4_Wert_value = value; return; } // 4 bits
void RxPdu_PSD_06::FOR_TESTING_set_PSD_Attribut_5_ID(std::uint32_t value) noexcept { PSD_Attribut_5_ID_value = value; return; } // 5 bits
void RxPdu_PSD_06::FOR_TESTING_set_PSD_Attribut_5_Wert(std::uint32_t value) noexcept { PSD_Attribut_5_Wert_value = value; return; } // 4 bits

#endif // VWG_SID_CLIENT_TESTING

// --   END: public API for testing & mocking purposes only


// -- BEGIN: private API for internal use only

void RxPdu_PSD_06::PRIVATE_setPduStatus(PduStatus status) noexcept { this->status = status; }

void RxPdu_PSD_06::PRIVATE_set_PSD_Attribut_Segment_ID(std::uint32_t value) noexcept { PSD_Attribut_Segment_ID_value = value; return; } // 6 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Attribut_3_ID(std::uint32_t value) noexcept { PSD_Attribut_3_ID_value = value; return; } // 5 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Attribut_3_Wert(std::uint32_t value) noexcept { PSD_Attribut_3_Wert_value = value; return; } // 4 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Attribut_4_ID(std::uint32_t value) noexcept { PSD_Attribut_4_ID_value = value; return; } // 5 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Attribut_4_Wert(std::uint32_t value) noexcept { PSD_Attribut_4_Wert_value = value; return; } // 4 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Attribut_5_ID(std::uint32_t value) noexcept { PSD_Attribut_5_ID_value = value; return; } // 5 bits
void RxPdu_PSD_06::PRIVATE_set_PSD_Attribut_5_Wert(std::uint32_t value) noexcept { PSD_Attribut_5_Wert_value = value; return; } // 4 bits

// --   END: private API for internal use only




ISignalDataAccessHandler & getSignalDataAccessHandler() {
    static mock::MinimalMockSignalDataAccessHandler res{};
    return res;
}

namespace mock {

std::shared_ptr<ISignalDataListener> MinimalMockSignalDataAccessHandler::pListener = nullptr;
ConnectionStateNotificationCallback MinimalMockSignalDataAccessHandler::cbConnectionState;

//start 这里什么操作都没有

void MinimalMockSignalDataAccessHandler::start(std::shared_ptr<ISignalDataListener> pListener, ConnectionStateNotificationCallback cb) {
   std::cout << "starting minimal mock" << std::endl;
   MinimalMockSignalDataAccessHandler::pListener = std::move(pListener);
   MinimalMockSignalDataAccessHandler::cbConnectionState = std::move(cb);
   if (MinimalMockSignalDataAccessHandler::cbConnectionState) {
      MinimalMockSignalDataAccessHandler::cbConnectionState(ConnectionState::kConnecting);
      MinimalMockSignalDataAccessHandler::cbConnectionState(ConnectionState::kConnected);
     
   }

}

void MinimalMockSignalDataAccessHandler::suspend() {
   if (MinimalMockSignalDataAccessHandler::cbConnectionState) {
      MinimalMockSignalDataAccessHandler::cbConnectionState(ConnectionState::kDisconnecting);
      MinimalMockSignalDataAccessHandler::cbConnectionState(ConnectionState::kDisconnected);
   }
}

void MinimalMockSignalDataAccessHandler::resume() {
   if (MinimalMockSignalDataAccessHandler::cbConnectionState) {
      MinimalMockSignalDataAccessHandler::cbConnectionState(ConnectionState::kConnecting);
      MinimalMockSignalDataAccessHandler::cbConnectionState(ConnectionState::kConnected);
   }
}


std::shared_ptr<ISignalDataListener> MinimalMockSignalDataAccessHandler::getListener() {
   return pListener;
}

} /* namespace mock */

} /* namespace LHWApp */
} /* namespace sid */
} /* namespace vwg */
