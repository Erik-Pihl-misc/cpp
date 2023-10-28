/********************************************************************************
 * @brief Contains functionality for using timers.
 ********************************************************************************/
#pragma once

#include <chrono>
#include <cstdint>
#include <time_unit.hpp>

namespace timer {

/********************************************************************************
 * @brief Class for using timers with selectable elapse time and control for
 *        staring and stopping.
 ********************************************************************************/
class Timer {

  public:

    /********************************************************************************
     * @brief Creates uninitialized timer.
     ********************************************************************************/
    Timer(void) = default;

    /********************************************************************************
     * @brief Creates new timer with specified elapse time.
     *
     * @param elapse_time_ns The elapse time in ns. 
     * @param enabled        Indicates if the timer is to be enabled at start 
     *                       (default = false).
     ********************************************************************************/
    Timer(const std::uint64_t elapse_time_ns, const bool enabled = false);

  public:

    /********************************************************************************
     * @brief Initializes timer with specified elapse time.
     *
     * @param elapse_time_ns The elapse time in ns. 
     * @param enabled        Indicates if the timer is to be enabled at start 
     *                       (default = false).
     * @return True upon successful initialization, else false.
     ********************************************************************************/
    bool init(const std::uint64_t elapse_time_ns, const bool enabled = false);

    /********************************************************************************
     * @brief Starts the timer.
     ********************************************************************************/
    void start(void);

    /********************************************************************************
     * @brief Stops the timer.
     ********************************************************************************/
    void stop(void) { enabled_ = false; }

    /********************************************************************************
     * @brief Toggles the timer.
     ********************************************************************************/
    void toggle(void);

    /********************************************************************************
     * @brief Indicates if the timer has elapsed.
     *
     * @return True if the timer has elapsed, else false.
     ********************************************************************************/
    bool elapsed(void);

    /********************************************************************************
     * @brief Provides the elapse time of the timer measured in nanoseconds.
     *
     * @return The elapse time of the timer in nanoseconds.
     ********************************************************************************/
    std::uint64_t getElapseTime_ns(void) const;

    /********************************************************************************
     * @brief Provides the elapse time of the timer measured in microseconds.
     *
     * @return The elapse time of the timer in microseconds.
     ********************************************************************************/
    std::uint64_t getElapseTime_us(void) const;

    /********************************************************************************
     * @brief Provides the elapse time of the timer measured in milliseconds.
     *
     * @return The elapse time of the timer in milliseconds.
     ********************************************************************************/
    std::uint64_t getElapseTime_ms(void) const;

    /********************************************************************************
     * @brief Provides the elapse time of the timer measured in seconds.
     *
     * @return The elapse time of the timer in seconds.
     ********************************************************************************/
    std::uint64_t getElapseTime_s(void) const;

    /********************************************************************************
     * @brief Provides the elapse frequency of the timer measured in Hz.
     *
     * @return
     *        The elapse frequency of the timer in Hz.
     ********************************************************************************/
    double getElapseFrequency_hz(void) const;

    /********************************************************************************
     * @brief Sets new elapse time of the timer measured in nanoseconds.
     *
     * @param time_ns The new elapse time of the timer measured in nanoseconds. 
     * 
     * @return True if a new elapse time was set, else false.
     ********************************************************************************/
    bool setElapseTime_ns(const std::uint64_t time_ns);

    /********************************************************************************
     * @brief Sets new elapse frequency of the timer measured in Hz.
     *
     * @param frequency_hz The new elapse frequency of the timer measured in Hz.
     * 
     * @return True if a new elapse frequency was set, else false.
     ********************************************************************************/
    bool setFrequency_hz(const double frequency_hz);

  private:
    std::chrono::nanoseconds elapse_time_ns_{};
    std::chrono::time_point<std::chrono::system_clock> start_time_{};
    bool enabled_{};
    
    double timeElapsed_s(void) const;
    double timeDelta_s(void) const;
    static std::chrono::time_point<std::chrono::system_clock> currentTime(void);
};

} /* namespace timer */