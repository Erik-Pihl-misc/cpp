/********************************************************************************
 * @brief Implementation of dynamic vectors of any data type.
 ********************************************************************************/
#pragma once

#include <cstdlib>

namespace container {

/********************************************************************************
 * @brief Class for implementation of dynamic vectors.
 * 
 * @tparam T The data type of the vector.
 ********************************************************************************/
template <typename T>
class Vector {
  public:

    /********************************************************************************
     * @brief Creates empty vector.
     ********************************************************************************/
    Vector(void) = default;

    /********************************************************************************
     * @brief Creates vector of specified size.
     *
     * @param size The size of the vector, i.e. the number of elements it can hold.
     ********************************************************************************/
    Vector(const std::size_t size) { resize(size); }

    /********************************************************************************
     * @brief Creates vector containing specified values.
     *
     * @tparam Values Parameter pack containing values.
     * 
     * @param values The values to add to the vector.
     ********************************************************************************/
    template <typename... Values>
    Vector(const Values&... values) {
        if (resize(sizeof...(values))) {
            assign(0, values...);
        }
    }

    /********************************************************************************
     * @brief Creates vector as a copy of referenced source.
     *
     * @param source Reference to vector whose content is copied to the new vector.
     ********************************************************************************/
    Vector(const Vector& source) { copy(source); }

    /********************************************************************************
     * @brief Moves memory from referenced source to assigned vector. The source
     *        vector is emptied after the move operation is performed.
     *
     * @param source Reference to vector whose content is moved to assigned vector.
     ********************************************************************************/
    Vector(Vector&& source) noexcept {
        data_ = source.data_;
        size_ = source.size_;
        source.data_ = nullptr;
        source.size_ = 0;
    }

    /********************************************************************************
     * @brief Empties vector before deletion.
     ********************************************************************************/
    ~Vector(void) { clear(); }

    /********************************************************************************
     * @brief Returns reference to the element at specified index in the vector.
     *
     * @param index Index of the requested element.
     * 
     * @return A reference to the element at specified index.
     ********************************************************************************/
    T& operator[](const std::size_t index) { return data_[index]; }

    /********************************************************************************
     * @brief Returns reference to the element at specified index in the vector.
     *
     * @param index Index of the requested element.
     * 
     * @return A reference to the element at specified index.
     ********************************************************************************/
    const T& operator[](const std::size_t index) const { return data_[index]; }

    /********************************************************************************
     * @brief Copies the content of the vector to assigned vector. Previous values 
     *        are cleared before copying.
     *
     * @tparam Values Parameter pack holding values.
     * 
     * @param values Reference to the values to add.
     ********************************************************************************/
    template <typename... Values>
    void operator=(const Values&... values) {
        clear();
        copy(values...);
    }

    /********************************************************************************
     * @brief Copies the content of the vector to assigned vector. Previous values 
     *        are cleared before copying.
     *
     * @param source Reference to vector containing the the values to add.    
     ********************************************************************************/
    void operator=(const Vector& source) {
        clear();
        copy(source);
    }

    /********************************************************************************
     * @brief Pushes referenced values to the back of the vector.
     *
     * @tparam NumValues The number of values to add.
     * 
     * @param values Reference to the values to add.
     ********************************************************************************/
    template <std::size_t NumValues>
    void operator+=(const T (&values)[NumValues]) { addValues(values); }

    /********************************************************************************
     * @brief Adds values from the vector to the back of assigned vector.
     *
     * @param source Reference to vector containing the the values to add.
     ********************************************************************************/
    void operator+=(const Vector& source) { addValues(source); }

  public:
    /********************************************************************************
     * @brief Provides the data held by the vector.
     *
     * @return Pointer to the start address of the vector.
     ********************************************************************************/
    const T* data(void) const { return data_; }

    /********************************************************************************
     * @brief Returns the size of the vector in the number of elements it can hold.
     *
     * @return The size of the vector as an unsigned integer.
     ********************************************************************************/
    std::size_t size(void) const { return size_; }

    /********************************************************************************
     * @brief Indicates if the vector is empty.
     *
     * @return True if the vector vector is empty, else false.
     ********************************************************************************/
    bool empty(void) const { return size_ == 0; }

