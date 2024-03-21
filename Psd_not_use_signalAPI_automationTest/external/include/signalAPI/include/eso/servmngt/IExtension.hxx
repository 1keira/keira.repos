#ifndef SERVMNGT_IEXTENSION_HXX_
#define SERVMNGT_IEXTENSION_HXX_

/*
	Copyright esolutions GmbH
	All rights reserved
	Authors:
		Martin Ruff
	$Id: IExtension.hxx 18077 2010-07-06 13:05:21Z matthias.grosam $
*/
#include <common/streams/ostream.hxx>
#include <util/config/Values.hxx>

namespace servmngt {



/*!
\brief	This class can be used to add user/project defined extensions to the 
		the service management. With this extension it has access to some
		features of the service management.
*/
class IExtension {
    public:

        /*!
         * Event for the extension jobs IJob
         *
         * usage:
         *  class MyEvent : IEvent {
         *      public:
			        static Type TYPE;
        *  
        *           MyEvent() : IEvent(TYPE)
        */
	    class IEvent {
		    public:
                class Type {
                    public:
                        Type() {}
                        ~Type() {}
                        bool operator==(const Type& other) const {
                            return (this==&other);
                        }
                        bool operator!=(const Type& other) const {
                            return !operator==(other);
                        }
                    private:
                        // not copy-assignable
                        Type(const Type& other);
                        Type& operator=(const Type& other);
                };
			virtual ~IEvent() {};

			// cast to T if T::TYPE equals type, return null if not
			template <typename T>
			const T* as() const { 
				if( T::TYPE == *m_type ) {
					return static_cast<const T*>(this);
				}
				return 0;
			}

			osal::TimeT timeStamp() const { return m_time_stamp; }

			virtual ipl::string toString() const = 0;

		protected:
			// not viable, derived classes are.
			IEvent(const Type& t): m_type(&t) {
				(void)osal::Time::getTime(m_time_stamp);
			}


		private:
			const Type* const	m_type;
			osal::TimeT			m_time_stamp;
	};


    /*! A job create by an extension. 
     *
     * It will be performed by the internal SM job execution
     * It will be fed with IExtension::IEvent instances
     *
     * No internal events will be routed into an extension job
    */
    class IJob {
        public:
            virtual ~IJob() {}
            /*!
             * start the job.
             *
             * \return
             *  true - job is done. It will be removed from the queue of
             *         processed jobs and it will be deleted
             *  false - put into the queue of running jobs and will be fed
             *          with IEvents
            */
            virtual bool start() = 0;

            /*!
             * a new event occured 
             *
             * \return see start()
            */
            virtual bool process(const IEvent& event) = 0;

            /*!
             * execution last longer than the given time
             * at Core::startExtensionJob(...)
             *
             * After this call returns, the job instance is deleted
            */
            virtual void timeout() = 0;
            
            virtual void cancel() = 0;
    
            //! return a textual representation of the job
            virtual ipl::string toString() const = 0;


            /*! get the timeout configuration of the job
             * derived class may overwrite default
             */
            virtual uint32_t getTimeout() const { return NO_TIMEOUT;}

             /*! declare the job as blocking
              * derived class may overwrite default
              */
            virtual bool isBlocking() { return true; };


            static const bool NON_BLOCKING = false;
            static const bool IS_BLOCKING = true;

            static const uint32_t NO_TIMEOUT = 0;
    };

	virtual ~IExtension() {}

	/*!
	\brief
		It reqisters the extension to initialize. Only static initialization must
		be done. IT extension must not be active after this call. 
	
		This method is called after the service management core has been 
		initialized, the watchdog has been initialized, the COMM agent has been 
		started, and the service management and watchdog COMM interfaces have 
		been registered.

		When the method is called the following steps have NOT yet been done:

		The static startup has not yet been read from the configuration and the jobs have
		not yet been created (i.e. the job queue is empty).

		The service management main loop has not been entered yet.
		
	*/
	virtual void setup() = 0; 

	/*!
	\brief
		Request to activate the extension. Up from now it shall do it's work.			
		This method is called immediately before the service management main loop,
		is entered, and after all setup from the service management is done.

		The static startup is initiated, but it's not guaranteed that the 
		static startup is performed completely

		It must not block the execution. The active part of the extension must be
		performed in an own thread.
	*/
	virtual void start() = 0; 

	/*!
	\brief
		Request to stop all activity of the extentions. 
	*/
	virtual void stop() = 0; 

	/*!
	\brief	request to dump any user defined information to the given stream
			any extension may overwrite this method, but need not to do
	*/
	virtual ipl::ostream& dumpInfo(ipl::ostream& out) { return out; };


};

}

#endif
