/*****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Martin Stein
*/
/*****************************************************************************/
#ifndef PERSISTENCE_TNG_ENGINESQLITE_HXX
#define PERSISTENCE_TNG_ENGINESQLITE_HXX
/*****************************************************************************/

#include <ipl_config.h>

#include <persistence/Engine.hxx>
#include <persistence/WorkerThread.hxx>
#include <persistence/SQLite.hxx>
#include <persistence/tracing.hxx>
#include <osal/Timer.hxx>
#include <osal/Mutex.hxx>
#include <common/types/list.hxx>
#include <common/types/string.hxx>

/*****************************************************************************/

IPL_TRACE_DECLARE_CHANNEL_EXTERN(FW_PERSISTENCE_BACKEND_SQLITE);

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/

    /*!
        \brief Persistence engine based on SQLite
    */
    class EngineSQLite: public Engine, public WorkerThread::Observer {

    public:

        class Partition;             // in .cxx
        class Conversion;            // in .cxx
        class VersionJob;            // in .cxx
        class PurgeJob;              // in .cxx
        class CopyJob;               // in .cxx
        class Fs_accessJob;          // in .cxx
        class FlushAllJob;           // in .cxx
        class RequestPartitionJob;   // in .cxx
        class RequestConversionJob;  // in .cxx
        class FlushJob;              // in .cxx
        class DestructPartitionJob;  // in .cxx
        class Factory;
        struct Config;

//         //! \brief Interface that gets notified when filesystem access takes long
//         class FsObserver {
//
//         public:
//             virtual ~FsObserver();  //!< \brief Just to make the compiler happy...
//             virtual void still_working(const ipl::string &what, uint32_t how_long_ms)=0;
//         };

        //! \brief Interface that gets notified when problems occur
        //!
        //! The default implementation does nothing.
        class ProblemReporter: public SQLite::ProblemReporter {

        public:
            //! \brief Some job (\a what) takes way too much time (\a how_long_ms)
            virtual void sqlite_still_working(const ipl::string &what, uint32_t how_long_ms) IPL_NOEXCEPT;
            //! \brief Some stored data is damaged (cannot be deserialized)
            virtual void sqlite_data_damaged(const ipl::string &partition, const ipl::string &key, const ipl::string &reason) IPL_NOEXCEPT;
        };

        EngineSQLite(/*FsObserver *fs_observer,*/ ProblemReporter &reporter,
                     Core &report_to_this_watchdog, size_t max_datachunk_size,
                     const Config &config) IPL_NOEXCEPT;

        virtual Core::Seqnum requestPartition(Core &core,
                                              const Name &partition,
                                              const Version &version) IPL_NOEXCEPT;
        virtual Core::Seqnum requestConversion(Core &core,
                                               const Name &partition,
                                               const Version &from_version,
                                               const Version &to_version) IPL_NOEXCEPT;
        virtual Core::Seqnum purge(Core &core, const Name &partition) IPL_NOEXCEPT;
        virtual Core::Seqnum version(Core &core, const Name &partition) IPL_NOEXCEPT;

        virtual void fs_access(FsAccess access) IPL_NOEXCEPT;
        virtual unsigned flushAll(Core &core) IPL_NOEXCEPT;

        virtual void currentJob(void *thread, void *job) IPL_NOEXCEPT;

    protected:

        // WARNING: This is part of the database's internal format and
        // MUST NOT CHANGE IN ANY CASE WHATSOEVER!
        enum Type {
            NONE=0,  //!< \brief Guaranteed to evaluate to false
            INT,
            STRING,
            INT_LIST_obsolete_but_we_need_to_retain_the_number,
            STRING_LIST_obsolete_but_we_need_to_retain_the_number,
            BLOB
        };

        friend class Partition;

        class FsTimer: public osal::Timer {

        public:
            //! \brief \a timeout_ms==0 means no timer
            FsTimer(uint32_t timeout_ms) IPL_NOEXCEPT:
                Timer(timer_rings, false), m_timeout_ms(timeout_ms) {}

            void start(const ipl::string &blame) IPL_NOEXCEPT;

        protected:
            static void timer_rings(osal::Timer *p) IPL_NOEXCEPT;
            virtual void complain() IPL_NOEXCEPT;

            osal::Mutex m_mutex;
            uint32_t m_timeout_ms;
            ipl::string m_blame;

        } m_fs_timer;  //!< \brief \b Warning: Do not use from core thread!

        class FsCallbackTimer: public FsTimer {

        public:
            FsCallbackTimer(/*FsObserver *observer*/ProblemReporter &reporter,
                            uint32_t timeout_ms) IPL_NOEXCEPT:
                FsTimer(timeout_ms), /*m_observer(observer)*/m_reporter(reporter) {}

        protected:
            virtual void complain() IPL_NOEXCEPT;

            //FsObserver *m_observer;
            ProblemReporter &m_reporter;
        } m_fs_callback_timer;  //!< \brief \b Warning: Do not use from core thread!

        ProblemReporter &m_reporter;

        //! \brief \b Warning: Do not access from the core thread!
        SQLite m_sqlite;

        typedef ipl::map<Name, util::WeakPtr<Partition> > Partitions;
        //! \brief \b Warning: Do not access from the core thread!
        Partitions m_partitions;

        const bool m_flush_cat_workaround;  //!< \brief enable cat after flushall
        const ipl::string m_filename;  //!< \brief only needed for cat after flushall
        const size_t m_max_datachunk_size;

        WorkerThread m_workerthread;
        Core &m_report_to_this_watchdog;
    };

/*****************************************************************************/

    /*!
        \brief Factory to create an EngineSQLite instance using the given configuration
    */
    class EngineSQLite::Factory : public Engine::Factory {

    public:
        Factory(/*FsObserver *fs_observer=NULL*/ProblemReporter &reporter) IPL_NOEXCEPT:
            /*m_fs_observer(fs_observer)*/m_reporter(reporter) {}
        ~Factory() IPL_NOEXCEPT;

        virtual Engine *createEngine(Core &core,
                                     const ipl::string &backend_name,
                                     const util::config::Value &config_array) IPL_NOEXCEPT;

    private:
        typedef ipl::map<ipl::string, EngineSQLite *> Engines;
        Engines m_engines;
        //FsObserver *m_fs_observer;
        ProblemReporter &m_reporter;
    };

/*****************************************************************************/

    struct EngineSQLite::Config {
        ipl::string type_name{};
        ipl::string filename{};
        int filesize_max_kb{0};
        int busy_timeout_ms{30000};
        int fs_warn_timeout_ms{0};
        int fs_callback_timeout_ms{0};
        bool flush_cat_workaround{false};
        bool start_readwrite{false};
        
        Config()=default;
        Config(const ipl::string &filename, int filesize_max_kb,
               int busy_timeout_ms, uint32_t fs_warn_timeout_ms,
               uint32_t fs_callback_timeout_ms,
               bool flush_cat_workaround, bool start_readwrite) IPL_NOEXCEPT:
            filename(filename), filesize_max_kb(filesize_max_kb),
            busy_timeout_ms(busy_timeout_ms),
            fs_warn_timeout_ms(fs_warn_timeout_ms),
            fs_callback_timeout_ms(fs_callback_timeout_ms),
            flush_cat_workaround(flush_cat_workaround),
            start_readwrite(start_readwrite) {}
        Config(const util::config::Value &config_array) IPL_NOEXCEPT {
            load(config_array);
        }
        
        void load(const util::config::Value &config_array) IPL_NOEXCEPT;
    };

/*****************************************************************************/

}  // end of namespace persistence

/*****************************************************************************/
#endif
