/*****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Martin Stein
*/
/*****************************************************************************/
#ifndef PERSISTENCE_TNG_ENGINE_HXX
#define PERSISTENCE_TNG_ENGINE_HXX
/*****************************************************************************/

#include <ipl_config.h>

#include <common/streams/sstream.hxx>
#include <common/types/vector.hxx>
#include <util/SharedPtr.hxx>
#include <util/config/Values.hxx>
#include <util/sharedptr/SharedPtr.hxx>
#include <util/sharedptr/WeakPtr.hxx>
#include <persistence/Utf8String.hxx>
#include <persistence/Blob.hxx>
#include <common/streams/sstream.hxx>
#include <persistence/Job.hxx>
#include <persistence/Core.hxx>

/*****************************************************************************/

//! \brief Reporting flush progress ONLY!
IPL_TRACE_DECLARE_CHANNEL_EXTERN(FW_PERSISTENCE_FLUSH);

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/

    /*!
        \brief Persistence engine interface (asynchronous)
    */
    class Engine {

    public:

        class Name;
        class Key;
        struct Address;

        typedef Utf8String                Version;
        typedef int64_t                   Int;
        typedef Utf8String                String;
        typedef persistence::Blob         Blob;      // Interface
        typedef persistence::ReadableBlob BlobImpl;  // concrete implementation
        typedef ipl::vector<Key>          KeyList;
        typedef uint32_t                  Size;

        /*!
            \brief Identity of Him Who Owns The Transaction

            Note: This must be different for (if applicable) distinct
            client programs, distinct open handles etc.,
            and it must not be NULL.
        */
        typedef void *Token;

        class Factory;

        //! \brief What is needed to properly answer asynchronously
        struct Context {
            Core &core;
            Core::Seqnum seqnum;
            ipl::string blame;

            Context(Core &core, Core::Seqnum seqnum) IPL_NOEXCEPT:
                core(core), seqnum(seqnum), blame(core.getBlame()) {}
            Context(Core &core) IPL_NOEXCEPT:  // ?
                core(core), seqnum(core.seqnum()), blame(core.getBlame()) {}
        };

        class Partition;
        class Job;

        enum FsAccess {
            FS_READ_ONLY,
            FS_READ_WRITE
        };

        //! \brief aka. persistence::ESSENTIAL_VALUE
        //! aka. dsi::persistence::DSIPersistence::IMPORTANCE_ESSENTIAL
        //! aka. dsi::persistence::DSIPersistence2::IMPORTANCE_ESSENTIAL
        static const int IMPORTANCE_ESSENTIAL=-1;
        //! \brief aka. persistence::DISPENSABLE_VALUE
        //! aka. dsi::persistence::DSIPersistence::IMPORTANCE_DISPENSABLE
        //! aka. dsi::persistence::DSIPersistence2::IMPORTANCE_DISPENSABLE
        static const int IMPORTANCE_DISPENSABLE=-2;

        virtual ~Engine() IPL_NOEXCEPT {}

        virtual Core::Seqnum requestPartition(Core &core,
                                              const Name &partition,
                                              const Version &version) IPL_NOEXCEPT=0;
        virtual Core::Seqnum requestConversion(Core &core,
                                               const Name &partition,
                                               const Version &from_version,
                                               const Version &to_version) IPL_NOEXCEPT=0;
        virtual Core::Seqnum purge(Core &core, const Name &partition) IPL_NOEXCEPT=0;
        virtual Core::Seqnum version(Core &core, const Name &partition) IPL_NOEXCEPT=0;

        virtual void fs_access(FsAccess access) IPL_NOEXCEPT=0;
        //! \return The number of Engine::Job::EventAllFlushed events that
        //! must be received before we can conclude that really all is flushed
        virtual unsigned flushAll(Core &core) IPL_NOEXCEPT=0;
    };

