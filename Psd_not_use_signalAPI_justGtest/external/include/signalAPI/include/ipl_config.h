// definitions generated by CMake configure checks
#ifndef BUILD_IPL_CONFIG_HXX
#define BUILD_IPL_CONFIG_HXX

// framework version info
// (the strange constructs are working around a CMake limitation)
#define IPL_VERSION_STRING
#ifdef IPL_VERSION_STRING
#undef IPL_VERSION_STRING
#define IPL_VERSION_STRING "12.2.1"
#endif

// Note: The full framework version contains the components
// branch, major, minor, patchlevel. You must not compare
// major numbers for differing branches (just as you wouldn't
// compare minor numbers for different major numbers)!
/* #undef IPL_VERSION_HAVE_BRANCH */
#ifdef IPL_VERSION_HAVE_BRANCH
#undef IPL_VERSION_BRANCH
#define IPL_VERSION_BRANCH ""
#endif

#define IPL_VERSION_HAVE_MAJOR
#ifdef IPL_VERSION_HAVE_MAJOR
#undef IPL_VERSION_MAJOR
#define IPL_VERSION_MAJOR 12
#endif

#define IPL_VERSION_HAVE_MINOR
#ifdef IPL_VERSION_HAVE_MINOR
#undef IPL_VERSION_MINOR
#define IPL_VERSION_MINOR 2
#endif

#define IPL_VERSION_HAVE_PATCHLEVEL
#ifdef IPL_VERSION_HAVE_PATCHLEVEL
#undef IPL_VERSION_PATCHLEVEL
#define IPL_VERSION_PATCHLEVEL 1
#endif

/* #undef IPL_VERSION_HAVE_PRERELEASE */
#ifdef IPL_VERSION_HAVE_PRERELEASE
#undef IPL_VERSION_PRERELEASE
#define IPL_VERSION_PRERELEASE ""
#endif

/* #undef IPL_VERSION_HAVE_METADATA */
#ifdef IPL_VERSION_HAVE_METADATA
#undef IPL_VERSION_METADATA
#define IPL_VERSION_METADATA ""
#endif

// endianess as defined in toolchain
/* #undef IPL_FW_BIG_ENDIAN */
#define IPL_FW_LITTLE_ENDIAN

/*!
    \brief Default alignment used in ipl::align if no alignment is specified explicitely.

    The requirement is that this alignment should accomodate all possible base types.
    This means a variable of any type located at offset 0 of a memory area with this
    alignment can be read or written without triggering a misaligned access.

    The value could be architecture dependent, but currently is not.
    The definitive source to define the required alignment is the architecture manual for
    the relevant CPU family.

    \todo This might be too strict
    \todo \c long \c double might need incompatible alignment
*/
#define IPL_MAX_ALIGNMENT sizeof(long long)

// wheter an implementation for atomic counting is available
#define HAVE_ATOMIC_COUNTER 1  // TODO: retire
#define HAVE_ATOMIC_SYNC  // GCC/ICC intrinsics
/* #undef HAVE_ATOMIC_SMP */

// whether the atomic ops for comm::atomic::Ops are available (checks gcc builtins)
/* #undef HAVE_COMM_ATOMIC_PREREQS */

// whether on QNX we have the pthread_mutex_timedlock_monotonic() fct.
/* #undef HAVE_QNX_MUTEX_TIMEDLOCK_MONOTONIC */

// whether on QNX we have the sem_timedwait_monotonic() fct.
/* #undef HAVE_QNX_SEM_TIMEDWAIT_MONOTONIC */

// on Linux we can use the mmap() flag MAP_UNINITIALIZED (only with
// kernel 2.6.33 & suitable headers)
/* #undef HAVE_LINUX_MAP_UNINITIALIZED */

// whether we can get heap allocation information via mallinfo2()
/* #undef HAVE_MALLINFO2 */
// whether we can get heap allocation information via mallinfo()
#define HAVE_MALLINFO 1

// whether on QNX we have -D_FILE_OFFSET_BITS=64 set
/* #undef HAVE_FILE_OFFSETS64 */

// whether on QNX we have -D_FILE_OFFSET_BITS=32 set
/* #undef HAVE_FILE_OFFSETS32 */

