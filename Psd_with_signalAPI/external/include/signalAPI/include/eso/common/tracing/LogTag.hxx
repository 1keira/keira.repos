/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_LOGTAG_HXX
#define TRACING_LOGTAG_HXX

#include <sstream>
#include <cstddef>
#include <memory>
#include <common/stdint.h>
#include <common/streams/ostream.hxx>
#include <common/types/vector.hxx>
#include <common/types/string.hxx>

namespace tracing
{
//! \brief Privacy Flags type constant definitions.
struct IPLCOMMON_EXPORT PrivacyFlagsType
{
    //! Flags for Frontend filtering.
    static const int16_t FILTER_FRONTEND = 0;
    //! Flags for Backend individual filtering.
    static const int16_t FILTER_BACKEND = 1;
    //! Flags for default backend filtering.
    static const int16_t FILTER_BACKEND_DEFAULT = 2;
    //! Default flags for messages without own flags.
    static const int16_t CONFIG_DEFAULT = 3;
};
}

/*****************************************************************************/
namespace tracing {

using LogTagType = uint32_t;
using LogTagGenType = uint8_t;

/*! \brief List of system default tag types.
 *      User can add own tag with IDs staring from TAG_LAST value.
 */
enum LogTagMain : LogTagType {
    TAG_TIMESTAMP_US,
    TAG_TLR_PRIVACY_FLAG,
    TAG_LAST
};

/*! \brief List of generic tag types. */
enum LogTagGenTypes : LogTagGenType {
    TAG_GEN_TYPE_U8       = 0x00,
    TAG_GEN_TYPE_U16      = 0x01,
    TAG_GEN_TYPE_U32      = 0x02,
    TAG_GEN_TYPE_U64      = 0x03,
    TAG_GEN_TYPE_U8_ARRAY = 0x04,
    TAG_GEN_TYPE_ENTRIES  = 0x05,
    TAG_GEN_INVALID       = 0xff
};

/*!
 * \brief
 *   A base class for Tags.

 * This class defines an interface for all tags. Every tag is identified by
 * unique id (type) and shall define how it shall be printed to console. The
 * backend can use it's own way how to handle tags from received message
 */
class LogTagBase {
public:
    //! \brief Default constructor.
    LogTagBase() = default;
    //! \brief Virtual default destructor.
    virtual ~LogTagBase() = default;

    //! \brief Get the size of the LogTag.
    virtual size_t getSize() const = 0;

    //! \brief Print Tag info into the stream.
    virtual void print(ipl::ostream &os) const = 0;

    /*!
     *    \brief
     *        Try to cast LogTag to given type.
     *
     *    \param
     *        type The \sa LogTagType.
     *    \return
     *        A valid \sa LogTagBase pointer when type matches, otherwise NULL.
     */
    virtual const void* cast(const LogTagType &type) const = 0;

    //! \brief Clones a LogTag instance
    virtual LogTagBase * clone() const = 0;

    //! \brief Equality comparison operator.
    virtual bool operator==(const LogTagBase& /*other*/) const {
        return false;
    }

    //! \brief Inequality comparison operator.
    virtual bool operator!=(const LogTagBase& other) const {
        return !(operator==(other));
    }

    //! \brief Get the \sa LogTagType.
    virtual LogTagType type() const = 0;

    //! \brief Get the generic \sa LogTagGenType.
    virtual LogTagGenType gen_type() const {return TAG_GEN_INVALID;}
};

using TagsList = ipl::vector<std::unique_ptr<LogTagBase>>;

/*!
 * \brief
 *   A simple tag class, that defines a pair of id and value
 */
template<typename valT>
class LogTag : public LogTagBase
{
protected:
    LogTagType m_type;
    valT m_value;
public:
    //! \brief Constructor.
    LogTag(LogTagType type, const valT& value) : m_type(type), m_value(value) {}
    //! \brief Virtual default destructor.
    ~LogTag() override = default;

    //! \sa LogTagBase::type.
    LogTagType type() const override{
        return m_type;
    }

    //! \sa LogTagBase::cast.
    const void* cast(const LogTagType &type) const override {return type == m_type?this:nullptr;}

    //! \sa Get the LogTag value
    valT value() const {
        return m_value;
    }

    //! \sa LogTagBase::getSize.
    size_t getSize() const override{
        return sizeof (valT);
    }

    //! \sa LogTagBase::clone.
    LogTagBase* clone() const override {
        return new LogTag(*this);
    }

