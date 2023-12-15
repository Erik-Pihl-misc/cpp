/********************************************************************************
 * @brief Implementation of static arrays of any data type.
 ********************************************************************************/
#pragma once

#include <cstdlib>

namespace container 
{
/********************************************************************************
 * @brief Class for implementation of static arrays.
 * 
 * @tparam T    The array type.
 * @tparam Size The array size.
 * 
 * @note The array size must exceed 0, else a compilation error will be generated.
 ********************************************************************************/
template <typename T, std::size_t Size>
class Array 
{
public:
    /********************************************************************************
     * @brief Creates empty array of specified size.
     ********************************************************************************/
    Array();

    /********************************************************************************
     * @brief Creates array containing referenced values.
     *
     * @tparam Values Parameter pack holding values.
     * 
     * @param values Reference to values to store in the newly created array.
     ********************************************************************************/
    template <typename... Values>
    Array(const Values&&... values);

    /********************************************************************************
     * @brief Creates array containing referenced values.
     *
     * @param values Reference to values to store in the newly created array.
     ********************************************************************************/
    Array(const T (&values)[Size]);

    /********************************************************************************
     * @brief Creates array as a copy of referenced source.
     *
     * @tparam NumValues The number of values in the source array.
     * 
     * @param source Reference to array whose content is copied to the new array.
     ********************************************************************************/
    template <std::size_t NumValues>
    Array(const Array<T, NumValues>& source);

    /********************************************************************************
     * @brief Deletes array.
     ********************************************************************************/
    ~Array();

    /********************************************************************************
     * @brief Returns reference to the element at specified index in the array.
     *
     * @param index Index of the requested element.
     * 
     * @return A reference to the element at specified index.
     ********************************************************************************/
    T& operator[](const std::size_t index);

    /********************************************************************************
     * @brief Returns reference to the element at specified index in the array.
     *
     * @param index Index of the requested element.
     * 
     * @return A reference to the element at specified index.
     ********************************************************************************/
    const T& operator[](const std::size_t index) const;

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
    Array& operator=(const T (&values)[NumValues]);

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
    Array& operator=(const Array<T, NumValues>& source);

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
    Array& operator+=(const T (&values)[NumValues]);

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
    Array& operator+=(const Array<T, NumValues>& source);

    /********************************************************************************
     * @brief Provides the data held by the array.
     *
     * @return Pointer to the start address of the array.
     ********************************************************************************/
    T* data();

    /********************************************************************************
     * @brief Provides the data held by the array.
     *
     * @return Pointer to the start address of the array.
     ********************************************************************************/
    T* data() const;

    /********************************************************************************
     * @brief Returns the size of the array in the number of elements it can hold.
     *
     * @return The size of the array as an unsigned integer.
     ********************************************************************************/
    std::size_t size() const;

    /********************************************************************************
     * @brief Provides the start address of the array.
     *
     * @return Pointer to the first element of the array.
     ********************************************************************************/
    T* begin();

    /********************************************************************************
     * @brief Provides the start address of the array.
     *
     * @return Pointer to the first element of the array.
     ********************************************************************************/
    const T* begin() const;

    /********************************************************************************
     * @brief Provides the end address of the array.
     *
     * @return Pointer to the address after the last element of the array.
     ********************************************************************************/
    T* end();

    /********************************************************************************
     * @brief Provides the end address of the array.
     *
     * @return Pointer to the address after the last element of the array.
     ********************************************************************************/
    const T* end() const;

    /********************************************************************************
     * @brief Returns the address of the last element of the array.
     *
     * @return Pointer to the last element of the array.
     ********************************************************************************/
    T* rbegin();

   /********************************************************************************
     * @brief Returns the address of the last element of the array.
     *
     * @return Pointer to the last element of the array.
     ********************************************************************************/
    const T* rbegin() const;

    /********************************************************************************
     * @brief Provides the start address of the array.
     *
     * @return Pointer to the first element of the array.
     ********************************************************************************/
    T* rend();

    /********************************************************************************
     * @brief Provides the start address of the array.
     *
     * @return Pointer to the first element of the array.
     ********************************************************************************/
    const T* rend() const;

    /********************************************************************************
     * @brief Clears array content.
     ********************************************************************************/
    void clear();

private:
    static_assert(Size > 0, "Static array size cannot be set to 0!");

    template <typename... Values>
    void copy(const Values&&... values);
    template <std::size_t NumValues>
    void copy(const T (&values)[NumValues], const std::size_t offset = 0);
    template <std::size_t NumValues>
    void copy(const Array<T, NumValues>& source, const std::size_t offset = 0);

    T myData[Size]{}; 
};

} // namespace container

#include "array_impl.h"