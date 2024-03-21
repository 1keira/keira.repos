/*
      Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Bittner
*/

#ifndef COMM_LIFECYCLE_HXX
#define COMM_LIFECYCLE_HXX

/**
    \brief     This intefarce supports managing a life cycle.
            
            The lifecycle has three states: UNBORN, ALIVE and DEAD with the meaning:
            UNBORN: object is initialized, but not yet usable
            ALIVE: object is usable
            DEAD: object is not usable any more
            The object can go through the lifecycle only this way: UNBORN->ALIVE->DEAD or
            UNBORN->DEAD.
            A DEAD object cannot be revived.
**/

#include <comm/comm_dso.h>
#include <comm/commtypes.hxx>

namespace comm {

    class Lifecycle;

    /** \brief This interface provides notification of Lifecycle changes.
         
          See classes Proxy and ServiceRegistration on how to register for Lifecycle change events.
        If you register the same LifecycleListener for several Lifecycle instances, you
        can use the Lifecycle pointer returned in the alive and dead calls to check which one is
        affected.
        Be careful when calling methods of the Lifecycle object directly since (especially in
        shutdown scenarios) the Lifecycle object can be destroyed at any time and no guarantees
        are made that it still exists when the callback is called.

        The only possible life cycles are:
        1) UNBORN -> ALIVE -> DEAD
        2) UNBORN -> DEAD
    */

    class LifecycleListener {
        public:
            LifecycleListener() {}
            virtual ~LifecycleListener() {}
            /** \brief A Lifecycle object went alive.
                \param l the object that changed state.
                \param e the event with InstanceID, action and reason.
            */
            virtual void alive( Lifecycle* l, const ServiceEvent& e) = 0;

            /** \brief A Lifecycle object went dead.
                \param l the object that changed state.
                \param e the event with InstanceID, action and reason.
            */
            virtual void dead( Lifecycle* l, const ServiceEvent& e ) = 0;
    };

    /// The Lifecycle interface.
    class COMM_EXPORT Lifecycle  {
        public:
            enum State { UNBORN, ALIVE, DEAD };

            Lifecycle ()  {}
            
            virtual ~Lifecycle() {}

            /** Answers if this instance is in state ALIVE */
            virtual bool isAlive() const = 0;
             
            /** Answers if this instance us in state DEAD */
            virtual bool isDead()  const = 0;

            /**
                 \brief
                    Waits until the object goes into state DEAD.

                    Waits until the object goes into state DEAD.
            */
            virtual void waitUntilDead() = 0;

            /**
                 \brief
                    Waits until the object goes into state ALIVE.

                    Waits until the object goes into state ALIVE.
                    If the object transitions directly to state DEAD, true
                    is returned and an error is raised.
                \return
                    true on error, false otherwise.
                \errorindicator
                    via return code.
                \errors
                    comm::Error with ID OBJECT_IS_DEAD
            */
            virtual bool waitUntilAlive() = 0;

    };

}

#endif // COMM_LIFECYCLE_HXX

