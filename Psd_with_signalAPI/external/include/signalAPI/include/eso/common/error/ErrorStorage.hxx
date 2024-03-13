/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef IPL_ERROR_STORAGE_H
#define IPL_ERROR_STORAGE_H

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>
#include <common/iplcommon_dso.h>
#include <common/error/ErrorObject.hxx>

namespace IPL_NAMESPACE
{

/*!
    \page error_handling_page Framework error handling
    
    \note Use \ref ipl_error to access your thread's ErrorStorage.

    What's an error storage?
    ------------------------
    
    An Error storage is a error reporting mechanism similar to the
    operating system's errno.
    A method call may fail. If it does so, the method reports the failure
    back to the caller and additionally stores the reason for the error 
    in a so-called error store - which is basically a small per thread
    container for errors.
    If errors are not handled the storage can be configured to trigger an action
    i.e. trace the error, abort, print the error, call a user function, ...

    How does a method report the failure or success of its operation?
    -----------------------------------------------------------------
    
    Basically this is up to programmer.
    There are many different ways on how to signal success or failure
    e.g. "0 on error, greater than 0 on success" or
    "0 on success, error code greather than 0 on failure " or
    "true, false" or "NULL-address on failure, non-NULL-address on success". 
    Of course a programmer should avoid mixing different ways of indicating
    an error within a single interface/API. 

    How does a method create an error?
    ----------------------------------
    
    By calling \ref ipl_raise.
    ipl_raise takes at least two arguments: the error type and the error id.
    If a new error is linked to the current error \ref ipl_reraise can be called
    to attach the new error to the existing one.
    
    Examples:
    \code
    ipl_raise(SYSTEM_ERROR_CLASS, OUT_OF_MEMORY);
    ipl_raise(USAGE_ERROR, INDEX_OUT_OF_BOUNDS, index, min_index, max_index);
    \endcode
    Error classes and error ids can be defined separately for each module. 
    The error id determines the error  message and the parameters that are
    possible. 
    For performance reasons -- in the error case -- constant message without
    any parameters should be preferred!
    (Dynamic messages i.e. messages with parameters require the creation).

    How to handle errors using error storage?
    -----------------------------------------
    
    When a method has failed, the caller can use the error storage to query
    the exact reason for the error.
    The object \ref ipl_error can be used to access the error storage.

    How are un-handled errors detected by the storage?
    --------------------------------------------------
    
    Each errro returned to a called must be acknowledged by calling
    \ref ipl::ErrorApi::ack() "ipl_error.ack()".
    Un-handled errors are detected in two cases:
    1. a new error is stored while the current error has not been acknowledged
    and 2. the storage is destroyed and still contains an error that has not
    been acknowledged.

    How to define an action for un-handled errors?
    ----------------------------------------------
    
    Different actions can be taken when errors in the storage are not handled
    (again: the storage will notice if errors are over-written and if errors
    still exist when it is detroyed). 
    The storage class defines the action that is executed when an un-handled
    error is detected (currently the following classes exist):
    * ErrorStorage: This is the default storage. Action is system defined
      (most likely trace/dump)
    * StdoutDumpErrorStorage: Print info about un-handled errors to stdout.
    * AbortErrorStorage: Print info about un-handled errors to stdout and abort.
    * TraceErrorStorage: Trace info about un-handled errors to a user defined
      trace channel.
    * CustomErrorStorage: Call a user defined function if an un-handled error
      is detected.

    If you wan't a specific action for un-handled errors you have to create
    an instance of the storage class.
    The error storage keeps track of storages already being defined. i.e.
    \code
    {
        ErrorStorage es; //from here on ErrorStorage's action is executed for un-handled errors being detected
        ...
        {
            AbortErrorStorage aes; //from here on AbortErrorStorage's action is executed for un-handled errors being detected
            ... 
        }
        //from here on ErrorStorage's action is executed for un-handled errors being detected
    }
    \endcode
    
    
    How do I use it?
    ----------------
    
    \code
    ...
    #include <Error.hxx>
    ...
    if(!loadConfigFile() ) //loadConfigFile signals failure, returning false
    {
        //loadConfigFile has failed

        //test error category
        if(ipl_error.isA(IO_ERROR)) { 

            //enable default config or whatever seems suitable
            //... we simply print the error message
            printf("%s",ipl_error.reason();

            //acknowledge error
            ipl_error.ack(); 
        }
    }
    \endcode

    What do I have to keep in mind when defining my errors?
    -------------------------------------------------------
    
    IMPORTANT!
    To speed-up access to the error messages, the error IDs of an error category
    (ErrorType) are identical to the index of the errorID in the
    error category's error message table.
    If this is not suitable or can not be guaranteed you have to define the
    preprocessor variable ERRORTYPE_SECURITY_FIRST__DO_CHECK_INDEX.
    However, then a linear search will be used to identify an error IDs message
    within the table.

    How can I define my own errors?
    -------------------------------
    
    \code
    enum 
    {
        MY_FILE_NOT_FOUND=0,
        MY_CONFIG_NOT_AVAILABLE,
        MY_SOMETHING_WRONG
    };
    ErrorID MY_ERROR_TABLE[] = 
    {
        { MY_FILE_NOT_FOUND, "File '%s' not found", 1 },
        { MY_CONFIG_NOT_AVAILABLE, "Config not available", 0 },
        { MY_SOMETHING_WRONG, "%s",1 },
        { -1, "", 0 } // end of table marker: do not change!
    };
    ErrorType MY_ERROR(MY_ERROR_TABLE);

    //=> ipl_raise(MY_ERROR, MY_FILE_NOT_FOUND, "engine.cfg");
    \endcode
*/


/*!
    \brief Store a single ErrorObject and trigger an action on un-handled errors
    
    \see \ref error_handling_page
*/    
class IPLCOMMON_EXPORT ErrorStorage
{
public:
    static const unsigned int MAX_NUM_ERROR_OBJECTS=8;

