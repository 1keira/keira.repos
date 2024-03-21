/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_MEMBIFILER_HXX
#define OSAL_MEMBIFILER_HXX

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/MemBinFileBase.hxx>

namespace osal {

    /**
    * \brief
    *     Specialization of MemBinFileBase for read-only, memory mapped
    *     file-access

    *     Makes the API of MemBinFileBase accessible for read-only
    *     operations
    **/
    class MemBinFileR :
        public MemBinFileBase
    {
    public: // functions
        //! Constructs an invalid file. no error is raised.
        MemBinFileR() :
            MemBinFileBase()
        { }

        /**
        * \brief
        *     Open the file at path \c p using \c flags
        * \errorindicator
        *     via isValid()
        * \errors
        *     \see MemBinFileR::open(const char*, ReadFlags&, FileAccess&)
        **/
        MemBinFileR(const char *p,
            const ReadFlags &flags = ReadFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write)
        {
            MemBinFileR::open(p, flags, access);
        }

        //! \see MemBinFileR(const char*, const ReadFlags&, FileAccess&)
        MemBinFileR(const ipl::string &p,
            const ReadFlags &flags = ReadFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write)
        {
            MemBinFileR::open(p, flags, access);
        }

        //! \brief Open a file from a unicode path
        //! \see MemBinFile(const char*, const ReadFlags&, FileAccess&)
        MemBinFileR(const UnicodeString &ucs,
            const ReadFlags &flags = ReadFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write)
        {
            MemBinFileR::open(ucs, flags, access);
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
            const ReadFlags &flags = ReadFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write)
        {
            return MemBinFileBase::open(p,
                static_cast<OpenFlags>(flags), access);
        }

        //! \see MemBinFileR::open(const char*, const ReadFlags&, FileAccess&)
        bool open(const ipl::string &p,
            const ReadFlags &flags = ReadFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write)
        {
            return MemBinFileR::open(p.c_str(), flags, access);
        }

        //! \brief Open a file from a unicode path
        //! \see MemBinFileR::open(const char*, const ReadFlags&, FileAccess&)
        bool open(const osal::UnicodeString &ucs,
            const ReadFlags &flags = ReadFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write)
        {
            return MemBinFileBase::open(ucs, flags, access);
        }

        /**
        * \brief
        *     Create a memory mapping for the currently opened file

        *     A read-only memory mapping will be setup for the
        *     currently opened file. If \c executable is set to \c
        *     true then execution of the mapped contents is allowed.
        * \errorindicator
        *     via MemMapping.isValid() of returned object
        * \errors
        *     \see MemBinFileBase::createMapping(const
        *     MemAccessFlags&, const size_t, const size_t)
        **/
        MemMapping createMapping(const size_t length, const size_t off,
            const bool executable = false,
            void *suggested_addr = NULL)
        {
            MemMapping::MemAccessFlags flags(true, false, executable);
            return MemBinFileBase::createMapping(flags, length, off,
                suggested_addr);
        }
    };

}  // end of namespace osal

#endif
