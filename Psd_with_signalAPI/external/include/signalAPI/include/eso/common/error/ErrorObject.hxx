/*
    Copyright 2020 e.solutions GmbH
        All rights reserved
*/
#ifndef IPL_ERROR_OBJECT_HXX
#define IPL_ERROR_OBJECT_HXX

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>
#include <common/iplcommon_dso.h>
#include <common/error/ErrorType.hxx>

#ifdef IPL_OS_INTEGRITY
#include <INTEGRITY.h>
#endif

namespace IPL_NAMESPACE
{

/**
 *    \brief
 *        Container for error data

 *        ErrorObjects may be linked together i.e. there can be a chain of errors like:
 *        FILE_NOT_FOUND->CONFIGURATION_INVALID->INITIALIZATION_FAILED
 **/
class IPLCOMMON_EXPORT ErrorObject
{
    friend class ErrorStorage;

public:
    static const unsigned int MAX_MSG_LEN=256;

    // This is an emergency measure to make this twisted mess
    // remotely usable as needed:
    const ErrorType *type() const IPL_NOEXCEPT { return m_type; }
    const char *file() const IPL_NOEXCEPT { return m_file; }
    unsigned line() const IPL_NOEXCEPT { return m_line; }
    const char *msg() const IPL_NOEXCEPT { return m_msg; }
    int tid() const IPL_NOEXCEPT { return m_ownthread; }
    int pid() const IPL_NOEXCEPT { return m_ownprocess; }
    ErrorObject *&next() IPL_NOEXCEPT { return m_next; }
    ErrorObject *next() const IPL_NOEXCEPT { return m_next; }
    // end of emergency

private:
    const ErrorType* m_type;
    ErrorInt     m_eint;
    const char*  m_file;
    unsigned int m_line;
    //! always points to the current error msg. need not to point to \c m_msgbuf.
    const char*  m_msg;
    //! the string buffer assoc. with this error object
    char         m_msgbuf[MAX_MSG_LEN];
#ifndef IPL_OS_INTEGRITY
    //! this thread
    int m_ownthread;
#else
    Value m_ownthread;
#endif
    //! this process
    int m_ownprocess;
    //! the attached error, if any
    ErrorObject* m_next;

protected:
public:
    /** Ctor, initialized members - nothing special.
     **/
    ErrorObject() IPL_NOEXCEPT;

    /**
     *     \brief
     *         Calls operator=(const ErrorObject&)
     **/
    ErrorObject(const ErrorObject &o) IPL_NOEXCEPT;

    /**
     *    \brief
     *        Copies the values of \c o into the new object

     *        Everything will be taken over except for the following:
     *
     *        - m_msg will point to m_msgbuf
     *        - m_msgbuf will get a copy of o.m_msg
     *        - m_next will be NULL
     **/
    ErrorObject& operator=(const ErrorObject &o) IPL_NOEXCEPT;

    /** Query if this errors type matches the other type or one of other's parents' types.
     **/
    bool isA(const ErrorType& other) const IPL_NOEXCEPT;
    /** Query if this error is identical to the other error.
     **/
    bool equals(const ErrorType& other) const IPL_NOEXCEPT;
    /** Query if isA(other) && this->id() == id in one go
     **/
    bool is(const ErrorType &other, const ErrorInt &id) const IPL_NOEXCEPT
    { return isA(other) && this->id() == id; }
    /** This error's ID
     **/
    ErrorInt     id() const IPL_NOEXCEPT;
    /** This error's error message.
     **/
    const char*  reason() const IPL_NOEXCEPT;
};

} // end ns ipl

#endif
