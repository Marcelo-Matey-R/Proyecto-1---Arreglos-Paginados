#include <cstdint>
#include <string_view>
#include <iostream>

#pragma once

enum SIZES : size_t {SMALL = 536870912, MEDIUM = 1073741824, LARGE = 2147483648};

SIZES StringToSize(std::string_view str) {
    if (str == "SMALL")  return SIZES::SMALL;
    if (str == "MEDIUM") return SIZES::MEDIUM;
    if (str == "LARGE")  return SIZES::LARGE;
    
    // Manejo de error si el string no coincide
    throw std::invalid_argument("Tamaño no válido");
}