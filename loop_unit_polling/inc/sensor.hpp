/********************************************************************************
 * @brief Contains functionality for using sensors.
 ********************************************************************************/
#pragma once

#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>

namespace devices {

/********************************************************************************
 * @brief Provides a unique device identifier.
 * 
 * @return A unique identifier as an unsigned integer.
 ********************************************************************************/
std::uint32_t getDeviceId(void);

/********************************************************************************
 * @brief Class for implementation of sensors capable of storing values between
 *        specified minimum and maximum value.
 ********************************************************************************/
class Sensor {
  public:
    
    /********************************************************************************
     * @brief Creates new sensor with specified parameters.
     * 
     * @param min_val The minimum data value the sensor can hold.
     * @param max_val The minimum data value the sensor can hold.
     * @param enabled The state of the sensor after creation (default = disabled).
     ********************************************************************************/
    Sensor(const std::uint32_t min_val, const std::uint32_t max_val, const bool enabled = false);

    /********************************************************************************
     * @brief Provides the sensor ID when assigning to an object of type std::int32_t.
     * 
     * @return The sensor ID as an unsigned integer.
     ********************************************************************************/
    operator std::int32_t() const;

    /********************************************************************************
     * @brief Assigns the sensor ID object to specified output stream when using 
     *        the << operator.
     * 
     * @param ostream Reference to the output stream to assign.
     * @param sensor  Reference to sensor whose ID is assigned to the output stream.
     * 
     * @return Reference to the output stream after assigning the sensor ID.
     ********************************************************************************/
    friend std::ostream& operator<<(std::ostream& ostream, const Sensor& sensor);

    /********************************************************************************
     * @brief Provides the minimum data value the sensor can hold.
     * 
     * @return The minimum data value the sensor can hold as an unsigned integer.
     ********************************************************************************/
    std::uint32_t minVal(void) const; 

    /********************************************************************************
     * @brief Provides the maximum data value the sensor can hold.
     * 
     * @return The maximum data value the sensor can hold as an unsigned integer.
     ********************************************************************************/
    std::uint32_t maxVal(void) const;

    /********************************************************************************
     * @brief Provides the unique identifier of the sensor.
     * 
     * @return The sensor ID as an unsigned integer.
     ********************************************************************************/
    std::uint32_t id(void) const;

    /********************************************************************************
     * @brief Provides the data value held by the sensor.
     * 
     * @return The data value held by the sensor as an unsigned integer.
     ********************************************************************************/
    std::uint32_t data(void) const;

    /********************************************************************************
     * @brief Indicates if the sensor if enabled.
     * 
     * @return True if the sensor is enabled, else false.
     ********************************************************************************/
    bool enabled(void) const;

    /********************************************************************************
     * @brief Indicates if the sensor event flag is set, which occurs upon change
     *        of the stored data value.
     * 
     * @return True if the sensor event flag is set, else false.
     ********************************************************************************/
    bool eventFlagSet(void) const;

  public:

    /********************************************************************************
     * @brief Enables the sensor.
     ********************************************************************************/
    void enable(void);

    /********************************************************************************
     * @brief Disables the sensor.
     ********************************************************************************/
    void disable(void);

    /********************************************************************************
     * @brief Toggles the sensor.
     ********************************************************************************/
    void toggle(void);

    /********************************************************************************
     * @brief Reads the sensor if it's enabled.
     * 
     * @return True if a new value was read, else false.
     ********************************************************************************/
    bool read(void);

     /********************************************************************************
     * @brief Prints information about the sensor.
     * 
     * @param ostream      Reference to output stream (default = terminal print).
     * @param print_dashes Indicates if dashes are to be printed around the info.
     ********************************************************************************/ 
    void print(std::ostream& ostream = std::cout, const bool print_dashes = true);

  private:
    const std::uint32_t min_val_;
    const std::uint32_t max_val_;
    const std::uint32_t id_{getDeviceId()};
    std::uint32_t data_{};
    bool enabled_;
    bool event_flag_{false};

    std::uint32_t getRandomVal(void);
    constexpr const char* getStatusString(void) { return enabled_ ? "Enabled" : "Disabled"; }
    constexpr const char* getEventFlagString(void) { return event_flag_ ? "Set" : "Cleared"; }
};

} /* namespace devices */