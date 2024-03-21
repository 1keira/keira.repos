/**
 * @brief System-API header for class Phm_client
 *
 * @file ara/phm/phm_client.hpp
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
 * R18-10 SWS_PHM refers to the Autosar software specification for platform
 * health management from the Autosar release 18-10.
 */

/*
 * R18-10 SWS_PHM does not describe a header file phm_client.hpp.  For
 * backwards compatibility with existing E3-1.1 code, however, the System-API
 * specifies that a header file phm_client.hpp has to be provided and shall
 * contain the declarations as given in this file (except where comments
 * indicate something different).
 */

#ifndef ARA_PHM_PHM_CLIENT_HPP_
#define ARA_PHM_PHM_CLIENT_HPP_

/*
 * The following standard library header files are included to make this
 * System-API header file self-contained.  Their inclusion, however, is not
 * part of the System-API.  That is, client code can assume the System-API
 * header files to be self-contained, but client code that makes use of
 * declarations from standard header files shall include these files itself.
 */
#include <memory> // unique_ptr
#include <string> // string

/**
 * \brief R18-10 SWS_PHM_01018
 */
namespace ara
{
namespace phm
{

    /**
     * \brief In the System-API, for backwards compatibility with existing E3-1.1
     * code, Instance_id replaces/is equivalent to InstanceType specified by
     * R18-10 SWS_PHM_00321.
     */
    using Instance_id = std::string;

    /**
     * \brief In the System-API, for backwards compatibility with existing E3-1.1
     * code, Phm_client replaces the PHM class specified by R18-10 SWS_PHM_01010.
     */
    class Phm_client final
    {
    public:
        /**
         * \brief In the System-API, for backwards compatibility with existing
         * E3-1.1 code, the following constructor is provided instead of the
         * default constructor which is specified by R18-10 SWS_PHM_00458.
         */
        explicit Phm_client(Instance_id instance_id);

        ~Phm_client();

        const Instance_id& instanceId() const;

    private:
        class PhmClientImpl;
        std::unique_ptr<PhmClientImpl> pImpl;
    };

} /* namespace phm */
} /* namespace ara */

#endif /* ARA_PHM_PHM_CLIENT_HPP_ */
