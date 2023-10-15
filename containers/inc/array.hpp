/********************************************************************************
 * @brief Implementation of static arrays of any data type.
 ********************************************************************************/
#pragma once

#include <cstdlib>

namespace container {

/********************************************************************************
 * @brief Class for implementation of static arrays.
 ********************************************************************************/
template <typename T, std::size_t Size>
class Array {
    static_assert(Size > 0, "Static array size cannot be set to 0!");
  public:

    /********************************************************************************
     * @brief Creates empty array of specified size.
     ********************************************************************************/
    Array(void) = default;

    /********************************************************************************
     * @brief Creates array containing referenced values.
     *
     * @tparam Values Parameter pack holding values.
     * 
     * @param values Reference to values to store in the newly created array.
     ********************************************************************************/
    template <typename... Values>
    Array(const Values&... values) { copy(values...); }

    /********************************************************************************
     * @brief Creates array containing referenced values.
     *
     * @param values Reference to values to store in the newly created array.
     ********************************************************************************/
    Array(const T (&values)[Size]) { copy(values); }

    /********************************************************************************
     * @brief Creates array as a copy of referenced source.
     *
     * @tparam NumValues The number of values in the source array.
     * 
     * @param source Reference to array whose content is copied to the new array.
     ********************************************************************************/
    template <std::size_t NumValues>
    Array(const Array<T, NumValues>& source) { copy(source); }

    /********************************************************************************
     * @brief Default destructor. Statically allocated memory is freed automatically
     *        when the array goes out of scope, so nothing needs to be done.
     ********************************************************************************/
    ~Array(void) = default;

    /********************************************************************************
     * @brief Returns reference to the element at specified index in the array.
     *
     * @param index Index of the requested element.
     * 
     * @return A reference to the element at specified index.
     ********************************************************************************/
    T& operator[](const std::size_t index) { return data_[index]; }

    /********************************************************************************
     * @brief Returns reference to the element at specified index in the array.
     *
     * @param index Index of the requested element.
     * 
     * @return A reference to the element at specified index.
     ********************************************************************************/
    const T& operator[](const std::size_t index) const { return data_[index]; }

     /********************************************************************************
     * @brief Copies referenced values to assigned array. 
     *
     * @tparam NumValues The number of values to copy.
     * 
     * @param values Reference to array holding the values to copy.
     * 
     * @return A reference to the assigned array.     
     ********************************************************************************/
    template <std::size_t NumValues>
    Array& operator=(const T (&values)[NumValues]) {
        copy(values);
        return *this;
    }

    /********************************************************************************
     * @brief Copies the content of referenced array to assigned array. 
     *
     * @tparam NumValues The number of values in the source array.
     * 
     * @param source Reference to array holding the values to copy.
     * 
     * @return A reference to the assigned array.     
     ********************************************************************************/
    template <std::size_t NumValues>
    Array& operator=(const Array<T, NumValues>& source) {
        copy(source);
        return *this;
    }

    /********************************************************************************
     * @brief Adds values to the back of assigned array.
     *
     * @tparam NumValues The number of values to copy.
     * 
     * @param values Reference to array holding the values to copy.
     * 
     * @return A reference to the assigned array.     
     ********************************************************************************/
    template <std::size_t NumValues>
    Array& operator+=(const T (&values)[NumValues]) {
        copy(values, NumValues);
        return *this;
    }

    /********************************************************************************
     * @brief Adds values from referenced array to the back of assigned array.
     *
     * @tparam NumValues The number of values in the source array.
     * 
     * @param source Reference to array containing the the values to add.
     * 
     * @return A reference to assigned array.     
     ********************************************************************************/
    template <std::size_t NumValues>
    Array& operator+=(const Array<T, NumValues>& source) {
        copy(source, NumValues);
        return *this;
    }

  public:

    /********************************************************************************
     * @brief Provides the data held by the array.
     *
     * @return Pointer to the start address of the array.
     ********************************************************************************/
    T* data(void) { return data_; }

    /********************************************************************************
     * @brief Provides the data held by the array.
     *
     * @return Pointer to the start address of the array.
     ********************************************************************************/
    T* data(void) const { return data_; }

    /********************************************************************************
     * @brief Returns the size of the array in the number of elements it can hold.
     *
     * @return The size of the array as an unsigned integer.
     ********************************************************************************/
    std::size_t size(void) const { return Size; }

    /********************************************************************************
     * @brief Provides the start address of the array.
     *
     * @return Pointer to the first element of the array.
     ********************************************************************************/
    T* begin(void) { return data_; }

    /********************************************************************************
     * @brief Provides the start address of the array.
     *
     * @return Pointer to the first element of the array.
     ********************************************************************************/
    const T* begin(void) const { return data_; }

    /********************************************************************************
     * @brief Provides the end address of the array.
     *
     * @return Pointer to the address after the last element of the array.
     ********************************************************************************/
    T* end(void) { return data_ + Size; }

    /********************************************************************************
     * @brief Provides the end address of the array.
     *
     * @return Pointer to the address after the last element of the array.
     ********************************************************************************/
    const T* end(void) const { return data_ + Size; }

    /********************************************************************************
     * @brief Returns the address of the last element of the array.
     *
     * @return Pointer to the last element of the array.
     ********************************************************************************/
    T* last(void) { return end() - 1; }

   /********************************************************************************
     * @brief Returns the address of the last element of the array.
     *
     * @return Pointer to the last element of the array.
     ********************************************************************************/
    const T* last(void) const { return end() - 1; }

    /********************************************************************************
     * @brief Clears content of the array.
     ********************************************************************************/
    void clear(void) {
        for (auto& i : *this) {
            i = {};
        }
    }

  private:
    T data_[Size]{}; 

    template <typename... Values>
    void copy(const Values&... values) { 
        std::size_t index{};
        for (const auto& i : {values...}) {
            if (index >= Size) { break; } 
            data_[index++] = i; 
        }
    }

    template <std::size_t NumValues>
    void copy(const T (&values)[NumValues], const std::size_t offset = 0) {
        for (std::size_t i{}; i + offset < Size && i < NumValues; ++i) {
            data_[offset + i] = values[i];
        }
    }

    template <std::size_t NumValues>
    void copy(const Array<T, NumValues>& source, const std::size_t offset = 0) {
        for (std::size_t i{}; i + offset < Size && i < source.Size(); ++i) {
            data_[offset + i] = source[i];
        }
    }
};

} /* namespace container */