    static void action_dump_to_stdout(void* data, const char* action_text,
                                      const ErrorObject* obj,
                                      unsigned int linkcnt) IPL_NOEXCEPT;
    static void action_dump_and_abort(void* data, const char* action_text,
                                      const ErrorObject* obj,
                                      unsigned int linkcnt) IPL_NOEXCEPT;
    static void action_trace(void* data, const char* action_text,
                             const ErrorObject* obj, unsigned int linkcnt) IPL_NOEXCEPT;

    typedef void (*FPtrAction)(void* data, const char* action_text, const ErrorObject* obj, unsigned int linkcnt);
private:
    ErrorObject*  m_current;    // there is exactly one current error, it may however be linked with other errors
    ErrorStorage* m_previous;   // pointer to ErrorStorage that alread existed when this one was instantiated
    unsigned int  m_linkcnt;    // ErrorObjects can be linked together (using add); 
                                // this is the link counter; if the link counter exceeds 
                                // IPL_ERROR_OBJECTS_MAX and a new error is linked 
                                // to this error, the oldest linked error will be overwritten
    ErrorObject   m_errors[MAX_NUM_ERROR_OBJECTS];  // ErrorObject array (for linking 
                                                    // error objects; maximum link count is MAX_NUM_ERROR_OBJECTS)
    FPtrAction    m_action;     // pointer to function that is called when un-handled errors are detected
    //! whether the current error has been acknowledged by the client
    bool m_acked;
protected:
    void*         m_actiondata; // data passed to m_action

    //! actually removes the current error
    void clear() IPL_NOEXCEPT;
public:
    /** Create error storage.
     *  @param action function that is executed when un-handled errors are detected
     **/
    ErrorStorage(FPtrAction action=action_dump_to_stdout) IPL_NOEXCEPT;
    /** Destroy error storage. Will trigger action if an un-handled error is detected.
     **/
    ~ErrorStorage() IPL_NOEXCEPT;
    /**
     *     \brief
     *         Tell if there is an error stored.

     *         If \c no_acked is set to true then the function returns only true if there
     *         is an error AND the error has not yet been acknowledged.
     *
     *         If \c no_acked is set to false then the function also returns true if there
     *         is an error that has already been acknowledged (this will actually always be
     *         the case if ever an error has been raised).
     **/
    static bool isError(const bool no_acked = true) IPL_NOEXCEPT;
    /** Add/Set the error in the error storage. Will trigger action if an un-handled error is over-written.
     **/
    static char* add(bool replace, const ErrorType& stat, ErrorInt eint,
                     const char* file, int line, const char* reason,
                     bool& no_errorstorage_defined) IPL_NOEXCEPT;
    /** Acknowledge the error - ack() signals to the storage that this error has been handled.
     **/
    static void ack() IPL_NOEXCEPT;
     /** Query if this error's type matches the other's type or one of other's parents' types
     **/
    static bool isA(const ErrorType& other) IPL_NOEXCEPT;
    /** Query if this error is identical to other
     **/
    static bool equals(ErrorType& other) IPL_NOEXCEPT;
    /** Get the error container for the error in the storage.
     *  If there is no error an empty dummy error will be returned.
     **/
    static const ErrorObject& get() IPL_NOEXCEPT;
    /** This error's error message. If there is no error "" will be returned.
     **/
    static const char*  reason() IPL_NOEXCEPT;
    /** The file where the error occured. If there is no error "" will be returned.
     **/
    static const char*  file() IPL_NOEXCEPT;
    /** The line number where the error occured. If there is no error 0 will be returned.
     **/
    static unsigned int line() IPL_NOEXCEPT;
    /** This error's id. If there is no error 0 will be returned.
     **/
    static ErrorInt id() IPL_NOEXCEPT;
};

} // end ns ipl

#endif
