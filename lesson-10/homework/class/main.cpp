#include "../include/avl_tree.hpp"
#include <iostream>
#include <cassert>
#include <map>
#include <vector>
#include <string>

void test_basic_operations() {
    std::cout << "Test 1: Basic operations\n";
    avl::Tree<int, std::string> tree;
    
    // Insert
    auto result1 = tree.insert({1, "one"});
    assert(result1.second);
    assert(result1.first->first == 1);
    assert(result1.first->second == "one");
    
    auto result2 = tree.insert({2, "two"});
    assert(result2.second);
    
    auto result3 = tree.insert({1, "ONE"}); // Duplicate
    assert(!result3.second);
    assert(tree[1] == "one"); // Should not update
    
    // Size
    assert(tree.size() == 2);
    assert(!tree.empty());
    
    // Access
    assert(tree[1] == "one");
    assert(tree[2] == "two");
    
    // Non-existing key creates default
    tree[3]; // Creates with default ""
    assert(tree.size() == 3);
    assert(tree[3] == "");
    
    // at() with existing key
    assert(tree.at(1) == "one");
    
    // at() with non-existing key throws
    try {
        tree.at(99);
        assert(false); // Should not reach here
    } catch (const avl::out_of_range&) {
        // Expected
    }
    
    std::cout << "✓ Basic operations passed\n";
}

void test_iteration() {
    std::cout << "\nTest 2: Iteration\n";
    avl::Tree<int, std::string> tree;
    
    // Insert in reverse order
    tree.insert({5, "five"});
    tree.insert({3, "three"});
    tree.insert({7, "seven"});
    tree.insert({1, "one"});
    tree.insert({4, "four"});
    tree.insert({6, "six"});
    tree.insert({8, "eight"});
    
    // Forward iteration
    std::vector<int> keys;
    for (const auto& pair : tree) {
        keys.push_back(pair.first);
    }
    
    assert(keys.size() == 7);
    assert(std::is_sorted(keys.begin(), keys.end()));
    
    // Reverse iteration
    std::vector<int> reverse_keys;
    for (auto rit = tree.rbegin(); rit != tree.rend(); ++rit) {
        reverse_keys.push_back(rit->first);
    }
    
    assert(reverse_keys.size() == 7);
    assert(std::is_sorted(reverse_keys.rbegin(), reverse_keys.rend()));
    
    std::cout << "✓ Iteration passed\n";
}

void test_erase() {
    std::cout << "\nTest 3: Erase\n";
    avl::Tree<int, std::string> tree;
    
    for (int i = 0; i < 10; ++i) {
        tree.insert({i, std::to_string(i)});
    }
    
    assert(tree.size() == 10);
    
    // Erase by key
    size_t removed = tree.erase(5);
    assert(removed == 1);
    assert(tree.size() == 9);
    assert(!tree.contains(5));
    
    // Erase by iterator
    auto it = tree.find(3);
    assert(it != tree.end());
    tree.erase(it);
    assert(tree.size() == 8);
    assert(!tree.contains(3));
    
    // Erase non-existing key
    removed = tree.erase(99);
    assert(removed == 0);
    assert(tree.size() == 8);
    
    std::cout << "✓ Erase passed\n";
}

void test_find_and_contains() {
    std::cout << "\nTest 4: Find and contains\n";
    avl::Tree<std::string, int> tree;
    
    tree.insert({"apple", 1});
    tree.insert({"banana", 2});
    tree.insert({"cherry", 3});
    
    // Find existing
    auto it = tree.find("banana");
    assert(it != tree.end());
    assert(it->first == "banana");
    assert(it->second == 2);
    
    // Find non-existing
    it = tree.find("date");
    assert(it == tree.end());
    
    // Contains
    assert(tree.contains("apple"));
    assert(tree.contains("cherry"));
    assert(!tree.contains("date"));
    
    std::cout << "✓ Find and contains passed\n";
}

void test_copy_and_move() {
    std::cout << "\nTest 5: Copy and move\n";
    
    // Original tree
    avl::Tree<int, std::string> tree1;
    tree1.insert({1, "one"});
    tree1.insert({2, "two"});
    tree1.insert({3, "three"});
    
    // Copy constructor
    avl::Tree<int, std::string> tree2(tree1);
    assert(tree2.size() == 3);
    assert(tree2[1] == "one");
    assert(tree2[2] == "two");
    assert(tree2[3] == "three");
    
    // Modify original, copy should not change
    tree1.erase(2);
    assert(tree1.size() == 2);
    assert(tree2.size() == 3); // Unchanged
    
    // Move constructor
    avl::Tree<int, std::string> tree3(std::move(tree1));
    assert(tree1.size() == 0);
    assert(tree3.size() == 2);
    
    // Assignment operator
    avl::Tree<int, std::string> tree4;
    tree4 = tree2;
    assert(tree4.size() == 3);
    
    // Move assignment
    avl::Tree<int, std::string> tree5;
    tree5 = std::move(tree3);
    assert(tree3.size() == 0);
    assert(tree5.size() == 2);
    
    std::cout << "✓ Copy and move passed\n";
}

void test_avl_properties() {
    std::cout << "\nTest 6: AVL properties\n";
    avl::Tree<int, int> tree;
    
    // Insert sorted sequence (worst case for BST, but AVL should handle)
    for (int i = 0; i < 100; ++i) {
        tree.insert({i, i * 10});
    }
    
    assert(tree.size() == 100);
    assert(tree.validate()); // Should validate AVL properties
    
    // Delete elements and maintain balance
    for (int i = 0; i < 50; ++i) {
        tree.erase(i * 2); // Delete even numbers
    }
    
    assert(tree.size() == 50);
    assert(tree.validate());
    
    std::cout << "✓ AVL properties maintained\n";
}

void test_comparison_with_std_map() {
    std::cout << "\nTest 7: Comparison with std::map\n";
    
    avl::Tree<int, std::string> avl_tree;
    std::map<int, std::string> std_map;
    
    // Insert same elements
    std::vector<int> values = {5, 2, 8, 1, 3, 7, 9, 4, 6};
    for (int val : values) {
        std::string str = "value_" + std::to_string(val);
        avl_tree.insert({val, str});
        std_map.insert({val, str});
    }
    
    // Check sizes match
    assert(avl_tree.size() == std_map.size());
    
    // Check forward iteration order matches
    auto avl_it = avl_tree.begin();
    auto map_it = std_map.begin();
    
    while (avl_it != avl_tree.end() && map_it != std_map.end()) {
        assert(avl_it->first == map_it->first);
        assert(avl_it->second == map_it->second);
        ++avl_it;
        ++map_it;
    }
    
    // Check reverse iteration
    auto avl_rit = avl_tree.rbegin();
    auto map_rit = std_map.rbegin();
    
    while (avl_rit != avl_tree.rend() && map_rit != std_map.rend()) {
        assert(avl_rit->first == map_rit->first);
        assert(avl_rit->second == map_rit->second);
        ++avl_rit;
        ++map_rit;
    }
    
    std::cout << "✓ Behavior matches std::map\n";
}

int main() {
    try {
        test_basic_operations();
        test_iteration();
        test_erase();
        test_find_and_contains();
        test_copy_and_move();
        test_avl_properties();
        test_comparison_with_std_map();
        
        std::cout << "\n✅ All tests passed successfully!\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "❌ Test failed: " << e.what() << std::endl;
        return 1;
    }
}