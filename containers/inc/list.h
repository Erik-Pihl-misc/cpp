/********************************************************************************
 * @brief Implementation of doubly linked lists of any data type.
 ********************************************************************************/
#pragma once

#include <cstdlib>

namespace container 
{

/********************************************************************************
 * @brief Class for implementation of doubly linked lists.
 * 
 * @tparam T The list type.
 ********************************************************************************/
template <typename T>
class List 
{
    struct Node;         
public:
    class Iterator;      
    class ConstIterator; 

    /********************************************************************************
     * @brief Creates empty list.
     ********************************************************************************/
    List() = default;

    /********************************************************************************
     * @brief Creates list of specified size initialized with specified start value.
     *
     * @param size The starting size of the list.
     * @param startValue The starting value for each element (default = 0).
     ********************************************************************************/
     List(const std::size_t size, const T& startValue = static_cast<T>(0)) 
     {
         resize(size, startValue);
     }

    /********************************************************************************
     * @brief Creates list initialized with values passed as input arguments.
     *
     * @tparam Values... Parameter pack holding input arguments.
     * 
     * @param values The arguments to store in newly created list.
     ********************************************************************************/
    template <typename... Values> 
    List(const Values&&... values) { copy(std::forward<const Values>(values)...); }

    /********************************************************************************
     * @brief Creates new list as a copy of referenced source.
     *
     * @param source Reference to list whose content is copied to the new list.
     ********************************************************************************/
    List(List& source) { copy(source); }

    /********************************************************************************
     * @briefClears memory allocated for nodes in the list.
     ********************************************************************************/
    ~List() { clear(); }

    /********************************************************************************
     * @brief Returns reference to the value at specified position in the list.
     *
     * @param iterator Reference to iterator pointing at the value to read.
     * 
     * @return A reference to the element at specified position.
     ********************************************************************************/
    T& operator[](Iterator& iterator) { return *iterator; }

    /********************************************************************************
     * @brief Returns a reference to the element at specified index in the list.
     *
     * @param iterator Reference to iterator pointing at the value to read.
     * 
     * @return A reference to the element at specified position.
     ********************************************************************************/
    const T& operator[] (ConstIterator& iterator) const { return *iterator; }

     /********************************************************************************
     * @brief Pushes values to the back of the list.
     *
     * @tparam NumValues The number of values to add.
     * 
     * @param values Reference to the values to add.
     ********************************************************************************/
    template <std::size_t NumValues>
    bool operator+=(const T (&values)[NumValues]) { return addValues(values); }

    /********************************************************************************
     * @brief Returns the size of the list.
     *
     * @return The size of the list in the number of element it holds.
     ********************************************************************************/
    std::size_t size() const { return mySize; }

    /********************************************************************************
     * @brief Clears the list.
     ********************************************************************************/
    void clear() 
    {
        removeAllNodes();
        myFirst = nullptr;
        myLast = nullptr;
        mySize = 0;
    }

    /********************************************************************************
     * @brief Indicates if the list is empty.
     *
     * @return True if the list is empty, else false.
     ********************************************************************************/
    bool empty() const { return mySize == 0; }

    /********************************************************************************
     * @brief Provides the address of the first node.
     *
     * @return A pointer to the first node in the list.
     ********************************************************************************/
    Iterator begin() { return Iterator{myFirst}; }

    /********************************************************************************
     * @brief Provides the address of the first node in the list.
     *
     * @return A pointer to the first node in the list.
     ********************************************************************************/
    ConstIterator begin() const { return ConstIterator{myFirst}; }

    /********************************************************************************
     * @brief Provides the ending address of the list (which is always null).
     *
     * @return A pointer to the ending address of the list.
     ********************************************************************************/
    Iterator end() { return Iterator{nullptr}; }

     /********************************************************************************
     * @brief Provides the ending address of the list (which is always null).
     *
     * @return A pointer to the ending address of the list.
     ********************************************************************************/
    ConstIterator end() const { return ConstIterator{nullptr}; }

    /********************************************************************************
     * @brief Provides the address of the last node in the list.
     *
     * @return A pointer to the last node in the list.
     ********************************************************************************/
    Iterator last() { return Iterator{myLast}; }

