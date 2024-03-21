/**
 * \file signal_data_access.hpp
 *
 * \brief Generated signal data access API specific for application LHWApp
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

#ifndef VWG_SID_LHWAPP_SIGNAL_DATA_ACCESS_HPP_
#define VWG_SID_LHWAPP_SIGNAL_DATA_ACCESS_HPP_

// standard library includes
#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

namespace vwg {
namespace sid {
namespace LHWApp {

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

class RxPdu_Blinkmodi_02 final {

   // -- BEGIN: public API for target code

public:
   RxPdu_Blinkmodi_02() = default; // default ctor
   ~RxPdu_Blinkmodi_02() = default; // default dtor
   RxPdu_Blinkmodi_02(RxPdu_Blinkmodi_02 const &) = default; // default copy ctor
   RxPdu_Blinkmodi_02(RxPdu_Blinkmodi_02 &&) = default; // default move ctor
   RxPdu_Blinkmodi_02 & operator=(RxPdu_Blinkmodi_02 const &) = default; // default copy assignment
   RxPdu_Blinkmodi_02 & operator=(RxPdu_Blinkmodi_02 &&) = default; // default move assignment

   PduStatus getPduStatus() const noexcept;

   bool get_BM_Warnblinken() const noexcept; // 1 bit
   bool get_BM_Crash() const noexcept; // 1 bit
   bool get_BM_Not_Bremsung() const noexcept; // 1 bit
   bool get_BM_Recas() const noexcept; // 1 bit

   // --   END: public API for target code


   // -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING
public:
   void FOR_TESTING_setPduStatus(PduStatus status) noexcept;

   void FOR_TESTING_set_BM_Warnblinken(bool) noexcept; // 1 bit
   void FOR_TESTING_set_BM_Crash(bool) noexcept; // 1 bit
   void FOR_TESTING_set_BM_Not_Bremsung(bool) noexcept; // 1 bit
   void FOR_TESTING_set_BM_Recas(bool) noexcept; // 1 bit
#endif // VWG_SID_CLIENT_TESTING

   // --   END: public API for testing & mocking purposes only


   // -- BEGIN: private API for internal use only

   void PRIVATE_setPduStatus(PduStatus status) noexcept;

   void PRIVATE_set_BM_Warnblinken(bool) noexcept; // 1 bit
   void PRIVATE_set_BM_Crash(bool) noexcept; // 1 bit
   void PRIVATE_set_BM_Not_Bremsung(bool) noexcept; // 1 bit
   void PRIVATE_set_BM_Recas(bool) noexcept; // 1 bit

private:
   PduStatus status = PduStatus::kNotValid;
   bool BM_Warnblinken_value;
   bool BM_Crash_value;
   bool BM_Not_Bremsung_value;
   bool BM_Recas_value;

   // --   END: private API for internal use only
};

class RxPdu_ESP_21 final {

   // -- BEGIN: public API for target code

public:
   RxPdu_ESP_21() = default; // default ctor
   ~RxPdu_ESP_21() = default; // default dtor
   RxPdu_ESP_21(RxPdu_ESP_21 const &) = default; // default copy ctor
   RxPdu_ESP_21(RxPdu_ESP_21 &&) = default; // default move ctor
   RxPdu_ESP_21 & operator=(RxPdu_ESP_21 const &) = default; // default copy assignment
   RxPdu_ESP_21 & operator=(RxPdu_ESP_21 &&) = default; // default move assignment

   PduStatus getPduStatus() const noexcept;

   bool get_ESP_Eingriff() const noexcept; // 1 bit
   bool get_ASR_Anf() const noexcept; // 1 bit
   std::uint32_t get_ESP_v_Signal() const noexcept; // 16 bits
   bool get_ESP_QBit_v_Signal() const noexcept; // 1 bit
   bool get_ABS_Bremsung() const noexcept; // 1 bit

   // --   END: public API for target code


   // -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING
public:
   void FOR_TESTING_setPduStatus(PduStatus status) noexcept;

   void FOR_TESTING_set_ESP_Eingriff(bool) noexcept; // 1 bit
   void FOR_TESTING_set_ASR_Anf(bool) noexcept; // 1 bit
   void FOR_TESTING_set_ESP_v_Signal(std::uint32_t) noexcept; // 16 bits
   void FOR_TESTING_set_ESP_QBit_v_Signal(bool) noexcept; // 1 bit
   void FOR_TESTING_set_ABS_Bremsung(bool) noexcept; // 1 bit
#endif // VWG_SID_CLIENT_TESTING

   // --   END: public API for testing & mocking purposes only


   // -- BEGIN: private API for internal use only

   void PRIVATE_setPduStatus(PduStatus status) noexcept;

   void PRIVATE_set_ESP_Eingriff(bool) noexcept; // 1 bit
   void PRIVATE_set_ASR_Anf(bool) noexcept; // 1 bit
   void PRIVATE_set_ESP_v_Signal(std::uint32_t) noexcept; // 16 bits
   void PRIVATE_set_ESP_QBit_v_Signal(bool) noexcept; // 1 bit
   void PRIVATE_set_ABS_Bremsung(bool) noexcept; // 1 bit

private:
   PduStatus status = PduStatus::kNotValid;
   bool ESP_Eingriff_value;
   bool ASR_Anf_value;
   std::uint32_t ESP_v_Signal_value;
   bool ESP_QBit_v_Signal_value;
   bool ABS_Bremsung_value;

   // --   END: private API for internal use only
};

class RxPdu_ESP_24 final {

   // -- BEGIN: public API for target code

public:
   RxPdu_ESP_24() = default; // default ctor
   ~RxPdu_ESP_24() = default; // default dtor
   RxPdu_ESP_24(RxPdu_ESP_24 const &) = default; // default copy ctor
   RxPdu_ESP_24(RxPdu_ESP_24 &&) = default; // default move ctor
   RxPdu_ESP_24 & operator=(RxPdu_ESP_24 const &) = default; // default copy assignment
   RxPdu_ESP_24 & operator=(RxPdu_ESP_24 &&) = default; // default move assignment

   PduStatus getPduStatus() const noexcept;

   bool get_ESP_Lampe() const noexcept; // 1 bit
   std::uint32_t get_BK_Lampe_02() const noexcept; // 2 bits
   std::uint32_t get_ESP_Textanzeigen_03() const noexcept; // 5 bits

   // --   END: public API for target code


   // -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING
public:
   void FOR_TESTING_setPduStatus(PduStatus status) noexcept;

   void FOR_TESTING_set_ESP_Lampe(bool) noexcept; // 1 bit
   void FOR_TESTING_set_BK_Lampe_02(std::uint32_t) noexcept; // 2 bits
   void FOR_TESTING_set_ESP_Textanzeigen_03(std::uint32_t) noexcept; // 5 bits
#endif // VWG_SID_CLIENT_TESTING

   // --   END: public API for testing & mocking purposes only


   // -- BEGIN: private API for internal use only

   void PRIVATE_setPduStatus(PduStatus status) noexcept;

   void PRIVATE_set_ESP_Lampe(bool) noexcept; // 1 bit
   void PRIVATE_set_BK_Lampe_02(std::uint32_t) noexcept; // 2 bits
   void PRIVATE_set_ESP_Textanzeigen_03(std::uint32_t) noexcept; // 5 bits

private:
   PduStatus status = PduStatus::kNotValid;
   bool ESP_Lampe_value;
   std::uint32_t BK_Lampe_02_value;
   std::uint32_t ESP_Textanzeigen_03_value;

   // --   END: private API for internal use only
};

class RxPdu_Airbag_01 final {

   // -- BEGIN: public API for target code

public:
   RxPdu_Airbag_01() = default; // default ctor
   ~RxPdu_Airbag_01() = default; // default dtor
   RxPdu_Airbag_01(RxPdu_Airbag_01 const &) = default; // default copy ctor
   RxPdu_Airbag_01(RxPdu_Airbag_01 &&) = default; // default move ctor
   RxPdu_Airbag_01 & operator=(RxPdu_Airbag_01 const &) = default; // default copy assignment
   RxPdu_Airbag_01 & operator=(RxPdu_Airbag_01 &&) = default; // default move assignment

   PduStatus getPduStatus() const noexcept;

   std::uint32_t get_AB_Crash_Int() const noexcept; // 3 bits

   // --   END: public API for target code


   // -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING
public:
   void FOR_TESTING_setPduStatus(PduStatus status) noexcept;

   void FOR_TESTING_set_AB_Crash_Int(std::uint32_t) noexcept; // 3 bits
#endif // VWG_SID_CLIENT_TESTING

   // --   END: public API for testing & mocking purposes only


   // -- BEGIN: private API for internal use only

   void PRIVATE_setPduStatus(PduStatus status) noexcept;

   void PRIVATE_set_AB_Crash_Int(std::uint32_t) noexcept; // 3 bits

private:
   PduStatus status = PduStatus::kNotValid;
   std::uint32_t AB_Crash_Int_value;

   // --   END: private API for internal use only
};

class RxPdu_Motor_18 final {

   // -- BEGIN: public API for target code

public:
   RxPdu_Motor_18() = default; // default ctor
   ~RxPdu_Motor_18() = default; // default dtor
   RxPdu_Motor_18(RxPdu_Motor_18 const &) = default; // default copy ctor
   RxPdu_Motor_18(RxPdu_Motor_18 &&) = default; // default move ctor
   RxPdu_Motor_18 & operator=(RxPdu_Motor_18 const &) = default; // default copy assignment
   RxPdu_Motor_18 & operator=(RxPdu_Motor_18 &&) = default; // default move assignment

   PduStatus getPduStatus() const noexcept;

   std::uint32_t get_MO_EPCL() const noexcept; // 3 bits

   // --   END: public API for target code


   // -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING
public:
   void FOR_TESTING_setPduStatus(PduStatus status) noexcept;

   void FOR_TESTING_set_MO_EPCL(std::uint32_t) noexcept; // 3 bits
#endif // VWG_SID_CLIENT_TESTING

   // --   END: public API for testing & mocking purposes only


   // -- BEGIN: private API for internal use only

   void PRIVATE_setPduStatus(PduStatus status) noexcept;

   void PRIVATE_set_MO_EPCL(std::uint32_t) noexcept; // 3 bits

private:
   PduStatus status = PduStatus::kNotValid;
   std::uint32_t MO_EPCL_value;

   // --   END: private API for internal use only
};

class RxPdu_HVK_01 final {

   // -- BEGIN: public API for target code

public:
   RxPdu_HVK_01() = default; // default ctor
   ~RxPdu_HVK_01() = default; // default dtor
   RxPdu_HVK_01(RxPdu_HVK_01 const &) = default; // default copy ctor
   RxPdu_HVK_01(RxPdu_HVK_01 &&) = default; // default move ctor
   RxPdu_HVK_01 & operator=(RxPdu_HVK_01 const &) = default; // default copy assignment
   RxPdu_HVK_01 & operator=(RxPdu_HVK_01 &&) = default; // default move assignment

   PduStatus getPduStatus() const noexcept;

   std::uint32_t get_HVK_HV_Netz_Warnungen() const noexcept; // 2 bits

   // --   END: public API for target code


   // -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING
public:
   void FOR_TESTING_setPduStatus(PduStatus status) noexcept;

   void FOR_TESTING_set_HVK_HV_Netz_Warnungen(std::uint32_t) noexcept; // 2 bits
#endif // VWG_SID_CLIENT_TESTING

   // --   END: public API for testing & mocking purposes only


   // -- BEGIN: private API for internal use only

   void PRIVATE_setPduStatus(PduStatus status) noexcept;

   void PRIVATE_set_HVK_HV_Netz_Warnungen(std::uint32_t) noexcept; // 2 bits

private:
   PduStatus status = PduStatus::kNotValid;
   std::uint32_t HVK_HV_Netz_Warnungen_value;

   // --   END: private API for internal use only
};

class RxPdu_Daempfer_01 final {

   // -- BEGIN: public API for target code

public:
   RxPdu_Daempfer_01() = default; // default ctor
   ~RxPdu_Daempfer_01() = default; // default dtor
   RxPdu_Daempfer_01(RxPdu_Daempfer_01 const &) = default; // default copy ctor
   RxPdu_Daempfer_01(RxPdu_Daempfer_01 &&) = default; // default move ctor
   RxPdu_Daempfer_01 & operator=(RxPdu_Daempfer_01 const &) = default; // default copy assignment
   RxPdu_Daempfer_01 & operator=(RxPdu_Daempfer_01 &&) = default; // default move assignment

   PduStatus getPduStatus() const noexcept;

   std::uint32_t get_DR_Gelbe_Warnlampe() const noexcept; // 2 bits

   // --   END: public API for target code


   // -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING
public:
   void FOR_TESTING_setPduStatus(PduStatus status) noexcept;

   void FOR_TESTING_set_DR_Gelbe_Warnlampe(std::uint32_t) noexcept; // 2 bits
#endif // VWG_SID_CLIENT_TESTING

   // --   END: public API for testing & mocking purposes only


   // -- BEGIN: private API for internal use only

   void PRIVATE_setPduStatus(PduStatus status) noexcept;

   void PRIVATE_set_DR_Gelbe_Warnlampe(std::uint32_t) noexcept; // 2 bits

private:
   PduStatus status = PduStatus::kNotValid;
   std::uint32_t DR_Gelbe_Warnlampe_value;

   // --   END: private API for internal use only
};

class RxPdu_ESP_30 final {

   // -- BEGIN: public API for target code

public:
   RxPdu_ESP_30() = default; // default ctor
   ~RxPdu_ESP_30() = default; // default dtor
   RxPdu_ESP_30(RxPdu_ESP_30 const &) = default; // default copy ctor
   RxPdu_ESP_30(RxPdu_ESP_30 &&) = default; // default move ctor
   RxPdu_ESP_30 & operator=(RxPdu_ESP_30 const &) = default; // default copy assignment
   RxPdu_ESP_30 & operator=(RxPdu_ESP_30 &&) = default; // default move assignment

   PduStatus getPduStatus() const noexcept;

   std::uint32_t get_RLE_Anzeigen() const noexcept; // 3 bits

   // --   END: public API for target code


   // -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING
public:
   void FOR_TESTING_setPduStatus(PduStatus status) noexcept;

   void FOR_TESTING_set_RLE_Anzeigen(std::uint32_t) noexcept; // 3 bits
#endif // VWG_SID_CLIENT_TESTING

   // --   END: public API for testing & mocking purposes only


   // -- BEGIN: private API for internal use only

   void PRIVATE_setPduStatus(PduStatus status) noexcept;

   void PRIVATE_set_RLE_Anzeigen(std::uint32_t) noexcept; // 3 bits

private:
   PduStatus status = PduStatus::kNotValid;
   std::uint32_t RLE_Anzeigen_value;

   // --   END: private API for internal use only
};

class RxPdu_Motor_41 final {

   // -- BEGIN: public API for target code

public:
   RxPdu_Motor_41() = default; // default ctor
   ~RxPdu_Motor_41() = default; // default dtor
   RxPdu_Motor_41(RxPdu_Motor_41 const &) = default; // default copy ctor
   RxPdu_Motor_41(RxPdu_Motor_41 &&) = default; // default move ctor
   RxPdu_Motor_41 & operator=(RxPdu_Motor_41 const &) = default; // default copy assignment
   RxPdu_Motor_41 & operator=(RxPdu_Motor_41 &&) = default; // default move assignment

   PduStatus getPduStatus() const noexcept;

   std::uint32_t get_FDR_Warnung_ALR() const noexcept; // 2 bits
   std::uint32_t get_MO_EM_Ueberhitzungswarnung() const noexcept; // 2 bits

   // --   END: public API for target code


   // -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING
public:
   void FOR_TESTING_setPduStatus(PduStatus status) noexcept;

   void FOR_TESTING_set_FDR_Warnung_ALR(std::uint32_t) noexcept; // 2 bits
   void FOR_TESTING_set_MO_EM_Ueberhitzungswarnung(std::uint32_t) noexcept; // 2 bits
#endif // VWG_SID_CLIENT_TESTING

   // --   END: public API for testing & mocking purposes only


   // -- BEGIN: private API for internal use only

   void PRIVATE_setPduStatus(PduStatus status) noexcept;

   void PRIVATE_set_FDR_Warnung_ALR(std::uint32_t) noexcept; // 2 bits
   void PRIVATE_set_MO_EM_Ueberhitzungswarnung(std::uint32_t) noexcept; // 2 bits

private:
   PduStatus status = PduStatus::kNotValid;
   std::uint32_t FDR_Warnung_ALR_value;
   std::uint32_t MO_EM_Ueberhitzungswarnung_value;

   // --   END: private API for internal use only
};

class RxPdu_RKA_01 final {

   // -- BEGIN: public API for target code

public:
   RxPdu_RKA_01() = default; // default ctor
   ~RxPdu_RKA_01() = default; // default dtor
   RxPdu_RKA_01(RxPdu_RKA_01 const &) = default; // default copy ctor
   RxPdu_RKA_01(RxPdu_RKA_01 &&) = default; // default move ctor
   RxPdu_RKA_01 & operator=(RxPdu_RKA_01 const &) = default; // default copy assignment
   RxPdu_RKA_01 & operator=(RxPdu_RKA_01 &&) = default; // default move assignment

   PduStatus getPduStatus() const noexcept;

   bool get_RKA_FMVSS138_Lampe() const noexcept; // 1 bit
   std::uint32_t get_RKA_Warnungen_02() const noexcept; // 5 bits

   // --   END: public API for target code


   // -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING
public:
   void FOR_TESTING_setPduStatus(PduStatus status) noexcept;

   void FOR_TESTING_set_RKA_FMVSS138_Lampe(bool) noexcept; // 1 bit
   void FOR_TESTING_set_RKA_Warnungen_02(std::uint32_t) noexcept; // 5 bits
#endif // VWG_SID_CLIENT_TESTING

   // --   END: public API for testing & mocking purposes only


   // -- BEGIN: private API for internal use only

   void PRIVATE_setPduStatus(PduStatus status) noexcept;

   void PRIVATE_set_RKA_FMVSS138_Lampe(bool) noexcept; // 1 bit
   void PRIVATE_set_RKA_Warnungen_02(std::uint32_t) noexcept; // 5 bits

private:
   PduStatus status = PduStatus::kNotValid;
   bool RKA_FMVSS138_Lampe_value;
   std::uint32_t RKA_Warnungen_02_value;

   // --   END: private API for internal use only
};

class RxPdu_ESC_50 final {

   // -- BEGIN: public API for target code

public:
   RxPdu_ESC_50() = default; // default ctor
   ~RxPdu_ESC_50() = default; // default dtor
   RxPdu_ESC_50(RxPdu_ESC_50 const &) = default; // default copy ctor
   RxPdu_ESC_50(RxPdu_ESC_50 &&) = default; // default move ctor
   RxPdu_ESC_50 & operator=(RxPdu_ESC_50 const &) = default; // default copy assignment
   RxPdu_ESC_50 & operator=(RxPdu_ESC_50 &&) = default; // default move assignment

   PduStatus getPduStatus() const noexcept;

   std::uint32_t get_ESP_Laengsbeschl() const noexcept; // 10 bits
   bool get_ESP_QBit_Laengsbeschl() const noexcept; // 1 bit
   std::uint32_t get_ESP_Querbeschleunigung() const noexcept; // 8 bits
   bool get_ESP_QBit_Querb() const noexcept; // 1 bit
   std::uint32_t get_ESP_Gierrate() const noexcept; // 14 bits
   bool get_ESP_VZ_Gierrate() const noexcept; // 1 bit
   bool get_ESP_QBit_Gierrate() const noexcept; // 1 bit

   // --   END: public API for target code


   // -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING
public:
   void FOR_TESTING_setPduStatus(PduStatus status) noexcept;

   void FOR_TESTING_set_ESP_Laengsbeschl(std::uint32_t) noexcept; // 10 bits
   void FOR_TESTING_set_ESP_QBit_Laengsbeschl(bool) noexcept; // 1 bit
   void FOR_TESTING_set_ESP_Querbeschleunigung(std::uint32_t) noexcept; // 8 bits
   void FOR_TESTING_set_ESP_QBit_Querb(bool) noexcept; // 1 bit
   void FOR_TESTING_set_ESP_Gierrate(std::uint32_t) noexcept; // 14 bits
   void FOR_TESTING_set_ESP_VZ_Gierrate(bool) noexcept; // 1 bit
   void FOR_TESTING_set_ESP_QBit_Gierrate(bool) noexcept; // 1 bit
#endif // VWG_SID_CLIENT_TESTING

   // --   END: public API for testing & mocking purposes only


   // -- BEGIN: private API for internal use only

   void PRIVATE_setPduStatus(PduStatus status) noexcept;

   void PRIVATE_set_ESP_Laengsbeschl(std::uint32_t) noexcept; // 10 bits
   void PRIVATE_set_ESP_QBit_Laengsbeschl(bool) noexcept; // 1 bit
   void PRIVATE_set_ESP_Querbeschleunigung(std::uint32_t) noexcept; // 8 bits
   void PRIVATE_set_ESP_QBit_Querb(bool) noexcept; // 1 bit
   void PRIVATE_set_ESP_Gierrate(std::uint32_t) noexcept; // 14 bits
   void PRIVATE_set_ESP_VZ_Gierrate(bool) noexcept; // 1 bit
   void PRIVATE_set_ESP_QBit_Gierrate(bool) noexcept; // 1 bit

private:
   PduStatus status = PduStatus::kNotValid;
   std::uint32_t ESP_Laengsbeschl_value;
   bool ESP_QBit_Laengsbeschl_value;
   std::uint32_t ESP_Querbeschleunigung_value;
   bool ESP_QBit_Querb_value;
   std::uint32_t ESP_Gierrate_value;
   bool ESP_VZ_Gierrate_value;
   bool ESP_QBit_Gierrate_value;

   // --   END: private API for internal use only
};

class RxPdu_POS_GNSS_DR_01 final {

   // -- BEGIN: public API for target code

public:
   RxPdu_POS_GNSS_DR_01() = default; // default ctor
   ~RxPdu_POS_GNSS_DR_01() = default; // default dtor
   RxPdu_POS_GNSS_DR_01(RxPdu_POS_GNSS_DR_01 const &) = default; // default copy ctor
   RxPdu_POS_GNSS_DR_01(RxPdu_POS_GNSS_DR_01 &&) = default; // default move ctor
   RxPdu_POS_GNSS_DR_01 & operator=(RxPdu_POS_GNSS_DR_01 const &) = default; // default copy assignment
   RxPdu_POS_GNSS_DR_01 & operator=(RxPdu_POS_GNSS_DR_01 &&) = default; // default move assignment

   PduStatus getPduStatus() const noexcept;

   std::uint64_t get_POS_GNSS_DR_Breite_Ortung() const noexcept; // 35 bits
   std::uint64_t get_POS_GNSS_DR_Laenge_Ortung() const noexcept; // 36 bits
   std::uint32_t get_POS_GNSS_DR_Ausrichtung_Geschw() const noexcept; // 12 bits
   std::uint32_t get_POS_GNSS_DR_Guete_Ausricht_Gesch() const noexcept; // 11 bits
   std::uint32_t get_POS_GNSS_DR_Guete_E_GrH_Ausr() const noexcept; // 12 bits
   std::uint32_t get_POS_GNSS_DR_Guete_E_GrHalbachse() const noexcept; // 15 bits
   std::uint32_t get_POS_GNSS_DR_Guete_E_KlHalbachse() const noexcept; // 15 bits

   // --   END: public API for target code


   // -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING
public:
   void FOR_TESTING_setPduStatus(PduStatus status) noexcept;

   void FOR_TESTING_set_POS_GNSS_DR_Breite_Ortung(std::uint64_t) noexcept; // 35 bits
   void FOR_TESTING_set_POS_GNSS_DR_Laenge_Ortung(std::uint64_t) noexcept; // 36 bits
   void FOR_TESTING_set_POS_GNSS_DR_Ausrichtung_Geschw(std::uint32_t) noexcept; // 12 bits
   void FOR_TESTING_set_POS_GNSS_DR_Guete_Ausricht_Gesch(std::uint32_t) noexcept; // 11 bits
   void FOR_TESTING_set_POS_GNSS_DR_Guete_E_GrH_Ausr(std::uint32_t) noexcept; // 12 bits
   void FOR_TESTING_set_POS_GNSS_DR_Guete_E_GrHalbachse(std::uint32_t) noexcept; // 15 bits
   void FOR_TESTING_set_POS_GNSS_DR_Guete_E_KlHalbachse(std::uint32_t) noexcept; // 15 bits
#endif // VWG_SID_CLIENT_TESTING

   // --   END: public API for testing & mocking purposes only


   // -- BEGIN: private API for internal use only

   void PRIVATE_setPduStatus(PduStatus status) noexcept;

   void PRIVATE_set_POS_GNSS_DR_Breite_Ortung(std::uint64_t) noexcept; // 35 bits
   void PRIVATE_set_POS_GNSS_DR_Laenge_Ortung(std::uint64_t) noexcept; // 36 bits
   void PRIVATE_set_POS_GNSS_DR_Ausrichtung_Geschw(std::uint32_t) noexcept; // 12 bits
   void PRIVATE_set_POS_GNSS_DR_Guete_Ausricht_Gesch(std::uint32_t) noexcept; // 11 bits
   void PRIVATE_set_POS_GNSS_DR_Guete_E_GrH_Ausr(std::uint32_t) noexcept; // 12 bits
   void PRIVATE_set_POS_GNSS_DR_Guete_E_GrHalbachse(std::uint32_t) noexcept; // 15 bits
   void PRIVATE_set_POS_GNSS_DR_Guete_E_KlHalbachse(std::uint32_t) noexcept; // 15 bits

private:
   PduStatus status = PduStatus::kNotValid;
   std::uint64_t POS_GNSS_DR_Breite_Ortung_value;
   std::uint64_t POS_GNSS_DR_Laenge_Ortung_value;
   std::uint32_t POS_GNSS_DR_Ausrichtung_Geschw_value;
   std::uint32_t POS_GNSS_DR_Guete_Ausricht_Gesch_value;
   std::uint32_t POS_GNSS_DR_Guete_E_GrH_Ausr_value;
   std::uint32_t POS_GNSS_DR_Guete_E_GrHalbachse_value;
   std::uint32_t POS_GNSS_DR_Guete_E_KlHalbachse_value;

   // --   END: private API for internal use only
};

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
   bool get_PSD_wahrscheinlichster_Pfad() const noexcept; // 1 bit
   bool get_PSD_Geradester_Pfad() const noexcept; // 1 bit
   bool get_PSD_Segment_Komplett() const noexcept; // 1 bit
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
   void FOR_TESTING_set_PSD_wahrscheinlichster_Pfad(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Geradester_Pfad(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Segment_Komplett(bool) noexcept; // 1 bit
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
   void PRIVATE_set_PSD_wahrscheinlichster_Pfad(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Geradester_Pfad(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Segment_Komplett(bool) noexcept; // 1 bit
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
   bool PSD_wahrscheinlichster_Pfad_value;
   bool PSD_Geradester_Pfad_value;
   bool PSD_Segment_Komplett_value;
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
   bool get_PSD_Pos_Standort_Eindeutig() const noexcept; // 1 bit
   std::uint32_t get_PSD_Pos_Fehler_Laengsrichtung() const noexcept; // 3 bits
   std::uint32_t get_PSD_Attribut_1_ID() const noexcept; // 5 bits
   std::uint32_t get_PSD_Attribut_1_Wert() const noexcept; // 4 bits
   std::uint32_t get_PSD_Attribut_2_ID() const noexcept; // 5 bits
   std::uint32_t get_PSD_Attribut_2_Wert() const noexcept; // 4 bits

   // --   END: public API for target code


   // -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING
public:
   void FOR_TESTING_setPduStatus(PduStatus status) noexcept;

   void FOR_TESTING_set_PSD_Pos_Segment_ID(std::uint32_t) noexcept; // 6 bits
   void FOR_TESTING_set_PSD_Pos_Segmentlaenge(std::uint32_t) noexcept; // 7 bits
   void FOR_TESTING_set_PSD_Pos_Standort_Eindeutig(bool) noexcept; // 1 bit
   void FOR_TESTING_set_PSD_Pos_Fehler_Laengsrichtung(std::uint32_t) noexcept; // 3 bits
   void FOR_TESTING_set_PSD_Attribut_1_ID(std::uint32_t) noexcept; // 5 bits
   void FOR_TESTING_set_PSD_Attribut_1_Wert(std::uint32_t) noexcept; // 4 bits
   void FOR_TESTING_set_PSD_Attribut_2_ID(std::uint32_t) noexcept; // 5 bits
   void FOR_TESTING_set_PSD_Attribut_2_Wert(std::uint32_t) noexcept; // 4 bits
#endif // VWG_SID_CLIENT_TESTING

   // --   END: public API for testing & mocking purposes only


   // -- BEGIN: private API for internal use only

   void PRIVATE_setPduStatus(PduStatus status) noexcept;

   void PRIVATE_set_PSD_Pos_Segment_ID(std::uint32_t) noexcept; // 6 bits
   void PRIVATE_set_PSD_Pos_Segmentlaenge(std::uint32_t) noexcept; // 7 bits
   void PRIVATE_set_PSD_Pos_Standort_Eindeutig(bool) noexcept; // 1 bit
   void PRIVATE_set_PSD_Pos_Fehler_Laengsrichtung(std::uint32_t) noexcept; // 3 bits
   void PRIVATE_set_PSD_Attribut_1_ID(std::uint32_t) noexcept; // 5 bits
   void PRIVATE_set_PSD_Attribut_1_Wert(std::uint32_t) noexcept; // 4 bits
   void PRIVATE_set_PSD_Attribut_2_ID(std::uint32_t) noexcept; // 5 bits
   void PRIVATE_set_PSD_Attribut_2_Wert(std::uint32_t) noexcept; // 4 bits

private:
   PduStatus status = PduStatus::kNotValid;
   std::uint32_t PSD_Pos_Segment_ID_value;
   std::uint32_t PSD_Pos_Segmentlaenge_value;
   bool PSD_Pos_Standort_Eindeutig_value;
   std::uint32_t PSD_Pos_Fehler_Laengsrichtung_value;
   std::uint32_t PSD_Attribut_1_ID_value;
   std::uint32_t PSD_Attribut_1_Wert_value;
   std::uint32_t PSD_Attribut_2_ID_value;
   std::uint32_t PSD_Attribut_2_Wert_value;

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

   std::uint32_t get_PSD_Attribut_Segment_ID() const noexcept; // 6 bits
   std::uint32_t get_PSD_Attribut_3_ID() const noexcept; // 5 bits
   std::uint32_t get_PSD_Attribut_3_Wert() const noexcept; // 4 bits
   std::uint32_t get_PSD_Attribut_4_ID() const noexcept; // 5 bits
   std::uint32_t get_PSD_Attribut_4_Wert() const noexcept; // 4 bits
   std::uint32_t get_PSD_Attribut_5_ID() const noexcept; // 5 bits
   std::uint32_t get_PSD_Attribut_5_Wert() const noexcept; // 4 bits

   // --   END: public API for target code


   // -- BEGIN: public API for testing & mocking purposes only

#ifdef VWG_SID_CLIENT_TESTING
public:
   void FOR_TESTING_setPduStatus(PduStatus status) noexcept;

   void FOR_TESTING_set_PSD_Attribut_Segment_ID(std::uint32_t) noexcept; // 6 bits
   void FOR_TESTING_set_PSD_Attribut_3_ID(std::uint32_t) noexcept; // 5 bits
   void FOR_TESTING_set_PSD_Attribut_3_Wert(std::uint32_t) noexcept; // 4 bits
   void FOR_TESTING_set_PSD_Attribut_4_ID(std::uint32_t) noexcept; // 5 bits
   void FOR_TESTING_set_PSD_Attribut_4_Wert(std::uint32_t) noexcept; // 4 bits
   void FOR_TESTING_set_PSD_Attribut_5_ID(std::uint32_t) noexcept; // 5 bits
   void FOR_TESTING_set_PSD_Attribut_5_Wert(std::uint32_t) noexcept; // 4 bits
#endif // VWG_SID_CLIENT_TESTING

   // --   END: public API for testing & mocking purposes only


   // -- BEGIN: private API for internal use only

   void PRIVATE_setPduStatus(PduStatus status) noexcept;

   void PRIVATE_set_PSD_Attribut_Segment_ID(std::uint32_t) noexcept; // 6 bits
   void PRIVATE_set_PSD_Attribut_3_ID(std::uint32_t) noexcept; // 5 bits
   void PRIVATE_set_PSD_Attribut_3_Wert(std::uint32_t) noexcept; // 4 bits
   void PRIVATE_set_PSD_Attribut_4_ID(std::uint32_t) noexcept; // 5 bits
   void PRIVATE_set_PSD_Attribut_4_Wert(std::uint32_t) noexcept; // 4 bits
   void PRIVATE_set_PSD_Attribut_5_ID(std::uint32_t) noexcept; // 5 bits
   void PRIVATE_set_PSD_Attribut_5_Wert(std::uint32_t) noexcept; // 4 bits

private:
   PduStatus status = PduStatus::kNotValid;
   std::uint32_t PSD_Attribut_Segment_ID_value;
   std::uint32_t PSD_Attribut_3_ID_value;
   std::uint32_t PSD_Attribut_3_Wert_value;
   std::uint32_t PSD_Attribut_4_ID_value;
   std::uint32_t PSD_Attribut_4_Wert_value;
   std::uint32_t PSD_Attribut_5_ID_value;
   std::uint32_t PSD_Attribut_5_Wert_value;

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

   virtual void receivedPdu_Blinkmodi_02 (RxPdu_Blinkmodi_02 const &) = 0;
   virtual void receivedPdu_ESP_21 (RxPdu_ESP_21 const &) = 0;
   virtual void receivedPdu_ESP_24 (RxPdu_ESP_24 const &) = 0;
   virtual void receivedPdu_Airbag_01 (RxPdu_Airbag_01 const &) = 0;
   virtual void receivedPdu_Motor_18 (RxPdu_Motor_18 const &) = 0;
   virtual void receivedPdu_HVK_01 (RxPdu_HVK_01 const &) = 0;
   virtual void receivedPdu_Daempfer_01 (RxPdu_Daempfer_01 const &) = 0;
   virtual void receivedPdu_ESP_30 (RxPdu_ESP_30 const &) = 0;
   virtual void receivedPdu_Motor_41 (RxPdu_Motor_41 const &) = 0;
   virtual void receivedPdu_RKA_01 (RxPdu_RKA_01 const &) = 0;
   virtual void receivedPdu_ESC_50 (RxPdu_ESC_50 const &) = 0;
   virtual void receivedPdu_POS_GNSS_DR_01 (RxPdu_POS_GNSS_DR_01 const &) = 0;
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
 * vwg::sid::LHWApp::ISignalDataAccessHandler.
 */
ISignalDataAccessHandler & getSignalDataAccessHandler();

[[deprecated]]
inline std::unique_ptr<ISignalDataAccessHandler> createSignalDataAccessHandler() {
   return std::unique_ptr<ISignalDataAccessHandler>(&getSignalDataAccessHandler());
}

} /* namespace LHWApp */
} /* namespace sid */
} /* namespace vwg */

#endif // VWG_SID_LHWAPP_SIGNAL_DATA_ACCESS_HPP_