// whether we build for Linux
#define IPL_OS_LINUX
// whether we build for Android
/* #undef IPL_OS_ANDROID */
// whether we build for QNX
/* #undef IPL_OS_QNX */
// whether we build for a Windows CE
/* #undef IPL_OS_WINCE */
// whether we build for a Windows Desktop (e.g. XP, Windows 7, Windows 2000) platform
/* #undef IPL_OS_WINPC */
// whether we build for a Win32 (e.g. Windows XP, Windows CE) platform
/* #undef IPL_OS_WIN32 */
// whether we build for a Posix platform
#define IPL_OS_POSIX
 // whether we build for a Integrity platform
/* #undef IPL_OS_INTEGRITY */

// separator between dirname and filename
#ifdef IPL_OS_WIN32
#define IPL_DIRSEPARATOR_CHAR '\\'
#define IPL_DIRSEPARATOR "\\"
#else
#define IPL_DIRSEPARATOR_CHAR '/'
#define IPL_DIRSEPARATOR "/"
#endif

// whether we use system stl
/* #undef IPL_USE_STD_STL */

// whether the STD STL uses type_traits internally,
// potentially conflicting with our own type_traits implementation
#define STL_USES_TYPE_TRAITS

// arch
#define IPL_ARCH_AARCH64

// whether the value AI_IDN is defined for ai_flags of addrinfo in netdb.h
#define HAVE_ADDRINFO_AIFLAGS_AI_IDN 1

// whether NI_IDN is defined (for getnameinfo flags)
#define HAVE_GETNAMEINFO_NI_IDN 1

// whether we have GNU strerror_r
#define HAVE_GNU_STRERROR_R 1

// whether we have XSI strerror_r
#define HAVE_XSI_STRERROR_R 1

// do we have stropts.h
#define HAVE_STROPTS_H 1

// is wcsnlen available?
#define HAVE_WCSNLEN 1

// whether localeconv() returns a usable struct lconv
#define HAVE_WORKING_LOCALECONV 1

// nl_langinfo call
#define HAVE_NL_LANGINFO

// whether HOST_NAME_MAX exists
#define HAVE_HOST_NAME_MAX 1

// whether MAXHOSTNAMELEN is defined (bsd style)
#define HAVE_MAXHOSTNAMELEN 1

#ifdef IPL_OS_POSIX
#ifndef HAVE_HOST_NAME_MAX
#ifdef HAVE_MAXHOSTNAMELEN
#define HOST_NAME_MAX MAXHOSTNAMELEN
#else
#error "neither HOST_NAME_MAX nor MAXHOSTNAMELEN are defined"
#endif
#endif
#endif

// whether tcdrain exists
#define HAVE_TCDRAIN 1

// whether we can set the CLOCK_REALTIME with clock_settime
#define HAVE_CLOCK_SETTIME_REALTIME 1

// whether pthread_condattr_setclock is available
#define HAVE_PTHREAD_CONDATTR_SETCLOCK 1

// whether pthread_mutexattr_setprotocol is available
#define HAVE_PTHREAD_MUTEXATTR_SETPROTOCOL 1

// whether the sys/stavfs.h header is available
#define HAVE_SYS_STATVFS_H  1
// and contains f_namemax
#define HAVE_SYS_STATVFS_NAMEMAX  1

// whether S_TYPEISSHM is defined for struct stat
#define HAVE_SYS_STAT_TYPEISSHM 1

// which regex implementation to use
/* #undef OSAL_USE_SPENCER */
#define OSAL_USE_POSIXREGEX

// whether POSIX regex.h defines REG_ESIZE
#define HAVE_POSIX_REGEX_ERR_ESIZE 1

// whether we have pthread_cancel
#define HAVE_PTHREAD_CANCEL 1

// whether pthread_attr_setinheritsched is provided
#define HAVE_PTHREAD_ATTR_SETINHERITSCHED 1

// timed join variants
/* #undef HAVE_PTHREAD_TIMEDJOIN */
/* #undef HAVE_PTHREAD_TIMEDJOIN_MONOTONIC */
#define HAVE_PTHREAD_TIMEDJOIN_NP 1

#if defined (HAVE_PTHREAD_TIMEDJOIN) || defined (HAVE_PTHREAD_TIMEDJOIN_MONOTONIC) || defined (HAVE_PTHREAD_TIMEDJOIN_NP)
#define HAVE_TIMED_JOIN 1
#else
#undef HAVE_TIMED_JOIN
#endif


// affinity control
#define HAVE_GNU_CPU_AFFINITY 1
/* #undef HAVE_THREADCTL_CPU_AFFINITY */

// whether spawn.h exists
#define HAVE_SPAWN_H 1

