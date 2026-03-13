#include "EnumSorts.h"
#include <unordered_map>
#include <string>
#include <string_view>
#include <iostream>
Algo StringToAlgo(std::string_view str) {
    static const std::unordered_map<std::string_view, Algo> tabla = {
        {"quicksort", Algo::QUICKSORT},
        {"mergesort", Algo::MERGESORT}
    };

    auto it = tabla.find(str);
    if (it != tabla.end()) return it->second;

    throw std::invalid_argument("Algoritmo no reconocido");
}

std::string_view AlgoToString(Algo alg){
    static const std::unordered_map<Algo, std::string_view> tabla = {
        {Algo::QUICKSORT, "quicksort"},
        {Algo::MERGESORT, "mergesort"},
    };

    auto it = tabla.find(alg);
    if (it != tabla.end()) return it->second;

    throw std::invalid_argument("Algoritmo no reconocido");
}