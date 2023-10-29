#include <sensor.hpp>

namespace devices {

namespace {

void initRandomGenerator(void) {
    static bool rand_initialized{false};
    if (!rand_initialized) {
        std::srand(std::time(nullptr));
        rand_initialized = true;
    }
}

void printDashedLine(std::ostream& ostream, const char* end = nullptr) {
    ostream << "--------------------------------------------------------------------------------\n";
    if (end) { ostream << end; }
}

} /* namespace */

std::uint32_t getDeviceId(void) {
    static std::uint32_t id{};
    return id++;
}

Sensor::Sensor(const std::uint32_t min_val, const std::uint32_t max_val, const bool enabled) 
    : min_val_{min_val}, max_val_{max_val}, enabled_{enabled} {
    initRandomGenerator();
}

Sensor::operator std::int32_t() const { return id_; }

std::ostream& operator<<(std::ostream& ostream, const Sensor& sensor) {
    return ostream << sensor.id_;
}

std::uint32_t Sensor::minVal(void) const { return min_val_; }
std::uint32_t Sensor::maxVal(void) const { return max_val_; }
std::uint32_t Sensor::id(void) const { return id_; }
std::uint32_t Sensor::data(void) const { return data_; }
bool Sensor::enabled(void) const { return enabled_; }
bool Sensor::eventFlagSet(void) const { return event_flag_; }

void Sensor::enable(void) { enabled_ = true; }
void Sensor::disable(void) { enabled_ = false; }
void Sensor::toggle(void) { enabled_ = !enabled_; }

bool Sensor::read(void) {
    if (!enabled_) { return false; }
    const auto old_val{data_};
    data_ = getRandomVal();
    event_flag_ = data_ != old_val;
    return true;
}

void Sensor::print(std::ostream& ostream, const bool print_dashes) {
    if (print_dashes) { printDashedLine(ostream); }
    ostream << "Sensor ID:\t\t\t" << id_ << "\n";
    ostream << "Sensor data:\t\t\t" << data_ << "\n";
    ostream << "Status:\t\t\t\t" << getStatusString() << "\n";
    ostream << "Event flag:\t\t\t" << getEventFlagString() << "\n";
    if (print_dashes) { printDashedLine(ostream, "\n"); }
}

std::uint32_t Sensor::getRandomVal(void) {
    return static_cast<std::uint32_t>((std::rand() % (max_val_ - min_val_)) + min_val_);
}

} /* devices */