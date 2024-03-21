/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef OSAL_FILEACCESS_HXX
#define OSAL_FILEACCESS_HXX
/*****************************************************************************/

#include <ipl_config.h>
#include <common/stdint.h>
#include <common/PseudoBool.hxx>
#include <osal/osal_dso.h>

/*****************************************************************************/

namespace osal {

/*****************************************************************************/

    class FileSys;
    class FileInfo;
    class BinFileBase;

/*****************************************************************************/

    /*!
        \brief Type for specifying file access rights

        While different OSes have different ways to describe who can do what
        with a file, POSIX-like access bits seem to emerge as the common model.
        Even the upcoming C++17 standard relies on them
        (http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4099.html,
        http://en.cppreference.com/w/cpp/experimental/fs).

        The read/write/execute permissions can typically be
        interpreted like the following:

        For regular files:

        - read means that you're allowed to read the contents
        but you cannot necessarily execute them (if it is e.g.
        a script source file).
        - write means that you're allowed to modify or overwrite
        the contents. if write is granted but read isn't then
        what is possible is pretty peculiar to the underlying
        system and the applied operation
        - execute means that you're allowed to execute the file
        if it is a binary or a script file. Execution might be
        possible even if read is not granted.

        For directories:

        - read means that you're generally allowed to read the
        directories content (but the content has got its own
        access rights again). It might be possible to read files
        in the directory without read permission for the
        directory, if you already know that there is a file of a
        certain name inside
        - write means that you're generally allowed to create
        new content inside the directory
        - execute means that you're allowed to enter the
        directory and access it's content. This does not
        influence the permission to list the content.
    */
    class OSAL_EXPORT FileAccess {

    public:
        static const FileAccess none;          //!< \brief 0 no rights for anyone
        static const FileAccess owner_read;    //!< \brief 0400 owner can write
        static const FileAccess owner_write;   //!< \brief 0200 owner can write
        static const FileAccess owner_exec;    //!< \brief 0100 owner can execute/enter
        static const FileAccess owner_all;     //!< \brief 0700 owner can everything
        static const FileAccess group_read;    //!< \brief 040 group can read
        static const FileAccess group_write;   //!< \brief 020 group can write
        static const FileAccess group_exec;    //!< \brief 010 group can execute/enter
        static const FileAccess group_all;     //!< \brief 070 group can everything
        static const FileAccess others_read;   //!< \brief 04 others can read
        static const FileAccess others_write;  //!< \brief 02 others can write
        static const FileAccess others_exec;   //!< \brief 01 others can execute/enter
        static const FileAccess others_all;    //!< \brief 07 others can everything
        static const FileAccess all;           //!< \brief 0777 everyone can everything
        static const FileAccess set_uid;       //!< \brief 04000
        static const FileAccess set_gid;       //!< \brief 02000
        static const FileAccess sticky_bit;    //!< \brief 01000
        static const FileAccess mask;          //!< \brief 07777 all bits used in any permissions

        //! \brief \b Deprecated! Initialize from the constants instead!
        FileAccess(bool read/*=true*/, bool write/*=true*/, bool execute=false) {
            setflags(read, write, execute);
        }

        FileAccess operator ~ () const { return FileAccess(~value); }
        FileAccess operator & (const FileAccess &other) const { return FileAccess(value&other.value); }
        FileAccess operator | (const FileAccess &other) const { return FileAccess(value|other.value);}
        FileAccess operator ^ (const FileAccess &other) const { return FileAccess(value^other.value); }
        FileAccess &operator &= (const FileAccess &other) { value&=other.value; return *this; }
        FileAccess &operator |= (const FileAccess &other) { value|=other.value; return *this; }
        FileAccess &operator ^= (const FileAccess &other) { value^=other.value; return *this; }

        operator ipl::PseudoBool () const { return value? &ipl::PSEUDO_TRUE : ipl::PSEUDO_FALSE; }
        bool operator ! () const { return !operator ipl::PseudoBool(); }

        bool operator == (const FileAccess &other) const { return value==other.value; }
        bool operator != (const FileAccess &other) const { return value!=other.value; }
        bool operator <  (const FileAccess &other) const { return value< other.value; }
        bool operator <= (const FileAccess &other) const { return value<=other.value; }
        bool operator >  (const FileAccess &other) const { return value> other.value; }
        bool operator >= (const FileAccess &other) const { return value>=other.value; }

        //! \brief \b Deprecated! Bitwise-and with owner_read instead!
        bool canRead() const    { return (*this&owner_read)==owner_read; }
        //! \brief \b Deprecated! Bitwise-and with owner_write instead!
        bool canWrite() const   { return (*this&owner_write)==owner_write; }
        //! \brief \b Deprecated! Bitwise-and with owner_exec instead!
        bool canExecute() const { return (*this&owner_exec)==owner_exec; }
        //! \brief \b Deprecated! Bitwise-or the constants you need and assign that instead!
        void setflags(bool read, bool write, bool execute) {
            *this=(read?    owner_read| group_read :  none)|
                  (write?   owner_write|group_write : none)|
                  (execute? owner_exec| group_exec :  none);
        }

    protected:
        typedef uint32_t /* at least 19 bits needed */ underlying_type;

        explicit FileAccess(underlying_type value): value(value) {}

        underlying_type value;

        friend class FileInfo;
        friend class FileSys;
        friend class BinFileBase;
    };

/*****************************************************************************/

}  // end of namespace osal

/*****************************************************************************/
#endif
