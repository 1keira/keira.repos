/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_CALENDARTIME_HXX
#define OSAL_CALENDARTIME_HXX

// framework includes
#include <ipl_config.h>
#include <common/error/Error.hxx>

#include <osal/osal.hxx>
// for WIN32 shared object definition
#include <osal/osal_dso.h>

namespace osal
{

/**
 * \brief
 *    An object for getting and setting the systems calendar time

 *    This is an object that allows to retrieve and change the systems
 *    calendar time. Calendar time is mainly used for displaying it
 *    to the user via HMI and is not used for doing any time-based
 *    calculations like performance measuring and alike. Thus
 *    CalendarTime is only available on a *second* time unit
 *    resolution.
 *
 *    The calendar time operations on OS level can be seen as rather
 *    slow and thus the class design here is also not oriented on
 *    performance but mainly on usage.
 * \note
 *    An instance of this object may be copied and assigned plainly
 *    without harm.
 **/
class OSAL_EXPORT CalendarTime
{
public:
    /**
     * \brief
     *    An enum type to represent a certain weekday
     **/
    enum WeekDay
    {
        SUNDAY = 0,
        MONDAY = 1,
        TUESDAY = 2,
        WEDNESDAY = 3,
        THURSDAY = 4,
        FRIDAY = 5,
        SATURDAY = 6
    };

    /**
     * \brief
     *    Human readable variant of month values
     **/
    enum Month
    {
        JANUARY = 0,
        FEBRUARY = 1,
        MARCH = 2,
        APRIL = 3,
        MAY = 4,
        JUNE = 5,
        JULY = 6,
        AUGUST = 7,
        SEPTEMBER = 8,
        OCTOBER = 9,
        NOVEMBER = 10,
        DECEMBER = 11
    };

    //! specific calendar time error IDs
    enum CalendarTimeErrors
    {
        CHANGE_DATE_FAILED = 0,
        ASSEMBLE_DATE_FAILED,
        YEAR_OUT_OF_RANGE
    };

    //! CalendarTime specific error type
    static ipl::ErrorType Error;
public:
    /**
     * \brief
     *    Construct a new object for storing calendar time.

     *    If get_time is false then the default value of the date
     *    will be the beginning of the UNIX epoch (1.1.1970
     *    00:00:00)
     * \param[in]
     *    get_time If this is set to true then the current
     *    calendar time will automatically be retrieved and the
     *    object contains the current time after construction.
     * \errors
     *    none
     **/
    CalendarTime(const bool get_time);

    /**
     * \brief
     *    Set all object members to a new value.

     *    Allows to set day, month, year, hour, minute and second
     *    of the current object. This does not affect the system
     *    time but is merely an operation on the C++ object.
     *
     *    If an invalid date is set then no error will occur until
     *    an attempt is made to change the current system time via
     *    changeDate()
     **/
    void setDate(
        const uint16_t year,
        const Month month,
        const uint8_t day,
        const uint8_t hour,
        const uint8_t minute,
        const uint8_t second);

    /**
     * \brief
     *    Retrieve all individual calendar time values from the
     *    object

     *    Allows to get all primitive calendar time values from
     *    the object. This does not represent the current system
     *    time but merely the values stored in the C++ object.
     **/
    void getDate(
        uint16_t &year,
        Month &month,
        uint8_t &day,
        uint8_t &hour,
        uint8_t &minute,
        uint8_t &second) const;

    /**
     * \brief
     *    Retrieve the systems current calendar time from the OS.

     *    Performs a system call to get the currently set calendar
     *    time of the system.
     *
     *    This fills all object members with the corresponding OS
     *    information.
     * \errors
     *    none. Usually if no valid date is set in the system
     *    and/or no clock is available then you will get some
     *    fallback date e.g. the beginning of the UNIX epoch or
     *    something alike.
     **/
    void retrieveDate();

    /**
     * \brief
     *    Set the systems calendar time to the values currently
     *    set in this object

     *    Performs a system call to set the current system
     *    calendar time to the time currently represented by this
     *    C++ object. On POSIX this affects the CLOCK_REALTIME
     *    which may cause other time based functions to
     *    experience time skips.
     *
     *    OSAL takes precaution not to use CLOCK_REALTIME for
     *    logical time operations where possible. But as this
     *    affect the whole system there may be other programs that
     *    experience side effects by changing the system time.
     * \errors
     *    CalendarTime::Error with ID
     *
     *    - ASSEMBLE_DATE_FAILED if no valid date could be
     *    constructed from the information present in the object.
     *    - CHANGE_DATE_FAILED if    something else went wrong
     *    setting the date. This can mean that the specified date
     *    wasn't accepted or that something is wrong with the
     *    clock in the system.
     *
     *     SystemError with ID
     *
     *    - PERMISSION_DENIED if the caller has insufficient
     *    priveleges to perform the operation.
     *    - INVALID_PARAMETER if the date wasn't accepted or the
     *    clock isn't available in the system
     *    - INTEGRITY_ERROR on severe internal errors
     * \errorindicator
     *    via return code
     * \return
     *    true on error, false on success.
     **/
    bool changeDate();

