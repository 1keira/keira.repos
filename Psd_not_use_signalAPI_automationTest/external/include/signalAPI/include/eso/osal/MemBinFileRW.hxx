/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_MEMBIFILERW_HXX
#define OSAL_MEMBIFILERW_HXX

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/MemBinFileBase.hxx>
#include <osal/BinTempFileRW.hxx>

namespace osal {

    /**
    * \brief
    *     Specialization of MemBinFileBase for read-write, memory mapped
    *     file-access

    *     Makes the API of MemBinFileBase accessible for read-write
    *     operations
    **/
    class MemBinFileRW :
        public MemBinFileBase
    {
    public: // functions
        using BinFileBase::truncateSize;

        //! Constructs an invalid file. no error is raised.
        MemBinFileRW() :
            MemBinFileBase()
        { }

        /**
        * \brief
        *     Open the file at path \c p using \c flags
        * \errorindicator
        *     via isValid()
        * \errors
        *     see MemBinFileRW::open(const char*, FileAccess&)
        **/
        explicit MemBinFileRW(const char *p,
            const ReadWriteFlags &flags = ReadWriteFlags())
        {
            MemBinFileRW::open(p, flags);
        }

        //! \see MemBinFileR(const char*, const ReadWriteFlags&, FileAccess&)
        explicit MemBinFileRW(const ipl::string &p,
            const ReadWriteFlags &flags = ReadWriteFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write)
        {
            MemBinFileRW::open(p, flags, access);
        }

        /**
        * \brief
        *     open file at unicode path
        * \see
        *     MemBinFileR(const char*, const ReadWriteFlags&, FileAccess&)
        **/
        explicit MemBinFileRW(const osal::UnicodeString &ucs,
            const ReadWriteFlags &flags = ReadWriteFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write)
        {
            MemBinFileRW::open(ucs, flags, access);
        }

        /**
        * \brief
        *     Open the given BinTempFileRW for mem-based access
        * \see
        *     MemBinFileRW::open(BinTempFileRW&, const bool)
        * \errors
        *     none
        **/
        explicit MemBinFileRW(BinTempFileRW &tempfile,
            const bool auto_delete)
        {
            this->open(tempfile, auto_delete);
        }

        /**
        * \brief
        *     Opens the file located at \c p using \c flags
        * \return
        *     true on error, false on success
        * \errorindicator
        *     via isValid(), return code
        * \errors
        *     \see BinFileBase::open(const char*, OpenFlags&, FileAccess&)
        **/
        bool open(const char *p,
            const ReadWriteFlags &flags = ReadWriteFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write)
        {
            return MemBinFileBase::open(
                p, static_cast<OpenFlags>(flags), access);
        }

        //! \see MemBinFileRW::open(const char*, const ReadWriteFlags&, FileAccess&)
        bool open(const ipl::string &p,
            const ReadWriteFlags &flags = ReadWriteFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write)
        {
            return MemBinFileRW::open(p.c_str(), flags, access);
        }

        //! \brief Opens the given unicode path
        //! \see MemBinFileRW(const char*, const ReadWriteFlags&, FileAccess&)
        bool open(const osal::UnicodeString &ucs,
            const ReadWriteFlags &flags = ReadWriteFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write)
        {
            return MemBinFileBase::open(ucs, flags, access);
        }

        /**
        * \brief
        *     Open the given BinTempFileRW for mem-based access
        * \see
        *     BinFileBase::open(BinTempFileRW&, const bool)
        **/
        bool open(BinTempFileRW &tempfile, const bool auto_delete)
        {
            return MemBinFileBase::open(tempfile, auto_delete);
        }

        /**
        * \brief
        *     Create a memory mapping for the currently opened file

        *     A read-write memory mapping will be setup for the
        *     currently opened file. If \c executable is set to \c
        *     true then execution of the mapped contents is allowed.
        * \errorindicator
        *     via MemMapping.isValid() or returned object
        * \errors
        *     see MemBinFileBase::createMapping(const
        *     MemAccessFlags&, const size_t, const size_t)
        **/
        MemMapping createMapping(const size_t length, const size_t off,
            const bool executable = false,
            void *suggested_addr = NULL)
        {
            MemMapping::MemAccessFlags flags(true, true, executable);
            return MemBinFileBase::createMapping(flags, length,
                off, suggested_addr);
        }
    };

}  // end of namespace osal

#endif