/*****************************************************************************/
    class Engine::Key{

    public:

        typedef Engine::Int Int;
        typedef Engine::String String;

        bool        use_string;
        Int         integer;
        String      string;
        ipl::string repr;

        Key(Int key) IPL_NOEXCEPT:
             use_string(false), integer(key),
             repr(mkrepr(key)) {}
        Key(const String &key) IPL_NOEXCEPT:
             use_string(true), integer(), string(key),
             repr(mkrepr(key)) {}
        Key(const char* key) IPL_NOEXCEPT:
             use_string(true), integer(), string(key),
             repr(mkrepr(key)) {}
        Key(const std::string& key) IPL_NOEXCEPT:
             use_string(true), integer(), string(key),
             repr(mkrepr(key)) {}

        bool operator == (const Int other) const IPL_NOEXCEPT {
            if(use_string)
                return false;
            return integer==other;
        }

        bool operator == (const Key&other) const IPL_NOEXCEPT {
            if(use_string)
                if(other.use_string)
                    return string==other.string;
                else
                    return false;
            else
                if(other.use_string)
                    return false;
                else
                    return integer==other.integer;
        }
        bool operator != (const Key&other) const IPL_NOEXCEPT {
            return !operator == (other);
        }

        bool operator < (const Key& other) const IPL_NOEXCEPT {
            if(use_string) {
                if(other.use_string) {
                    return string < other.string;
                }
                return false;  // String > int
            }
            if(other.use_string)
                return true;  // int < String
            return integer < other.integer;
        }

        bool operator <= (const Key &other) const IPL_NOEXCEPT {
            return operator < (other) || operator == (other);
        }
        bool operator > (const Key &other) const IPL_NOEXCEPT {
            return !operator <= (other);
        }
        bool operator >= (const Key &other) const IPL_NOEXCEPT {
            return !operator < (other);
        }

    protected:
        static ipl::string mkrepr(Int key) IPL_NOEXCEPT {
            ipl::ostringstream s;
            s << key;
            return s.str();
        }
        static ipl::string mkrepr(const String &key) IPL_NOEXCEPT {
            ipl::ostringstream s;
            s << '"' << key << '"';
            return s.str();
        }

    private:
        Key() {}
    };

/*****************************************************************************/

    /*!
        \brief Union of how partitions and entries can be named
        \todo Unduplicate code by merging Int and String methods
        into a single Name method.
    */
    class Engine::Name {

    public:

        typedef Engine::Int Int;
        typedef Engine::String String;

        bool        use_string;
        Int         integer;
        String      string;
        bool        has_profile;
        Int         profile;
        ipl::string repr;

        Name(Int name) IPL_NOEXCEPT:
             use_string(false), integer(name), has_profile(false), profile(-1),
             repr(mkrepr(name)) {}
        Name(const String &name) IPL_NOEXCEPT:
             use_string(true), string(name), has_profile(false), profile(-1),
             repr(mkrepr(name)) {}
        Name(Int name, Int profile) IPL_NOEXCEPT:
             use_string(false), integer(name), has_profile(true), profile(profile),
             repr(mkrepr(name, profile)) {}
        Name(const String &name, Int profile) IPL_NOEXCEPT:
             use_string(true), string(name), has_profile(true), profile(profile),
             repr(mkrepr(name, profile)) {}
        Name(bool use_string, Int integer, const String &string,
             bool has_profile, Int profile) IPL_NOEXCEPT:
             use_string(use_string), integer(integer), string(string),
             has_profile(has_profile), profile(profile),
             repr(mkrepr(use_string, integer, string, has_profile, profile)) {}

        bool operator == (const Name &other) const IPL_NOEXCEPT {
            if(has_profile)
                if(other.has_profile) {
                    if(profile!=other.profile)
                        return false;
                } else
                    return false;
            else
                if(other.has_profile)
                    return false;

            if(use_string)
                if(other.use_string)
                    return string==other.string;
                else
                    return false;
            else
                if(other.use_string)
                    return false;
                else
                    return integer==other.integer;
        }
        bool operator != (const Name &other) const IPL_NOEXCEPT {
            return !operator == (other);
        }

        bool operator < (const Name &other) const IPL_NOEXCEPT {
            if(use_string)
                if(other.use_string)
                    if(string==other.string) {
                        if(has_profile)
                            if(other.has_profile)
                                return profile<other.profile;
                            else
                                return false;  // profile > no profile
                        else
                            return other.has_profile;  // no profile < profile
                    } else
                        return string<other.string;
                else
                    return false;  // String > int
            else
                if(other.use_string)
                    return true;  // int < String
                else
                    if(integer==other.integer) {
                        if(has_profile)
                            if(other.has_profile)
                                return profile<other.profile;
                            else
                                return false;  // profile > no profile
                        else
                            return other.has_profile;  // no profile < profile
                    } else
                        return integer<other.integer;
        }
        bool operator <= (const Name &other) const IPL_NOEXCEPT {
            return operator < (other) || operator == (other);
        }
        bool operator > (const Name &other) const IPL_NOEXCEPT {
            return !operator <= (other);
        }
        bool operator >= (const Name &other) const IPL_NOEXCEPT {
            return !operator < (other);
        }

    protected:
        static ipl::string mkrepr(Int name) IPL_NOEXCEPT {
            ipl::ostringstream s;
            s << name;
            return s.str();
        }
        static ipl::string mkrepr(const String &name) IPL_NOEXCEPT {
            ipl::ostringstream s;
            s << '"' << name << '"';
            return s.str();
        }
        static ipl::string mkrepr(Int name, Int profile) IPL_NOEXCEPT {
            ipl::ostringstream s;
            s << name << '[' << profile << ']';
            return s.str();
        }
        static ipl::string mkrepr(const String &name, Int profile) IPL_NOEXCEPT {
            ipl::ostringstream s;
            s << '"' << name << '"' << '[' << profile << ']';
            return s.str();
        }
        static ipl::string mkrepr(bool use_string, Int integer, const String &string,
                                  bool has_profile, Int profile) IPL_NOEXCEPT {
            if(use_string)
                if(has_profile)
                    return mkrepr(string, profile);
                else
                    return mkrepr(string);
            else
                if(has_profile)
                    return mkrepr(integer, profile);
                else
                    return mkrepr(integer);
        }
    };

