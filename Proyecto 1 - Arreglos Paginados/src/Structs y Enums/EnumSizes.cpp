#include "C:\Users\casam\OneDrive\Documentos\GitHub\Proyecto-1---Arreglos-Paginados\Proyecto 1 - Arreglos Paginados\src\Structs y Enums\EnumSizes.h"
#include <iostream>
#include <cstdint>
#include <string_view>

SIZES StringToSize(std::string_view str) {
    if (str == "SMALL")  return SIZES::SMALL;
    if (str == "MEDIUM") return SIZES::MEDIUM;
    if (str == "LARGE")  return SIZES::LARGE;
    
    // Manejo de error si el string no coincide
    throw std::invalid_argument("Tamaño no válido");
}