#pragma once

#include "avl_node.hpp"
#include <iterator>
#include <type_traits>

namespace avl {

template<typename Key, typename T, bool Const>
class Iterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::pair<const Key, T>;
    using difference_type = std::ptrdiff_t;
    using pointer = typename std::conditional<Const, const value_type*, value_type*>::type;
    using reference = typename std::conditional<Const, const value_type&, value_type&>::type;
    using node_pointer = typename std::conditional<Const, const Node<Key, T>*, Node<Key, T>*>::type;

private:
    node_pointer current_;

public:
    // Constructors
    Iterator() noexcept : current_(nullptr) {}
    explicit Iterator(node_pointer node) noexcept : current_(node) {}
    
    // Allow conversion from iterator to const_iterator
    template<bool Const_ = Const, typename = std::enable_if_t<Const_>>
    Iterator(const Iterator<Key, T, false>& other) noexcept : current_(other.current_) {}
    
    // Dereference operators
    reference operator*() const {
        return current_->data;
    }
    
    pointer operator->() const {
        return &current_->data;
    }
    
    // Increment operators
    Iterator& operator++() {
        if (current_ == nullptr) {
            throw invalid_iterator("Cannot increment end iterator");
        }
        current_ = static_cast<node_pointer>(current_->successor());
        return *this;
    }
    
    Iterator operator++(int) {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }
    
    // Decrement operators
    Iterator& operator--() {
        // To decrement end(), we need the maximum element
        // This requires tree context, so we'll handle this in Tree class
        throw invalid_iterator("Decrement requires tree context - use rbegin()/rend() instead");
        return *this;
    }
    
    Iterator operator--(int) {
        Iterator temp = *this;
        --(*this);
        return temp;
    }
    
    // Comparison operators
    bool operator==(const Iterator& other) const noexcept {
        return current_ == other.current_;
    }
    
    bool operator!=(const Iterator& other) const noexcept {
        return !(*this == other);
    }
    
    // For internal use by Tree class
    node_pointer node() const noexcept { return current_; }
    
private:
    friend class Tree<Key, T>;
    friend class Iterator<Key, T, !Const>;
};

// Iterator types
template<typename Key, typename T>
using iterator = Iterator<Key, T, false>;

template<typename Key, typename T>
using const_iterator = Iterator<Key, T, true>;

} // namespace avl