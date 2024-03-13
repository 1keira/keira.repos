/*****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Martin Stein
*/
/*****************************************************************************/
#ifndef PERSISTENCE_EVENT_HXX_
#define PERSISTENCE_EVENT_HXX_
/*****************************************************************************/

#include <ipl_config.h>

#include <common/types/string.hxx>
#include <util/SharedPtr.hxx>

/*****************************************************************************/

namespace persistence {
    class Job;
}

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/

    class Event {
    public:
        virtual ~Event() IPL_NOEXCEPT {}
        virtual ipl::string toString() const IPL_NOEXCEPT = 0;
        virtual void process(const util::SharedPtr<Job> &job) const IPL_NOEXCEPT = 0;
        //! \brief Do whatever needs to be done to clean up before being deleted
        //!
        //! Return whether the Event can be deleted now.
        virtual bool abort() IPL_NOEXCEPT = 0;
    };

/*****************************************************************************/

}  // end of namespace persistence

/*****************************************************************************/
#endif
