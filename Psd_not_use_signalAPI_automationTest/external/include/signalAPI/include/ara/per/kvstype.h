/*****************************************************************************/
/*
    Copyright 2021 e.solutions GmbH
    All rights reserved

    contains the realization of 
        ADAPTIVE AUTOSAR - Specification of Persistency
        Part of Standard Release 17-10
*/
/*****************************************************************************/

#if defined(ESOFW_ARA_BACKPORT_17_10_FEATURES)
#ifndef ARA_PER_KVSTYPE_H_
#define ARA_PER_KVSTYPE_H_

#include <string> 
#include <memory>
#include <ara/core/internal/ara_dso.h>

// SWS_PER_00002
namespace ara {
namespace per {

//! \link2req{satisfies,req~ARA_SWS_PER_KVSTYPE_1710_COMPATIBLE~1}
class ARA_PER_EXPORT KvsType final {
public:

    // Internal Type
    enum class ValueType : std::uint8_t
    {
        kFloat,
        kDouble,
        kSInt8,
        kSInt16,
        kSInt32,
        kSInt64,
        kUInt8,
        kUInt16,
        kUInt32,
        kUInt64,
        kString,
        kBinary,
        kBoolean,
        kNotSet
    };

    // SWS_PER_00004
    enum class Status: std::uint8_t {
        kSuccess,
        kNotFound,
        kCheckSumError,
        kGeneralError
    };

    // SWS_PER_00006
    /*
     * \brief Default constructor; creates a KvsType without value
     *
     * \param[in] state The status of the KvsType; if kSuccess, the status
     * is changed to kGeneralError instead as success can only occur if
     * a value type CTOR was called
     */
    KvsType( KvsType::Status = Status::kNotFound ) noexcept;

    // Copy and move operators
    KvsType(KvsType const &) noexcept(false);
    KvsType &operator=(KvsType const &) noexcept(false);

    KvsType(KvsType &&) noexcept;
    KvsType &operator=(KvsType &&) noexcept;

    // SWS_PER_00005
    // !brief CTOR for bool value
    KvsType(bool value) noexcept;
    // !brief CTOR for signed 8bit Integer value
    KvsType(int8_t value) noexcept;
    // !brief CTOR for signed 16bit Integer value
    KvsType(int16_t value) noexcept;
    // !brief CTOR for signed 32bit Integer value
    KvsType(int32_t value) noexcept;
    // !brief CTOR for signed 64bit Integer value
    KvsType(int64_t value) noexcept;
    // !brief CTOR for unsigned 8bit Integer value
    KvsType(uint8_t value) noexcept;
    // !brief CTOR for unsigned 16bit Integer value
    KvsType(uint16_t value) noexcept;
    // !brief CTOR for unsigned 32bit Integer value
    KvsType(uint32_t value) noexcept;
    // !brief CTOR for unsigned 64bit Integer value
    KvsType(uint64_t value) noexcept;
    // !brief CTOR for float value
    KvsType(float value) noexcept;
    // !brief CTOR for double value
    KvsType(double value) noexcept;

    // !brief CTOR for string value
    KvsType(std::string const &value) noexcept(false);
    // !brief CTOR for cstring value
    KvsType(char const *value) noexcept(false);

    // SWS_PER_00007
    // !brief Plain-old-data type CTOR
    KvsType(void const *data, std::size_t len) noexcept(false);

    // SWS_PER_00008
    ~KvsType();

    /*
     * \brief Retrieve the type of the value stored
     */
    ValueType Type() const noexcept; 

    // SWS_PER_00150
    /*
     * \brief Retrieve the stored value as signed 32bit Integer
     * \throws ara::per::ExceptionLogicError if stored value
     *         is not an integer type
     */
    int32_t GetSInt() const noexcept(false);

    // SWS_PER_00151
    /*
     * \brief Retrieve the stored value as unsigned 32bit Integer
     * \throws ara::per::ExceptionLogicError if stored value
     *         is not an integer type
     */
    uint32_t GetUInt() const noexcept(false);

    // SWS_PER_00152
    /*
     * \brief Retrieve the stored value as signed 64bit Integer
     * \throws ara::per::ExceptionLogicError if stored value
     *         is not an integer type
     */
    int64_t GetSInt64() const noexcept(false);

    // SWS_PER_00153
    /*
     * \brief Retrieve the stored value as unsigned 64bit Integer
     * \throws ara::per::ExceptionLogicError if stored value
     *         is not an integer type
     */
    uint64_t GetUInt64() const noexcept(false);

    // SWS_PER_00154
    /*
     * \brief Retrieve the stored value as Float
     * \throws ara::per::ExceptionLogicError if stored value
     *         is not a floating point type
     */
    float GetFloat() const noexcept(false);

    // SWS_PER_00155
    /*
     * \brief Retrieve the stored value as Double
     * \throws ara::per::ExceptionLogicError if stored value
     *         is not a floating point type
     */
    double GetDouble() const noexcept(false);

    // SWS_PER_00156
    /*
     * \brief Retrieve the stored value as String
     * \throws ara::per::ExceptionLogicError if stored value
     *         is not a string
     */
    std::string GetString() const noexcept(false);

    // SWS_PER_00157
    /*
     * \brief Retrieve the stored value as Bool
     * \throws ara::per::ExceptionLogicError if stored value
     *         is not a bool
     */
    bool GetBool() const noexcept(false);

    // SWS_PER_00012
    /*
     * \brief Retrieve the stored value as binary stream with up
     *        to \a len characters
     * \param[out] data Pointer to buffer to fill
     * \param[in] len Size of buffer pointed to by \a data
     * \throws ara::per::ExceptionLogicError if stored value
     *         is not a binary stream
     */
    void GetBinary(void *data, std::size_t len) const noexcept(false);

    // !brief Retrieve the number of bytes in a binary stream
    // \throws ara::per::ExceptionLogicError if stored value
    //         is not a binary stream
    std::size_t BinarySize() const noexcept(false);

    // SWS_PER_00013
    // !brief Retrieve the status of the object
    Status GetStatus() const noexcept;

    // SWS_PER_00016
    /*
     * \brief Returns true if the stored value is a signed
     *        integer type. False otherwise.
     */
    bool IsSignedInteger() const noexcept;

    // SWS_PER_00017
    /*
     * \brief Returns true if the stored value is an unsigned
     *        integer type. False otherwise
     */
    bool IsUnsignedInteger() const noexcept;

private:
    class KvsTypeImpl;
    std::unique_ptr<KvsTypeImpl> pImpl;
};

} // namespace per
} // namespace ara

#endif // ARA_PER_KVSTYPE_H_

#endif // ESOFW_ARA_BACKPORT_17_10_FEATURES
