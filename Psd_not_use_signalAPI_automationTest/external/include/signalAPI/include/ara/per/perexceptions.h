/*****************************************************************************/
/*
    Copyright 2021 e.solutions GmbH
    All rights reserved

    contains the realization of 
        ADAPTIVE AUTOSAR - Specification of Persistency
        Part of Standard Release 17-10
*/
/*****************************************************************************/

#if defined(ESOFW_ARA_BACKPORT_17_10_FEATURES)

#ifndef ARA_PER_PEREXCEPTIONS_H_
#define ARA_PER_PEREXCEPTIONS_H_

#include <exception>
#include <memory>
#include <string>
#include <ara/core/internal/ara_dso.h>


// SWS_PER_00002
namespace ara {
namespace per {

/*
 * As the exception constructors are marked noexcept, but a
 * string object is given as parameter, we have to be able
 * to handle memory shortage. In those cases we use a default message
 * to indicate the type of error.
 */

// Base class which contains all the functionality
class ARA_PER_EXPORT PerExceptionBase : std::exception {
protected:
    explicit PerExceptionBase( const std::string &message ) noexcept;
    explicit PerExceptionBase( const char *const message ) noexcept;

    ~PerExceptionBase() override;

    PerExceptionBase( const PerExceptionBase &other ) noexcept;
    PerExceptionBase( PerExceptionBase &&other ) noexcept;

    /*
     * \brief Retrieves the error message; in case the message could not be
     *        copied, returns a default message specific to the exception
     */
    char const *what() const noexcept override;


private:
    std::string m_msg{};
};

//! \link2req{satisfies,req~ARA_SWS_PER_EXCEPTION_1710_COMPATIBLE~1}
class ARA_PER_EXPORT ExceptionLogicError : PerExceptionBase {
public:
    // SWS_PER_00076
    // !brief CTOR for an ExceptionLogicError with string
    explicit ExceptionLogicError( const std::string &message ) noexcept;

    // !brief CTOR for an ExceptionLogicError with cstring
    explicit ExceptionLogicError( const char *const message ) noexcept;

    ~ExceptionLogicError() override;

    ExceptionLogicError( const ExceptionLogicError &other ) noexcept;
    ExceptionLogicError( ExceptionLogicError &&other ) noexcept;

    // SWS_PER_00132
    /*
     * \brief Retrieves the error message; in case the message could not be
     *        copied, returns a default message specific to a logic error
     */
    char const *what() const noexcept override;

};

class ARA_PER_EXPORT ExceptionStorageLocationNotFound : PerExceptionBase {
public:
    // SWS_PER_00060
    // !brief CTOR for an ExceptionLogicError with string
    explicit ExceptionStorageLocationNotFound( const std::string &message ) noexcept;

    // !brief CTOR for an ExceptionLogicError with cstring
    explicit ExceptionStorageLocationNotFound( const char *const message ) noexcept;

    ~ExceptionStorageLocationNotFound() override;

    ExceptionStorageLocationNotFound( const ExceptionStorageLocationNotFound &other ) noexcept;
    ExceptionStorageLocationNotFound( ExceptionStorageLocationNotFound &&other ) noexcept;

    // SWS_PER_00133
    /*
     * \brief Retrieves the error message; in case the message could not be
     *        copied, returns a default message specific to a missing storage location
     */
    char const *what() const noexcept override;

};

class ARA_PER_EXPORT ExceptionPhysicalStorageError : PerExceptionBase {
public:
    // SWS_PER_00061
    // !brief CTOR for an ExceptionLogicError with string
    explicit ExceptionPhysicalStorageError( const std::string &message ) noexcept;

    // !brief CTOR for an ExceptionLogicError with cstring
    explicit ExceptionPhysicalStorageError( const char *const message ) noexcept;

    ~ExceptionPhysicalStorageError() override;

    ExceptionPhysicalStorageError( const ExceptionPhysicalStorageError &other ) noexcept;
    ExceptionPhysicalStorageError( ExceptionPhysicalStorageError &&other ) noexcept;

    // SWS_PER_00134
    /*
     * \brief Retrieves the error message; in case the message could not be
     *        copied, returns a default message specific to a storage operation error
     */
    char const *what() const noexcept override;

};


} // namespace per
} // namespace ara

#endif // ARA_PER_PEREXCEPTIONS_H_

#endif // ESOFW_ARA_BACKPORT_17_10_FEATURES
