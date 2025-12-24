#include "../include/avl_tree.hpp"
#include "../include/avl_node.hpp"
#include "../include/avl_iterator.hpp"
#include <algorithm>
#include <utility>
#include <iostream>

namespace avl {

// Exception implementations
out_of_range::out_of_range(const std::string& what) : std::out_of_range(what) {}

invalid_iterator::invalid_iterator(const std::string& what) : std::runtime_error(what) {}

// Helper function to get height safely
template<typename Key, typename T, typename Compare, typename Allocator>
int Tree<Key, T, Compare, Allocator>::get_height(node_type* node) const {
    return node ? node->height : 0;
}

template<typename Key, typename T, typename Compare, typename Allocator>
int Tree<Key, T, Compare, Allocator>::get_balance_factor(node_type* node) const {
    if (!node) return 0;
    int left_height = get_height(node->left);
    int right_height = get_height(node->right);
    return left_height - right_height;
}

// Constructor implementations
template<typename Key, typename T, typename Compare, typename Allocator>
Tree<Key, T, Compare, Allocator>::Tree() 
    : root_(nullptr), size_(0), comp_(), alloc_() {}

template<typename Key, typename T, typename Compare, typename Allocator>
Tree<Key, T, Compare, Allocator>::Tree(const Compare& comp, const Allocator& alloc)
    : root_(nullptr), size_(0), comp_(comp), alloc_(alloc) {}

template<typename Key, typename T, typename Compare, typename Allocator>
Tree<Key, T, Compare, Allocator>::Tree(const Tree& other)
    : root_(nullptr), size_(0), comp_(other.comp_), alloc_(other.alloc_) {
    root_ = copy_tree(other.root_, nullptr);
    size_ = other.size_;
}

template<typename Key, typename T, typename Compare, typename Allocator>
Tree<Key, T, Compare, Allocator>::Tree(Tree&& other) noexcept
    : root_(other.root_), size_(other.size_), comp_(std::move(other.comp_)), 
      alloc_(std::move(other.alloc_)) {
    other.root_ = nullptr;
    other.size_ = 0;
}

template<typename Key, typename T, typename Compare, typename Allocator>
Tree<Key, T, Compare, Allocator>::~Tree() {
    delete_tree(root_);
}

// Assignment operators
template<typename Key, typename T, typename Compare, typename Allocator>
Tree<Key, T, Compare, Allocator>& 
Tree<Key, T, Compare, Allocator>::operator=(const Tree& other) {
    if (this != &other) {
        clear();
        comp_ = other.comp_;
        alloc_ = other.alloc_;
        root_ = copy_tree(other.root_, nullptr);
        size_ = other.size_;
    }
    return *this;
}

template<typename Key, typename T, typename Compare, typename Allocator>
Tree<Key, T, Compare, Allocator>& 
Tree<Key, T, Compare, Allocator>::operator=(Tree&& other) noexcept {
    if (this != &other) {
        clear();
        root_ = other.root_;
        size_ = other.size_;
        comp_ = std::move(other.comp_);
        alloc_ = std::move(other.alloc_);
        other.root_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

// Capacity
template<typename Key, typename T, typename Compare, typename Allocator>
bool Tree<Key, T, Compare, Allocator>::empty() const noexcept {
    return size_ == 0;
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::size_type 
Tree<Key, T, Compare, Allocator>::size() const noexcept {
    return size_;
}

// Element access
template<typename Key, typename T, typename Compare, typename Allocator>
T& Tree<Key, T, Compare, Allocator>::operator[](const Key& key) {
    node_type* node = find_node(key);
    if (node) {
        return node->data.second;
    }
    
    // Insert new element with default value
    auto result = insert(std::make_pair(key, T()));
    return result.first->second;
}

template<typename Key, typename T, typename Compare, typename Allocator>
T& Tree<Key, T, Compare, Allocator>::at(const Key& key) {
    node_type* node = find_node(key);
    if (!node) {
        throw out_of_range("avl::Tree::at: key not found");
    }
    return node->data.second;
}

template<typename Key, typename T, typename Compare, typename Allocator>
const T& Tree<Key, T, Compare, Allocator>::at(const Key& key) const {
    node_type* node = find_node(key);
    if (!node) {
        throw out_of_range("avl::Tree::at: key not found");
    }
    return node->data.second;
}

// Modifiers
template<typename Key, typename T, typename Compare, typename Allocator>
std::pair<typename Tree<Key, T, Compare, Allocator>::iterator, bool>
Tree<Key, T, Compare, Allocator>::insert(const value_type& value) {
    node_type* inserted = nullptr;
    root_ = insert_node(root_, nullptr, value, inserted);
    if (inserted) {
        ++size_;
        return std::make_pair(iterator(inserted), true);
    }
    return std::make_pair(iterator(find_node(value.first)), false);
}

template<typename Key, typename T, typename Compare, typename Allocator>
template<typename P>
std::pair<typename Tree<Key, T, Compare, Allocator>::iterator, bool>
Tree<Key, T, Compare, Allocator>::insert(P&& value) {
    return insert(value_type(std::forward<P>(value)));
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::iterator
Tree<Key, T, Compare, Allocator>::erase(iterator pos) {
    if (pos == end()) {
        return end();
    }
    
    Key key = pos->first;
    bool removed = false;
    root_ = remove_node(root_, key, removed);
    if (removed) {
        --size_;
        // Return iterator to next element
        node_type* next_node = find_node(key);
        if (next_node) {
            next_node = next_node->successor();
        }
        return iterator(next_node);
    }
    return ++pos;
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::size_type
Tree<Key, T, Compare, Allocator>::erase(const Key& key) {
    bool removed = false;
    root_ = remove_node(root_, key, removed);
    if (removed) {
        --size_;
        return 1;
    }
    return 0;
}

template<typename Key, typename T, typename Compare, typename Allocator>
void Tree<Key, T, Compare, Allocator>::clear() noexcept {
    delete_tree(root_);
    root_ = nullptr;
    size_ = 0;
}

// Lookup
template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::iterator
Tree<Key, T, Compare, Allocator>::find(const Key& key) {
    node_type* node = find_node(key);
    return iterator(node);
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::const_iterator
Tree<Key, T, Compare, Allocator>::find(const Key& key) const {
    node_type* node = find_node(key);
    return const_iterator(node);
}

template<typename Key, typename T, typename Compare, typename Allocator>
bool Tree<Key, T, Compare, Allocator>::contains(const Key& key) const {
    return find_node(key) != nullptr;
}

// Iterators
template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::iterator
Tree<Key, T, Compare, Allocator>::begin() noexcept {
    if (!root_) return end();
    return iterator(get_min_node());
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::const_iterator
Tree<Key, T, Compare, Allocator>::begin() const noexcept {
    if (!root_) return end();
    return const_iterator(get_min_node());
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::const_iterator
Tree<Key, T, Compare, Allocator>::cbegin() const noexcept {
    return begin();
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::iterator
Tree<Key, T, Compare, Allocator>::end() noexcept {
    return iterator(nullptr);
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::const_iterator
Tree<Key, T, Compare, Allocator>::end() const noexcept {
    return const_iterator(nullptr);
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::const_iterator
Tree<Key, T, Compare, Allocator>::cend() const noexcept {
    return end();
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::reverse_iterator
Tree<Key, T, Compare, Allocator>::rbegin() noexcept {
    return reverse_iterator(end());
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::const_reverse_iterator
Tree<Key, T, Compare, Allocator>::rbegin() const noexcept {
    return const_reverse_iterator(end());
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::const_reverse_iterator
Tree<Key, T, Compare, Allocator>::crbegin() const noexcept {
    return rbegin();
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::reverse_iterator
Tree<Key, T, Compare, Allocator>::rend() noexcept {
    return reverse_iterator(begin());
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::const_reverse_iterator
Tree<Key, T, Compare, Allocator>::rend() const noexcept {
    return const_reverse_iterator(begin());
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::const_reverse_iterator
Tree<Key, T, Compare, Allocator>::crend() const noexcept {
    return rend();
}

// Swap
template<typename Key, typename T, typename Compare, typename Allocator>
void Tree<Key, T, Compare, Allocator>::swap(Tree& other) noexcept {
    using std::swap;
    swap(root_, other.root_);
    swap(size_, other.size_);
    swap(comp_, other.comp_);
    swap(alloc_, other.alloc_);
}

// Validation
template<typename Key, typename T, typename Compare, typename Allocator>
bool Tree<Key, T, Compare, Allocator>::validate() const {
    if (!root_) return size_ == 0;
    
    int height = 0;
    return validate_node(root_, nullptr, nullptr, height) && size_ > 0;
}

template<typename Key, typename T, typename Compare, typename Allocator>
int Tree<Key, T, Compare, Allocator>::height() const {
    return root_ ? root_->height : 0;
}

// Private helper methods
template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::node_type*
Tree<Key, T, Compare, Allocator>::create_node(const value_type& value, node_type* parent) {
    node_type* node = node_alloc_traits::allocate(alloc_, 1);
    try {
        node_alloc_traits::construct(alloc_, node, value, parent);
    } catch (...) {
        node_alloc_traits::deallocate(alloc_, node, 1);
        throw;
    }
    return node;
}

template<typename Key, typename T, typename Compare, typename Allocator>
void Tree<Key, T, Compare, Allocator>::destroy_node(node_type* node) {
    if (node) {
        node_alloc_traits::destroy(alloc_, node);
        node_alloc_traits::deallocate(alloc_, node, 1);
    }
}

// AVL rotations
template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::node_type*
Tree<Key, T, Compare, Allocator>::rotate_left(node_type* node) {
    node_type* new_root = node->right;
    node->right = new_root->left;
    if (new_root->left) {
        new_root->left->parent = node;
    }
    
    new_root->parent = node->parent;
    new_root->left = node;
    node->parent = new_root;
    
    node->update_height();
    new_root->update_height();
    
    return new_root;
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::node_type*
Tree<Key, T, Compare, Allocator>::rotate_right(node_type* node) {
    node_type* new_root = node->left;
    node->left = new_root->right;
    if (new_root->right) {
        new_root->right->parent = node;
    }
    
    new_root->parent = node->parent;
    new_root->right = node;
    node->parent = new_root;
    
    node->update_height();
    new_root->update_height();
    
    return new_root;
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::node_type*
Tree<Key, T, Compare, Allocator>::rotate_left_right(node_type* node) {
    node->left = rotate_left(node->left);
    return rotate_right(node);
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::node_type*
Tree<Key, T, Compare, Allocator>::rotate_right_left(node_type* node) {
    node->right = rotate_right(node->right);
    return rotate_left(node);
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::node_type*
Tree<Key, T, Compare, Allocator>::balance(node_type* node) {
    if (!node) return nullptr;
    
    node->update_height();
    int balance = node->balance_factor();
    
    // Left heavy
    if (balance > 1) {
        if (node->left->balance_factor() >= 0) {
            return rotate_right(node);
        } else {
            return rotate_left_right(node);
        }
    }
    
    // Right heavy
    if (balance < -1) {
        if (node->right->balance_factor() <= 0) {
            return rotate_left(node);
        } else {
            return rotate_right_left(node);
        }
    }
    
    return node;
}

// Insertion helper
template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::node_type*
Tree<Key, T, Compare, Allocator>::insert_node(node_type* node, node_type* parent, 
                                            const value_type& value, node_type*& inserted) {
    if (!node) {
        inserted = create_node(value, parent);
        return inserted;
    }
    
    if (comp_(value.first, node->data.first)) {
        node->left = insert_node(node->left, node, value, inserted);
    } else if (comp_(node->data.first, value.first)) {
        node->right = insert_node(node->right, node, value, inserted);
    } else {
        // Key already exists, update value
        node->data.second = value.second;
        inserted = nullptr;
        return node;
    }
    
    return balance(node);
}

// Deletion helper
template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::node_type*
Tree<Key, T, Compare, Allocator>::remove_node(node_type* node, const Key& key, bool& removed) {
    if (!node) {
        removed = false;
        return nullptr;
    }
    
    if (comp_(key, node->data.first)) {
        node->left = remove_node(node->left, key, removed);
    } else if (comp_(node->data.first, key)) {
        node->right = remove_node(node->right, key, removed);
    } else {
        // Found the node to delete
        removed = true;
        
        // Node with only one child or no child
        if (!node->left || !node->right) {
            node_type* temp = node->left ? node->left : node->right;
            
            if (!temp) {
                // No children
                destroy_node(node);
                return nullptr;
            } else {
                // One child
                temp->parent = node->parent;
                destroy_node(node);
                return temp;
            }
        } else {
            // Node with two children
            node_type* successor = node->right->minimum();
            
            // Create new node with successor's data
            node_type* new_node = create_node(successor->data, node->parent);
            new_node->left = node->left;
            new_node->right = node->right;
            
            if (new_node->left) new_node->left->parent = new_node;
            if (new_node->right) new_node->right->parent = new_node;
            
            destroy_node(node);
            
            // Remove the successor from right subtree
            new_node->right = remove_node(new_node->right, successor->data.first, removed);
            
            return balance(new_node);
        }
    }
    
    return balance(node);
}

// Tree operations
template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::node_type*
Tree<Key, T, Compare, Allocator>::copy_tree(node_type* other, node_type* parent) {
    if (!other) return nullptr;
    
    node_type* new_node = create_node(other->data, parent);
    new_node->left = copy_tree(other->left, new_node);
    new_node->right = copy_tree(other->right, new_node);
    new_node->height = other->height;
    
    return new_node;
}

template<typename Key, typename T, typename Compare, typename Allocator>
void Tree<Key, T, Compare, Allocator>::delete_tree(node_type* node) {
    if (!node) return;
    
    delete_tree(node->left);
    delete_tree(node->right);
    destroy_node(node);
}

// Search helpers
template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::node_type*
Tree<Key, T, Compare, Allocator>::find_node(const Key& key) const {
    node_type* current = root_;
    while (current) {
        if (comp_(key, current->data.first)) {
            current = current->left;
        } else if (comp_(current->data.first, key)) {
            current = current->right;
        } else {
            return current;
        }
    }
    return nullptr;
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::node_type*
Tree<Key, T, Compare, Allocator>::find_min_node(node_type* node) const {
    if (!node) return nullptr;
    while (node->left) {
        node = node->left;
    }
    return node;
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::node_type*
Tree<Key, T, Compare, Allocator>::find_max_node(node_type* node) const {
    if (!node) return nullptr;
    while (node->right) {
        node = node->right;
    }
    return node;
}

// Validation helper
template<typename Key, typename T, typename Compare, typename Allocator>
bool Tree<Key, T, Compare, Allocator>::validate_node(node_type* node, const Key* min_key, 
                                                    const Key* max_key, int& height) const {
    if (!node) {
        height = 0;
        return true;
    }
    
    // Check BST property
    if (min_key && !comp_(*min_key, node->data.first)) {
        return false; // node->key <= min_key
    }
    if (max_key && !comp_(node->data.first, *max_key)) {
        return false; // node->key >= max_key
    }
    
    int left_height, right_height;
    bool left_valid = validate_node(node->left, min_key, &node->data.first, left_height);
    bool right_valid = validate_node(node->right, &node->data.first, max_key, right_height);
    
    if (!left_valid || !right_valid) {
        return false;
    }
    
    // Check AVL property
    int balance = left_height - right_height;
    if (balance < -1 || balance > 1) {
        return false;
    }
    
    // Check height
    height = 1 + (left_height > right_height ? left_height : right_height);
    if (height != node->height) {
        return false;
    }
    
    return true;
}

// Iterator helpers
template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::node_type*
Tree<Key, T, Compare, Allocator>::get_min_node() const {
    return find_min_node(root_);
}

template<typename Key, typename T, typename Compare, typename Allocator>
typename Tree<Key, T, Compare, Allocator>::node_type*
Tree<Key, T, Compare, Allocator>::get_max_node() const {
    return find_max_node(root_);
}

// Non-member swap function
template<typename Key, typename T, typename Compare, typename Allocator>
void swap(Tree<Key, T, Compare, Allocator>& lhs, Tree<Key, T, Compare, Allocator>& rhs) noexcept {
    lhs.swap(rhs);
}

} // namespace avl