    //! \sa LogTagBase::print.
    void print(ipl::ostream &os) const override {
        os << "[" << m_type << ":" << m_value << "]";
    }

    //! \sa LogTagBase::operator==.
    bool operator==(const LogTagBase& other) const override {
        if (decltype(this) otherPtrValue = (decltype(this)) other.cast(m_type)) {
            return otherPtrValue->m_type == m_type;
        }

        return false;
    }
};

//! Generic LogTag for a predefined types LogTagGenType
template<typename valT>
class LogTagGen : public LogTag<valT>
{
protected:
    LogTagGenType m_gen_type;

public:
    //! \brief Constructor.
    LogTagGen(const LogTagGenType generic_type, LogTagType type, const valT& value)
        : LogTag<valT>(type, value)
        , m_gen_type(generic_type)
    {}
    //! \brief Virtual default destructor.
    ~LogTagGen() override = default;

    //! \sa LogTagBase::gen_type.
    LogTagGenType gen_type() const override {return m_gen_type;}

    //! \sa LogTagBase::clone.
    LogTagBase* clone() const override {return new LogTagGen(*this);}

    //! \sa LogTagBase::print.
    void print(ipl::ostream &os) const override
    {
        os << "[" << LogTag<valT>::m_type << ":" << (uint32_t)m_gen_type << ":"
           << (uint64_t)LogTag<valT>::m_value << "]";
    }
};

//! Define generic LogTag for a byte array
class LogTagGenByteArray : public LogTag<std::size_t>
{
protected:
    //! The byte array
    std::vector<uint8_t> m_array;
    //! Optional array separator for printing
    std::string m_separator;
public:
    //! \brief Constructor.
    LogTagGenByteArray(
            const LogTagType type,
            const std::vector<uint8_t>& array,
            const std::string& separator="")
        : LogTag<std::size_t>(type, array.size())
        , m_array(array)
        , m_separator(separator)
    {}
    //! \brief Virtual default destructor.
    ~LogTagGenByteArray() override = default;

    //! \sa LogTagBase::clone.
    LogTagBase* clone() const override
    {
        return new LogTagGenByteArray(*this);
    }

    //! \sa LogTagBase::gen_type.
    LogTagGenType gen_type() const override {return TAG_GEN_TYPE_U8_ARRAY;}

    //! \sa LogTagBase::print.
    void print(ipl::ostream &os) const override
    {
        os << "[" << m_type << ":" << (uint32_t)TAG_GEN_TYPE_U8_ARRAY << ":" << (uint64_t) m_array.size() << ":";
        for (size_t i=0; i<m_array.size()-1; i++)
        {
            os << (uint32_t)m_array[i] << m_separator;
        }
        os << (uint32_t)m_array.back();
        os << "]";
    }

    //! \brief Get the generic byte array.
    std::vector<uint8_t> array() const
    {
        return m_array;
    }
};

//! Define LogTagTimestampUS tag (one of system default tags)
class LogTagTimestampUS : public LogTagGen<uint64_t>
{
public:
    //! \brief Constructor.
    explicit LogTagTimestampUS(uint64_t ts) : LogTagGen<uint64_t>(TAG_GEN_TYPE_U64, TAG_TIMESTAMP_US, ts){}
    //! \brief Virtual default destructor.
    ~LogTagTimestampUS() override = default;

    //! \brief Creation method as used by factories for \sa LogTagTimestampUS generation.
    static std::unique_ptr<LogTagBase> CreateMethod(const std::string &strValue)
    {
        return std::make_unique<LogTagTimestampUS>(std::stoull(strValue));
    }
};

//! Privacy flag value indicates presence of filter level specific flags
static constexpr uint32_t PRIV_FLAG_PER_LEVEL = 0xffffffff;
//! Unspecified privacy flag value
static constexpr uint32_t PRIV_FLAG_NONE      = 0xeeeeeeee;

//! Define LogTag for Privacy Flags
class LogTagTLRPrivacyFlag : public LogTagGen<uint32_t>
{
  public:
    //! Privacy info owner values
    static constexpr uint32_t TLR_PRIV_OWNER_UNDECIDED     = 0x00000001;