// whether the non POSIX pthread_mutex_lock_timeout_np exists
/* #undef HAVE_PTHREAD_MUTEX_LOCK_TIMEOUT_NP */

// whether pthread_mutex_timedlock exists
#define HAVE_PTHREAD_MUTEX_TIMED_LOCK

// pthread_mutex_lock_timeout_np is a non standard extenion in bionic.
// It got deprecated. If we have both pthread_mutex_lock_timeout_np and pthread_mutex_timedlock
// use the standard one
#if defined (HAVE_PTHREAD_MUTEX_LOCK_TIMEOUT_NP) && defined (HAVE_PTHREAD_MUTEX_TIMED_LOCK)
#undef HAVE_PTHREAD_MUTEX_LOCK_TIMEOUT_NP
#endif

// wheter the non POSIX pthread_cond_timedwait_monotonic_np exists
/* #undef HAVE_PTHREAD_COND_TIMEDWAIT_MONOTONIC_NP */

// POSIX.1-2008 functions
#define HAVE_OPENAT 1
#define HAVE_FSTATAT 1
#define HAVE_FDOPENDIR 1

// osal uses a generic 'have POSIX.1-2008' so we set it here based on the above functions
#if defined (HAVE_OPENAT) && defined (HAVE_FSTATAT) && defined (HAVE_FDOPENDIR)
#define OSAL_POSIX_2008
#endif

// do we have stdint.h
#define HAVE_STDINT_H 1

// do we have inttypes.h
#define HAVE_INTTYPES_H 1

// do we have symlink, readlink
#define HAVE_SYMLINK 1
#define HAVE_READLINK 1

// do we have the sys/select.h header
#define HAVE_SYS_SELECT_H 1

// do we have the C89 system() API
#define HAVE_C89_SYSTEM_CALL 1

// do we have pthread_setname_np
#define HAVE_PTHREAD_SETNAME_NP 1

// where to use the new iplthreadsafe
#define USE_THREADSAFE_IN_TINYOSAL
#define USE_THREADSAFE_IN_OSAL

// which iplthreadsafe::Tls implementation to use
#define THREADSAFE_USE_GENERIC_TLS

// which persistence::Serialization implementation to use
#define PERSISTENCE_USE_INTERNAL_SERIALIZATION

// which util::SharedPtr implementation to use
/* #undef USE_STD_SHAREDPTR_IN_UTIL_SHAREDPTR */

/* #undef HAVE_VALGRIND_VALGRIND_H */

// do we have the openssl header
/* #undef HAVE_OPENSSL_SSL_H */

// do we have some way to set the environment
#define HAVE_SETENV

/* #undef HAVE__PUTENV_S */

// dbus c api
/* #undef HAVE_DBUS_H */

//llabs
#define HAVE_LLABS

//swprintf
#define HAVE_SWPRINTF

// is std::_Construct(T1*, T2&&) available
#define HAVE__CONSTRUCT_RVALUE_REFERENCE

// is std::_Construct(T1*, T2&) available
#define HAVE__CONSTRUCT_LVALUE_REFERENCE

// do we have type_traits
#define HAVE_TYPE_TRAITS

// have AF_UNIX protocol family?
#define HAVE_AF_UNIX

// can the namespace for unix domain sockets be abstract?
#if defined (HAVE_AF_UNIX)
#if defined (IPL_OS_QNX)
#include <sys/neutrino.h> // for qnx version
#endif
#if defined (IPL_OS_ANDROID) || defined (IPL_OS_LINUX) || ( defined(IPL_OS_QNX) && (_NTO_VERSION >= 660) )
#define HAVE_AF_UNIX_ABSTRACT
#endif
#endif

// is std::_Exit(int) available
#define HAVE_STD__EXIT

// do we have iov_t, struct iovec
/* #undef HAVE_IOV_T */
#define HAVE_STRUCT_IOVEC

// is strtoll available
#define HAVE_STRTOLL

// does clock_nanosleep exist
#define HAVE_CLOCK_NANOSLEEP

// does clock_getcpuclockid() exist
#define HAVE_CLOCK_GETCPUCLOCKID

// do we have the SIGEV_MAKE_UPDATEABLE macro for struct sigevent
/* #undef HAVE_UPDATEABLE_SIGEVENT */

// do we have private channels on QNX
/* #undef HAVE_QNX_PRIVATE_CHANNEL */

// is void quick_exit( int exit_code )  available (since C11)
#define HAVE_QUICK_EXIT

