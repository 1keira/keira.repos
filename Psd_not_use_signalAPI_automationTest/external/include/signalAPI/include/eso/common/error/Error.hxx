/*
    Copyright 2020 e.solutions GmbH
        All rights reserved
*/
#ifndef IPL_ERROR_HXX
#define IPL_ERROR_HXX

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>

#include <common/stdint.h>

#include <common/error/ErrorStorages.hxx>
#include <common/error/ErrorObject.hxx>
#include <common/types/string.hxx>

namespace IPL_NAMESPACE
{

    /**
     * \brief
     *    Forward-iterator to traverse error history
     **/
    class ErrorIterator
    {
    public:
        ErrorIterator(const ErrorObject *o = NULL) IPL_NOEXCEPT :
            cur(o)
        { }

        ErrorIterator(const ErrorIterator &ei) IPL_NOEXCEPT :
            cur(ei.cur)
        { }

        ErrorIterator& operator=(const ErrorIterator &ei) IPL_NOEXCEPT
        {
            if ( this != &ei ) {
                cur = ei.cur;
            }
            return *this;
        }

        ErrorIterator& operator++() IPL_NOEXCEPT
        {
            cur = cur->next();
            return *this;
        }

        ErrorIterator operator++(int) IPL_NOEXCEPT
        {
            ErrorIterator ret(*this);
            ++*this;

            return ret;
        }

        const ErrorObject& operator*() const IPL_NOEXCEPT
        {
            return *cur;
        }

        const ErrorObject* operator->() const IPL_NOEXCEPT
        {
            return cur;
        }

        bool operator==(const ErrorIterator &ei) const IPL_NOEXCEPT
        { return cur == ei.cur; }

        bool operator!=(const ErrorIterator &ei) const IPL_NOEXCEPT
        { return !operator==(ei); }
    private:
        const ErrorObject *cur;
    };

    /**
     * \brief
     *    Container for an error context

     *    This is a simple container that is able to hold an
     *    arbitrary error context.  An error context is viewed as
     *    a sequence of errors as stored in the thread local
     *    ipl_error object. The sequence is ordered from newest to
     *    oldest errors.
     *
     *    The API of the object allows to iterate over this
     *    sequence via ErrorIterators. This way the errors can be
     *    inspected without invoking the ipl_error API.
     *
     *    ErrorApi::getErrorContext() allows to store the
     *    currently active error context in a container of this
     *    type.  ErrorApi::setErrorContext() allows to restore a
     *    previously stored error context into the current error
     *    context of the thread.
     **/
    class ErrorContext
    {
        friend class ErrorApi;
    public:
        ErrorContext() IPL_NOEXCEPT : m_num_errs(0) { }

        /**
         * \brief
         *     Return an iterator to the most recent error of
         *     the current error history
         **/
        inline ErrorIterator begin() const IPL_NOEXCEPT
        {
            if( m_num_errs )
                return ErrorIterator( & m_errs[0] );

            return ErrorIterator(NULL);
        }

        /**
         * \brief
         *    Return an iterator the position after the oldest
         *    error of the current error history
         **/
        inline ErrorIterator end() const IPL_NOEXCEPT
        {
            return ErrorIterator(NULL);
        }
    private:

        /**
         * \brief
         *    Adds an error to the current context

         *    Only accessible from ErrorApi
         **/
        void addError( const ipl::ErrorObject &eo ) IPL_NOEXCEPT
        {
            if( m_num_errs < ipl::ErrorStorage::MAX_NUM_ERROR_OBJECTS )
            {
                m_errs[m_num_errs] = eo;

                // add ptr. to previous error, if present
                if( m_num_errs )
                {
                    m_errs[m_num_errs-1].next() =
                        &m_errs[m_num_errs];
                }

                m_num_errs++;
            }
        }
    private:
        //! array able to hold a full error context
        ipl::ErrorObject
            m_errs[ipl::ErrorStorage::MAX_NUM_ERROR_OBJECTS];
        //! number of valid errors in m_errs
        uint_fast8_t m_num_errs;
    };

    //! \brief
    //! ErrorOutput is a helper class that handles varargs passed to
    //! ipl_raise, ipl_reraise macro (see below)
    class IPLCOMMON_EXPORT ErrorOutput
    {
    private:
        const char* m_file;
        int m_line;
        bool m_set;
    public:
        ErrorOutput( const char* file, int line, bool set ) IPL_NOEXCEPT;
        void operator()( const ErrorType& et, const ErrorInt ei, ... ) IPL_NOEXCEPT;
        void operator()( const ErrorObject &eo ) IPL_NOEXCEPT;
    };

    //! accessor API to ErrorStorage
    class IPLCOMMON_EXPORT ErrorApi
    {
    public:
        /**
         * \brief
         *     Tell if there is an error active.

         *     An error is considered active if there is an
         *     error object available that has not yet been
         *     acknowledged via ack().
         **/
        inline operator bool () const IPL_NOEXCEPT
        { return this->isError(); }

        //! \brief
        //! more verbose variant of operator bool() const, see
        //! ErrorStorage::isError()
        inline bool isError(const bool no_acked = true) const IPL_NOEXCEPT
        { return ErrorStorage::isError(no_acked); }

