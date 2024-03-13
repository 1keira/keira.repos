/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef IPL_IBINSTREAMBASE_HXX
#define IPL_IBINSTREAMBASE_HXX

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>
#include <common/iplcommon_dso.h>
#include <common/error/Error.hxx>

#include <stdlib.h>

namespace IPL_NAMESPACE
{

/**
    \brief
        This header defines the base class for a general binary stream abstraction

        This is a common base class for IBinInputStream and IBinOutputStream. The class
        hierarchy is a diamond similar to the C++ std. streams library ios, istream, ostream
        and iostream.

        The difference here is that these streams are considered for binary input/output
        only. Thus no formatted input/output operations like in the streams library are
        provided. Actually it is a thin as possible abstraction to access different i/o
        implementations in a uniform way.

        The C++ std. streams library is pretty complex regarding its API and buffering
        scheme. Still the behaviour e.g. regarding error indication and interpretation of
        certain flags isn't very well defined under all circumstances. While binary i/o is
        possible with the streams library (so called unformatted i/o operations) it clearly
        focusses on formatted operations.

        For sake of a simpler interface and possibly more efficient implementation this
        binary stream abstraction thus only provides a means to read and write chunks of
        binary data. It also supports a primitive buffering scheme if enabled during
        construction time.

        This base class provides definitions, interface and data that is shared between
        binary input and output similar to the ios class in the streams library.
**/
class IPLCOMMON_EXPORT IBinStreamBase
{
public: // types
    /**
     * \brief
     *     Generalized error type for stream operations

     *     Every implementation of the binary stream interface(s) should raise an error of this
     *     type if an implementation-specific operation on the stream failed. Attached to this
     *     error can be more detailed, implementation-specific errors.
     *
     *     If a perform*() call into the stream implementation indicated and error and did not
     *     raise a StreamError then a warning will be output by the generic stream
     *     implementation part.
     **/
    static ipl::ErrorType StreamError;

    //! possible error values for StreamError
    enum StreamErrors
    {
        //! the stream is broken and further operations will fail
        STREAM_BROKEN,
        //! a single operation failed but the stream might still be usable
        OPERATION_FAILED,
        //! the end of the stream has been reached (i.e. no more data can be read/written)
        END_OF_STREAM,
        //! the requested operation is not possible on the stream in principle
        NOT_SUPPORTED,
        //! any other, uncategorized error
        UNKNOWN_STREAM_ERROR
    };
public: // functions

    /**
     *    \brief
     *        Default constructor that assumes blocking mode for the stream

     *        Be aware that the input/output stream interfaces are using virtual
     *        inheritance to derive from this base class. This causes a number of
     *        side-effects. The most important being that every class that derives from
     *        the input/output stream interfaces is again responsible for calling the base
     *        class constructor for IBinStreamBase. This is known as the "most derived
     *        class" has to call the base class constructor.
     *
     *        Thus if we don't have a default constructor then all clients of the stream
     *        interfaces need to call the IBinStreamBase constructor again and again which
     *        is pretty confusing. The solution to this problem is to have a
     *        default constructor and do the actual initialization stuff via protected
     *        member functions in this case e.g. the setBlocking() function.
     *
     *        This is done similarly in the C++ std. streams library. But we should always
     *        be aware of this behaviour as it can cause strange stuff.
     **/
    IBinStreamBase() IPL_NOEXCEPT :
        m_blocking(true)
    { }

    /**
        \brief
            virtual destructor to make sure derived class destructors are always called
    **/
    virtual ~IBinStreamBase() IPL_NOEXCEPT
    { }

    /**
     *    \brief
     *        returns wheter this output stream instance realises blocking or non-blocking
     *        behaviour.

     *        This setting determines the way the buffering mechanism of derived stream
     *        interfaces behave when trying to actually read/write data from/to the
     *        stream.
     **/
    bool isBlocking() const IPL_NOEXCEPT
    {
        return m_blocking;
    }

    /**
     *    \brief
     *        Determines validity of the stream

     *        The implementation of this function should indicate for the complete stream
     *        (i.e. any involved classes in the hierarchy dealing with the stream) if the
     *        stream is in a state that allows using it.
     *    \return
     *        true if valid, false otherwise
     **/
    virtual bool isValid() const IPL_NOEXCEPT = 0;
protected: // functions

    //! set the blocking mode of the stream to \c b
    void setBlocking(const bool b) IPL_NOEXCEPT
    { m_blocking = b; }
private: // data
    //! \see isBlocking()
    bool m_blocking;
}; // end class

} // end namespace

#endif /* IPL_IBINSTREAMBASE_HXX */
