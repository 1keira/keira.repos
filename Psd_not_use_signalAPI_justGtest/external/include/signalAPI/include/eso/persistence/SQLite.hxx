/*****************************************************************************/
/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
    $Id$
*/
/*****************************************************************************/
#ifndef PERSISTENCE_TNG_SQLITE_HXX
#define PERSISTENCE_TNG_SQLITE_HXX
/*****************************************************************************/

#include <ipl_config.h>

#include <persistence/Engine.hxx>

#include <persistence/Utf8String.hxx>
#include <util/transport/Readable.hxx>
//#include <util/config/Values.hxx>
#include <common/streams/sstream.hxx>  // TODO: --> .cxx

#include <persistence/Blob.hxx>  // for XxxIpl
#include <common/types/map.hxx>

#ifdef ERROR
#undef ERROR  // Window$ strikes again...
#endif

/*****************************************************************************/

struct sqlite3;

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/

    /*!
        \internal
        \brief Restricted wrapper around one sqlite3 database connection

        This is not a generalized C++ binding for sqlite3.
        It is rather specialized for what's needed within persistence.
    */
    class SQLite {

    protected:
        class Statement;  //!< \internal

    public:
//        class BusySleeper;

        //! \internal
        struct Null {};

        //! \brief Interface that gets notified when problems occur
        //!
        //! The default implementation does nothing.
        class ProblemReporter {

        public:
            //! \brief Just to make the compiler happy...
            virtual ~ProblemReporter() IPL_NOEXCEPT;

            //! \brief The database file is damaged (sanity check failed)
            virtual void sqlite_db_damaged(const ipl::string &filename,
                                           const ipl::string &reason) IPL_NOEXCEPT;
        };

        class Client;
        //! \brief What is needed to properly answer asynchronously
        struct Context: public Engine::Context {
            Client &client;

            Context(const Engine::Context &context, Client &client) IPL_NOEXCEPT:
                Engine::Context(context), client(client) {}
        };

        class Savepoint;
        class Shadow;
        class Journal;
//        class Config;

        //! \brief Opaque handle for a partition
        class Partition {
            friend class SQLite;
            Partition(int64_t id): id(id) {}
            //! \brief Evaluates \c false on error
            int64_t id;
        public:
            Partition() IPL_NOEXCEPT: id(0) {}
            operator bool () const IPL_NOEXCEPT { return id; }
            operator int64_t () const IPL_NOEXCEPT { return id; }
            bool operator < (const Partition &other) const IPL_NOEXCEPT { return id<other.id; }
        };

        typedef int64_t Int;        // TODO
        typedef Utf8String String;  // TODO

//        typedef String Filename;

        SQLite(ProblemReporter &problem_reporter,
               /*Filename*/const char *sqlite_file,
               int filesize_max_kb,
               int busy_timeout_ms,
               bool report_status=false,
               int32_t status_interval_ms=0,
               int32_t status_skip=0,
               int32_t memory_limit=0,
               int32_t memsys=1,
               bool autodelete=true/*,
               BusySleeper &sleeper=NON_SLEEPER,
               bool use_memory_tables=true*/) IPL_NOEXCEPT;
        ~SQLite() IPL_NOEXCEPT;

        void closeDbHack() IPL_NOEXCEPT;
        void dumpLastModeHack() IPL_NOEXCEPT;

        void shutdown() IPL_NOEXCEPT;
        //! \brief Initialize until operable (idempotently)
        //! \return \c true on error
        bool ensure_usable() IPL_NOEXCEPT;
        //! \brief Perform SQLite's PRAGMA integrity_check
        //! \return Whether it failed
        bool integrity_check() IPL_NOEXCEPT;
        //! \brief Create database tables (idempotently)
        //! \return \c true on error
        bool ensure_tables() IPL_NOEXCEPT;
        //! \brief \b Must be called before sanity_check(), returns true when
        //! the tables don't exist and hence serves as test
        bool init_sanity_check() IPL_NOEXCEPT;
        //! \brief Perform some sanity check over the database
        //! \return Whether it failed
        bool sanity_check() IPL_NOEXCEPT;

        //! \brief Is the database operable?
        bool can_use() const IPL_NOEXCEPT;
        //! \brief Is the database operable and initialized so we can
        //!  actually access data?
        bool can_read() /*const*/ IPL_NOEXCEPT;

        bool getVersion(const Engine::Name &partition, String &version) IPL_NOEXCEPT;
        bool remove(const Engine::Name &partition) IPL_NOEXCEPT;

//        static BusySleeper NON_SLEEPER;

        volatile bool write_allowed;  //!< \brief Enables filesystem write access

    protected:

        class Reporter {

        public:
            Reporter(bool active, int32_t interval_ms, int32_t skip) IPL_NOEXCEPT:
                m_active(active), m_interval_ms(interval_ms), m_skip(skip),
                m_last_report(0), m_reports_skipped(0) {}

            void report_status() IPL_NOEXCEPT;

        protected:
            bool m_active;
            unsigned m_interval_ms;
            unsigned m_skip;
            osal::TimeT m_last_report;
            unsigned m_reports_skipped;
        };

        void emergency_delete(const ipl::string &reason) IPL_NOEXCEPT;

        /*Filename*/ ipl::string m_sqlite_file;
        sqlite3 *m_sqlite;
        ProblemReporter &m_problem_reporter;
        Reporter m_reporter;

        int m_filesize_max_kb;
        int m_busy_timeout_ms;
        unsigned m_memory_limit;
        unsigned m_memsys;

        bool m_autodelete;

//        BusySleeper &m_busy_sleeper;

        Statement *m_sql_sanity_check;
    };

