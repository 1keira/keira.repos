/**
 * @brief Main System-API header for logging
 *
 * @file ara/log/logging.hpp
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

/*
 * R17-10 SWS_LOG does not describe a header file logging.hpp.  For backwards
 * compatibility with existing E3-1.1 code, however, the System-API specifies
 * that a header file logging.hpp has to be provided and shall contain the
 * declarations as given in this file (except where comments indicate
 * something different).
 */

#ifndef ARA_LOG_LOGGING_HPP_
#define ARA_LOG_LOGGING_HPP_

/*
 * Note that logging.hpp includes logger.hpp, which from a technical
 * perspective is not necessary: A forward declaration of class Logger would
 * be sufficient.  For backwards compatibility with existing E3-1.1 code,
 * however, the System-API specifies that logging.hpp shall include also
 * logger.hpp.
 */

#include "logcommon.hpp" // Loglevel, LogMode
#include "logger.hpp"    // Logger
#include "logstream.hpp" // LogStream, LogRawBuffer, LogHex<n>, LogBin<n>

/*
 * The following standard library header files are included to make this
 * System-API header file self-contained.  Their inclusion, however, is not
 * part of the System-API.  That is, client code can assume the System-API
 * header files to be self-contained, but client code that makes use of
 * declarations from standard header files shall include these files itself.
 */

#include <cstdint> // Fixed width integer types
#include <string>  // string

/*
 * The use of the namespace ara::log is not described in R17-10 SWS_LOG.  For
 * backwards compatibility with existing E3-1.1 code, however, the System-API
 * specifies that logging declarations are added to ara::log.
 */

