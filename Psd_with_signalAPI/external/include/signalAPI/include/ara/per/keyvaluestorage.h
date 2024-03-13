/**
 * @brief System-API header for persistency class KeyValueStorage
 *
 * @file ara/per/keyvaluestorage.h
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
 * R17-10 SWS_PER refers to the Autosar software specification for persistency
 * from the Autosar release 17-10.
 */

#ifndef ARA_PER_KEYVALUESTORAGE_H_
#define ARA_PER_KEYVALUESTORAGE_H_

#include "kvstype.h"

/*
 * The following standard library header files are included to make this
 * System-API header file self-contained.  Their inclusion, however, is not
 * part of the System-API.  That is, client code can assume the System-API
 * header files to be self-contained, but client code that makes use of
 * declarations from standard header files shall include these files itself.
 */

#include <string> // string
#include <vector> // vector<...>

/*
 * The following standard library header files are needed by the mocking
 * support that is part of this header file, but which is not defined to be
 * part of the System-API.
 */

#include <memory> // unique_ptr

/*
 * R17-10 SWS_PER_00002
 */
namespace eso_ara_per_backport
{

/*
 * R17-10 SWS_PER does not make any statements about thread safety.  Thus,
 * client applications shall not assume thread safety for any operation.
 */

/**
 * \brief R17-10 SWS_PER_00051
 *
 * R17-10 SWS_PER does not (except for one example) give any details about
 * what strings are allowed as keys.  For the system API, the following is
 * guaranteed:
 *
 * * Keys may contain the following ASCII characters: lowercase letters a-z,
 *   uppercase letters A-Z, digits 0-9, special characters dash "-",
 *   underscore "_", dot ".".
 *
 *   Implementation note: Implementations may accept further characters in
 *   keys.  It is not required to enforce that application provided keys use
 *   only characters from the list above.
 *
 * * Keys can have a length of 1 to 127 characters.
 *
 *   Implementation note: Implementations may accept keys that are longer than
 *   127 characters.  It is not required to enforce that application provided
 *   keys are shorter than 128 characters.
 *
 * * Keys are case sensitive.
 *
 * Since user code is expected to create instances using the constructor
 * specified by R17-10 SWS_PER_00052, and, since none of the member functions
 * are specified as virtual by R17-10 SWS_PER, there is no way to derive from
 * the class in a meaningful way, and thus the System-API defines the class to
 * be final.
 */
class KeyValueStorage final
{
public:
    /*
     * R17-10 SWS_PER_00041
     */
    KeyValueStorage(KeyValueStorage const&) = delete;
    KeyValueStorage& operator=(KeyValueStorage const&) = delete;

    /**
     * \brief R17-10 SWS_PER_00052
     *
     * R17-10 SWS_PER does not (except for one example) give any details about
     * what strings are allowed for the database argument.  For the system
     * API, the following constraints apply: a) The database string may
     * contain only the following characters: lowercase letters a-z, uppercase
     * letters A-Z, digits 0-9, special characters dash "-", underscore "_",
     * dot ".".  b) The database string shall have a length of 1 to 24
     * characters.  Moreover, it is not defined whether the database string is
     * case sensitive.  Thus, if the constructor of KeyValueStorage is called
     * one time with some string s1 and another time (from the same or another
     * application) with a string s2 where s1 != s2 but s1 and s2 only differ
     * with respect to case, then it is not defined whether s1 and s2 will
     * refer to the same database.  A system implementation that uses
     * KeyValueStorage with such database strings s1 and s2 is considered
     * malformed.
     */
    explicit KeyValueStorage(std::string const& database) noexcept(false);

    /**
     * \brief R17-10 SWS_PER_00050
     */
    ~KeyValueStorage();

    /**
     * \brief R17-10 SWS_PER_00042
     */
    std::vector<std::string> GetAllKeys() const noexcept(false);

    /**
     * \brief R17-10 SWS_PER_00043
     */
    bool HasKey(std::string const& key) const noexcept;

