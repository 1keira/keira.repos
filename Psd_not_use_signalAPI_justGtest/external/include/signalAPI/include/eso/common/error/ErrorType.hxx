/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef IPL_ERROR_TYPE_HXX
#define IPL_ERROR_TYPE_HXX

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>
#include <common/iplcommon_dso.h>

#include <stdlib.h> // for NULL

namespace IPL_NAMESPACE
{

/**
 * \brief
 *     Table entry used by ErrorType

 *    each entry has an id, a message (which may include % placeholders), and the number of placeholders in the message
 *    eg.
 *    { UTIL_FILE_NOT_FOUND, "File '%s' not found", 1 }
 *      { OUT_OF_MEMORY, "Out of memory", 0 }
 *
 *    Messages without placeholders (i.e. argcnt==0) should be preferred as they require neither dealing with
 *    varargs nor string copying operations.
 **/
typedef signed int ErrorInt;
struct ErrorID
{
    ErrorInt eid;
    const char* emessage;
    unsigned int eargcnt;
};

}  // end of namespace IPL_NAMESPACE

template <size_t N>
constexpr size_t ipl_get_table_size(const ipl::ErrorID (&)[N]) {
    return N;
}

namespace IPL_NAMESPACE
{

//! Each instance of ErrorType denotes one category of errors
class IPLCOMMON_EXPORT ErrorType
{
public:

    /** Create a new error category, being a child category of parent. Error IDs can be looked-up using table idtable.
     **/
    ErrorType(const ErrorID* idtable, unsigned int tablesize, const ErrorType& parent) IPL_NOEXCEPT;
    /** Create a new error category. Error IDs can be looked-up using idtable.
     **/
    ErrorType(const ErrorID* idtable, unsigned int tablesize) IPL_NOEXCEPT;
    /** Query if this type equals other or one of other's parents' types
     **/
    bool isA(const ErrorType& other) const IPL_NOEXCEPT;
    /** Get the message string (field emessage in ErrorInt) for ei from the error table of this error category.
     **/
    const char* getMessageString(ErrorInt ei) const IPL_NOEXCEPT;
    /** Get the argument count (field eargcnt in ErrorInt) for ei from the error table of this error category.
     **/
    unsigned int getArgumentCount(ErrorInt ei) const IPL_NOEXCEPT;
protected:
    const ErrorID* m_idtable;
    const ErrorType* m_parent;
    int   m_numtableentries;
private:
    ErrorType() IPL_NOEXCEPT;
};

} // end ns ipl

#endif
