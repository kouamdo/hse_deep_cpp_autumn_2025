#pragma once

#include <memory>
#include <functional>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <iterator>
#include <utility>

namespace avl {

// Exceptions
class out_of_range : public std::out_of_range {
public:
    out_of_range(const std::string& what);
};

class invalid_iterator : public std::runtime_error {
public:
    invalid_iterator(const std::string& what);
};

// Forward declarations
template<typename Key, typename T>
struct Node;

template<typename Key, typename T, bool Const = false>
class Iterator;

// Main AVL Tree class
template<
    typename Key,
    typename T,
    typename Compare = std::less<Key>,
    typename Allocator = std::allocator<std::pair<const Key, T>>
>
class Tree {
public:
    // Types
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const Key, T>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using key_compare = Compare;
    using allocator_type = Allocator;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    
    // Iterators
    using iterator = Iterator<Key, T, false>;
    using const_iterator = Iterator<Key, T, true>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
    using node_type = Node<Key, T>;
    using node_allocator = typename std::allocator_traits<Allocator>::template rebind_alloc<node_type>;
    using node_alloc_traits = typename std::allocator_traits<node_allocator>;
    
    node_type* root_;
    size_type size_;
    Compare comp_;
    node_allocator alloc_;

public:
    // Constructors/Destructors
    Tree();
    explicit Tree(const Compare& comp, const Allocator& alloc = Allocator());
    Tree(const Tree& other);
    Tree(Tree&& other) noexcept;
    ~Tree();
    
    Tree& operator=(const Tree& other);
    Tree& operator=(Tree&& other) noexcept;
    
    // Capacity
    bool empty() const noexcept;
    size_type size() const noexcept;
    
    // Element access
    T& operator[](const Key& key);
    T& at(const Key& key);
    const T& at(const Key& key) const;
    
    // Modifiers
    std::pair<iterator, bool> insert(const value_type& value);
    template<typename P>
    std::pair<iterator, bool> insert(P&& value);
    
    iterator erase(iterator pos);
    size_type erase(const Key& key);
    void clear() noexcept;
    
    // Lookup
    iterator find(const Key& key);
    const_iterator find(const Key& key) const;
    bool contains(const Key& key) const;
    
    // Iterators
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    
    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    
    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crend() const noexcept;
    
    // Swap
    void swap(Tree& other) noexcept;
    
    // For testing/debugging
    bool validate() const;
    int height() const;
    
private:
    // Internal methods
    node_type* create_node(const value_type& value, node_type* parent = nullptr);
    void destroy_node(node_type* node);
    
    // AVL rotations
    node_type* rotate_left(node_type* node);
    node_type* rotate_right(node_type* node);
    node_type* rotate_left_right(node_type* node);
    node_type* rotate_right_left(node_type* node);
    node_type* balance(node_type* node);
    
    // Insertion/Deletion helpers
    node_type* insert_node(node_type* node, node_type* parent, const value_type& value, node_type*& inserted);
    node_type* remove_node(node_type* node, const Key& key, bool& removed);
    node_type* find_min_node(node_type* node) const;
    node_type* find_max_node(node_type* node) const;
    
    // Search helpers
    node_type* find_node(const Key& key) const;
    
    // Tree operations
    node_type* copy_tree(node_type* other, node_type* parent);
    void delete_tree(node_type* node);
    
    // Validation
    bool validate_node(node_type* node, const Key* min_key, const Key* max_key, int& height) const;
    int get_height(node_type* node) const;
    int get_balance_factor(node_type* node) const;
    
    // Iterator helpers
    node_type* get_min_node() const;
    node_type* get_max_node() const;
};

// Non-member functions
template<typename Key, typename T, typename Compare, typename Allocator>
void swap(Tree<Key, T, Compare, Allocator>& lhs, Tree<Key, T, Compare, Allocator>& rhs) noexcept;

} // namespace avl