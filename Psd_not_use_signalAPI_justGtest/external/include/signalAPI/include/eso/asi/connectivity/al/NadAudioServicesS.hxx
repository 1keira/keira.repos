/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADAUDIOSERVICESS_HXX
#define ASI_CONNECTIVITY_AL_NADAUDIOSERVICESS_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/al/NadAudioServicesServiceRegistration.hxx>
#include <asi/connectivity/al/StructAudioScenario.hxx>

#include <asi/connectivity/al/Definitions.hxx>

#include <asi/connectivity/al/NadAudioServicesProxyReply.hxx>
#include <asi/connectivity/al/NadAudioServicesReplyS.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief  The al::NadAudioServices interface on tthe service side.
    \details
            A service instance needs to implement this interface.
    **/
    class NadAudioServicesS
    {
    public:
        NadAudioServicesS () {}
    // List of request methods
        /**
            *
         * Playback
         * @param audioFile, the file, which should be played back.
         
            startPlayback Method ID: 12
        **/
        virtual void startPlayback(
            const CIPtr< CIString >& audioFile
            ,NadAudioServicesProxyReply& reply
        ) = 0;
        /**
            stopPlayback Method ID: 16
        **/
        virtual void stopPlayback(
            
            NadAudioServicesProxyReply& reply
        ) = 0;
        /**
            *
         * Records
         * @param recordingFile, the file, which stores the recording.
         
            startRecording Method ID: 14
        **/
        virtual void startRecording(
            const CIPtr< CIString >& recordingFile
            ,NadAudioServicesProxyReply& reply
        ) = 0;
        /**
            stopRecording Method ID: 18
        **/
        virtual void stopRecording(
            
            NadAudioServicesProxyReply& reply
        ) = 0;
        /**
            loadAudioConfiguration Method ID: 0
        **/
        virtual void loadAudioConfiguration(
            const CIPtr< CIString >& file
            ,NadAudioServicesProxyReply& reply
        ) = 0;
        /**
            setAudioScenario Method ID: 2
        **/
        virtual void setAudioScenario(
            const CIPtr< asi::connectivity::al::AudioScenario >& scenario
            ,NadAudioServicesProxyReply& reply
        ) = 0;
        /**
            setSpeakerLevel Method ID: 8
        **/
        virtual void setSpeakerLevel(
            const int32_t level
            ,NadAudioServicesProxyReply& reply
        ) = 0;
        /**
            setMicLevel Method ID: 4
        **/
        virtual void setMicLevel(
            const int32_t level
            ,NadAudioServicesProxyReply& reply
        ) = 0;
        /**
            *
        * Mute or unmute the microphone and speakers.
        
            setMuteState Method ID: 6
        **/
        virtual void setMuteState(
            const bool mute
            ,NadAudioServicesProxyReply& reply
        ) = 0;
        /**
            *
        * Enable or disable the wideband capability for voice calls.
        * @param onoff if true wideband is enabled, if false wideband is disabled.
        
            setWideband Method ID: 10
        **/
        virtual void setWideband(
            const bool onoff
            ,NadAudioServicesProxyReply& reply
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        \param reply A proxy that can be used to reply to the connected client. If the client did
        not register its reply interface, calling valid() or isAlive() on reply will return false.
        In this case calling any other methods of the proxy will yield in undefined behaviour.
        */
        virtual void clientConnected(uint32_t count
            ,NadAudioServicesProxyReply& reply
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        \param reply The proxy to the disconnected client. It is not alive any more, but can be used for comparison
        if it ever was valid.
        */
        virtual void clientDisconnected(uint32_t count
            ,NadAudioServicesProxyReply& reply
        ) {}

        /*!
        \brief  Registers this service instance.
        \param  instance_no is the instance number for the service.
        \param  p a user provided ActiveObject factory. This gives control over the threads that call the service.
        \return false on success, true on error
        \errorindicator
                return code
        \errors
                any possible error generated from COMM
        */
        bool registerSelf(uint32_t instance_no, const comm::ActiveObjectFactoryPtr& factory, comm::LifecycleListener* l=nullptr)
        {
            if (m_registration.isAlive()) {
                ipl_raise(comm::Error, comm::error::SELF_ALREADY_REGISTERED
                            ,((ipl::string)m_registration.getInstanceID()).c_str());
                return true;
            }

            m_registration =
                NadAudioServicesServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_NADAUDIOSERVICES_REQUEST), instance_no), static_cast<NadAudioServicesS*>(this), l, factory );
            if (!m_registration.valid()) {
                comm::error::fatal( "can't create ServiceRegistration, OOM ", COMM_HERE);
                return true;
            }
            return m_registration.registerService();
        }

        /*!
        \brief  Registers this service instance.
        \param  instance_no is the instance number for the service interface.
        \param  l is the lifecycle listern instance
        \return false on success, true on error
        \errorindicator
                return code
        \errors
                any possible error generated from COMM
        */
        bool registerSelf(uint32_t instance_no, comm::LifecycleListener* l=nullptr)
        {
            if (m_registration.isAlive()) {
                ipl_raise(comm::Error, comm::error::SELF_ALREADY_REGISTERED
                            ,((ipl::string)m_registration.getInstanceID()).c_str());
                return true;
            }

            m_registration =
                NadAudioServicesServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_NADAUDIOSERVICES_REQUEST), instance_no), static_cast<NadAudioServicesS*>(this), l );
            if (!m_registration.valid()) {
                comm::error::fatal( "can't create ServiceRegistration, OOM ", COMM_HERE);
                return true;
            }
            return m_registration.registerService();
        }

        /*!
        \brief  Registers this service instance.
        \param  instance_no is the instance number for the service interface
        \param  l is the lifecycle listern instance
        \return false on success, true on error
        \errorindicator
                return code
        \errors
                any possible error generated from COMM
        */
        bool registerSelf(uint32_t instance_no, comm::LifecycleListener& l)
        {
            return registerSelf (instance_no, &l);
        }

        /*!
        \brief  Unregisters this service instance.
        \return false on success, true on error
        \errorindicator
                return code
        \errors
                none
        */
        bool unregisterSelf()
        {
            if (!m_registration.isAlive()) {
                // not registered -> nothing to do.
                return false;
            }
            m_registration.unregisterService();
            // must not be alive after unregistration
            IPL_ASSERT(!m_registration.isAlive());
            // let go of the reference
            m_registration = NadAudioServicesServiceRegistration();
            return false;
        }

        /*!
        \brief  Unregisters this service instance and calls a callback.
        \return false if the service is being unregistered, true on error
                The callback is called only if false is returned.
                Errors are:
                <ul>
                <li>the service registration is not valid
                <li>an unregisterSelf() or ServiceRegistration::unregisterService() or
                    or ServiceRegistration::unregisterAndNotify had already been called.
                <li>the callback is NULL.
                </ul>
        \errorindicator
                return code
        \errors
                \see comm::ServiceRegistration::unregisterAndNotify
        */
        bool unregisterSelf(comm::ServiceReleasedFct callback, void* ctx) // NOSONAR - must not be changed because of API compatibility
        {
            // to not race with the callback. we can't touch m_registration after
            // calling unregisterAndNotify
            // make a temporary copy
            NadAudioServicesServiceRegistration tmp{m_registration};
            // let go of the reference the member holds
            m_registration = NadAudioServicesServiceRegistration();
            // call unregisterAndNotify
            return tmp.unregisterAndNotify(callback, ctx);
        }

        virtual ~NadAudioServicesS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        startPlaybackCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 12;
            ce.assign(inst, mid);
        }
        void
        stopPlaybackCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 16;
            ce.assign(inst, mid);
        }
        void
        startRecordingCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 14;
            ce.assign(inst, mid);
        }
        void
        stopRecordingCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 18;
            ce.assign(inst, mid);
        }
        void
        loadAudioConfigurationCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }
        void
        setAudioScenarioCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }
        void
        setSpeakerLevelCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 8;
            ce.assign(inst, mid);
        }
        void
        setMicLevelCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 4;
            ce.assign(inst, mid);
        }
        void
        setMuteStateCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 6;
            ce.assign(inst, mid);
        }
        void
        setWidebandCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 10;
            ce.assign(inst, mid);
        }

    protected:
        NadAudioServicesServiceRegistration m_registration;
    };

} //namespace asi
} //namespace connectivity
} //namespace al
#endif// ASI_CONNECTIVITY_AL_NADAUDIOSERVICESS_HXX
