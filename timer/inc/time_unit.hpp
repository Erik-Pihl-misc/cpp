/********************************************************************************
 * @brief Contains classes for different time units.
 ********************************************************************************/
#pragma once

#include <iostream>
#include <type_traits>
#include <cstdint>

namespace timer {

class Timer;

/********************************************************************************
 * @brief Type trait for indicating if specified type is a timer.
 * 
 * @tparam T Specified type to check.
 * 
 * @param value Set to true when specified type is a timer, else false.
 ********************************************************************************/
template <typename T>
struct IsTimer {
    const static bool value{false};
};

/********************************************************************************
 * @brief Setting the value parameter of the IsTimer type trait to true when
 *        specified type is a timer, i.e. an object of class timer::Timer. 
 ********************************************************************************/
template <>
struct IsTimer<Timer>
{
    const static bool value{true};
};

/********************************************************************************
 * @brief Base class for time unit classes.
 ********************************************************************************/
class TimeUnit {
  public:

    /********************************************************************************
     * @brief Provides the time held by TimeUnit object when using the assignment 
     *        operator.
     * 
     * @tparam T The type of the assigned object (integral type or timer).
     ********************************************************************************/
    template <typename T>
    operator T() const {
        static_assert(std::is_arithmetic<T>::value || IsTimer<T>::value, 
            "Cannot convert time to non-arithmetic type!");
        return static_cast<T>(time_);
    }

    /********************************************************************************
     * @brief Rounds floating number to nearest integer.
     * 
     * @tparam T Integral type of the rounded integer.
     * 
     * @param number The floating point number to round.
     * 
     * @return The nearest integral value.
     ********************************************************************************/
    template <typename T>
    static constexpr T round(const double number) {
        static_assert(std::is_integral<T>::value, "Cannot round to non-integral type!");
        return static_cast<T>(number + 0.5);
    }

    /********************************************************************************
     * @brief Provides the time held by time unit object in the unit specified
     *        when creating the object.
     * 
     * @return The time held by the unit object.
     ********************************************************************************/
    constexpr std::uint64_t getTime(void) const { 
        return static_cast<std::uint64_t>(time_ / multiplier_); 
    }

    /********************************************************************************
     * @brief Provides the time held by time unit object in nanoseconds.
     * 
     * @return The time held by the unit object in nanoseconds.
     ********************************************************************************/
    constexpr std::uint64_t getTime_ns(void) const { 
        return static_cast<std::uint64_t>(time_); 
    }

     /********************************************************************************
     * @brief Provides the time held by time unit object in microseconds.
     * 
     * @return The time held by the unit object in microseconds.
     ********************************************************************************/
    constexpr std::uint64_t getTime_us(void) const { 
        return static_cast<std::uint64_t>(time_ / Multiplier<std::uint64_t>::ONE_THOUSAND); 
    }

    /********************************************************************************
     * @brief Provides the time held by time unit object in the milliseconds.
     * 
     * @return The time held by the unit object in milliseconds.
     ********************************************************************************/
    constexpr std::uint64_t getTime_ms(void) const { 
        return static_cast<std::uint64_t>(time_ / Multiplier<std::uint64_t>::ONE_MILLION); 
    }

    /********************************************************************************
     * @brief Provides the time held by time unit object in seconds.
     * 
     * @return The time held by the unit object in seconds.
     ********************************************************************************/
    constexpr std::uint64_t getTime_s(void) const { 
        return static_cast<std::uint64_t>(time_ / Multiplier<std::uint64_t>::ONE_BILLION); 
    }

    /********************************************************************************
     * @brief Provides the time held by time unit object as frequency measured in Hz.
     * 
     * @return The time held by the unit object as a frequency in Hz.
     ********************************************************************************/
    constexpr double getFrequency_hz(void) const {
        return time_ > 0 ? Multiplier<double>::ONE_BILLION / time_ : 0;
    }