/*****************************************************************************/

    struct Engine::Address {

        Name partition;
        Key  key;

        Address(const Name &partition, Key& key):
            partition(partition), key(key) {}
        Address(const Name &partition, Engine::Int key):
            partition(partition), key(key) {}

        bool operator == (const Address &other) const IPL_NOEXCEPT {
            return key==other.key && partition==other.partition;
        }
        bool operator != (const Address &other) const IPL_NOEXCEPT {
            return !operator == (other);
        }

        bool operator < (const Address &other) const IPL_NOEXCEPT {
            if(key<other.key) return true;
            if(key==other.key && partition<other.partition) return true;
            return false;
        }
        bool operator <= (const Address &other) const IPL_NOEXCEPT {
            return operator < (other) || operator == (other);
        }
        bool operator > (const Address &other) const IPL_NOEXCEPT {
            return !operator <= (other);
        }
        bool operator >= (const Address &other) const IPL_NOEXCEPT {
            return !operator < (other);
        }
    };

/*****************************************************************************/

    class Engine::Partition {

    public:
        virtual ~Partition() IPL_NOEXCEPT;

        virtual bool may_open_with(const Version &version) const IPL_NOEXCEPT=0;
        virtual Core::Seqnum beginGet(Core &client, int timeout) IPL_NOEXCEPT=0;
        virtual Core::Seqnum beginSubscribe(Core &client, int timeout) IPL_NOEXCEPT=0;
        virtual Core::Seqnum beginUnsubscribe(Core &client) IPL_NOEXCEPT=0;
        virtual void key(const Context &context, const Key& key, bool resubscribe=false) IPL_NOEXCEPT=0;
        virtual void end(const Context &context) IPL_NOEXCEPT=0;

        virtual Core::Seqnum remove(Core &client, Token token, const Key& key) IPL_NOEXCEPT=0;
        virtual Core::Seqnum putInt(Core &client, Token token, const Key& key, Int val) IPL_NOEXCEPT=0;
        virtual Core::Seqnum putString(Core &client, Token token, const Key& key, const String &val) IPL_NOEXCEPT=0;
        virtual Core::Seqnum putBlob(Core &client, Token token, const Key& key, const Blob &val) IPL_NOEXCEPT=0;

        virtual Core::Seqnum beginTransaction(Core &client, Token token) IPL_NOEXCEPT=0;
        virtual Core::Seqnum endTransaction(Core &client, Token token, bool flush) IPL_NOEXCEPT=0;

        virtual Core::Seqnum flush(Core &client) IPL_NOEXCEPT=0;
        virtual Core::Seqnum copy(Core &client, const Name &to) IPL_NOEXCEPT=0;
        virtual Core::Seqnum getAllKeys(Core &client) IPL_NOEXCEPT=0;
        virtual Core::Seqnum removeAll(Core &client, Token token) IPL_NOEXCEPT=0;
    };

