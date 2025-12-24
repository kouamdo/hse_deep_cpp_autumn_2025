#pragma once

#include "avl_common.hpp"
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
    node_pointer root_;

public:
    Iterator() noexcept : current_(nullptr), root_(nullptr) {}
    explicit Iterator(node_pointer node, node_pointer root = nullptr) noexcept : current_(node), root_(root) {}

    template<bool Const_ = Const, typename = std::enable_if_t<Const_>>
    Iterator(const Iterator<Key, T, false>& other) noexcept : current_(other.current_), root_(other.root_) {}

    reference operator*() const {
        if (!current_) throw invalid_iterator("Dereferencing end iterator");
        return current_->data;
    }

    pointer operator->() const {
        if (!current_) throw invalid_iterator("Accessing member of end iterator");
        return &current_->data;
    }

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

    Iterator& operator--() {
        if (!current_) {
            if (!root_) throw invalid_iterator("Cannot decrement end iterator for empty tree");
            current_ = static_cast<node_pointer>(root_->maximum());
            return *this;
        }
        node_pointer pred = static_cast<node_pointer>(current_->predecessor());
        if (!pred) {
            throw invalid_iterator("Cannot decrement begin iterator");
        }
        current_ = pred;
        return *this;
    }

    Iterator operator--(int) {
        Iterator temp = *this;
        --(*this);
        return temp;
    }

    bool operator==(const Iterator& other) const noexcept {
        return current_ == other.current_;
    }

    bool operator!=(const Iterator& other) const noexcept {
        return !(*this == other);
    }

    node_pointer node() const noexcept { return current_; }
    node_pointer root() const noexcept { return root_; }
};

} // namespace avl
