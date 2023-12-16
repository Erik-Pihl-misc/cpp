/********************************************************************************
 * @brief Demonstration of implementing lists with the container::Vector class.
 ********************************************************************************/
#include <iostream>
#include <iomanip>
#include <type_traits>

#include <list.h>

namespace 
{
/********************************************************************************
 * @brief Prints numbers held by referenced list.
 * 
 * @tparam T The data type of the list.
 * 
 * @param list        Reference to list holding the data to print.
 * @param ostream     Output stream to print to (default = the terminal).
 * @param numDecimals The number of decimals to print (default = 1).
 ********************************************************************************/
template <typename T>
void printNumbers(const container::List<T>& list,
                  std::ostream& ostream = std::cout, 
                  const std::size_t numDecimals = 1) 
{
    static_assert(std::is_arithmetic<T>::value, "Invalid list type for printing numbers!");
    ostream << std::fixed << std::setprecision(numDecimals);
    ostream << "--------------------------------------------------------------------------------\n";
    for (const auto& i : list) 
    {
        ostream << i << "\n";
    }
    ostream << "--------------------------------------------------------------------------------\n\n";
}
} // namespace

/********************************************************************************
 * @brief Creates a list holding 16 integers in the range 0 - 15 and a list
 *        holding five floating-point numbers in the range 0.5 - 2.5.
 *        The content held by each list is printed in the terminal before 
 *        terminating the program.
 ********************************************************************************/
int main() 
{
    container::List<int> v1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    container::List<double> v2{};
    double num{};

    v1.pushBack(10);
    v1 += {11, 12, 13, 14, 15};
    v2.resize(5);

    for (auto& i : v2) 
    {
        i = num += 0.5;
    }
    printNumbers<int>(v1);
    printNumbers<double>(v2);
    return 0;
}