/*****************************************************************************/

    /*!
        \brief Common base for jobs talking to an Engine
    */
    class Engine::Job: public persistence::Job {

    public:

        class Event;
        class EventTimeout;
        class EventOk;
        class EventInternalError;
        class EventInvalidTimeout;
        class EventPartition;
        class EventUnsubscribed;
        class EventVersionMismatch;
        class EventTransactionPending;
        class EventNoTransactionPending;
        class EventPartitionInUse;
        class EventNoSuchPartition;
        class EventNotAllowed;
        class EventVersion;
        class EventNoSuchValue;
        class EventValueInt;
        class EventValueString;
        class EventValueBlob;
        class EventEnd;
        class EventKeys;
        class EventAllFlushed;

        Job(Core &core, const ipl::string &description) IPL_NOEXCEPT:
            persistence::Job(core, description), m_seqnum(0) {}

        static JobType TYPE;

        virtual void *cast(const JobType &type) IPL_NOEXCEPT;

        /* Engine events *****************************************************/

        //! \brief "Some lower machinery has timeouted"
        virtual void timeout(Core::Seqnum) IPL_NOEXCEPT;
        //! \brief "Whatever you asked for has succeeded"
        virtual void ok(Core::Seqnum seqnum) IPL_NOEXCEPT;
        //! \brief "Sorry, I have encountered an internal error, here's the description"
        virtual void internalError(Core::Seqnum seqnum,
                                   const ipl::string &reason) IPL_NOEXCEPT;
        //! \brief "The timeout value you provided is invalid"
        virtual void invalidTimeout(Core::Seqnum seqnum, int offending_timeout) IPL_NOEXCEPT;
        //! \brief "Here's the partition you requested"
        virtual void partition(Core::Seqnum seqnum,
                               const util::SharedPtr<Partition> &partition) IPL_NOEXCEPT;
        //! \brief "The partition you requested has a mismatching version"
        virtual void versionMismatch(Core::Seqnum seqnum) IPL_NOEXCEPT;
        //! \brief "Failed due to a pending transaction"
        virtual void transactionPending(Core::Seqnum seqnum) IPL_NOEXCEPT;
        //! \brief "Failed due to no pending transaction"
        virtual void noTransactionPending(Core::Seqnum seqnum) IPL_NOEXCEPT;
        //! \brief "Failed due to partition already being used"
        virtual void partitionInUse(Core::Seqnum seqnum) IPL_NOEXCEPT;
        //! \brief "You must not do so"
        virtual void notAllowed(Core::Seqnum seqnum) IPL_NOEXCEPT;

        //! \brief "The partition you have asked for doesn't exist"
        virtual void noSuchPartition(Core::Seqnum) IPL_NOEXCEPT;
        //! \brief "Here you have the version you asked for"
        virtual void version(Core::Seqnum seqnum, const Engine::Version &version) IPL_NOEXCEPT;
        //! \brief "A value you have asked for doesn't exist"
        virtual void noSuchValue(Core::Seqnum seqnum, const Engine::Key& key, bool is_failed) IPL_NOEXCEPT;
        //! \brief "A value you have subscribed for doesn't exist"
        virtual void noSuchValue(const Engine::Name &partition, const Engine::Key& key, bool is_failed) IPL_NOEXCEPT;
        //! \brief "Here you have a value you have asked for"
        virtual void value(Core::Seqnum seqnum, const Engine::Key& key,
                           Engine::Int value) IPL_NOEXCEPT;
        //! \brief "Here you have a value you have subscribed for"
        virtual void value(const Engine::Name &partition, const Engine::Key& key,
                           Engine::Int value) IPL_NOEXCEPT;
        //! \brief "Here you have a value you have asked for"
        virtual void value(Core::Seqnum seqnum, const Engine::Key& key,
                           const Engine::String &value) IPL_NOEXCEPT;
        //! \brief "Here you have a value you have subscribed for"
        virtual void value(const Engine::Name &partition, const Engine::Key& key,
                           const Engine::String &value) IPL_NOEXCEPT;
        //! \brief "Here you have a value you have asked for"
        virtual void value(Core::Seqnum seqnum, const Engine::Key& key,
                           const Engine::Blob &value) IPL_NOEXCEPT;
        //! \brief "Here you have a value you have subscribed for"
        virtual void value(const Engine::Name &partition, const Engine::Key& key,
                           const Engine::Blob &value) IPL_NOEXCEPT;
        //! \brief "Here you have the list of requested keys from a partition
        virtual void keys(Core::Seqnum seqnum,
                          const Engine::KeyList &keylist) IPL_NOEXCEPT;
        //! \brief "This entry has been unsubscribes for"
        virtual void unsubscribed(Core::Seqnum seqnum, const Engine::Key& key) IPL_NOEXCEPT;
        //! \brief "That's all, you can conclude processing the values,
        //! unsubscription status or whatever"
        virtual void end(Core::Seqnum seqnum) IPL_NOEXCEPT;
        //! \brief "That's all, you can conclude processing the changed values"
        virtual void end() IPL_NOEXCEPT;

        //! \brief "I have flushed all, where 'all' is one of the 'alls'
        //! that got returned by Engine::flushAll()
        virtual void allFlushed() IPL_NOEXCEPT;

    protected:
        //! \brief Store the sequence number returned by any engine method here
        Core::Seqnum m_seqnum;
    };

