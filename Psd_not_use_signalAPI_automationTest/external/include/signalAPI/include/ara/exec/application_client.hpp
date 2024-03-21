/**
 * @brief System-API execution management class ApplicationClient
 *
 * @file ara/exec/application_client.hpp
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
 * R17-10 SWS_EM refers to the Autosar software specification for execution
 * management from the Autosar release 17-10.
 *
 * R17-10 SWS_AP refers to the Autosar General Specification of Adaptive
 * Platform from the Autosar release 17-10.
 */

#ifndef ARA_EXEC_APPLICATION_CLIENT_HPP_
#define ARA_EXEC_APPLICATION_CLIENT_HPP_

/*
 * The following standard library header files are included to make this
 * System-API header file self-contained.  Their inclusion, however, is not
 * part of the System-API.  That is, client code can assume the System-API
 * header files to be self-contained, but client code that makes use of
 * declarations from standard header files shall include these files itself.
 */

#include <cstdint> // Fixed width integer types
#include <memory>  // unique_ptr

/*
 * The use of the namespace ara::exec is not described in R17-10 SWS_EM, but
 * the namespace appears in SWS_AP_00001.  For this reason and for backwards
 * compatibility with existing E3-1.1 code, the System-API specifies that
 * execution management declarations are added to ara::exec.
 */

namespace ara
{
namespace exec
{

    /**
     * \brief R17-10 SWS_EM_02000
     */
    enum class ApplicationState : std::uint8_t
    {
        kRunning                    = 0,
        kTerminating [[deprecated]] = 1
    };

    /**
     * \brief R17-10 SWS_EM_02070
     */
    enum class ApplicationReturnType : std::uint8_t
    {
        kSuccess      = 0,
        kGeneralError = 1
    };

    /**
     * \brief R17-10 SWS_EM_02030
     */
    class ApplicationClient
    {
    public:
        /**
         * \brief R17-10 SWS_EM_02030.  Autosar leaves it to the implementation
         * whether the constructor can throw an exception or not.  Note to
         * implementors: Be aware that client code will likely not be prepared to
         * catch and handle an exception thrown by the constructor, which means
         * that an exception will likely lead to the termination of the process.
         */
        ApplicationClient() noexcept(false);

        /**
         * \brief R17-10 SWS_EM_02002
         */
        ~ApplicationClient();

        /*
         * Deleted according to R17-10 SWS_EM_02071
         */
        ApplicationClient(ApplicationClient const&) = delete;
        ApplicationClient(ApplicationClient&&)      = delete;
        ApplicationClient& operator=(ApplicationClient const&) = delete;
        ApplicationClient& operator=(ApplicationClient&&) = delete;

        /**
         * \brief R17-10 SWS_EM_02003
         */
        ApplicationReturnType ReportApplicationState(ApplicationState state) noexcept;

    private:
        class ApplicationClientImpl;
        std::unique_ptr<ApplicationClientImpl> pImpl;
    };

} /* namespace exec */
} /* namespace ara */

#endif /* ARA_EXEC_APPLICATION_CLIENT_HPP_ */
