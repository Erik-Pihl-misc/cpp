/********************************************************************************
 * @brief Implementation of dynamic vectors of any data type.
 ********************************************************************************/
#pragma once

#include <cstdlib>

namespace container 
{

/********************************************************************************
 * @brief Class for implementation of dynamic vectors.
 * 
 * @tparam T The data type of the vector.
 ********************************************************************************/
template <typename T>
class Vector 
{
public:
    /********************************************************************************
     * @brief Creates empty vector.
     ********************************************************************************/
    Vector();

    /********************************************************************************
     * @brief Creates vector of specified size.
     *
     * @param size The size of the vector, i.e. the number of elements it can hold.
     ********************************************************************************/
    Vector(const std::size_t size);

    /********************************************************************************
     * @brief Creates vector containing specified values.
     *
     * @tparam Values Parameter pack containing values.
     * 
     * @param values The values to add to the vector.
     ********************************************************************************/
    template <typename... Values>
    Vector(const Values&&... values);

    /********************************************************************************
     * @brief Creates vector as a copy of referenced source.
     *
     * @param source Reference to vector whose content is copied to the new vector.
     ********************************************************************************/
    Vector(const Vector<T>& source);

    /********************************************************************************
     * @brief Moves memory from referenced source to assigned vector. The source
     *        vector is emptied after the move operation is performed.
     *
     * @param source Reference to vector whose content is moved to assigned vector.
     ********************************************************************************/
    Vector(Vector&& source);

    /********************************************************************************
     * @brief Empties vector before deletion.
     ********************************************************************************/
    ~Vector();

    /********************************************************************************
     * @brief Returns reference to the element at specified index in the vector.
     *
     * @param index Index of the requested element.
     * 
     * @return A reference to the element at specified index.
     ********************************************************************************/
    T& operator[](const std::size_t index);

    /********************************************************************************
     * @brief Returns reference to the element at specified index in the vector.
     *
     * @param index Index of the requested element.
     * 
     * @return A reference to the element at specified index.
     ********************************************************************************/
    const T& operator[](const std::size_t index) const;

    /********************************************************************************
     * @brief Copies the content of the vector to assigned vector. Previous values 
     *        are cleared before copying.
     *
     * @tparam Values Parameter pack holding values.
     * 
     * @param values Reference to the values to add.
     ********************************************************************************/
    template <typename... Values>
    void operator=(const Values&&... values);

    /********************************************************************************
     * @brief Copies the content of the vector to assigned vector. Previous values 
     *        are cleared before copying.
     *
     * @param source Reference to vector containing the the values to add.    
     ********************************************************************************/
    void operator=(const Vector<T>& source);

    /********************************************************************************
     * @brief Pushes referenced values to the back of the vector.
     *
     * @tparam NumValues The number of values to add.
     * 
     * @param values Reference to the values to add.
     ********************************************************************************/
    template <std::size_t NumValues>
    void operator+=(const T (&values)[NumValues]);

    /********************************************************************************
     * @brief Adds values from the vector to the back of assigned vector.
     *
     * @param source Reference to vector containing the the values to add.
     ********************************************************************************/
    void operator+=(const Vector<T>& source);

public:
    /********************************************************************************
     * @brief Provides the data held by the vector.
     *
     * @return Pointer to the start address of the vector.
     ********************************************************************************/
    const T* data() const;

    /********************************************************************************
     * @brief Returns the size of the vector in the number of elements it can hold.
     *
     * @return The size of the vector as an unsigned integer.
     ********************************************************************************/
    std::size_t size() const;

    /********************************************************************************
     * @brief Indicates if the vector is empty.
     *
     * @return True if the vector vector is empty, else false.
     ********************************************************************************/
    bool empty() const;

    /********************************************************************************
     * @brief Provides the start address of the vector.
     *
     * @return Pointer to the first element of the vector.
     ********************************************************************************/
    T* begin();

    /********************************************************************************
     * @brief Provides the start address of the vector.
     *
     * @return Pointer to the first element of the vector.
     ********************************************************************************/
    const T* begin() const;

    /********************************************************************************
     * @brief Provides the end address of the vector.
     *
     * @return Pointer to the address after the last element of the vector.
     ********************************************************************************/
    T* end();

    /********************************************************************************
     * @brief Provides the end address of the vector.
     *
     * @return Pointer to the address after the last element of the vector.
     ********************************************************************************/
    const T* end() const;

    /********************************************************************************
     * @brief Returns the address of the last element of the vector.
     *
     * @return Pointer to the last element of the vector.
     ********************************************************************************/
    T* last();
   
    /********************************************************************************
     * @brief Returns the address of the last element of the vector.
     *
     * @return Pointer to the last element of the vector.
     ********************************************************************************/
    const T* last() const;

    /********************************************************************************
     * @brief Clears content of the vector.
     ********************************************************************************/
    void clear();

    /********************************************************************************
     * @brief Resizes the vector to specified new size.
     *
     * @param newSize The new size of the vector.
     * 
     * @return True if the vector was resized, else false.
     ********************************************************************************/
    bool resize(const std::size_t newSize);

    /********************************************************************************
     * @brief Pushes new value to the back of the vector.
     *
     * @param value Reference to the new value to push to the vector.
     * 
     * @return True if the value was pushed to the back of the vector, else false.
     ********************************************************************************/
    bool pushBack(const T& value);

    /******************************************************************************** 
     * @brief Pops value at the back of the vector.
     *
     * @return True if the last value of the vector was popped, else false.
     ********************************************************************************/
    bool popBack();

private:
    bool copy(const Vector<T>& source);
    template <typename... Values>
    void assign(const std::size_t offset, const Values&&... values);
    void assign(const Vector<T>& source, const std::size_t offset = 0);
    template <std::size_t NumValues>
    void assign(const T (&values)[NumValues], const std::size_t offset = 0);
    bool addValues(const Vector<T>& source);
    template <std::size_t NumValues>
    bool addValues(const T (&values)[NumValues]);

    T* myData{nullptr}; 
    std::size_t mySize{};  
};

} // namespace container

#include "vector_impl.h"