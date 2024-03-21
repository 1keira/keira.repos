/**
 * @brief System-API header for class Logger
 *
 * @file ara/log/logger.hpp
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
 * R17-10 SWS_LOG does not describe a header file logstream.hpp.  For
 * backwards compatibility with existing E3-1.1 code, however, the System-API
 * specifies that a header file logstream.hpp has to be provided and shall
 * contain the declarations as given in this file (except where comments
 * indicate something different).
 */

#ifndef ARA_LOG_LOGGER_HPP_
#define ARA_LOG_LOGGER_HPP_

#include "logcommon.hpp" // LogLevel
#include "logstream.hpp" // LogStream

/*
 * The following standard library header files are needed by the mocking
 * support that is part of this header file, but which is not defined to be
 * part of the System-API.
 */

#include <memory> // unique_ptr
#include <string> // string

/*
 * The use of the namespace ara::log is not described in R17-10 SWS_LOG.  For
 * backwards compatibility with existing E3-1.1 code, however, the System-API
 * specifies that logging declarations are added to ara::log.
 */

namespace eso_ara_log_backport
{

class Logger final
{
public:
    /*
     * In R17-10 SWS_LOG nothing is mentioned about constructors for Logger or
     * its destructor.  Client code is expected to use createLogger to obtain
     * Logger instances.  And, according to R17-10 SWS_LOG_00005, management
     * of logger objects is the responsibility of the logging framework.
     * Therefore, the System-API does not specify any constructors for Logger,
     * but leaves this open for the implementation.  To clarify that client
     * code is not expected to create and delete Logger objects directly, the
     * destructor is declared private in this header file.  However, it is not
     * a requirement on implementations that the destructor has to be private
     * or that there has to be a destructor at all.
     */

    /*
     * Since according to R17-10 SWS_LOG_00005 management of logger objects is
     * the responsibility of the logging framework, and, for backwards
     * compatibility with E3-1.1 software, the System-API specifies the
     * special member functions to be deleted.
     */
    Logger()              = delete;
    ~Logger()             = default;
    Logger(Logger const&) = delete;
    Logger& operator=(Logger const&) = delete;
    Logger(Logger&&)                 = delete;
    Logger& operator=(Logger&&) = delete;

    /**
     * \brief R17-10 SWS_LOG_00064.  The System-API specification extends the
     * Autosar specification by granting that the call to this method is
     * thread safe.
     */
    LogStream LogFatal() noexcept;

    /**
     * \brief R17-10 SWS_LOG_00065.  The System-API specification extends the
     * Autosar specification by granting that the call to this method is
     * thread safe.
     */
    LogStream LogError() noexcept;

    /**
     * \brief R17-10 SWS_LOG_00066.  The System-API specification extends the
     * Autosar specification by granting that the call to this method is
     * thread safe.
     */
    LogStream LogWarn() noexcept;

    /**
     * \brief R17-10 SWS_LOG_00067.  The System-API specification extends the
     * Autosar specification by granting that the call to this method is
     * thread safe.
     */
    LogStream LogInfo() noexcept;

    /**
     * \brief R17-10 SWS_LOG_00068.  The System-API specification extends the
     * Autosar specification by granting that the call to this method is
     * thread safe.
     */
    LogStream LogDebug() noexcept;

    /**
     * \brief R17-10 SWS_LOG_00069.  The System-API specification extends the
     * Autosar specification by granting that the call to this method is
     * thread safe.
     */
    LogStream LogVerbose() noexcept;

    /**
     * \brief R17-10 SWS_LOG_00070.  The System-API specification extends the
     * Autosar specification by granting that the call to this method is
     * thread safe.
     */
    bool IsLogEnabled(LogLevel logLevel) noexcept;

    /*
     * The following private section is only here for mocking support.  It is not
     * part of the System-API - other implementations of the System-API can look
     * completely different.
     */

private:
    friend Logger& CreateLogger(std::string ctxId, std::string ctxDescription) noexcept;
    friend LogStream::LogStream(LogLevel logLevel, Logger const& logger) noexcept;

    Logger(std::string const& ctxId, std::string const& ctxDescription) noexcept;

    class LoggerImpl;
    std::unique_ptr<LoggerImpl> pImpl;
};

} // namespace eso_ara_log_backport

#ifndef INCLUDED_BY_ESO
namespace ara
{
namespace log
{
    using eso_ara_log_backport::Logger;
} // namespace log
} // namespace ara
#endif

#endif /* ARA_LOG_LOGGER_HPP_ */