    /********************************************************************************
     * @brief Provides the start address of the vector.
     *
     * @return Pointer to the first element of the vector.
     ********************************************************************************/
    T* begin(void) { return data_; }

    /********************************************************************************
     * @brief Provides the start address of the vector.
     *
     * @return Pointer to the first element of the vector.
     ********************************************************************************/
    const T* begin(void) const { return data_; }

    /********************************************************************************
     * @brief Provides the end address of the vector.
     *
     * @return Pointer to the address after the last element of the vector.
     ********************************************************************************/
    T* end(void) { return data_ + size_; }

    /********************************************************************************
     * @brief Provides the end address of the vector.
     *
     * @return Pointer to the address after the last element of the vector.
     ********************************************************************************/
    const T* end(void) const { return data_ + size_; }

    /********************************************************************************
     * @brief Returns the address of the last element of the vector.
     *
     * @return Pointer to the last element of the vector.
     ********************************************************************************/
    T* last(void) { return size_ > 0 ? end() - 1 : nullptr; }
   
    /********************************************************************************
     * @brief Returns the address of the last element of the vector.
     *
     * @return Pointer to the last element of the vector.
     ********************************************************************************/
    const T* last(void) const { return size_ > 0 ? end() - 1 : nullptr; }

    /********************************************************************************
     * @brief Clears content of the vector.
     ********************************************************************************/
    void clear(void) {
        std::free(data_);
        data_ = nullptr;
        size_ = 0;
    }

    /********************************************************************************
     * @brief Resizes the vector to specified new size.
     *
     * @param new_size The new size of the vector.
     * 
     * @return True if the vector was resized, else false.
     ********************************************************************************/
    bool resize(const std::size_t new_size) {
        auto copy{static_cast<T*>(std::realloc(data_, sizeof(T) * new_size))};
        if (copy == nullptr) return false;
        data_ = copy;
        size_ = new_size;
        return true;
    }

    /********************************************************************************
     * @brief Pushes new value to the back of the vector.
     *
     * @param value Reference to the new value to push to the vector.
     * 
     * @return True if the value was pushed to the back of the vector, else false.
     ********************************************************************************/
    bool pushBack(const T& value) {
        if (resize(size_ + 1)) {
            data_[size_ - 1] = value;
            return true;
        } else {
            return false;
        }
    }

    /******************************************************************************** 
     * @brief Pops value at the back of the vector.
     *
     * @return True if the last value of the vector was popped, else false.
     ********************************************************************************/
    bool popBack(void) {
        if (size_ <= 1) {
            clear();
            return true;
        } else {
            return resize(size_ - 1);
        }
    }

  private:
    T* data_{nullptr}; 
    std::size_t size_{};  

    bool copy(const Vector& source) {
        if (resize(source.size_)) {
            assign(source);
            return true;
        } else {
            return false;
        }
    }

    template <typename... Values>
    void assign(const std::size_t offset, const Values&... values) {
        std::size_t index{};
        for (const auto& i : {values...}) {
            if (offset + index >= size_) { break; }
            data_[index++ + offset] = i;
        }
    }

    void assign(const Vector& source, const std::size_t offset = 0) {
        for (std::size_t i{}; offset + i < size_ && i < source.size_; ++i) {
            data_[offset + i] = source.data_[i];
        }
    }

    template <std::size_t NumValues>
    void assign(const T (&values)[NumValues], const std::size_t offset = 0) noexcept {
        for (std::size_t i{}; i < NumValues && offset + i < size_; ++i) {
            data_[offset + i] = values[i];
        }
    }

    bool addValues(const Vector& source) {
        const auto offset{size_};
        if (resize(size_ + source.size_)) {
            assign(source, offset);
            return true;
        } else {
            return false;
        }
    }

    template <std::size_t NumValues>
    bool addValues(const T (&values)[NumValues]) {
        const auto offset{size_};
        if (resize(size_ + NumValues)) {
            assign(values, offset);
            return true;
        } else {
            return false;
        }
    }
};

} /* namespace container */