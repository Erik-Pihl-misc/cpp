/********************************************************************************
 * @brief Example of polling frequency controlled via a poll timer.
 ********************************************************************************/
#include <iostream>
#include <iomanip>
#include <vector>
#include <type_traits>
#include <thread>
#include <chrono>
#include <timer.hpp>

namespace {

/********************************************************************************
 * @brief Blocks the calling thread for specified amount of time.
 * 
 * @param time_ms The time to block the calling thread, measured in milliseconds.
 ********************************************************************************/
void wait(const std::size_t time_ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(time_ms));
}

/********************************************************************************
 * @brief Prints content of arithmetic vector to specified output stream.
 * 
 * @tparam T The vector type.
 * 
 * @param data         Reference to vector containing the content to print.
 * @param ostream      Reference to output stream (default = the terminal).
 * @param num_decimals The number of decimals to print if floating-point 
 *                     numbers are to be printed (default = 1).
 ********************************************************************************/
template <typename T>
void print(const std::vector<T>& data, 
           std::ostream& ostream = std::cout, 
           const std::size_t num_decimals = 1) {
    static_assert(std::is_arithmetic<T>::value, 
        "Printing vector content only available for arithmetic values!");
    if (data.empty()) { return; }
    ostream << std::fixed << std::setprecision(num_decimals);
    ostream << "--------------------------------------------------------------------------------\n";
    for (const auto& num: data) {
        ostream << num << "\n";
    }
    ostream << "--------------------------------------------------------------------------------\n\n";
}

/********************************************************************************
 * @brief Provides string containing the specified polling number with the
 *        corresponding ending, such as 1st, 2nd, 3rd, 4th, 5th etc.
 * 
 * @param num The polling number.
 * 
 * @return String holding the polling number with the corresponding ending.
 ********************************************************************************/
 std::string getPollNumberString(const std::size_t num) {
    auto getNumericEnding = [](const std::size_t num) {
        if (num == 1)      { return "st"; }
        else if (num == 2) { return "nd"; }
        else if (num == 3) { return "rd"; }
        else               { return "th"; }
    };
    return std::string{std::to_string(num) + getNumericEnding(num)};
}

/********************************************************************************
 * @brief Runs initialization sequence involving printing starting information
 *        and starting the polling timer after specified amount of time.
 * 
 * @param poll_timer Reference to the polling timer.
 * @param time_ms    The time to block the calling thread, measured in milliseconds.
 ********************************************************************************/
void runInitSequence(timer::Timer& poll_timer, const std::size_t time_before_starting_polling_ms) {
    std::cout << "\nPoll timer set to " << poll_timer.getElapseFrequency_hz() << " Hz!\n";
    std::cout << "Starting polling in " << time_before_starting_polling_ms << " milliseconds!\n\n";
    wait(time_before_starting_polling_ms);
    poll_timer.start();
}

/********************************************************************************
 * @brief Performs polling whenever the poll timer elapses and stores retrieved
 *        data in referenced vector. 
 * 
 * @tparam T The vector type.
 * 
 * @param poll_timer Reference to the poll timer.
 * @param buffer     Reference to vector storing retrieved data.
 * 
 * @return True if polling was performed, else false.
 ********************************************************************************/
template<typename T>
bool poll(timer::Timer& poll_timer, std::vector<T>& buffer) {
    static_assert(std::is_arithmetic<T>::value, "Polling only possible for arithmetic values!");
    static T num{};
    if (!poll_timer.elapsed()) { return false; }
    for (auto& i : buffer) {
        i = num++;
    }
    return true;
}
} /* namespace */

/********************************************************************************
 * @brief Performs polling continuously, where a poll timer controls how often
 *        to retrieve data. The timer is set to 2 Hz, hence polling is performed
 *        every 500 ms. Retrieved data is stored in a buffer with capacity to
 *        hold five integers. The retrieved data is printed in the terminal
 *        after every poll.
 * 
 * @return Success code 0 upon termination of the program.
 ********************************************************************************/
int main(void) {
    timer::Timer poll_timer{timer::Hertz{2}};
    std::vector<std::int32_t> buffer(5, 0);
    std::size_t num_polls{};
    runInitSequence(poll_timer, 2000);

    while (1) {
        if (poll<std::int32_t>(poll_timer, buffer)) {
            std::cout << "Retrieved data from " << getPollNumberString(++num_polls) << " poll:\n";
            print<std::int32_t>(buffer);
        }
    }
    return 0;
}