// do we have getpeereid
/* #undef HAVE_GETPEEREID */

// do we have SO_PEERCRED
#define HAVE_SO_PEERCRED

// do we have getpwuid_r
#define HAVE_GETPWUID_R

// do we have getpwnam_r
#define HAVE_GETPWNAM_R

// do we have getgrgid_r
#define HAVE_GETGRGID_R

// do we have getgrnam_r
#define HAVE_GETGRNAM_R

// do we have getgrouplist
#define HAVE_GETGROUPLIST

// do we have chmod
#define HAVE_CHMOD

// do we have getegid
#define HAVE_GETEGID

// do we have geteuid
#define HAVE_GETEUID

// do we have iofunc_client_info_ext
/* #undef HAVE_CLIENTINFO_EXT */

// are widestring to multibyte string conversion functions broken?
/* #undef IPL_BROKEN_WIDESTRING_CONV */

// do we have strnlen
#define HAVE_STRNLEN

// do we have std::strnlen
/* #undef HAVE_STD_STRNLEN */

// std::shared_ptr
#define HAVE_STD_SHAREDPTR

// std::atomic<bool>
#define HAVE_STD_ATOMIC_BOOL

// nullptr_t type
#define HAVE_STD_NULLPTR_T

// number of signals available / highest signal number +1
#define IPL_NSIGNALS 65

// Which clock source should be used, on POSIX anyway?
// (this is done via a configure check as we want IPL_CLOCK_PREFERRED
// in ipl_config.h where we should not include the required unistd.h
#define HAVE_POSIX_MONOTONIC_CLOCK
#ifdef HAVE_POSIX_MONOTONIC_CLOCK
#define IPL_CLOCK_PREFERRED CLOCK_MONOTONIC  // if we have it we should use it
#else
#define IPL_CLOCK_PREFERRED CLOCK_REALTIME   // if not fall back to realtime
#endif

#define HAVE_LINUX_BOOTTIME_CLOCK
/* #undef HAVE_ARMV8_CLOCK_REGISTER */
#define HAVE_CLOCK_REALTIME

/* #undef TRACING_FORCE_CLOCK_REALTIME */
/* #undef TRACING_FORCE_CLOCK_MONOTONIC */
/* #undef TRACING_FORCE_CLOCK_BOOTTIME */
/* #undef TRACING_FORCE_CLOCK_MONOBOOT */
/* #undef TRACING_FORCE_CLOCK_CPU */
/* #undef TRACING_FORCE_CLOCK_MONOCPU */

// set the fallback clocksource
#if defined(TRACING_FORCE_CLOCK_REALTIME)
#   define TRACING_USE_CLOCK_REALTIME
#elif defined(TRACING_FORCE_CLOCK_MONOTONIC)
#   define TRACING_USE_CLOCK_MONOTONIC
#elif defined(TRACING_FORCE_CLOCK_BOOTTIME)
#   define TRACING_USE_CLOCK_BOOTTIME
#elif defined(TRACING_FORCE_CLOCK_CPU)
#   define TRACING_USE_CLOCK_CPU
#elif defined(TRACING_FORCE_CLOCK_MONOCPU)
#   define TRACING_USE_CLOCK_MONOCPU
#elif defined(TRACING_FORCE_CLOCK_MONOBOOT)
#   define TRACING_USE_CLOCK_MONOBOOT
#else
    // no forced fallback is configured use the default order
#if defined(HAVE_LINUX_BOOTTIME_CLOCK) && defined(HAVE_POSIX_MONOTONIC_CLOCK)
#       define TRACING_USE_CLOCK_MONOBOOT
#   elif defined(HAVE_ARMV8_CLOCK_REGISTER) && defined(HAVE_POSIX_MONOTONIC_CLOCK)
#       define TRACING_USE_CLOCK_MONOCPU
#   elif defined(HAVE_ARMV8_CLOCK_REGISTER)
#       define TRACING_USE_CLOCK_CPU
#   elif defined(HAVE_LINUX_BOOTTIME_CLOCK)
#       define TRACING_USE_CLOCK_BOOTTIME
#   elif defined(HAVE_POSIX_MONOTONIC_CLOCK)
#       define TRACING_USE_CLOCK_MONOTONIC
#   elif defined(HAVE_CLOCK_REALTIME)
#       define TRACING_USE_CLOCK_REALTIME
#   else
#       error "can not run TRACING without any valid fallback clocksource"
#   endif
#endif

