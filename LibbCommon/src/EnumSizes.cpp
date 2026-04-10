#include "common/EnumSizes.h"
#include <iostream>
#include <cstdint>
#include <string_view>
#include <unordered_map>

SIZES StringToSize(std::string_view str) {
    static const std::unordered_map<std::string_view, SIZES> tabla = {
        {"SMALL", SIZES::SMALL},
        {"small", SIZES::SMALL},
        {"Small", SIZES::SMALL},

        {"MEDIUM", SIZES::MEDIUM},
        {"medium", SIZES::MEDIUM},
        {"Medium", SIZES::MEDIUM},
        
        {"LARGE", SIZES::LARGE},
        {"large", SIZES::LARGE},
        {"Large", SIZES::LARGE},

        {"val1", SIZES::VAL_1},   {"val2", SIZES::VAL_2},   {"val3", SIZES::VAL_3},
        {"val4", SIZES::VAL_4},   {"val5", SIZES::VAL_5},   {"val6", SIZES::VAL_6},
        {"val7", SIZES::VAL_7},   {"val8", SIZES::VAL_8},   {"val9", SIZES::VAL_9},
        {"val10", SIZES::VAL_10}, {"val11", SIZES::VAL_11}, {"val12", SIZES::VAL_12},
        {"val13", SIZES::VAL_13}, {"val14", SIZES::VAL_14}, {"val15", SIZES::VAL_15},
        {"val16", SIZES::VAL_16}, {"val17", SIZES::VAL_17}, {"val18", SIZES::VAL_18},
        {"val19", SIZES::VAL_19}, {"val20", SIZES::VAL_20}, {"val21", SIZES::VAL_21},
        {"val22", SIZES::VAL_22}, {"val24", SIZES::VAL_24}, {"val26", SIZES::VAL_26},
        {"val27", SIZES::VAL_27}, {"val28", SIZES::VAL_28}, {"val29", SIZES::VAL_29}

    };
    
    auto it = tabla.find(str);
    if(it != tabla.end()) return it->second;
    
    // Manejo de error si el string no coincide
    throw std::invalid_argument("Tamaño no válido");
}