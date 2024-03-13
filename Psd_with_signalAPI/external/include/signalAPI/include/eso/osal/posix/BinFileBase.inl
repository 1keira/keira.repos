/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

namespace osal {

    inline bool BinFileBase::open(const osal::UnicodeString &ucs,
                                  const OpenFlags &flags,
                                  const FileAccess &access)
    {
        // yeah! reuse!
        return BinFileBase::open(ucs.data(), flags, access);
    }

}  // end of namespace osal