    /**
     * \brief R17-10 SWS_PER_00044
     */
    ara::per::KvsType GetValue(std::string const& key) const noexcept;

    /**
     * \brief R17-10 SWS_PER_00046
     *
     * Implementation notes:
     *
     * * Calls to SetValue by themselves are not allowed to cause any write
     *   operation on the persistent storage medium.  Only calls to
     *   SyncToStorage may cause write operations on the persistent storage
     *   medium.
     */
    void SetValue(std::string const& key, ara::per::KvsType const& value) noexcept(false);

    /**
     * \brief R17-10 SWS_PER_00047
     *
     * Implementation notes:
     *
     * * Calls to RemoveKey by themselves are not allowed to cause any write
     *   operation on the persistent storage medium.  Only calls to
     *   SyncToStorage may cause write operations on the persistent storage
     *   medium.
     */
    void RemoveKey(std::string const& key) noexcept;

    /**
     * \brief R17-10 SWS_PER_00048
     *
     * Implementation notes:
     *
     * * Calls to RemoveAllKeys by themselves are not allowed to cause any
     *   write operation on the persistent storage medium.  Only calls to
     *   SyncToStorage may cause write operations on the persistent storage
     *   medium.
     */
    void RemoveAllKeys() noexcept;

    /**
     * \brief R17-10 SWS_PER_00049
     *
     * Note: Care has to be taken with calls to SyncToStorage.  Every call to
     * SyncToStorage will cause a write operation to the physical medium.  Too
     * many writes will damage the medium!  On the other hand, without a call
     * to SyncToStorage, data is not granted to be truly persisted.
     *
     * Therefore, applications that need data to be persisted shall call
     * SyncToStorage once when preparing for shutdown or for suspend-to-RAM,
     * but after all outstanding calls to SetValue have been done.
     * Applications shall not call SyncToStorage otherwise, with one rather
     * unusual exception:
     *
     * If an application has some data that *needs* to be put to the physical
     * medium immediately - for example to minimize the risk of data loss in
     * case of a later crash - then, a call to SyncToStorage during system
     * operation is in order.  Such calls to SyncToStorage, however, need to
     * be agreed with the respective system architects.
     *
     * Implementation notes:
     *
     * * Implementations of the System-API have to take into consideration
     *   that applications which use the persistency API will call
     *   SyncToStorage when preparing for shutdown or suspend-to-RAM.  In
     *   particular the requirements on the lifetime of the storage medium
     *   still have to be fulfilled.  (An unfortunate implementation, for
     *   example, might aggregate all application data bases into one big
     *   file: Then, in preparation for shutdown, all applications will call
     *   SyncToStorage, and this may end in the one big file being written
     *   several times.)
     *
     * * Implementations of the System-API shall support the detection of
     *   incorrect uses of SyncToStorage by applications during development
     *   time - for example by logging suspicious calls to SyncToStorage.
     *
     * Background: R17-10 SWS_PER does not describe under which circumstances
     * client code needs to call SyncToStorage.  Only starting from Autosar
     * release 18-10 it is made explicit that data that was added/updated via
     * SetValue will only be truly persisted by a call to SyncToStorage.  At
     * least on ICAS1 a call to SyncToStorage is necessary to get the data
     * persisted.  Therefore, the System-API also defines the call to
     * SyncToStorage to be necessary.
     */
    void SyncToStorage() noexcept(false);

    /*
     * The following private section is only here for mocking support.  It is not
     * part of the System-API - other implementations of the System-API can look
     * completely different.
     */

private:
    class KeyValueStorageImpl;
    std::unique_ptr<KeyValueStorageImpl> pImpl;
};

} // namespace eso_ara_per_backport

#ifndef INCLUDED_BY_ESO
namespace ara
{
namespace per
{
    using eso_ara_per_backport::KeyValueStorage;
} // namespace per
} // namespace ara
#endif

#endif /* ARA_PER_KEYVALUESTORAGE_H_ */
