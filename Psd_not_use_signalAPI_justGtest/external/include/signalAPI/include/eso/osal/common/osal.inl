/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

namespace osal {

    inline Osal::~Osal()
    {
        IPL_ASSERT( s_initialized );

        if( !(--s_init_count) && s_initialized )
        {
            this->cleanupAll();
        }
    }

}  // end of namespace osal