// Configure additional built-in tracing frontend plugins
/* #undef BUILTIN_COMMANDPIPE */
/* #undef BUILTIN_FILEUPLOADER */
/* #undef BUILTIN_LOGCATREADER */
/* #undef BUILTIN_PLUGINSERVER */
/* #undef BUILTIN_POWERSTATEHANDLER */
/* #undef BUILTIN_PRESETMANAGER */
/* #undef BUILTIN_PROCESSEXECUTOR */
/* #undef BUILTIN_RLBMGR */
/* #undef BUILTIN_SIGNALHANDLER */
/* #undef BUILTIN_SLOGREADER */
/* #undef BUILTIN_TIMEZONEPROVIDER */

// Configure additional built-in tracing backend plugins
/* #undef BUILTIN_BINARYFILEBACKEND */
/* #undef BUILTIN_CALLBACKBACKEND */
/* #undef BUILTIN_EMERGENCYRECORDERBACKEND */
/* #undef BUILTIN_EMERGENCYTRIGGERBACKEND */
/* #undef BUILTIN_FANCYFORMATTER */
/* #undef BUILTIN_REMOTECONNECTBACKEND */
/* #undef BUILTIN_ROLLINGFILEBACKEND */

// Provide libfmt support in tracing
#define TRACING_WITH_LIBFMT

// Initial hard-coded size of process entity names
/* #undef IPL_INITIAL_MAX_PROC_NAME_SIZE */
#ifndef IPL_INITIAL_MAX_PROC_NAME_SIZE
#define IPL_INITIAL_MAX_PROC_NAME_SIZE 4096
#endif

// Which Posix process creation API should be used?
/* #undef USE_SPAWN_API_IN_POSIX_PROCESSTNG */

//! \def IPL_FALLTHROUGH
//! \brief Conditional null statement of
//! [[fallthrough]];, __attribute__((fallthrough)); or a magic comment and semicolon
//!
//! The macro is set from the CMake variables IPL_FALLTHROUGH or, if empty,
//! IPL_FALLTHROUGH_C and IPL_FALLTHROUGH_CXX, respectively.
/* #undef IPL_FALLTHROUGH_CXX */
/* #undef IPL_FALLTHROUGH_C */
#define IPL_FALLTHROUGH     __attribute__((fallthrough));
// This here is to cope with possible incompatible syntaxes in C and C++:
#ifdef __cplusplus
    #ifdef IPL_FALLTHROUGH_CXX
        #undef IPL_FALLTHROUGH
        #define IPL_FALLTHROUGH IPL_FALLTHROUGH_CXX
    #endif
#else
    #ifdef IPL_FALLTHROUGH_C
        #undef IPL_FALLTHROUGH
        #define IPL_FALLTHROUGH IPL_FALLTHROUGH_C
    #endif
#endif
#ifndef IPL_FALLTHROUGH
    // Note: The attributes need to precede a null-statement,
    // so for consistency we also add a null-statement to the comment
    #define IPL_FALLTHROUGH ; /* fall-through */
#endif

#ifndef IPL_NOEXCEPT
//! \brief Conditional noexcept, throw() or nothing
//!
//! You can override it via -D on the compiler’s command line
#define IPL_NOEXCEPT noexcept
#endif

//! \def IPL_HAVE_EXCEPTIONS
//! You can force this to undefined via -DIPL_FORCE_NO_EXCEPTIONS
//! on the compiler's command line.
#ifndef IPL_FORCE_NO_EXCEPTIONS
// Whether we support exceptions
#define IPL_HAVE_EXCEPTIONS
#endif

// do we have an elf header
#define HAVE_ELF_H

// Do we have IntegrityOS's statfs header?
#define HAVE_SYS_STATFS_H

// Do we have fcntl(fd, F_SETFD, FD_CLOEXEC)
#define HAVE_FCNTL_FD_CLOEXEC

// Do we have the SOCK_CLOEXEC flag for socket()
#define HAVE_SOCK_CLOEXEC

// Do we have the O_CLOEXEC flag to open (POSIX.1-2008)
#define HAVE_OPEN_O_CLOEXEC

// Do we have the SOCK_CLOEXEC and accept4
#define HAVE_ACCEPT4_SOCK_CLOEXEC

// Do we have the O_CLOEXEC and pipe2
#define HAVE_PIPE2_O_CLOEXEC

// Do we have SOCK_SEQPACKET
#define HAVE_SOCK_SEQPACKET

