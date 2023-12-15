/********************************************************************************
 * @brief Demonstration of implementing arrays with the container::Array class.
 ********************************************************************************/
#include <iostream>
#include <iomanip>
#include <type_traits>

#include <array.h>

namespace 
{

/********************************************************************************
 * @brief Prints numbers held by referenced array.
 * 
 * @tparam T    The data type of the array.
 * @tparam Size The size of the array.
 * 
 * @param array        Reference to array holding the data to print.
 * @param ostream      Output stream to print to (default = the terminal).
 * @param num_decimals The number of decimals to print (default = 1).
 ********************************************************************************/
template <typename T, std::size_t Size>
void printNumbers(const container::Array<T, Size> & array, 
                  std::ostream& ostream = std::cout, 
                  const std::size_t num_decimals = 1) 
{
    static_assert(std::is_arithmetic<T>::value, "Invalid array type for printing numbers!");
    ostream << std::fixed << std::setprecision(num_decimals);
    ostream << "--------------------------------------------------------------------------------\n";
    for (const auto& i : array) 
    {
        ostream << i << "\n";
    }
    ostream << "--------------------------------------------------------------------------------\n\n";
}
} // namespace

/********************************************************************************
 * @brief Creates an array holding ten integers in the range 1 - 10 and an 
 *        array holding five floating-point numbers in the range 0.5 - 2.5.
 *        The content held by each array is printed in the terminal before 
 *        terminating the program.
 ********************************************************************************/
int main() 
{
    const container::Array<int, 10> a1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    container::Array<double, 5> a2{};
    double num{};

    for (auto& i : a2)
    {
        i = num += 0.5;
    }

    printNumbers<int>(a1);
    printNumbers<double>(a2);
    return 0;
}