/*****************************************************************************/

   //! \brief Magic object to denote SQL's \c %NULL
   extern SQLite::Null SQL_NULL;

/*****************************************************************************/

//    //! \internal
//    class SQLite::BusySleeper {
//
//    public:
//        BusySleeper(int timeout_ms=0) IPL_NOEXCEPT: m_timeout_ms(timeout_ms) {}
//
//        void stop_trying() IPL_NOEXCEPT { m_timeout_ms=0; }
//
//        static int busy_handler(void *p, int count) IPL_NOEXCEPT;
//
//    protected:
//        int m_timeout_ms;
//    };

/*****************************************************************************/

    /*!
        \brief Callback interface for users of an SQLite
    */
    class SQLite::Client {

    public:
        virtual ~Client() IPL_NOEXCEPT;  //!< \brief Just to make the compiler happy...

        virtual void ok(const Engine::Context &context) IPL_NOEXCEPT=0;
        virtual void error(const Engine::Context &context,
                           const ipl::string &reason) IPL_NOEXCEPT=0;
        virtual void notfound(const Engine::Context &context,
                              const Engine::Key &key) IPL_NOEXCEPT=0;
        virtual void notfound(const Engine::Key &key) IPL_NOEXCEPT=0;
        virtual void value(const Engine::Context &context,
                           const Engine::Key &key, int type, const Blob &buf) IPL_NOEXCEPT=0;
        virtual void value(const Engine::Key &key, int type, const Blob &buf) IPL_NOEXCEPT=0;
        virtual void endOfValues() IPL_NOEXCEPT=0;
        virtual void keys(const Engine::Context &context, const Engine::KeyList& keys) IPL_NOEXCEPT=0;
    };


/*****************************************************************************/

    //! \brief Transaction guard
    //!
    //! Represents a hierarchical database transaction.
    class SQLite::Savepoint {

    public:
        Savepoint(SQLite &sqlite/*, const ipl::string &name*/, bool &ok) IPL_NOEXCEPT;
        ~Savepoint() IPL_NOEXCEPT;

        operator bool () const IPL_NOEXCEPT { return m_ok; }

    protected:
        SQLite     &m_sqlite;
        //ipl::string m_name;
        bool       &m_ok;
    };

