#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../include/avl_tree.hpp"
#include <map>
#include <vector>
#include <random>

TEST_CASE("AVL Tree Basic Operations", "[avl]") {
    avl::Tree<int, int> tree;
    
    SECTION("Insert and size") {
        tree.insert({1, 100});
        tree.insert({2, 200});
        REQUIRE(tree.size() == 2);
    }
    
    SECTION("Operator[]") {
        tree[1] = 100;
        tree[2] = 200;
        REQUIRE(tree[1] == 100);
        REQUIRE(tree[2] == 200);
    }
    
    SECTION("Find and contains") {
        tree.insert({5, 500});
        auto it = tree.find(5);
        REQUIRE(it != tree.end());
        REQUIRE(it->second == 500);
        // REQUIRE(tree.contains(5) == true);
    }
    
    SECTION("Erase") {
        tree.insert({1, 100});
        tree.insert({2, 200});
        tree.insert({3, 300});
        
        tree.erase(2);
        REQUIRE(tree.size() == 2);
        REQUIRE(tree.find(2) == tree.end());
    }
    
    SECTION("Iterator traversal") {
        std::vector<int> keys = {3, 1, 4, 1, 5, 9, 2};
        for (int k : keys) {
            tree.insert({k, k * 10});
        }
        
        std::vector<int> sorted_keys;
        for (const auto& p : tree) {
            sorted_keys.push_back(p.first);
        }
        
        REQUIRE(std::is_sorted(sorted_keys.begin(), sorted_keys.end()));
    }
}

TEST_CASE("AVL Tree vs std::map", "[avl][comparison]") {
    avl::Tree<int, std::string> avl_tree;
    std::map<int, std::string> std_map;
    
    std::vector<int> data = {5, 2, 8, 1, 3, 7, 9, 4, 6};
    
    for (int key : data) {
        std::string value = "value_" + std::to_string(key);
        avl_tree.insert({key, value});
        std_map.insert({key, value});
    }
    
    SECTION("Same size") {
        REQUIRE(avl_tree.size() == std_map.size());
    }
    
    SECTION("Same elements in order") {
        auto avl_it = avl_tree.begin();
        auto map_it = std_map.begin();
        
        while (avl_it != avl_tree.end() && map_it != std_map.end()) {
            REQUIRE(avl_it->first == map_it->first);
            REQUIRE(avl_it->second == map_it->second);
            ++avl_it;
            ++map_it;
        }
    }
}