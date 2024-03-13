/**
 * @brief System-API header for checkpoint monitoring
 *
 * @file ara/phm/supervision_entity_api.hpp
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
 * R18-10 SWS_PHM does not describe a header file supervision_entity_api.hpp.
 * For backwards compatibility with existing E3-1.1 code, however, the
 * System-API specifies that a header file supervision_entity_api.hpp has to
 * be provided and shall contain the declarations as given in this file
 * (except where comments indicate something different).
 */

#ifndef ARA_PHM_SUPERVISION_ENTITY_API_HPP_
#define ARA_PHM_SUPERVISION_ENTITY_API_HPP_

/*
 * The following standard library header files are included to make this
 * System-API header file self-contained.  Their inclusion, however, is not
 * part of the System-API.  That is, client code can assume the System-API
 * header files to be self-contained, but client code that makes use of
 * declarations from standard header files shall include these files itself.
 */
#include <cstdint> // Fixed width integer types
#include <memory>  // std::unique_ptr

/**
 * \brief R18-10 SWS_PHM_01018
 */
namespace ara
{
namespace phm
{

    /**
     * \brief In the System-API, for backwards compatibility with existing E3-1.1
     * code, Checkpoint_id is a replacement for the generated enum class
     * Checkpoints as described in R18-10 SWS_PHM Section 8.1.
     */
    using Checkpoint_id = std::uint16_t;

    /**
     * \brief In the System-API, for backwards compatibility with existing E3-1.1
     * code, Supervision_entity_id is a replacement for InterfaceType specified by
     * R18-10 SWS_PHM_00321.
     */
    using Supervision_entity_id = std::uint16_t;

    class Phm_client;

    /**
     * \brief The template class specified by R18-10 SWS_PHM_01132 is not part of
     * the System-API.  In the System-API, for backwards compatibility with
     * existing E3-1.1 code, that functionality is provided by the following
     * non-template class.
     */
    class SupervisionEntity final
    {
    public:
        /**
         * \brief In the System-API, for backwards compatibility with existing
         * E3-1.1 code, the following constructor provides the functionality of
         * the constructor specified by R18-10 SWS_PHM_01123.
         */
        explicit SupervisionEntity(Phm_client const& phm_client);

        ~SupervisionEntity();

        /**
         * \brief In the System-API, for backwards compatibility with existing
         * E3-1.1 code, the following method provides the functionality of the
         * method specified by R18-10 SWS_PHM_01127.  The argument Checkpoint_id
         * substitutes the enum argument, and the argument Supervision_entity_id
         * eliminates the need for the template class arguments.
         */
        void CheckpointReached(Supervision_entity_id supervision_entity_id,
                               Checkpoint_id         checkpoint_id);

    private:
        class SupervisionEntityImpl;
        std::unique_ptr<SupervisionEntityImpl> pImpl;
    };

} /* namespace phm */
} /* namespace ara */

#endif /* ARA_PHM_SUPERVISION_ENTITY_API_HPP_ */