    /********************************************************************************
     * @brief Provides the address of the last node in the list.
     *
     * @return A pointer to the last node in the list.
     ********************************************************************************/
    ConstIterator last() const { return ConstIterator{myLast}; }

    /********************************************************************************
     * @brief resizes the list to specified new size.
     *
     * @param newSize The new size of the list.
     * @param startValue The starting value for each new element (default = 0).
     * 
     * @return True if the list was resized, else false.
     ********************************************************************************/
    bool resize(const std::size_t newSize, const T& startValue = static_cast<T>(0)) 
    {
        while (mySize < newSize) 
        {
            if (!pushBack(startValue)) { return false; }
        }
        while (mySize > newSize) { popFront(); }
        return true;
    }

    /********************************************************************************
     * @brief Inserts value at the front of the list.
     *
     * @param value Reference to the value to add.
     * 
     * @return True if the value was added, else false.
     ********************************************************************************/
    bool pushFront(const T& value) 
    {
        auto node1{Node::create(value)};
        if (node1 == nullptr) { return false; }

        if (mySize++ == 0) 
        {
            myFirst = node1;
            myLast = node1;
        } 
        else 
        {
            auto node2{myFirst};
            node1->next = node2;
            node2->previous = node1;
            myFirst = node1;
        }
        return true;
    }

    /********************************************************************************
     * @brief Inserts value at the back of the list.
     *
     * @param value Reference to the value to add.
     * 
     * @return True if the value was added, else false.
     ********************************************************************************/
    bool pushBack(const T& value) 
    {
        auto node2{Node::create(value)};
        if (node2 == nullptr) { return false; }  

        if (mySize++ == 0) 
        {
            myFirst = node2;
            myLast = node2;
        } 
        else 
        {
            auto node1{myLast};
            node1->next = node2;
            node2->previous = node1;
            myLast = node2;
        }
        return true;
    }

    /********************************************************************************
     * @brief Inserts value at specified position in the list.
     *
     * @param iterator Reference to iterator pointing at the location to place
     *                 the new value.
     * @param value Reference to the value to add.
     * 
     * @return True if the value was added, else false.
     ********************************************************************************/
    bool insert(Iterator& iterator, const T& value)
     {
        if (iterator == nullptr) {  return false; }
        auto node2{Node::create(value)};
        if (node2 == nullptr) return false;            
        auto node1{Node::get(iterator)->previous};
        auto node3{node1->next};

        node1->next = node2;
        node2->previous = node1;
        node2->next = node3;
        node3->previous = node2;
        mySize++;
        return true;      
    }

    /********************************************************************************
     * @brief Removes value at the front of the list.
     ********************************************************************************/
    void popFront() 
    {
        if (mySize <= 1) 
        {
            clear();
            return;
        } 
        auto node1{myFirst};
        auto node2{node1->next};
        node2->previous = nullptr;
        
        Node::destroy(node1);
        myFirst = node2;
        mySize--;
    }

    /********************************************************************************
     * @brief Removes value at the back of the list.
     ********************************************************************************/
    void popBack() {
        if (mySize <= 1) 
        {
            clear();
            return;
        } 
        auto node2{myLast};
        auto node1{node2->previous};
        node1->next = nullptr;     
        Node::destroy(node2);
        myLast = node1;
        mySize--;
    }

    
    /********************************************************************************
     * @brief Removes value at specified position in the list.
     *
     * @param iterator Reference to iterator pointing at the value to remove.
     *
     * @return True if the value was removed, else false.
     ********************************************************************************/
    bool remove(Iterator& iterator) 
    {
        if (iterator == nullptr) 
        {
            return false;
        } 
        else 
        {
            auto node2{iterator.get()};
            auto node1{node2->previous};
            auto node3{node2->next};

            node1->next = node3;
            node3->previous = node1;
            Node::destroy(node2);
            mySize--;
            return true;
        }
    }
    
    /********************************************************************************
     * @brief Class for iterating through nodes in mutable linked lists.
     ********************************************************************************/
    class Iterator 
    {
    public:
      
        /********************************************************************************
         * @brief Creates empty iterator.
         ********************************************************************************/
        Iterator() = default;

