#include "timer.hpp"

namespace timer {

namespace {

template <typename T>
constexpr double ns_to_s(const T time_ns) {
    static_assert(std::is_arithmetic<T>::value, 
        "Non-arithmetic type specified for time value!");
    constexpr double divisor{1000000000.0};
    return time_ns / divisor;
}

} /* namespace */

Timer::Timer(const std::uint64_t elapse_time_ns, const bool enabled) {
    init(elapse_time_ns, enabled);
}

bool Timer::init(const std::uint64_t elapse_time_ns, const bool enabled) {
    if (setElapseTime_ns(elapse_time_ns)) {
        if (enabled) {
            start();
        }
        return true;
    } else {
        return false;
    }
}

void Timer::start(void) {
    start_time_ = currentTime();
    enabled_ = true;
}

void Timer::toggle(void) {
    if (enabled_) {
        stop();
    } else {
        start();
    }
}

bool Timer::elapsed(void) {
    if (enabled_ && getElapseTime_ns() && timeDelta_s() >= timeElapsed_s()) {
        start_time_ = currentTime();
        return true;
    } else {
        return false;
    }
}

std::uint64_t Timer::getElapseTime_ns(void) const { 
    return elapse_time_ns_.count(); 
}

std::uint64_t Timer::getElapseTime_us(void) const { 
    return Nanoseconds{getElapseTime_ns()}.getTime_us(); 
}

std::uint64_t Timer::getElapseTime_ms(void) const { 
    return Nanoseconds{getElapseTime_ns()}.getTime_ms(); 
}

std::uint64_t Timer::getElapseTime_s(void) const { 
    return Nanoseconds{getElapseTime_ns()}.getTime_s(); 
}

double Timer::getElapseFrequency_hz(void) const { 
    return Nanoseconds{getElapseTime_ns()}.getFrequency_hz();
}

bool Timer::setElapseTime_ns(const std::uint64_t elapse_time_ns) {
    if (elapse_time_ns >= 0) {
        elapse_time_ns_ = std::chrono::nanoseconds{elapse_time_ns};
        return true;
    } else {
        return false;
    }
}

bool Timer::setFrequency_hz(const double frequency_hz) {
    if (frequency_hz >= 0) {
        elapse_time_ns_ = std::chrono::nanoseconds{Hertz(frequency_hz)};
        return true;
    } else {
        return false;
    }
}

double Timer::timeElapsed_s(void) const { 
    return ns_to_s(getElapseTime_ns());
}

double Timer::timeDelta_s(void) const {
    std::chrono::duration<double> elapsed_time_s{currentTime() - start_time_};
    return elapsed_time_s.count();
}

std::chrono::time_point<std::chrono::system_clock> Timer::currentTime(void) {
    return std::chrono::system_clock::now();
}

} /* namespace timer */