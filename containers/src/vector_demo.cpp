/********************************************************************************
 * @brief Demonstration of implementing vectors with the container::Vector class.
 ********************************************************************************/
#include <iostream>
#include <iomanip>
#include <type_traits>
#include <vector.hpp>

namespace {

/********************************************************************************
 * @brief Prints numbers held by referenced vector.
 * 
 * @tparam T The data type of the vector.
 * 
 * @param vector       Reference to vector holding the data to print.
 * @param ostream      Output stream to print to (default = the terminal).
 * @param num_decimals The number of decimals to print (default = 1).
 ********************************************************************************/
template <typename T>
void printNumbers(const container::Vector<T>& vector,
                  std::ostream& ostream = std::cout, 
                  const std::size_t num_decimals = 1) {
    static_assert(std::is_arithmetic<T>::value, "Invalid vector type for printing numbers!");
    ostream << std::fixed << std::setprecision(num_decimals);
    ostream << "--------------------------------------------------------------------------------\n";
    for (const auto& i : vector) {
        ostream << i << "\n";
    }
    ostream << "--------------------------------------------------------------------------------\n\n";
}
} /* namespace */

/********************************************************************************
 * @brief Creates a vector holding 16 integers in the range 0 - 15 and an 
 *        vector holding five floating-point numbers in the range 0.5 - 2.5.
 *        The content held by each vector is printed in the terminal before 
 *        terminating the program.
 ********************************************************************************/
int main(void) {
    container::Vector<int> v1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    container::Vector<double> v2{};
    double num{};

    v1.pushBack(10);
    v1 += {11, 12, 13, 14, 15};
    v2.resize(5);

    for (auto& i : v2) {
        i = num += 0.5;
    }

    printNumbers<int>(v1);
    printNumbers<double>(v2);
    return 0;
}