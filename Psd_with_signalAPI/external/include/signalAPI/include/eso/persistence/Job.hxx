/*****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Martin Stein
*/
/*****************************************************************************/
#ifndef PERSISTENCE_JOB_HXX_
#define PERSISTENCE_JOB_HXX_
/*****************************************************************************/

#include <ipl_config.h>

#include <persistence/tracing.hxx>
#include <persistence/Event.hxx>
#include <util/sharedptr/SharedFromThisBase.hxx>
#include <common/types/string.hxx>

/*****************************************************************************/

namespace persistence {
    class Core;
}

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/

    class JobType {
    public:
        bool operator==(const JobType& other) const IPL_NOEXCEPT {
            return this == &other;
        }
        bool operator!=(const JobType& other) const IPL_NOEXCEPT {
            return this != &other;
        }
    };

/*****************************************************************************/

    class Job: public Event, public util::SharedFromThisBase<Job> {

    public:

        Job(Core &core, const ipl::string &description) IPL_NOEXCEPT:
            m_core(core), m_removeme(false), m_description(description) {}

        bool to_be_removed() const IPL_NOEXCEPT { return m_removeme; }

        virtual ipl::string toString() const IPL_NOEXCEPT;

        //! \brief Abort the job
        //!
        //! A transient (non-long-running, request-) Job does whatever cleanup
        //! needed before being deleted (e.g. replying) and returns \c true,
        //! a persistent (long-running, system-) job returns \c false.
        virtual bool abort() IPL_NOEXCEPT = 0;

        virtual void process(const util::SharedPtr<Job> &job) const IPL_NOEXCEPT;

        virtual void *cast(const JobType &type) IPL_NOEXCEPT=0;

        //! \brief Start the job's business
        virtual void start() IPL_NOEXCEPT = 0;

    protected:
        void removeme() IPL_NOEXCEPT { m_removeme=true; }

        Core       &m_core;
        bool        m_removeme;
        //! \brief To be returned by toString()
        ipl::string m_description;
    };

/*****************************************************************************/

}  // end of namespace persistence

/*****************************************************************************/
#endif