/*****************************************************************************/

    //! \brief In-memory copy of one partition's data
    class SQLite::Shadow {

        struct Entry {
            int type;  //!< This field stores the value type, it evaluates to false for entries that are deleted, see EngineSQLite::Type
            ReadableBlob value;
            bool clean;  //!< true if value-and-type in shadow-memory equal value-and-type in sqlite3-database
            //! \brief "deleted" entry
            Entry() IPL_NOEXCEPT: type(0) /* Assumes Engine knowledge */, clean(false) {}
            Entry(int type, const ReadableBlob &value) IPL_NOEXCEPT: type(type), value(value), clean(false) {}
            Entry(const Entry &other) IPL_NOEXCEPT: type(other.type), value(other.value), clean(false) {}
            Entry &operator = (const Entry &other) IPL_NOEXCEPT {
                if (this != &other) {
                    type=other.type;
                    value=(const Blob::Readable &)other.value;
                    clean=false;
                }
                return *this;
            }
        };
        friend class Journal;

    public:
        //! \a max_bytes limits the size of data read from the database.
        //! If it's 0, there is no limit, else any datum approximated bigger
        //! than the limit will silently replaced by something empty.
        Shadow(const Context &context, SQLite &sqlite,
               const Engine::Name &name, const String &requested_version,
               size_t max_bytes=0) IPL_NOEXCEPT;
        Shadow(const Shadow &other) IPL_NOEXCEPT;
        ~Shadow() IPL_NOEXCEPT;

        void flush_to(const Context *context, const Engine::Name &name) IPL_NOEXCEPT;
        void flush_to(const Context &context, const Engine::Name &name) IPL_NOEXCEPT {
            flush_to(&context, name);
        }
        void flush(const Context *context=NULL) IPL_NOEXCEPT { flush_to(context, m_name); }
        void flush(const Context &context) IPL_NOEXCEPT { flush(&context); }
        void get(const Context &context, const Engine::Key &key) IPL_NOEXCEPT;
        //! \return existing keys, keys marked as deleted are filtered
        void get_keys(const Context &context) IPL_NOEXCEPT;

        const String &version() const IPL_NOEXCEPT { return m_version; }

    protected:
        SQLite      &m_sqlite;
        Engine::Name m_name;
        bool         m_clean;
        Reporter    &m_reporter;
        String       m_version;

        Engine::KeyList get_existing_keys() IPL_NOEXCEPT;

        typedef ipl::map<Int, Entry> EntriesByInt;
        EntriesByInt m_entries_by_int;
        typedef ipl::map<String, Entry> EntriesByString;
        EntriesByString m_entries_by_string;
    };

/*****************************************************************************/

    //! \brief Log of changes to be applied to a Shadow atomically
    class SQLite::Journal {

    public:

        Journal(Shadow &shadow, const String &to_version) IPL_NOEXCEPT;

        void commit(const Context &context) IPL_NOEXCEPT;
        void purge(const Context &context) IPL_NOEXCEPT;
        void put(const Context &context, const Engine::Key &key,
                 int type, const Blob &value) IPL_NOEXCEPT;
        /*!
        \brief    remove the value indentified by the given key
        \return    true on failure (e.g. does not exist), false on success
        */
        bool remove(const Context &context, const Engine::Key &key) IPL_NOEXCEPT;
        /*! \brief Clears all pending changes and creates a remove request for each existing key in shadow */
        void removeAll(const Context &context) IPL_NOEXCEPT;

    protected:
        String m_version;
        Shadow &m_shadow;
        typedef Shadow::Entry Entry;
        typedef Shadow::EntriesByInt EntriesByInt;
        EntriesByInt m_entries_by_int;
        typedef Shadow::EntriesByString EntriesByString;
        EntriesByString m_entries_by_string;
    };

/*****************************************************************************/

//    /*!
//        \brief Convenient set of config options needed for an SQLite
//
//        This is separate from SQLite construction to allow
//        for maximum flexibility, i.e. you can use SQLite
//        with mixed configurations or with no configuration at all.
//    */
//    class SQLite::Config {
//
//    public:
//        Config(const util::config::Value &proc_root) IPL_NOEXCEPT;
//
//        bool report;
//        int32_t status_interval_ms;
//        int32_t status_skip;
//        int32_t memory_limit;
//        int32_t memsys;
//        bool autodelete;  // ugly hack
//        bool memory_tables;
//
//    protected:
//        bool reap(const util::config::Value &proc_root) IPL_NOEXCEPT;
//    };

/*****************************************************************************/

}  // end of namespace persistence

/*****************************************************************************/
#endif