        /** Query if this error's type matches the other's type or a parent's type
         **/
        inline bool isA(const ErrorType &other) const IPL_NOEXCEPT
        { return ErrorStorage::isA(other); }

        //! \brief
        //! returns \c true if the current error and ID match \c
        //! other and \c id
        inline bool matches(const ErrorType &other, const ErrorInt &id) IPL_NOEXCEPT
        {
            return this->isA(other) && this->id() == id;
        }

        /** Query the error message of this error
         **/
        inline const char *reason() const IPL_NOEXCEPT
        { return ErrorStorage::reason(); }

        /** Acknowledge the error - ack() signals to the storage
         * that this error has been handled.
         **/
        inline void ack() IPL_NOEXCEPT
        { ErrorStorage::ack(); }

        /** Query if this error is identical to other
         **/
        inline bool equals(ErrorType& other) IPL_NOEXCEPT
        { return ErrorStorage::equals(other); }

        /** Get this error's ID.
         **/
        inline ErrorInt id() IPL_NOEXCEPT
        { return ErrorStorage::id(); }

        /**
         * \brief
         *     Get the error container at front of the error
         *     list of the current ErrorStorage

         *     If there is no error an empty dummy error will
         *     be returned.
         *
         *     Error history can be accessed via
         *     ErrorObject::next().
         **/
        inline const ErrorObject& get() const IPL_NOEXCEPT
        { return ErrorStorage::get(); }

        /**
         * \brief
         *     Return an iterator to the most recent error of
         *     the current error history
         **/
        inline ErrorIterator begin() const IPL_NOEXCEPT
        {
            if( this->isError(false) )
                return ErrorIterator( & this->get() );

            return end();
        }

        /**
         * \brief
         *    Return an iterator the position after the oldest
         *    error of the current error history
         **/
        inline ErrorIterator end() const IPL_NOEXCEPT
        {
            return ErrorIterator(NULL);
        }

        /**
         * \brief
         *    Get a string containing formatted error history
         *    from oldest to newest error

         *    This string can be used to quickly dump the
         *    current error context to console or file.
         **/
        ipl::string getReasonList() IPL_NOEXCEPT;

        /**
         * \brief
         *    Get the currently active error context into an
         *    external object

         *    Stores the currently present error sequence into
         *    an ErrorContext container and returns that
         *    container.
         *
         *    Storing and restoring error contexts is a way to
         *    allow for delayed error reporting e.g. in
         *    asynchronous operations.
         **/
        inline ErrorContext getErrorContext() IPL_NOEXCEPT
        {
            ErrorContext ret;

            for( ErrorIterator ei = this->begin();
                ei != this->end(); ei++ )
            {
                ret.addError( *ei );
            }

            return ret;
        }

        /**
         * \brief
         *    Restore the error context from \c ex in the
         *    current thread

         *    The error sequence stored in \c ex will be made
         *    active as if the errors stored in \c ex have
         *    been raised and reraised in the original
         *    sequence i.e. from oldest to newest.
         *
         *    If currently an unacknowledged error is present
         *    in the ErrorStorage then the same rules apply as
         *    if an error is overwritten via ipl_raise().
         *
         *    After setting the error sequence active there
         *    will be an unacknowledged error present that
         *    needs to be acknowledged by the thread.
         **/
        inline void setErrorContext(const ErrorContext &ex) IPL_NOEXCEPT
        {
            for( int_fast8_t i = (int_fast8_t)(ex.m_num_errs - 1);
                i >= 0; i-- )
            {
                const ErrorObject& e = ex.m_errs[i];
                const bool is_first =
                    (i == (ex.m_num_errs - 1));

                ErrorOutput(e.file(), (int)e.line(), is_first)(e);
            }
        }

        /**
         * \brief
         *    Tests if the error history contains the passed error type and error id

         **/
        inline bool hasA(const ErrorType &etype, const ErrorInt &id) IPL_NOEXCEPT
        {
            for( ErrorIterator ei = this->begin();
                ei != this->end(); ei++ )
            {
                if ( ei->isA(etype) && (ei->id() == id) )
                {
                    return true;
                }

            }

            return false;
        }
    };

} // end ns ipl

/*
 *    The following stuff needs to be global and not in a namespace.
 *
 *    This is ugly but raise and error are notable candidates for
 *    preprocessor name clashes thus the explicit ipl prefix is safer
 *    here.
 */

/** ipl_raise sets the error in the current ErrorStorage
 **/
#define ipl_raise (ipl::ErrorOutput(__FILE__, __LINE__, true))

/** ipl_reraise attaches an error to the error in the current ErrorStorage
 **/
#define ipl_reraise (ipl::ErrorOutput(__FILE__, __LINE__, false))

//! like ipl_reraise but doesn't attach if there's currently an unacknowledged error present
#define ipl_try_reraise ( ipl::ErrorOutput(__FILE__, __LINE__, ipl_error.isError() ? false : true) )


/** use ipl_error to access the ErrorStorage
 **/
IPLCOMMON_EXPORT extern ipl::ErrorApi ipl_error;

#endif