/*****************************************************************************/

    class Engine::Job::Event: public persistence::Event {

    public:
        virtual bool abort() IPL_NOEXCEPT;
    };

/*****************************************************************************/

    class Engine::Job::EventTimeout: public Engine::Job::Event {

    public:
        EventTimeout(Core::Seqnum seqnum) IPL_NOEXCEPT: m_seqnum(seqnum) {}

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        Core::Seqnum m_seqnum;
    };

/*****************************************************************************/

    class Engine::Job::EventOk: public Engine::Job::Event {

    public:
        EventOk(Core::Seqnum seqnum) IPL_NOEXCEPT: m_seqnum(seqnum) {}

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        Core::Seqnum m_seqnum;
    };

/*****************************************************************************/

    class Engine::Job::EventInternalError: public Engine::Job::Event {

    public:
        EventInternalError(Core::Seqnum seqnum, const ipl::string &reason) IPL_NOEXCEPT:
            m_seqnum(seqnum), m_reason(reason) {}

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        Core::Seqnum m_seqnum;
        ipl::string m_reason;
    };

/*****************************************************************************/

    class Engine::Job::EventInvalidTimeout: public Engine::Job::Event {

    public:
        EventInvalidTimeout(Core::Seqnum seqnum, int timeout) IPL_NOEXCEPT:
            m_seqnum(seqnum), m_timeout(timeout) {}

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        Core::Seqnum m_seqnum;
        int m_timeout;
    };

/*****************************************************************************/

    class Engine::Job::EventPartition: public Engine::Job::Event {

    public:
        EventPartition(Core::Seqnum seqnum,
                       const util::SharedPtr<Partition> &partition) IPL_NOEXCEPT:
            m_seqnum(seqnum), m_partition(partition) {}

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        Core::Seqnum m_seqnum;
        util::SharedPtr<Partition> m_partition;
    };

/*****************************************************************************/

    class Engine::Job::EventUnsubscribed: public Engine::Job::Event {

    public:
        EventUnsubscribed(Core::Seqnum seqnum, const Engine::Key& key) IPL_NOEXCEPT:
            m_seqnum(seqnum), m_key(key) {}

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        Core::Seqnum    m_seqnum;
        Engine::Key     m_key;
    };

/*****************************************************************************/

    class Engine::Job::EventVersionMismatch: public Engine::Job::Event {

    public:
        EventVersionMismatch(Core::Seqnum seqnum) IPL_NOEXCEPT: m_seqnum(seqnum) {}

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        Core::Seqnum m_seqnum;
    };

/*****************************************************************************/

    class Engine::Job::EventTransactionPending: public Engine::Job::Event {

    public:
        EventTransactionPending(Core::Seqnum seqnum) IPL_NOEXCEPT: m_seqnum(seqnum) {}

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        Core::Seqnum m_seqnum;
    };

/*****************************************************************************/

    class Engine::Job::EventNoTransactionPending: public Engine::Job::Event {

    public:
        EventNoTransactionPending(Core::Seqnum seqnum) IPL_NOEXCEPT: m_seqnum(seqnum) {}

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        Core::Seqnum m_seqnum;
    };

/*****************************************************************************/

    class Engine::Job::EventPartitionInUse: public Engine::Job::Event {

    public:
        EventPartitionInUse(Core::Seqnum seqnum) IPL_NOEXCEPT: m_seqnum(seqnum) {}

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        Core::Seqnum m_seqnum;
    };

/*****************************************************************************/

    class Engine::Job::EventNoSuchPartition: public Engine::Job::Event {

    public:
        EventNoSuchPartition(Core::Seqnum seqnum) IPL_NOEXCEPT: m_seqnum(seqnum) {}
        // TODO: common base

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        const Core::Seqnum m_seqnum;  // TODO: const 'em all!
    };

/*****************************************************************************/

    class Engine::Job::EventNotAllowed: public Engine::Job::Event {

    public:
        EventNotAllowed(Core::Seqnum seqnum) IPL_NOEXCEPT: m_seqnum(seqnum) {}

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        Core::Seqnum m_seqnum;
    };