// Do we have SO_PRIORITY
#define HAVE_SO_PRIORITY

// Do we have SO_VLANPRIO
/* #undef HAVE_SO_VLANPRIO */

// Do we have SOL_TCP
#define HAVE_SOL_TCP_IN_NETINET_TCP
/* #undef HAVE_SOL_TCP_IN_SYS_SOCKET */

// Do we have epoll
#define HAVE_EPOLL
#define USE_EPOLL

#define HAVE_SYNC

#define HAVE_SCHED_YIELD

// Do we have C++'s std::align?
#define HAVE_STD_ALIGN

// Do we have C++11's alignas? (__alignas_is_defined would be standard
// but is buggy in relevant headers)
#define HAVE_ALIGNAS
#define HAVE_ALIGNOF

// Do we have the Unix/Linux getpriority call?
#define HAVE_SCHED_GETPRIORITY

// sched_setscheduler
#define HAVE_SCHED_SETSCHEDULER
// scheduling policies (linux/posix)
#define HAVE_SCHED_OTHER
#define HAVE_SCHED_RR
#define HAVE_SCHED_FIFO

// affinity via pthread interface
#define HAVE_PTHREAD_SETAFFINITY_NP
#define HAVE_PTHREAD_ATTR_SETAFFINITY_NP

// get pthread attributes
#define HAVE_PTHREAD_GETATTR_NP

// can set stack size vi pthread atributes
#define HAVE_PTHREAD_ATTR_SETSTACKSIZE

/* #undef IPL_THREADS_WANT_STACKSIZE */

// gettid() from libc or via syscall
/* #undef HAVE_GETTID */
#define HAVE_GETTID_SYSCALL

// does pthread_create start the thread before its
// output parameters are properly initialized?
/* #undef HAVE_BROKEN_PTHREAD_CREATE */

// does sem_wait just segfault or are semaphores otherwise unusable?
/* #undef HAVE_BROKEN_SEM_WAIT */

//  if this is configured, a signal handler is installed by osal
//  that flushes the coverage data for gcov to the .gcda file.
//
//  OSAL_GCOV_FLUSH_SIGNAL may be set to any of the osal/signal.h constants,
//  e.g. SIGUSR1
/* #undef OSAL_GCOV_FLUSH_SIGNAL */

// do we have std::optional or std::experimental::optional available
/* #undef HAVE_STD_OPTIONAL */
#define HAVE_STD_EXP_OPTIONAL

// do we have std::stringview or std::experimental::stringview available
/* #undef HAVE_STD_STRINGVIEW */
#define HAVE_STD_EXP_STRINGVIEW

// do we have a std::variant available
/* #undef HAVE_STD_VARIANT */

// do we have a third party ara::core::variant available
/* #undef USE_ARA_CORE_VARIANT */
/* #undef HAVE_ARA_CORE_VARIANT */

// do we have a third party ara::core::string available
/* #undef HAVE_ARA_CORE_STRING */

// should the framework's rapidjson's namespace be anything other than rapidjson?
/* #undef IPL_RAPIDJSON_NAMESPACE */
#ifndef IPL_RAPIDJSON_NAMESPACE
#define IPL_RAPIDJSON_NAMESPACE rapidjson
#endif

// do we have SIGSTOP
#define HAVE_SIGSTOP

// do we have SO_LINGER
#define HAVE_SO_LINGER

// do we have TCP_KEEPIDLE
#define HAVE_TCP_KEEPIDLE

// do we have TCP_KEEPINTVL
#define HAVE_TCP_KEEPINTVL

// do we have TCP_KEEPCNT
#define HAVE_TCP_KEEPCNT

// do we have TCP_USER_TIMEOUT
#define HAVE_TCP_USER_TIMEOUT

//do we have eventfd
#define HAVE_EVENT_FD

// should we build the libkeystore2 substitute lib
// default value is set in the toolchain files
/* #undef BUILD_LIBKEYSTORE2 */

// should the util library use cryptographic primitives
// from an external library (openssl, botan etc)
// default value is set in the toolchain files
/* #undef BUILD_UTIL_WITH_CRYPTO */

// is setsockopt() declared with noexcept?
#define HAVE_SETSOCKOPT_NOEXCEPT

// are dl-functions, execinfo.h and program_invocation_name available?
#define HAVE_DLFCN_EXECINFO_GNU_SOURCE

// is log/log.h available in android build
/* #undef HAVE_ANDROID_LOG_H */

#endif