namespace eso_ara_log_backport
{

/**
 * \brief The System-API specification differs from R17-10 SWS_LOG_00004 in
 * the following way: The logMode and directoryPath arguments are only
 * necessary for backwards compatibility.  Application code shall always use
 * kRemote as log mode.  The directoryPath will be ignored.  For more details,
 * see the documentation for the enum LogMode.
 *
 * The System-API specification refines R17-10 SWS_LOG_00004 in the following
 * way: The directory path for the log mode kFile is optional according to
 * SWS_LOG_00004.  This is solved in the System-API by defining the
 * directoryPath to be a default parameter of function InitLogging.
 */
void InitLogging(std::string appId,
                 std::string appDescription,
                 LogLevel    appDefLogLevel,
                 LogMode     logMode,
                 std::string directoryPath = "") noexcept;

/**
 * \brief R17-10 SWS_LOG_00021.  The System-API specification extends the
 * Ausosar specification by granting that the creation of logger objects is
 * thread safe.
 */
Logger& CreateLogger(std::string ctxId, std::string ctxDescription) noexcept;

/**
 * \brief R17-10 SWS_LOG_00022
 */
LogHex8 HexFormat(std::uint8_t value) noexcept;

/**
 * \brief R17-10 SWS_LOG_00023
 */
LogHex8 HexFormat(std::int8_t value) noexcept;

/**
 * \brief R17-10 SWS_LOG_00024
 */
LogHex16 HexFormat(std::uint16_t value) noexcept;

/**
 * \brief R17-10 SWS_LOG_00025
 */
LogHex16 HexFormat(std::int16_t value) noexcept;

/**
 * \brief R17-10 SWS_LOG_00026
 */
LogHex32 HexFormat(std::uint32_t value) noexcept;

/**
 * \brief R17-10 SWS_LOG_00027
 */
LogHex32 HexFormat(std::int32_t value) noexcept;

/**
 * \brief R17-10 SWS_LOG_00028
 */
LogHex64 HexFormat(std::uint64_t value) noexcept;

/**
 * \brief R17-10 SWS_LOG_00029
 */
LogHex64 HexFormat(std::int64_t value) noexcept;

/**
 * \brief R17-10 SWS_LOG_00030
 */
LogBin8 BinFormat(std::uint8_t value) noexcept;

/**
 * \brief R17-10 SWS_LOG_00031
 */
LogBin8 BinFormat(std::int8_t value) noexcept;

/**
 * \brief R17-10 SWS_LOG_00032
 */
LogBin16 BinFormat(std::uint16_t value) noexcept;

/**
 * \brief R17-10 SWS_LOG_00033
 */
LogBin16 BinFormat(std::int16_t value) noexcept;

/**
 * \brief R17-10 SWS_LOG_00034
 */
LogBin32 BinFormat(std::uint32_t value) noexcept;

/**
 * \brief R17-10 SWS_LOG_00035
 */
LogBin32 BinFormat(std::int32_t value) noexcept;

/**
 * \brief R17-10 SWS_LOG_00036
 */
LogBin64 BinFormat(std::uint64_t value) noexcept;

/**
 * \brief R17-10 SWS_LOG_00037
 */
LogBin64 BinFormat(std::int64_t value) noexcept;

/*
 * R17-10 SWS_LOG_00038 specifies a template function RawBuffer to create
 * LogRawBuffer objects that are used to print out binary information.  The
 * creation and printing of LogRawBuffer objects is intentionally not made
 * part of the System-API, because R17-10 SWS_LOG leaves important aspects
 * unspecified, for example information about the life time of data in
 * LogRawBuffer objects, or, the use of RawBuffer with data types like
 * std::vector.
 */

/*
 * According to R17-10 SWS_LOG_00064 to SWS_LOG_00069, the following are
 * defined as methods of class Logger.  However, different pieces of example
 * code in R17-10 indicate that there are also the following corresponding
 * namespace-scoped functions.  These are also defined to be part of the
 * System-API.
 */

/**
 * \brief Added to the System-API in analogy to R17-10 SWS_LOG_00064.  The
 * System-API specification extends the Autosar specification by granting that
 * the call to this function is thread safe.
 */
LogStream LogFatal() noexcept;

/**
 * \brief Added to the System-API in analogy to R17-10 SWS_LOG_00065.  The
 * System-API specification extends the Autosar specification by granting that
 * the call to this function is thread safe.
 */
LogStream LogError() noexcept;

/**
 * \brief Added to the System-API in analogy to R17-10 SWS_LOG_00066.  The
 * System-API specification extends the Autosar specification by granting that
 * the call to this function is thread safe.
 */
LogStream LogWarn() noexcept;

/**
 * \brief Added to the System-API in analogy to R17-10 SWS_LOG_00067.  The
 * System-API specification extends the Autosar specification by granting that
 * the call to this function is thread safe.
 */
LogStream LogInfo() noexcept;

/**
 * \brief Added to the System-API in analogy to R17-10 SWS_LOG_00068.  The
 * System-API specification extends the Autosar specification by granting that
 * the call to this function is thread safe.
 */
LogStream LogDebug() noexcept;

/**
 * \brief Added to the System-API in analogy to R17-10 SWS_LOG_00069.  The
 * System-API specification extends the Autosar specification by granting that
 * the call to this function is thread safe.
 */
LogStream LogVerbose() noexcept;

/**
 * \brief R17-10 SWS_LOG_00070.  The System-API specification extends the
 * Autosar specification by granting that the call to this function is thread
 * safe.
 */
bool IsLogEnabled(LogLevel logLevel) noexcept;

} // namespace eso_ara_log_backport

#ifndef INCLUDED_BY_ESO
namespace ara
{
namespace log
{
    using eso_ara_log_backport::BinFormat;
    using eso_ara_log_backport::CreateLogger;
    using eso_ara_log_backport::HexFormat;
    using eso_ara_log_backport::InitLogging;
    using eso_ara_log_backport::LogDebug;
    using eso_ara_log_backport::LogError;
    using eso_ara_log_backport::LogFatal;
    using eso_ara_log_backport::LogInfo;
    using eso_ara_log_backport::LogVerbose;
    using eso_ara_log_backport::LogWarn;
} // namespace log
} // namespace ara
#endif

#endif /* ARA_LOG_LOGGING_HPP_ */
