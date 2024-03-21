/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef TRACING_CLOCKSOURCELOADER_HXX
#define TRACING_CLOCKSOURCELOADER_HXX

#include <osal/SharedObj.hxx>
#include <common/types/string.hxx>
#include <common/types/map.hxx>
#include <tracing/clocksource/IClockSource.hxx>
#include <tracing/clocksource/ClockSource_dso.hxx>
#include <tracing/Error.hxx>
#include <tracing/util/Common.hxx>
#include <tracing/util/TraceMe.hxx>

namespace tracing
{
/*!
*    \brief
*        Provides functionality to load clocksource plugins for the trace system.
*
*        Besides a set of platform specific clocksources also externally provided
*        clocksources can be loaded.
*        When the configured clocksource is not available a platform and project dependent
*        default clocksource is selected.
*
*        This class follows the same architecture as PluginLoader
*/

class ClockSourceLoader
{
public:

    friend class ClockBoottimeInitializer;
    friend class ClockCpuInitializer;
    friend class ClockLocalInitializer;
    friend class ClockMonoBootInitializer;
    friend class ClockMonoCpuInitializer;
    friend class ClockMonotonicInitializer;
    friend class ClockOsalInitializer;
    friend class ClockRealtimeInitializer;

    static const char * IPL_CLOCKSOURCE_SYMBOL;

public:
    //! \brief Default constructor.
    ClockSourceLoader();
    //! \brief Default destructor.
    ~ClockSourceLoader() = default;

    /*!
     *  \brief
     *      Returns a clocksource.
     *  \param
     *      name The clocksource name.
     *  \param
     *      fallback Flag to indicate if a fallback clocksource shall be provided
     *               in case of initial failure.
     *  \return
     *      The clocksource instance or nullptr in case of failure
     */
    IClockSource * getClockSource(const std::string &name, bool fallback=true);

    /*!
     *  \brief
     *      Initializes the clocksource loader.
     *  \param
     *      name Optional clocksource name.
     *  \param
     *      directory The plugins directory.
     */
    void init(const std::string & name = "",
              const std::string & directory = "");

    //! \brief Indication if plugins directory is valid.
    bool isValid() const
    {
        return m_valid;
    }

    /*!
     *  \brief
     *      Adds a clocksource factory to the trace system.
     *  \param
     *      name A unique clock source name.
     *  \param
     *      create The factory creation method.
     *  \param
     *      destroy The destroy method.
     */
    void addClockSourceFactory(ClockSourceName name,
            ClockSourceCreate create,
            ClockSourceDestroy destroy);

protected:
    //! \brief Evaluates if a given directory is valid.
    static bool isDirectoryValid(const std::string & directory);

    /*!
    *    \brief
    *        Searches for the clocksource factory with given name.
    *        If it cannot be found in the internal clocksource list the search
    *        is extended for the related loadable plugin in the configured directory.
    */
    template<typename T> T* getPlugin(std::map<std::string, T *> & type,
                                      const char * symbol, const std::string & name);

    //! \brief Provides the factory for the clocksource with given name
    struct ClockSourceFactory * loadClockSourcePlugin(const ipl::string & name)
    {
        struct ClockSourceFactory * factory =
                getPlugin<ClockSourceFactory>(m_clocksource_factories,
                                              IPL_CLOCKSOURCE_SYMBOL, name);
        if (!factory)
            ipl_error.ack();
        return factory;
    }

    //! \brief Searches for the clocksource factory with given name in the list of
    //!       already available factories.
    struct ClockSourceFactory * getClockSourcePlugin(const ipl::string & name)
    {
        auto it = m_clocksource_factories.find(name);
        if (it != m_clocksource_factories.end())
        {
            return it->second;
        }
        return nullptr;
    }

protected:
    //! The directory where clock source plugins should be searched.
    ipl::string m_directory;
    bool m_valid;

    //! \brief Contains clock sources found at startup.
    ipl::map<ipl::string, struct ClockSourceFactory *> m_clocksource_factories;
    //! \brief Contains references to any loaded shared clock source lib.
    std::vector<osal::SharedObj> m_loaded_libs;
    //! \brief TraceMe client channel
    IPL_TRACEME_DECLARE_SCOPE(ClockSourceLoader);

    /*!
     *    \brief
     *        A helper class for builtin clock sources.
     */
    class InternalClockSourceList
    {
    public:
        //! \brief Get the instance of the internal clocksource list.
        static InternalClockSourceList & getInstance()
        {
            static InternalClockSourceList instance;
            return instance;
        }

        /*!
         *  \brief
         *      Adds a builtin clocksource factory.
         *  \param
         *      name A unique clock source name.
         *  \param
         *      create The factory creation method.
         *  \param
         *      destroy The destroy method.
         */
        void addClockSourceFactory(ClockSourceName name, ClockSourceCreate create,
                                   ClockSourceDestroy destroy);

        //! \brief Provides the clocksource loader instance.
        void setInitialized(ClockSourceLoader * loader)
        {
            m_loader = loader;
        }

        //! \brief Indicates if the clocksource loader is valid.
        bool isInitialized() const
        {
            return m_loader != nullptr;
        }

        //! \brief Removes the clocksource factory with matching name from internal
        //!        list and deletes it.
        void removeMe(const char * name);

        std::map<std::string, struct ClockSourceFactory *> m_factories;

    protected:
        friend ClockSourceLoader;
        std::vector<std::string> m_prio_list;
        InternalClockSourceList() : m_loader(nullptr) {/* nop */}
        ClockSourceLoader * m_loader;
    }; //end of class InternalClockSourceList

}; //end of class ClockSourceLoader
}//end of namespace tracing

#endif //#define TRACING_CLOCKSOURCELOADER_HXX
