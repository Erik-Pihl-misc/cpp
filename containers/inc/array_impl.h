/********************************************************************************
 * @brief Implementation details for the container::Array class.
 * 
 * @note Don't include this file directly.
 ********************************************************************************/
#pragma once

namespace container
{
// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
Array<T, Size>::Array() = default;

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
template <typename... Values>
Array<T, Size>::Array(const Values&&... values) 
{ 
    copy(std::forward<const Values>(values)...); 
}

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
Array<T, Size>::Array(const T (&values)[Size]) { copy(values); }

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
template <std::size_t NumValues>
Array<T, Size>::Array(const Array<T, NumValues>& source) { copy(source); }

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
Array<T, Size>::~Array() = default;

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
T& Array<T, Size>::operator[](const std::size_t index) { return myData[index]; }

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
const T& Array<T, Size>::operator[](const std::size_t index) const { return myData[index]; }

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
template <std::size_t NumValues>
Array<T, Size>& Array<T, Size>::operator=(const T (&values)[NumValues]) 
{
    copy(values);
    return *this;
}

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
template <std::size_t NumValues>
Array<T, Size>& Array<T, Size>::operator=(const Array<T, NumValues>& source) 
{
    copy(source);
    return *this;
}

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
template <std::size_t NumValues>
Array<T, Size>& Array<T, Size>::operator+=(const T (&values)[NumValues]) 
{
    copy(values, NumValues);
    return *this;
}

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
template <std::size_t NumValues>
Array<T, Size>& Array<T, Size>::operator+=(const Array<T, NumValues>& source)
{
    copy(source, NumValues);
    return *this;
}

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
T* Array<T, Size>::data() { return myData; }

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
T* Array<T, Size>::data() const { return myData; }

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
std::size_t Array<T, Size>::size() const { return Size; }

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
T* Array<T, Size>::begin() { return myData; }

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
const T* Array<T, Size>::begin() const { return myData; }

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
T* Array<T, Size>::end() { return myData + Size; }

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
const T* Array<T, Size>::end() const { return myData + Size; }

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
T* Array<T, Size>::rbegin() { return end() - 1; }

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
const T* Array<T, Size>::rbegin() const { return end() - 1; }

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
T* Array<T, Size>::rend() { return myData; }

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
const T* Array<T, Size>::rend() const { return myData; }

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
void Array<T, Size>::clear() 
{
    for (auto& i : *this) {
        i = {};
    }
}

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
template <typename... Values>
void Array<T, Size>::copy(const Values&&... values) 
{ 
    std::size_t index{};
    for (const auto& i : {values...}) 
    {
        if (index >= Size) { break; } 
        myData[index++] = i; 
    }
}

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
template <std::size_t NumValues>
void Array<T, Size>::copy(const T (&values)[NumValues], const std::size_t offset) 
{
    for (std::size_t i{}; i + offset < Size && i < NumValues; ++i) 
    {
        myData[offset + i] = values[i];
    }
}

// -----------------------------------------------------------------------------
template <typename T, std::size_t Size>
template <std::size_t NumValues>
void Array<T, Size>::copy(const Array<T, NumValues>& source, const std::size_t offset) 
{
    for (std::size_t i{}; i + offset < Size && i < source.Size(); ++i) 
    {
        myData[offset + i] = source[i];
    }
}

} // namespace container