/*****************************************************************************/

    class Engine::Job::EventVersion: public Engine::Job::Event {

    public:
        EventVersion(Core::Seqnum seqnum, const Version &version) IPL_NOEXCEPT:
            m_seqnum(seqnum), m_version(version) {}
        // TODO: common base

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        const Core::Seqnum m_seqnum;  // TODO: const 'em all!
        const Version m_version;
    };

/*****************************************************************************/

    class Engine::Job::EventNoSuchValue: public Engine::Job::Event {

    public:
        EventNoSuchValue(const Name &partition, const Key& key, bool is_failed = false) IPL_NOEXCEPT:
            m_update(true), m_partition(partition), m_key(key), m_is_failed(is_failed) {}
        EventNoSuchValue(Core::Seqnum seqnum, const Key& key, bool is_failed = false) IPL_NOEXCEPT:
            m_update(false), m_seqnum(seqnum), m_partition(-1), m_key(key), m_is_failed(is_failed) {}

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        bool m_update;
        Core::Seqnum m_seqnum;
        Name m_partition;
        Key m_key;
        bool m_is_failed;
    };

/*****************************************************************************/

    class Engine::Job::EventValueInt: public Engine::Job::Event {

    public:
        EventValueInt(const Name &partition, const Key& key, Int value) IPL_NOEXCEPT:
            m_update(true), m_partition(partition), m_key(key), m_value(value) {}
        EventValueInt(Core::Seqnum seqnum, const Key& key, Int value) IPL_NOEXCEPT:
            m_update(false), m_seqnum(seqnum), m_partition(-1), m_key(key), m_value(value) {}

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        bool m_update;
        Core::Seqnum m_seqnum;
        Name m_partition;
        Key m_key;
        Int m_value;
    };

/*****************************************************************************/

    class Engine::Job::EventValueString: public Engine::Job::Event {

    public:
        EventValueString(const Name &partition, const Key& key, const String &value) IPL_NOEXCEPT:
            m_update(true), m_partition(partition), m_key(key), m_value(value) {}
        EventValueString(Core::Seqnum seqnum, const Key& key, const String &value) IPL_NOEXCEPT:
            m_update(false), m_seqnum(seqnum), m_partition(-1), m_key(key), m_value(value) {}

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        bool m_update;
        Core::Seqnum m_seqnum;
        Name m_partition;
        Key m_key;
        String m_value;
    };

/*****************************************************************************/

    class Engine::Job::EventValueBlob: public Engine::Job::Event {

    public:
        EventValueBlob(const Name &partition, const Key& key, const Blob &value) IPL_NOEXCEPT:
            m_update(true), m_partition(partition), m_key(key), m_value(value) {}
        EventValueBlob(Core::Seqnum seqnum, const Key& key, const Blob &value) IPL_NOEXCEPT:
            m_update(false), m_seqnum(seqnum), m_partition(-1), m_key(key), m_value(value) {}

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        bool m_update;
        Core::Seqnum m_seqnum;
        Name m_partition;
        Key m_key;
        BlobImpl m_value;
    };

/*****************************************************************************/

    class Engine::Job::EventEnd: public Engine::Job::Event {

    public:
        EventEnd() IPL_NOEXCEPT: m_update(true) {}
        EventEnd(Core::Seqnum seqnum) IPL_NOEXCEPT:
            m_update(false), m_seqnum(seqnum) {}

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        bool m_update;
        Core::Seqnum m_seqnum;
    };

/*****************************************************************************/

    class Engine::Job::EventKeys: public Engine::Job::Event {

    public:
        EventKeys(Core::Seqnum seqnum, const KeyList& keys) IPL_NOEXCEPT:
            m_seqnum(seqnum), m_keys(keys) {}

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        Core::Seqnum m_seqnum;
        KeyList m_keys;
    };

/*****************************************************************************/

    class Engine::Job::EventAllFlushed: public Engine::Job::Event {

    public:
        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;
    };

/*****************************************************************************/

    /*!
        \brief Interface for concrete PersistenceA::Factory configurations and -factories
    */
    class Engine::Factory {

    public:
        virtual ~Factory() IPL_NOEXCEPT;

        virtual Engine *createEngine(Core &core,
                                     const ipl::string &backend_name,
                                     const util::config::Value &config_array) IPL_NOEXCEPT=0;
    };

/*****************************************************************************/

}  // end of namespace persistence

/*****************************************************************************/
#endif
