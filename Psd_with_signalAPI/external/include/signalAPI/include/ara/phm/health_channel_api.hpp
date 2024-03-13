/**
 * @brief System-API header for deprecated class HealthChannel
 *
 * @file ara/phm/health_channel_api.hpp
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
 * R18-10 SWS_PHM does not describe a header file health_channel_api.hpp.  For
 * backwards compatibility with existing E3-1.1 code, however, the System-API
 * specifies that a header file health_channel_api.hpp has to be provided and
 * shall contain the declarations as given in this file (except where comments
 * indicate something different).
 */

#ifndef ARA_PHM_HEALTH_CHANNEL_API_HPP_
#define ARA_PHM_HEALTH_CHANNEL_API_HPP_

/**
 * \brief R18-10 SWS_PHM_01018
 */
namespace ara
{
namespace phm
{

    class Phm_client;

    /**
     * \brief Deprecated (see notes below): The template class specified by R18-10
     * SWS_PHM_01122 is not part of the System-API.  In the System-API, that
     * functionality is provided by the following non-template class.
     *
     * Note to developers of client code of the System-API: This class is only
     * provided for source code compatibility with existing E3-1.1 code.  In that
     * existing E3-1.1 code, however, the use of HealthChannel did not serve any
     * functional purpose, i.e. it was unnecessary.  Therefore, when writing new
     * code, don't use HealthChannel.
     *
     * Note to implementors of the System-API: Due to the abovementioned
     * functional irrelevance of class HealthChannel, a dummy (do-nothing)
     * implementation will be a valid implementation of this class.
     */
    class HealthChannel final
    {
    public:
        /**
         * \brief Deprecated (see notes on class HealthChannel): In the System-API
         * the following constructor provides the functionality of the constructor
         * specified by R18-10 SWS_PHM_00457.
         */
        explicit HealthChannel(Phm_client const& phm_client);
    };

} /* namespace phm */
} /* namespace ara */

#endif /* ARA_PHM_HEALTH_CHANNEL_API_HPP_ */