    /********************************************************************************
     * @brief Assigns the time held by time unit object to specified output
     *        stream when using the << operator.
     * 
     * @param ostream   Reference to the output stream to assign.
     * @param time_base Reference to time unit object holding the time to assign.
     * 
     * @return Reference to the output stream after assigning the time.
     ********************************************************************************/
    friend std::ostream& operator<<(std::ostream& ostream, const TimeUnit& time_base) {
        return ostream << time_base.getTime();
    }

  protected:
    TimeUnit(void) = default;
    TimeUnit(const std::uint64_t time, const std::uint32_t multiplier = 1) 
        : time_{static_cast<std::uint64_t>(time * multiplier)}, multiplier_{multiplier} { }
        
    template <typename T = std::uint64_t>
    struct Multiplier {
        static_assert(std::is_arithmetic<T>::value, 
            "Numbers cannot be converted to non-arithmetic type!\n");
        static constexpr T ONE_BILLION{static_cast<T>(1000000000)};
        static constexpr T ONE_MILLION{static_cast<T>(1000000)};
        static constexpr T ONE_THOUSAND{static_cast<T>(1000)};
    };

  private:
    const std::uint64_t time_{};
    const std::uint32_t multiplier_{1};
    
};

/********************************************************************************
 * @brief Time unit class for holding time measured in nanoseconds.
 ********************************************************************************/
class Nanoseconds : public TimeUnit {
  public:
    /********************************************************************************
     * @brief Creates new object holding specified time in nanoseconds.
     * 
     * @param time_ns The time to hold measured in nanoseconds.
     *******************************************************************************/
    Nanoseconds(const std::uint64_t time_ns) : TimeUnit{time_ns} { }
};

/********************************************************************************
 * @brief Time unit class for holding time measured in microseconds.
 ********************************************************************************/
class Microseconds : public TimeUnit {
  public:
    /********************************************************************************
     * @brief Creates new object holding specified time in microseconds.
     * 
     * @param time_us The time to hold measured in microseconds.
     *******************************************************************************/
    Microseconds(const std::uint64_t time_us) 
        : TimeUnit{time_us, Multiplier<std::uint64_t>::ONE_THOUSAND} {}
};

/********************************************************************************
 * @brief Time unit class for holding time measured in milliseconds.
 ********************************************************************************/
class Milliseconds : public TimeUnit {
  public:
    /********************************************************************************
     * @brief Creates new object holding specified time in milliseconds.
     * 
     * @param time_ms The time to hold measured in milliseconds.
     *******************************************************************************/
    Milliseconds(const std::uint64_t time_ms) 
        : TimeUnit{time_ms, Multiplier<std::uint64_t>::ONE_MILLION} {}
};

/********************************************************************************
 * @brief Time unit class for holding time measured in seconds.
 ********************************************************************************/
class Seconds : public TimeUnit {
  public:
    /********************************************************************************
     * @brief Creates new object holding specified time in seconds.
     * 
     * @param time_s The time to hold measured in seconds.
     *******************************************************************************/
    Seconds(const std::uint64_t time_s) 
        : TimeUnit{time_s, Multiplier<std::uint64_t>::ONE_BILLION} {}
};

/********************************************************************************
 * @brief Time unit class for holding time measured in seconds.
 ********************************************************************************/
class Hertz : public TimeUnit {
  public:
    /********************************************************************************
     * @brief Creates new object holding specified frequency in Hz.
     * 
     * @param frequency_hz The frequency to hold measured in Hz.
     *******************************************************************************/
    Hertz(const double frequency_hz) :
        TimeUnit{round<std::uint64_t>(getTime_ns(frequency_hz))} {}
  private:
    static constexpr double getTime_ns(const double frequency_hz) {
        return frequency_hz > 0 ? 
            Multiplier<std::uint64_t>::ONE_BILLION / frequency_hz : 0;
    }
};

} /* namespace timer */