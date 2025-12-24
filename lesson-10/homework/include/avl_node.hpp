#pragma once

namespace avl {

template<typename Key, typename T>
struct Node {
    using value_type = std::pair<const Key, T>;
    
    value_type data;
    Node* left;
    Node* right;
    Node* parent;
    int height;
    
    // Constructors
    Node(const Key& key, const T& value, Node* parent = nullptr)
        : data(std::piecewise_construct, 
               std::forward_as_tuple(key), 
               std::forward_as_tuple(value)),
          left(nullptr), right(nullptr), parent(parent), height(1) {}
    
    Node(const value_type& pair, Node* parent = nullptr)
        : data(pair), left(nullptr), right(nullptr), parent(parent), height(1) {}
    
    // Copy constructor (not used for keys, but for internal copy)
    Node(const Node& other, Node* parent = nullptr)
        : data(other.data), left(nullptr), right(nullptr), parent(parent), height(other.height) {}
    
    // Find minimum node in subtree
    Node* minimum() {
        Node* current = this;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    
    // Find maximum node in subtree
    Node* maximum() {
        Node* current = this;
        while (current->right != nullptr) {
            current = current->right;
        }
        return current;
    }
    
    // Find successor (next in-order)
    Node* successor() {
        Node* current = this;
        
        // If right subtree exists, successor is minimum of right subtree
        if (current->right != nullptr) {
            return current->right->minimum();
        }
        
        // Otherwise, go up until we find a node that is left child of its parent
        Node* p = current->parent;
        while (p != nullptr && current == p->right) {
            current = p;
            p = p->parent;
        }
        return p;
    }
    
    // Find predecessor (previous in-order)
    Node* predecessor() {
        Node* current = this;
        
        // If left subtree exists, predecessor is maximum of left subtree
        if (current->left != nullptr) {
            return current->left->maximum();
        }
        
        // Otherwise, go up until we find a node that is right child of its parent
        Node* p = current->parent;
        while (p != nullptr && current == p->left) {
            current = p;
            p = p->parent;
        }
        return p;
    }
    
    // Update height based on children
    void update_height() {
        int left_height = left ? left->height : 0;
        int right_height = right ? right->height : 0;
        height = 1 + (left_height > right_height ? left_height : right_height);
    }
    
    // Get balance factor
    int balance_factor() const {
        int left_height = left ? left->height : 0;
        int right_height = right ? right->height : 0;
        return left_height - right_height;
    }
};

} // namespace avl