        /********************************************************************************
         * @brief Creates iterator pointing at referenced node.
         *
         * @param node Reference to node the iterator is to point at.
         ********************************************************************************/
        Iterator(Node* node) : myNode{node} {}

        /********************************************************************************
         * @brief Prefix increment operator, sets the iterator to point at next node.
         ********************************************************************************/
        void operator++() { myNode = myNode->next; }

        /********************************************************************************
         * @brief Postfix increment operator, sets the iterator to point at next node.
         ********************************************************************************/
        void operator++(int) { myNode = myNode->next; }

        /********************************************************************************
         * @brief Prefix decrement operator, sets the iterator to point at previous node.
         ********************************************************************************/
        void operator--() { myNode = myNode->previous; }

        /********************************************************************************
         * @brief Postfix decrement operator, sets the iterator to point at previous node.
         ********************************************************************************/
        void operator--(int) { myNode = myNode->previous; }

        /********************************************************************************
         * @brief Addition operator, increments the iterator specified number of times.
         *
         * @param numIncrements The number of times the iterator will be incremented.
         ********************************************************************************/
        void operator+= (const std::size_t numIncrements) 
        {
            for (std::size_t i{}; i < numIncrements; ++i) 
            {
                myNode = myNode->next;
            }
        }

        /********************************************************************************
         * @brief Subtraction operator, decrements the iterator specified number of times.
         *
         * @param numIncrements The number of times the iterator will be decremented.
         ********************************************************************************/
        void operator-=(const std::size_t numIncrements) 
        {
            for (std::size_t i{}; i < numIncrements; ++i) 
            {
                myNode = myNode->previous;
            }
        }

        /********************************************************************************
         * @brief Equality operator, checks if the iterator points at the same node as
         *        referenced other iterator.
         *
         * @param other Reference to other iterator.
         * 
         * @return True if the iterators point at the same node, else false.
         ********************************************************************************/
        bool operator==(const Iterator& other) { return myNode == other.myNode; }

        /********************************************************************************
         * @brief Inequality operator, checks if the iterator and referenced other
         *        iterator points at different nodes.
         *
         * @param other Reference to other iterator.
         * 
         * @return True if the iterators point at different nodes, else false.
         ********************************************************************************/
        bool operator!=(const Iterator& other) { return myNode != other.myNode; }

        /********************************************************************************
         * @brief Dereference operator, provides a reference to the value stored by the
         *        node the iterator is pointing at.
         *
         * @return Reference to the value stored by the node the iterator is pointing at.
         ********************************************************************************/
        T& operator*() { return myNode->data; }

        /********************************************************************************
         * @brief Returns the address of the node the iterator points at. A void pointer
         *        is returned to keep information about nodes private within the List 
         *        class.
         *
         * @return 
         *        Pointer to the node the iterator is pointing at.
         ********************************************************************************/
        void* address() { return myNode; }

    private:
        Node* myNode{nullptr};
    };

    /********************************************************************************
     * @brief Class for iterating through nodes in constant linked lists.
     ********************************************************************************/
    class ConstIterator {
    public:

        /********************************************************************************
         * @brief Constructor, creates iterator pointing at referenced node.
         *
         * @param node
         *        Pointer to node that the iterator is set to point at.
         ********************************************************************************/
        ConstIterator(const Node* node) : myNode{node} {}

        /********************************************************************************
         * @brief Prefix increment operator, sets the iterator to point at next node.
         ********************************************************************************/
        void operator++() { myNode = myNode->next; }

        /********************************************************************************
         * @brief Postfix increment operator, sets the iterator to point at next node.
         ********************************************************************************/
        void operator++(int) { myNode = myNode->next; }

        /********************************************************************************
         * @brief Prefix decrement operator, sets the iterator to point at previous node.
         ********************************************************************************/
        void operator--() {  myNode = myNode->previous; }

        /********************************************************************************
         * @brief Postfix decrement operator, sets the iterator to point at previous node.
         ********************************************************************************/
        void operator--(int) { myNode = myNode->previous; }

        /********************************************************************************
         * @brief Addition operator, increments the iterator specified number of times.
         *
         * @param numIncrements
         *        The number of times the iterator will be incremented.
         ********************************************************************************/
        void operator+=(const std::size_t numIncrements) 
        {
            for (std::size_t i{}; i < numIncrements; ++i) 
            {
                myNode = myNode->next;
            }
        }

