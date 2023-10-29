/********************************************************************************
 * @brief Contains functionality for using loop units.
 ********************************************************************************/
#pragma once

#include <cstdint>
#include <limits>
#include <list>
#include <sensor.hpp>

namespace devices {

/********************************************************************************
 * @brief Class for implementation of loop units capable of holding specified
 *        number of sensors.
 * 
 * @tparam MaxNumSensors The maximum number of sensors the loop unit can hold.
 ********************************************************************************/
template <std::uint16_t MaxNumSensors>
class LoopUnit {
    static_assert(MaxNumSensors > 0, "Maximum number of sensors cannot be set to 0!");
  public:
 
    /********************************************************************************
     * @brief Creates new loop unit.
     ********************************************************************************/
    constexpr LoopUnit(void) = default;

    /********************************************************************************
     * @brief Deleted memory for all sensors before deletion of the loop unit.
     ********************************************************************************/
    ~LoopUnit(void) { removeAllSensors(); }

    /********************************************************************************
     * @brief Provides the loop unit ID when assigning to an object of 
     *        type std::int32_t.
     * 
     * @return The loop unit ID as an unsigned integer.
     ********************************************************************************/
    operator std::uint32_t() const { return id_; }

    /********************************************************************************
     * @brief Assigns the loop unit ID object to specified output stream when using 
     *        the << operator.
     * 
     * @param ostream   Reference to the output stream to assign.
     * @param loop_unit Reference to loop unit whose ID is assigned to the 
     *                  output stream.
     * 
     * @return Reference to the output stream after assigning the loop unit ID.
     ********************************************************************************/
    friend std::ostream& operator<<(std::ostream& ostream, const LoopUnit& loop_unit) {
        return ostream << loop_unit.id_;
    }

    /********************************************************************************
     * @brief Provides the sensors held by the loop unit.
     * 
     * @return Reference to list holding the sensors held by the loop unit.
     ********************************************************************************/
    const std::list<Sensor*>& sensors(void) const { return sensors_; }

    /********************************************************************************
     * @brief Provides the maximum number of sensors the loop unit can hold.
     * 
     * @return The maximum number of sensors the loop unit can hold as an 
     *         unsigned integer.
     ********************************************************************************/
    std::uint16_t capacity(void) const { return MaxNumSensors; }

    /********************************************************************************
     * @brief Provides the loop unit ID.
     * 
     * @return The loop unit ID as an unsigned integer.
     ********************************************************************************/
    std::uint32_t id(void) const { return id_; }

    /********************************************************************************
     * @brief Provides the number of sensors currently held by the loop unit.
     * 
     * @return The number of sensors currently held by the loop unit as an 
     *         unsigned integer.
     ********************************************************************************/
    std::size_t numSensors(void) const { return sensors_.size(); }

    /********************************************************************************
     * @brief Indicates if the loop unit is full.
     * 
     * @return True if the loop unit is full, else false.
     ********************************************************************************/
    bool full(void) const { return numSensors() >= capacity(); }

  public:

    /********************************************************************************
     * @brief Adds specified number of sensors to the loop unit.
     * 
     * @param min_val         The minimum data value each new sensor can hold.
     * @param max_val         The minimum data value each new sensor can hold.
     * @param num_new_sensors The number of new sensors to add.
     * @param enabled         The state of each sensor after creation 
     *                        (default = disabled).
     * 
     * @return True if at least one sensor was added, else false.
     ********************************************************************************/
    bool addSensors(const std::uint32_t min_val, 
                    const std::uint32_t max_val, 
                    const std::size_t num_new_sensors = std::numeric_limits<std::uint32_t>::max(),
                    const bool enabled = false) {
        if (full()) { return false; }
        for (std::size_t i{}; i < num_new_sensors && numSensors() < capacity(); ++i) {
            addSensor(min_val, max_val, enabled);
        }
        return true;
    }

    /********************************************************************************
     * @brief Removes all sensors associated with the loop unit.
     ********************************************************************************/
    void removeAllSensors(void) {
        for (auto& sensor: sensors_) {
            delete sensor;
        }
        sensors_.clear();
    }

    /********************************************************************************
     * @brief Adds new sensor to the loop unit.
     * 
     * @param min_val The minimum data value the new sensor can hold.
     * @param max_val The minimum data value the new sensor can hold.
     * @param enabled The state of the sensor after creation (default = disabled).
     * 
     * @return True if the sensor was added, else false.
     ********************************************************************************/
    bool addSensor(const std::uint32_t min_val,
                   const std::uint32_t max_val,
                   const bool enabled = false) {
        if (full()) { return false; }
        Sensor* sensor{new Sensor{min_val, max_val, enabled}};
        return addSensor(sensor);
    }

    /********************************************************************************
     * @brief Adds new sensor to the loop unit.
     * 
     * @param new_sensor Reference to the sensor to add.
     * 
     * @return True if the sensor was added, else false.
     ********************************************************************************/
    bool addSensor(Sensor& new_sensor) { return addSensor(&new_sensor); }

    /********************************************************************************
     * @brief Adds new sensor to the loop unit.
     * 
     * @param new_sensor Reference to the sensor to add.
     * 
     * @return True if the sensor was added, else false.
     ********************************************************************************/
    bool addSensor(Sensor* new_sensor) {
        if (full() || new_sensor == nullptr) { return false; }
        sensors_.push_back(new_sensor);
        return true;
    }

    /********************************************************************************
     * @brief Provides a reference to sensor with specified ID, if it exists.
     * 
     * @param sensor_id ID of the searched sensor.
     * 
     * @return A pointer to the sensor if it exists, else a nullptr.
     ********************************************************************************/
    constexpr Sensor* getSensor(const std::uint32_t sensor_id) const {
        for (const auto& sensor: sensors_) {
            if (sensor->id() == sensor_id) { 
                return sensor; 
            }
        }
        return nullptr;
    }

    /********************************************************************************
     * @brief Removes sensor with specified ID, if it exists.
     * 
     * @param sensor_id ID of the sensor to remove.
     * 
     * @return True if the sensor was removed, false it the sensor wasn't found.
     ********************************************************************************/
    constexpr bool removeSensor(const std::uint32_t sensor_id) {
        auto sensor{getSensor(sensor_id)};
        if (sensor == nullptr) { return false; }
        sensors_.remove(sensor);
        delete sensor;
        return true;
    }

    /********************************************************************************
     * @brief Polls all sensors associated with the poll unit.
     ********************************************************************************/
    void poll(void) {
        for (auto& sensor: sensors()) {
            sensor->read();
        }
    }

    /********************************************************************************
     * @brief Prints information about the unit and all associated sensors.
     * 
     * @param ostream Reference to output stream (default = terminal print).
     ********************************************************************************/
    void print(std::ostream& ostream = std::cout) const {
        if (numSensors() == 0) { return; }
        std::size_t num_printed_sensors{};
        ostream << "--------------------------------------------------------------------------------\n";
        ostream << "Loop unit ID:\t\t\t" << id_ << "\n";
        ostream << "Number of connected sensors:\t" << numSensors() << "\n\n";
        for (const auto& sensor: sensors()) {
            sensor->print(ostream, false);
            if (++num_printed_sensors < numSensors()) { ostream << "\n"; }
        }
        ostream << "--------------------------------------------------------------------------------\n\n";
    }

  private:
    std::list<Sensor*> sensors_{};
    std::uint32_t id_{getDeviceId()};
};

} /* namespace devices */