/********************************************************************************
 * @brief Example demonstrating implementation of arithmetic matrixes via the 
 *        Matrix class.
 ********************************************************************************/
#include <matrix.hpp>

/********************************************************************************
 * @brief Creates a 5 x 3 matrix holding integers and a 4 x 2 matrix holding
 *        floating-point numbers. The content of the matrixes are randomized
 *        (except the last column of the integral matrix) and then printed in 
 *        the terminal before terminating the program.
 ********************************************************************************/
int main(void) {
    utils::Matrix<int> m1{5, 3};
    m1.randomize();
    m1[4][0] = 250;
    m1[4][1] = 500;
    m1[4][2] = 1000;
    m1.print();

    utils::Matrix<double> m2{4, 2};
    m2.randomize(0, 1);
    m2.print();
    return 0;
}