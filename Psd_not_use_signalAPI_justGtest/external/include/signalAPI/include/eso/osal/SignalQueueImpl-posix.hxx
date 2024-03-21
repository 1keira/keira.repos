/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_SIGNALQUEUEIMPL_POSIX_HXX
#define OSAL_SIGNALQUEUEIMPL_POSIX_HXX
/****************************************************************************/

#include <ipl_config.h>

#ifndef IPL_OS_POSIX
#error Only valid on Posix
#endif

#include <osal/osal_dso.h>

#include "SignalQueuePosixBase.hxx"

#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <errno.h>

/****************************************************************************/

namespace osal {

/****************************************************************************/

    /*!
        \internal
        \brief System dependent part of SignalQueue, Posix incarnation
    */
    class OSAL_EXPORT SignalQueueImpl: public SignalQueuePosixBase {

    protected:

        /*!
            \brief A pipe, read and write access to the appropriate end
            plus some management to help polling
        */
        class SelfPipe {

        public:
            SelfPipe(): pipe_read(-1), pipe_write(-1) {
#if defined(HAVE_PIPE2_O_CLOEXEC)
                int result=::pipe2(&pipe_read, O_CLOEXEC);
#else
                int result=::pipe(&pipe_read);
#endif
                IPL_ASSERT_VERBOSE(result==0, "couldn't create self-pipe");
                (void)result;  // non-debug no-warnings
                errno=0;
                ::fcntl(pipe_write, F_SETFL, ::fcntl(pipe_write, F_GETFL)|O_NONBLOCK);
                IPL_ASSERT_VERBOSE(errno==0, "couldn't configure self-pipe as non-blocking");
#if !defined(HAVE_PIPE2_O_CLOEXEC) && defined(HAVE_FCNTL_FD_CLOEXEC)
                errno=0;
                ::fcntl(pipe_read, F_SETFD, ::fcntl(pipe_read, F_GETFD) | FD_CLOEXEC);
                ::fcntl(pipe_write, F_SETFD, ::fcntl(pipe_write, F_GETFD) | FD_CLOEXEC);
                IPL_ASSERT_VERBOSE(errno==0, "couldn't configure self-pipe to not be inherited");
#endif
            }
            ~SelfPipe() {
                close(pipe_read);
                close(pipe_write);
            }

            int read(void *buf, size_t bytes);
            int write(void *buf, size_t max_bytes);
            void set(::fd_set *readme, int &nfds);
            bool is_set(::fd_set *readme);

        protected:
            int pipe_read, pipe_write;  // assumption: memory layout same as int[2]

        };

    public:

        /*!
            \internal
            \brief System dependent part of SignalQueue::Notifier, Posix incarnation
            (pipe based)
        */
        class NotifierImpl: public Dispatcher::Notifier {

        public:
            void wait() IPL_NOEXCEPT override;
            void signal() IPL_NOEXCEPT override;

        protected:
            SelfPipe pipe;
        };

        SignalQueueImpl(NotifierImpl &notifier): SignalQueuePosixBase(notifier) {}
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
