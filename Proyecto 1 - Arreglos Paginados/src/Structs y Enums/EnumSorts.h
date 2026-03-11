#include <string_view>
#include <unordered_map>
#include <string>

#pragma once

enum class Algo { QUICKSORT, MERGESORT };

Algo StringToAlgo(std::string_view str) {
    static const std::unordered_map<std::string_view, Algo> tabla = {
        {"quicksort", Algo::QUICKSORT},
        {"mergesort", Algo::MERGESORT}
    };

    auto it = tabla.find(str);
    if (it != tabla.end()) return it->second;

    throw std::invalid_argument("Algoritmo no reconocido");
}
