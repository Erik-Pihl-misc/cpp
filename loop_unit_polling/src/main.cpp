/********************************************************************************
 * @brief Implementation of multiple loop units with associated sensors.
 *        Since no hardware is used, the sensors are assigned randomized values.
 ********************************************************************************/
#include <iostream>
#include <array>
#include <timer.hpp>
#include <loop_unit.hpp>

using namespace devices;
using namespace timer;

namespace {

/********************************************************************************
 * @brief Initializes loop units by adding sensors with specified parameters.
 * 
 * @tparam NumLoopUnits The number of loop units to add.
 * @tparam NumSensors   The number of sensors to add to each loop unit.
 * 
 * @param loop_units Reference to array holding the loop units to initialize.
 * @param min_val    The minimum data value each sensor can hold.
 * @param max_val    The maximum data value each sensor can hold.
 * @param enabled    The state of each sensor after creation (default = disabled).
 ********************************************************************************/
template <std::size_t NumLoopUnits, std::uint16_t NumSensors>
void initLoopUnits(const std::array<LoopUnit<NumSensors>*, NumLoopUnits>& loop_units,
                   const uint32_t min_val,
                   const uint32_t max_val,
                   const bool enabled = false) {
    for (auto& loop_unit : loop_units) {
        loop_unit->addSensors(min_val, max_val, NumSensors, enabled);
    }
}

/********************************************************************************
 * @brief Runs all loop units. Every time the poll timer elapses, a specific 
 *        loop unit polls all it's associated sensors. After the polling is
 *        complete, information about the loop unit is printed.
 *        
 * @tparam NumLoopUnits The number of loop units to run.
 * @tparam NumSensors   The number of sensors associated with each loop unit.
 * 
 * @param loop_units Reference to array holding the loop units.
 * @param poll_timer Reference to poll timer used for setting the polling
 *                   frequency.
 * @param ostream    Reference to output stream (default = terminal print).
 ********************************************************************************/
template <std::size_t NumLoopUnits, std::uint16_t NumSensors>
void runLoopUnits(std::array<LoopUnit<NumSensors>*, NumLoopUnits>& loop_units, 
                  Timer& poll_timer,
                  std::ostream& ostream = std::cout) {
    for (auto& loop_unit : loop_units) {
        while (!poll_timer.elapsed()) {}
        loop_unit->poll();
        loop_unit->print(ostream);
    }
}

} /* namespace */

/********************************************************************************
 * @brief Creates two loop units holding five sensors each. A poll timer is set
 *        to elapse every 1000 ms. The loop units take turns polling every time
 *        the poll timer elapses. After each poll, information about the loop
 *        unit is printed in the terminal.
 * 
 * @return Success code 0 upon termination of the program.
 ********************************************************************************/
int main(void) {
    LoopUnit<5> loop1, loop2;
    Timer poll_timer{Milliseconds(1000)};
    std::array<LoopUnit<5>*, 2> loop_units{&loop1, &loop2};

    initLoopUnits(loop_units, 0, 255, true);
    poll_timer.start();
    
    while (1) {
        runLoopUnits(loop_units, poll_timer);
    }
    return 0;
}