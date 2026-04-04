#include <cstdint>
#include <string_view>
#include <iostream>

#pragma once

enum SIZES : size_t {SMALL = 134217728, MEDIUM = 268435456, LARGE = 536870912};

SIZES StringToSize(std::string_view str);