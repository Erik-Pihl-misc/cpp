/********************************************************************************
 * @brief Interface for arithmetic matrixes.
 ********************************************************************************/
#pragma once

#include <vector>
#include <type_traits>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

namespace utils {

/********************************************************************************
 * @brief Class for implementation of arithmetic matrixes.
 * 
 * @tparam T The data type of the array.
 ********************************************************************************/
template <typename T>
class Matrix {
    static_assert(std::is_arithmetic<T>::value, "Non-integral data type specified for Matrix object!");

  public:
    /********************************************************************************
     * @brief Creates empty matrix.
     ********************************************************************************/
    Matrix(void) = default;
    
    /********************************************************************************
     * @brief Creates matrix with specified dimensions (columns x rows).
     * 
     * @param num_columns The number of columns of the matrix.
     * @param num_rows    The number of rows of the matrix.
     * @param start_val   Starting value for each element of the matrix (default = 0).
     ********************************************************************************/
    Matrix(const std::size_t num_columns, 
           const std::size_t num_rows, 
           const T start_val = static_cast<T>(0)) { 
        resize(num_columns, num_rows, start_val);
    }

    /********************************************************************************
     * @brief Clears the matrix before deletion.
     ********************************************************************************/
    ~Matrix(void) { clear(); }

    /********************************************************************************
     * @brief Creates a copy of specified source matrix.
     * 
     * @param source Reference to the matrix to copy.
     ********************************************************************************/
    Matrix(Matrix& source) { data_ = source.data; }

    /********************************************************************************
     * @brief Moves memory from specified source matrix to assigned matrix.
     *        The source matrix will be empty after the move operation is complete.
     * 
     * @param source Reference to the source matrix to move memory from.
     ********************************************************************************/
    Matrix(Matrix&& source) noexcept {
        data_ = source.data_;
        source.clear();
    }

    /********************************************************************************
     * @brief Provides the data held by the matrix.
     * 
     * @return Reference to two-dimensional vector holding the matrix data.
     ********************************************************************************/
    std::vector<std::vector<T>>& operator=(Matrix& matrix) { return matrix.data_; }

    /********************************************************************************
     * @brief Provides the data held by the matrix.
     * 
     * @return Reference to two-dimensional vector holding the matrix data.
     ********************************************************************************/
    const std::vector<std::vector<T>>& operator=(const Matrix& matrix) const { return matrix.data_; }

    /********************************************************************************
     * @brief Provides row at specified column index.
     * 
     * @return Reference to vector holding the data at the specified column index.
     ********************************************************************************/
    std::vector<T>& operator[](const std::size_t index)  { return data_[index]; }

    /********************************************************************************
     * @brief Provides row at specified column index.
     * 
     * @return Reference to vector holding the data at the specified column index.
     ********************************************************************************/
    const std::vector<T>& operator[](const std::size_t index) const { return data_[index]; }
    
  public:
    /********************************************************************************
     * @brief Provides the start address of the matrix.
     * 
     * @return Pointer to the start address of the matrix.
     ********************************************************************************/
    std::vector<T>* begin(void) { return data_.size() > 0 ? &data_[0] : nullptr; };

    /********************************************************************************
     * @brief Provides the start address of the matrix.
     * 
     * @return Pointer to the start address of the matrix.
     ********************************************************************************/
    const std::vector<T>* begin(void) const { return data_.size() > 0 ? &data_[0] : nullptr; };

    /********************************************************************************
     * @brief Provides the end address of the matrix.
     * 
     * @return Pointer to the end address of the matrix.
     ********************************************************************************/
    std::vector<T>* end(void) { return data_.size() > 0 ? &data_[data_.size()] : nullptr; }

    /********************************************************************************
     * @brief Provides the end address of the matrix.
     * 
     * @return Pointer to the end address of the matrix.
     ********************************************************************************/
    const std::vector<T>* end(void) const { return data_.size() > 0 ? &data_[data_.size()] : nullptr; }

