/*****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
*/
/*****************************************************************************/
#ifndef PERSISTENCELOCAL_HXX
#define PERSISTENCELOCAL_HXX
/*****************************************************************************/

#include <ipl_config.h>

#include <persistence/Core.hxx>
#include <persistence/EngineSQLite.hxx>
#include <persistence/EngineSQLite.hxx>
#include <persistence/PersistenceService.hxx>

#ifdef USE_IPERSISTENCE_B
#include <persistence/IPersistenceBService.hxx>
#else
#include <persistence/IPersistenceAService.hxx>
#endif

#include <persistence/WatchdogJob.hxx>
#include <persistence/FlushAll.hxx>

#include <osal/osal.hxx>
#include <osal/Mutex.hxx>
#include <osal/Condition.hxx>
#include <util/util.hxx>
#include <comm/commtypes.hxx>

/*****************************************************************************/

/*!
    Agent must already be started
*/

template <typename IPersistenceServiceType=persistence::IPersistenceAService>
class PersistenceLocal:
    public persistence::application::ConnectionListener,
    public persistence::WatchdogJob::Client,
    public persistence::FlushAll::Client
{
    
public:
    struct Config;
    
    PersistenceLocal(const Config &config) IPL_NOEXCEPT;
    
    //! \brief Get the instance id to connect to
    uint32_t instanceid() IPL_NOEXCEPT { return ipersistence.instanceid(); }

    //! \brief Pass your application's r/o state to this method
    //!
    //! \b Warning: You cannot write before you call with \c true!
    void write_allowed(bool allowed) IPL_NOEXCEPT {
        engine.fs_access(allowed?
                             persistence::Engine::FS_READ_WRITE :
                             persistence::Engine::FS_READ_ONLY);
    }
    
    //! \brief Big Shutdown Flush
    void flushAll() IPL_NOEXCEPT;

    //! \brief Gain watchdog information
    bool still_alive(unsigned timeout_ms) IPL_NOEXCEPT;
    
    /* Watchdog::Client *****************************************************/
    virtual void watchdogAlive() IPL_NOEXCEPT;
    
    /* FlushAll::Client *****************************************************/
    virtual void allFlushed() IPL_NOEXCEPT;
    
    static constexpr auto DEFAULT_INSTANCEID {comm::GENERATE_HANDLE};
    static constexpr auto DEFAULT_JOBS_WARN_LEVEL              {100};
    static constexpr auto DEFAULT_JOBS_ERROR_LEVEL             {150};
    static constexpr auto DEFAULT_EVENTS_WARN_LEVEL            {200};
    static constexpr auto DEFAULT_EVENTS_ERROR_LEVEL           {250};
    static constexpr auto UNLIMITED_DATACHUNK_SIZE               {0};
    static constexpr auto UNLIMITED_FILESIZE                     {0};
    static constexpr auto DEFAULT_BUSY_TIMEOUT_MS                {0};
    static constexpr auto DEFAULT_FS_WARN_TIMEOUT_MS         {15000};
    static constexpr auto DEFAULT_FS_CALLBACK_TIMEOUT_MS     {30000};
    static constexpr auto DEFAULT_FLUSH_CAT_WORKAROUND       {false};
    static constexpr auto DEFAULT_START_READWRITE            {false};

struct Config:
    public IPersistenceServiceType::Config,
    public persistence::Core::Config,
    public persistence::EngineSQLite::Config
    {

    Config(int32_t jobs_warn_level, int32_t jobs_error_level,
           int32_t events_warn_level, int32_t events_error_level,
           size_t max_datachunk_size,
           const ipl::string &filename, int filesize_max_kb,
           int busy_timeout_ms, uint32_t fs_warn_timeout_ms,
           uint32_t fs_callback_timeout_ms, bool flush_cat_workaround,
           bool start_readwrite) IPL_NOEXCEPT:
        IPersistenceServiceType::Config(),
        persistence::Core::Config(jobs_warn_level, jobs_error_level,
                                  events_warn_level, events_error_level,
                                  max_datachunk_size),
        persistence::EngineSQLite::Config(filename, filesize_max_kb,
                                          busy_timeout_ms, fs_warn_timeout_ms,
                                          fs_callback_timeout_ms,
                                          flush_cat_workaround, start_readwrite)
    {}

    Config() IPL_NOEXCEPT:
        IPersistenceServiceType::Config(),
        persistence::Core::Config(DEFAULT_JOBS_WARN_LEVEL, DEFAULT_JOBS_ERROR_LEVEL,
                                  DEFAULT_EVENTS_WARN_LEVEL, DEFAULT_EVENTS_ERROR_LEVEL,
                                  UNLIMITED_DATACHUNK_SIZE),
        persistence::EngineSQLite::Config("", UNLIMITED_FILESIZE,
                                          DEFAULT_BUSY_TIMEOUT_MS,
                                          DEFAULT_FS_WARN_TIMEOUT_MS,
                                          DEFAULT_FS_CALLBACK_TIMEOUT_MS,
                                          DEFAULT_FLUSH_CAT_WORKAROUND,
                                          DEFAULT_START_READWRITE)
    {}

    Config(const util::config::Value &config_root) IPL_NOEXCEPT:
        IPersistenceServiceType::Config(),
        persistence::Core::Config(DEFAULT_JOBS_WARN_LEVEL, DEFAULT_JOBS_ERROR_LEVEL,
                                  DEFAULT_EVENTS_WARN_LEVEL, DEFAULT_EVENTS_ERROR_LEVEL,
                                  UNLIMITED_DATACHUNK_SIZE),
        persistence::EngineSQLite::Config("", UNLIMITED_FILESIZE,
                                          DEFAULT_BUSY_TIMEOUT_MS,
                                          DEFAULT_FS_WARN_TIMEOUT_MS,
                                          DEFAULT_FS_CALLBACK_TIMEOUT_MS,
                                          DEFAULT_FLUSH_CAT_WORKAROUND,
                                          DEFAULT_START_READWRITE) {
        load(config_root);
    }

    void load(const util::config::Value &config_root) IPL_NOEXCEPT;
};
    
protected:
    osal::Osal osal;
    util::Util util;
    persistence::Core core;
    persistence::EngineSQLite::ProblemReporter dummy_reporter;
    persistence::EngineSQLite engine;
    comm::ActiveObjectFactoryPtr aoFactory;
    persistence::PersistenceService persistence_service;
    IPersistenceServiceType ipersistence;
    util::SharedPtr<persistence::WatchdogJob> watchdog;
    
    osal::Mutex mutex;
    osal::Condition condition;
    bool alive;
    bool flushed;
};

/*****************************************************************************/
#endif
