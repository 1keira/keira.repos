/**
 * @brief Common System-API definitions for logging
 *
 * @file ara/log/logcommon.hpp
 *
 * (c) 2021, 2022, 2023 CARIAD SE, All rights reserved.
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

/*
 * R17-10 SWS_LOG refers to the Autosar software specification for logging
 * from the Autosar release 17-10.
 */

#ifndef ARA_LOG_LOGCOMMON_HPP_
#define ARA_LOG_LOGCOMMON_HPP_

/*
 * The following standard library header files are included to make this
 * System-API header file self-contained.  Their inclusion, however, is not
 * part of the System-API.  That is, client code can assume the System-API
 * header files to be self-contained, but client code that makes use of
 * declarations from standard header files shall include these files itself.
 */

#include <cstdint>     // Fixed width integer types
#include <type_traits> // underlying_type

/*
 * The use of the namespace ara::log is not described in R17-10 SWS_LOG.  For
 * backwards compatibility with existing E3-1.1 code, however, the System-API
 * specifies that logging declarations are added to ara::log.
 */

namespace eso_ara_log_backport
{

/**
 * \brief R17-10 SWS_LOG_00018
 */
enum class LogLevel : std::uint8_t
{
    kOff,
    kFatal,
    kError,
    kWarn,
    kInfo,
    kDebug,
    kVerbose
};

/**
 * \brief According to R17-10 SWS_LOG_00019, application code shall have the
 * option to choose from multiple log modes.  The System-API, in contrast,
 * does not allow applications to choose any other log mode than kRemote.
 * Note that this restriction only applies to the use of log modes from the
 * application code.  There will be other ways to configure the behaviour of
 * the logging framework.
 *
 * Application code shall always select kRemote as log mode, no more, no less.
 * The LogMode enum with its three individually selectable log modes is only
 * part of the api for backwards compatibility reasons.
 *
 * However, independent of which log modes the application actually requests,
 * the implementation shall always gracefully behave as if kRemote and only
 * kRemote was chosen.
 */
enum class LogMode : std::uint8_t
{
    kRemote  = 0x01,
    kFile    = 0x02, // not to be used by application code
    kConsole = 0x04  // not to be used by application code
};

/**
 * \brief According to R17-10 SWS_LOG_00019, an OR operator has to be
 * provided.  Details about its signature are left open.  (To be clarified:
 * Does the operator have to be constexpr for compatibility with existing
 * E3-1.1 code?)  For the System-API the signature is defined as follows:
 */
LogMode operator|(LogMode lhs, LogMode rhs) noexcept;

/**
 * \brief According to R17-10 SWS_LOG_00019, an AND operator has to be
 * provided.  Details about its signature are left open.  For the System-API
 * the signature is defined as follows:
 */
typename std::underlying_type<LogMode>::type operator&(LogMode lhs, LogMode rhs) noexcept;

} // namespace eso_ara_log_backport

#ifndef INCLUDED_BY_ESO
namespace ara
{
namespace log
{
    using eso_ara_log_backport::LogLevel;
    using eso_ara_log_backport::LogMode;
} // namespace log
} // namespace ara
#endif

#endif /* ARA_LOG_LOGCOMMON_HPP_ */