    /**
     * \brief
     *    Return the current value for the year datum of the
     *    object
     * \return
     *    The current year value.
     **/
    uint16_t getYear() const;

    /**
     * \brief
     *    Return the current value for the month datum of the
     *    object
     * \return
     *    The current month value.
     **/
    Month getMonth() const;

    /**
     * \brief
     *    Return the current value for the day datum of the object
     * \return
     *    The current day value.
     **/
    uint8_t getDay() const;

    /**
     * \brief
     *    Return the current value for the hour datum of the
     *    object
     * \return
     *    The current hour value.
     **/
    uint8_t getHour() const;

    /**
     * \brief
     *    Return the current value for the minute datum of the
     *    object
     * \return
     *    The current minute value.
     **/
    uint8_t getMinute() const;

    /**
     * \brief
     *    Return the current value for the second datum of the
     *    object
     * \return
     *    The current second value.
     **/
    uint8_t getSecond() const;

    /**
     * \brief
     *    Returns the current day of the week
     * \note
     *    This cannot be explicitly set. It is calculated after
     *    every retrieveDate() call.
     **/
    WeekDay getWeekday() const;

    /**
     * \brief
     *     Sets the day of the week
     * \note
     *     The weekday only is guaranteed to correspond to the rest
     *     of the date values after a call to retrieveDate()
     **/
    void setWeekday(const WeekDay &wd);

    /**
     * \brief
     *    Set the value for the year datum of the object
     * \param[in] year
     *    The new year to set in the object.
     **/
    void setYear(const uint16_t year);

    /**
     * \brief
     *    Set the value for the month datum of the object
     * \param[in] month
     *    The new month to set in the object
     **/
    void setMonth(const Month month);

    /**
     * \brief
     *    Set the value for the day datum of the object
     * \param[in] day
     *    The new day to set in the object
     **/
    void setDay(const uint8_t day);

    /**
     * \brief
     *    Set the value for the hour datum of the object
     * \param[in] hour
     *    The new hour to set in the object
     **/
    void setHour(const uint8_t hour);

    /**
     * \brief
     *    Set the value for the minute datum of the object
     * \param[in] minute
     *    The new minute to set in the object.
     **/
    void setMinute(const uint8_t minute);

    /**
     * \brief
     *    Set the value for the second datum of the object
     * \param[in] second
     *    The new second to set in the object
     **/
    void setSecond(const uint8_t second);

    /**
     * \brief
     *     Set the calendar time from the given UNIX timestamp

     *     The given timestamp will be interpreted as a UNIX
     *     timestamp in milliseconds, starting from 01.01.1970
     *     00:00. Based on this timestamp the current calendar time
     *     will be set appropriately.
     **/
    void setTimestamp(const osal::TimeT unix_time);

    /**
     * \brief
     *     Get a UNIX timestamp corresponding to the currently set
     *     date

     *     The returned value is a UNIX timestamp in milliseconds,
     *     starting from 01.01.1970 00:00.
     *
     *     If the currently set date is invalid then -1 may be
     *     returned instead of a timestamp.
     **/
    osal::TimeT getTimestamp() const;

    /**
     * \brief
     *  Get the absolute time difference between two
     *  CalendarTime instances.

     *  The returned value will be the difference between
     *  t1 and t2 expressed in milliseconds, starting from
     *  01.01.1970 00:00.
     *
     *  If any of both parameters contain an invalid date
     *  -1 is returned.
     *
     * \param[in]
     *  t1, t2 The two calendar time instances for which
     *  a difference should be calculated.
     *
     * \errors
     *    CalendarTime::Error with ID
     *
     *    - ASSEMBLE_DATE_FAILED if no valid date could be
     *      constructed from the information present in the
     *      objects t1 or t2.
     *    - YEAR_OUT_OF_RANGE if the supplied year in any
     *      of t1 or t2 is less than 1970.
     *
     * \errorindicator
     *    via return code
     *
     * \return
     *    -1 on error, >=0 on success.
     **/
    static osal::TimeT getTimediff(
        const CalendarTime & t1,
        const CalendarTime & t2);

private: // functions
    friend class osal::Osal;

    static bool init();

    void resetToEpoch();
private: // members
    //! the primitive value for the year
    uint16_t m_year;
    //! the primitive value for the month in range 0 .. 11
    Month m_month;
    //! the primitive value for the day in range 1 .. 31
    uint8_t m_day;
    //! the primitive value for the hour in range 0 .. 23
    uint8_t m_hour;
    //! the primitive value for the minute in range 0 .. 59
    uint8_t m_minute;
    //! the primitive value for the second in range 0 .. 59
    uint8_t m_second;
    //! the current day of the week
    WeekDay m_weekday;
};

} // end namespace

#endif
