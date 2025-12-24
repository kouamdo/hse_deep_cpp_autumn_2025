#pragma once

#include <stdexcept>
#include <string>

namespace avl {

class out_of_range : public std::out_of_range {
public:
    using std::out_of_range::out_of_range;
};

class invalid_iterator : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

} // namespace avl