    //! Privacy info category values
    static constexpr uint32_t TLR_PRIV_CATEGORY_UNDECIDED  = 0x80000000;
    static constexpr uint32_t TLR_PRIV_LOCATION            = 0x40000000;
    static constexpr uint32_t TLR_PRIV_UNIQUE_ID           = 0x20000000;
    static constexpr uint32_t TLR_PRIV_COMM_CONTENT        = 0x10000000;
    static constexpr uint32_t TLR_PRIV_USER_RELATED        = 0x08000000;
    static constexpr uint32_t TLR_PRIV_NOT_CATEGORIZED     = 0x04000000;
    static constexpr uint32_t TLR_PRIV_GNSS                = 0x02000000;
    static constexpr uint32_t TLR_PRIV_AUDIO_VIDEO_PICTURE = 0x01000000;
    static constexpr uint32_t TLR_PRIV_VIN                 = 0x00800000;

    //! \brief Constructor.
    explicit LogTagTLRPrivacyFlag(uint32_t flag) : LogTagGen<uint32_t>(TAG_GEN_TYPE_U32, TAG_TLR_PRIVACY_FLAG, flag){}
    //! \brief Virtual default destructor.
    ~LogTagTLRPrivacyFlag() override = default;

    //! \brief Creation method as used by factories for \sa LogTagTLRPrivacyFlag generation.
    static std::unique_ptr<LogTagBase> CreateMethod(const std::string &strValue)
    {
        return std::make_unique<LogTagTLRPrivacyFlag>(static_cast<uint32_t>(std::stoull(strValue)));
    }

    //! \brief Translate the privacy flags bit field into concatenated string of related letters.
    ipl::string getPrivacyFlagString() const
    {
        uint32_t value = (uint32_t)this->value();
        ipl::string flags;

        if (value & TLR_PRIV_OWNER_UNDECIDED)
            flags += 'U';

        if (value & TLR_PRIV_CATEGORY_UNDECIDED)
            flags += 'u';
        if (value & TLR_PRIV_LOCATION)
            flags += 'l';
        if (value & TLR_PRIV_UNIQUE_ID)
            flags += 'i';
        if (value & TLR_PRIV_COMM_CONTENT)
            flags += 'c';
        if (value & TLR_PRIV_USER_RELATED)
            flags += 'r';
        if (value & TLR_PRIV_NOT_CATEGORIZED)
            flags += 'n';
        if (value & TLR_PRIV_GNSS)
            flags += 'g';
        if (value & TLR_PRIV_AUDIO_VIDEO_PICTURE)
            flags += 'a';
        if (value & TLR_PRIV_VIN)
            flags += 'v';

        return flags;
    }

    //! \brief Translate a privacy flags string into privacy flags bit field.
    static uint32_t getPrivacyFlagsBitField(const std::string & str, const bool set_default_flags = true)
    {
        uint32_t flags = 0;

        auto it = str.begin();
        while (it != str.end())
        {
            switch(*it)
            {
            case 'U': flags |= TLR_PRIV_OWNER_UNDECIDED; break;

            case 'u': flags |= TLR_PRIV_CATEGORY_UNDECIDED; break;
            case 'l': flags |= TLR_PRIV_LOCATION; break;
            case 'i': flags |= TLR_PRIV_UNIQUE_ID; break;
            case 'c': flags |= TLR_PRIV_COMM_CONTENT; break;
            case 'r': flags |= TLR_PRIV_USER_RELATED; break;
            case 'n': flags |= TLR_PRIV_NOT_CATEGORIZED; break;
            case 'g': flags |= TLR_PRIV_GNSS; break;
            case 'a': flags |= TLR_PRIV_AUDIO_VIDEO_PICTURE; break;
            case 'v': flags |= TLR_PRIV_VIN; break;

            default: break;
            }
            it++;
        }

        if (set_default_flags)
        {
            if ((flags & 0x0000003f) == 0)
                flags |= TLR_PRIV_OWNER_UNDECIDED;
            if ((flags & 0xff800000) == 0)
                flags |= TLR_PRIV_CATEGORY_UNDECIDED;
        }
        return flags;
    }

    //! \brief Check if given value is a valid known privacy flag.
    static bool isValid(const uint32_t privacy_flag)
    {
        bool valid = true;

        if ((privacy_flag & 0x007fffc0) > 0)
            valid = false;

        return valid;
    }
};


//! \brief Allows to append tags into existing tags list.
inline TagsList& append_tags(TagsList &list) {return list;}

//! \brief Allows to append tags into existing tags list.
template<typename T1, typename... Types>
TagsList& append_tags(TagsList &list, T1 &&t1, Types&&... args)
{
    list.emplace_back(std::unique_ptr<T1>((T1*)t1.clone()));

    return append_tags(list, std::forward<Types>(args)...);
}

}

/*****************************************************************************/
#endif /* TRACING_LOGTAG_HXX */

