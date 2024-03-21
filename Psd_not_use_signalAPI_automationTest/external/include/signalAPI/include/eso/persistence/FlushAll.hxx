/*****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
*/
/*****************************************************************************/
#ifndef PERSISTENCE_FLUSHALL_HXX
#define PERSISTENCE_FLUSHALL_HXX
/*****************************************************************************/

#include <ipl_config.h>

#include <persistence/Core.hxx>
#include <persistence/Engine.hxx>

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/

    class FlushAll: public Engine::Job {

    public:
        
        class Client;
        
        FlushAll(Core &core, Engine &engine, Client &client) IPL_NOEXCEPT:
            Engine::Job(core, "FlushAll"),
            engine(engine), client(client), flushs_pending(0) {}

        virtual bool abort() IPL_NOEXCEPT;
        virtual void start() IPL_NOEXCEPT;
        virtual void allFlushed() IPL_NOEXCEPT;

    protected:
        Engine &engine;
        Client &client;
        unsigned flushs_pending;
    };
    
/*****************************************************************************/

    class FlushAll::Client {
        
    public:
        virtual ~Client() IPL_NOEXCEPT;
        
        virtual void allFlushed() IPL_NOEXCEPT=0;
    };
    
/*****************************************************************************/

}  // end of namespace persistence

/*****************************************************************************/
#endif
