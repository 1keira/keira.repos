/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

namespace osal
{

    inline void SharedObj::load(const osal::UnicodeString &ucs)
    {
        return this->load( ucs.nativeData() );
    }

}  // end of namespace osal