    /********************************************************************************
     * @brief Provides the data held by the matrix.
     * 
     * @return Reference to two-dimensional vector holding the matrix data.
     ********************************************************************************/
    std::vector<std::vector<T>>& data(void) { return data_; }

    /********************************************************************************
     * @brief Provides the data held by the matrix.
     * 
     * @return Reference to two-dimensional vector holding the matrix data.
     ********************************************************************************/
    const std::vector<std::vector<T>>& data(void) const { return data_; }

    /********************************************************************************
     * @brief Provides the number of columns of the matrix.
     * 
     * @return The number of columns of the matrix as an unsigned integer.
     ********************************************************************************/
    std::size_t numColumns(void) const { return data_.size(); }

    /********************************************************************************
     * @brief Provides the number of rows of the matrix.
     * 
     * @return The number of rows of the matrix as an unsigned integer.
     ********************************************************************************/
    std::size_t numRows(void) const { return data_.size() > 0 ? data_[0].size() : 0; }

    /********************************************************************************
     * @brief Provides row at specified column index.
     * 
     * @return Reference to vector holding the data at the specified column index.
     ********************************************************************************/
    std::vector<T>& at(const std::size_t index) { return data_[index]; }

    /********************************************************************************
     * @brief Provides row at specified column index.
     * 
     * @return Reference to vector holding the data at the specified column index.
     ********************************************************************************/
    const std::vector<T>& at(const std::size_t index) const { return data_[index]; }

     /********************************************************************************
     * @brief Indicates if the matrix is empty.
     * 
     * @return True if the matrix is empty, else false.
     ********************************************************************************/
    bool empty(void) const { return data_.size() == 0; }

    /********************************************************************************
     * @brief Empties the matrix.
     ********************************************************************************/
    void clear(void) { data_.clear(); }

    /********************************************************************************
     * @brief Resizes matrix to specified dimensions (columns x rows).
     * 
     * @param num_columns The new number of columns of the matrix.
     * @param num_rows    The new number of rows of the matrix.
     * @param start_val   Starting value for each element of the matrix (default = 0).
     ********************************************************************************/
    void resize(const std::size_t num_columns, 
                const std::size_t num_rows, 
                const T start_val = static_cast<T>(0)) {
        data_.resize(num_columns, std::vector<T>(num_rows, 0));
    }

    /********************************************************************************
     * @brief Randomizes matrix with numbers in specified range [min, max].
     * 
     * @param min The minimum permitted randomized value (default = 0).
     * @param max The maximum permitted randomized value (default = 100).
     ********************************************************************************/
    void randomize(const T min = static_cast<T>(0), const T max = static_cast<T>(100)) {
        initRandomGenerator();
        for (auto& i : data_) {
            for (auto& j : i) {
                j = getRandom(min, max);
            }
        }
    }

    /********************************************************************************
     * @brief Prints content held by the matrix.
     * 
     * @param ostream      Output stream to print to (default = the terminal).
     * @param num_decimals The number of decimals to print (default = 1).
     ********************************************************************************/
    void print(std::ostream& ostream = std::cout, const std::size_t num_decimals = 1) {
        if (empty()) return;
        ostream << std::fixed << std::setprecision(num_decimals);
        ostream << "--------------------------------------------------------------------------------\n";
        for (std::size_t i{}; i < numRows(); ++i) {
            for (std::size_t j{}; j < numColumns(); ++j) {
                ostream << data_[j][i] << " ";
            }
            ostream << "\n";
        }
        ostream << "--------------------------------------------------------------------------------\n\n";
    }

  private:
    std::vector<std::vector<T>> data_{};

    static void initRandomGenerator(void) {
        static bool rand_gen_init{false};
        if (!rand_gen_init) {
            std::srand(std::time(nullptr));
            rand_gen_init = true;
        }
    }

    static T getRandom(const T min = static_cast<T>(0), const T max = static_cast<T>(100)) {
        if constexpr (std::is_integral<T>::value) {
            return (std::rand() % (max - min + 1)) + min;
        } else {
            return (std::rand() / static_cast<double>(RAND_MAX) * (max - min)) + min;
        }
    }
};

} /* namespace utils */