        /********************************************************************************
         * @brief Subtraction operator, decrements the iterator specified number of 
         *        times.
         *
         * @param numIncrements
         *        The number of times the iterator will be decremented.
         ********************************************************************************/
        void operator-=(const std::size_t numIncrements) 
        {
            for (std::size_t i{}; i < numIncrements; ++i) 
            {
                myNode = myNode->previous;
            }
        }

        /********************************************************************************
         * @brief Equality operator, checks if the iterator points at the same node as
         *        referenced other iterator.
         *
         * @param other
         *        Reference to other iterator.
         * @return 
         *        True if the iterators point at the same node, else false.
         ********************************************************************************/
        bool operator==(ConstIterator& other) const { return myNode == other.myNode; }

        /********************************************************************************
         * @brief Inequality operator, checks if the iterator and referenced other
         *        iterator points at different nodes.
         *
         * @param other
         *        Reference to other iterator.
         * @return 
         *        True if the iterators point at different nodes, else false.
         ********************************************************************************/
        bool operator!=(ConstIterator& other) const { return myNode != other.myNode; }

        /********************************************************************************
         * @brief Dereference operator, provides a reference to the value stored by the
         *        node the iterator is pointing at. Not
         *
         * @return 
         *        Reference to the value stored by the node the iterator is pointing at.
         ********************************************************************************/
        const T& operator*() const { return myNode->data; }
        
        /********************************************************************************
         * @brief Returns the address of the node the iterator points at. 
         * 
         * @note A void pointer is provided to keep information about nodes private.
         *
         * @return Pointer to the node the iterator is pointing at.
         ********************************************************************************/
        const void* address() const { return myNode; }

    private:
        const Node* myNode{nullptr}; 
    };

private:

    struct Node 
    {
        Node* previous; 
        Node* next;     
        T data;         

        // -----------------------------------------------------------------------------
        static Node* create(const T& data) 
        {
            auto self{static_cast<Node*>(std::malloc(sizeof(Node)))};
            if (self == nullptr) { return nullptr; }
            self->data = data;
            self->previous = nullptr;
            self->next = nullptr;
            return self;
        }

        // -----------------------------------------------------------------------------
        static void destroy(Node* self) 
        { 
            std::free(self);
            self = nullptr;
        }

        // -----------------------------------------------------------------------------
        static Node* get(Iterator& iterator) 
        { 
            return static_cast<Node*>(iterator.address()); 
        }

        // -----------------------------------------------------------------------------
        static const Node* get(ConstIterator& iterator) 
        {
            return static_cast<Node*>(iterator.address());
        }
    };

    // -----------------------------------------------------------------------------
    template <typename... Values>
    bool copy(const Values&&... values) 
    {
        clear();
        for (const auto& value : {values...})
        {
            if (!pushBack(value)) { return false; }
        }
        return true;
    }

    // -----------------------------------------------------------------------------
    bool copy(List& source) 
    {
        clear();
        for (std::size_t i{}; i < source.Size(); ++i) 
        {
            if (!pushBack(source[i])) { return false; }
        }
        return true;
    }

    // -----------------------------------------------------------------------------
    template <std::size_t NumValues>
    void assign(const T (&values)[NumValues], const std::size_t offset = 0)
    {
        for (std::size_t i{}; i < NumValues && offset + i < mySize; ++i)
        {
            (*this)[offset + i] = values[i];
        }
    }

    // -----------------------------------------------------------------------------
    template <std::size_t NumValues>
    bool addValues(const T (&values)[NumValues])
    {
        if (NumValues == 0) { return false; }
        for (std::size_t i{}; i < NumValues; ++i)
        {
            if (!pushBack(values[i])) { return false; }
        }
        return true;
    }
    
    // -----------------------------------------------------------------------------
    void removeAllNodes() 
    {
        for (auto i{begin()}; i != end();) 
        {
            auto next{Node::get(i)->next};
            Node::destroy(Node::get(i));
            i = next;
        }
    }

    Node* myFirst{nullptr}; 
    Node* myLast{nullptr};  
    std::size_t mySize{}; 
};

} // namespace container