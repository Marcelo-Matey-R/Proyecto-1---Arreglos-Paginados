#include "common/EnumSorts.h"
#include <unordered_map>
#include <string>
#include <string_view>
#include <iostream>
Algo StringToAlgo(std::string_view str) {
    static const std::unordered_map<std::string_view, Algo> tabla = {
        // QuickSort
        {"quicksort", Algo::QUICKSORT},
        {"QUICKSORT", Algo::QUICKSORT},
        {"Quicksort", Algo::QUICKSORT},

        // MergeSort
        {"mergesort", Algo::MERGESORT},
        {"MERGESORT", Algo::MERGESORT},
        {"Mergesort", Algo::MERGESORT},

        // InsertionSort
        {"insertionsort", Algo::INSERTIONSORT},
        {"INSERTIONSORT", Algo::INSERTIONSORT},
        {"Insertionsort", Algo::INSERTIONSORT},

        // SelectionSort
        {"selectionsort", Algo::SELECTIONSORT},
        {"SELECTIONSORT", Algo::SELECTIONSORT},
        {"Selectionsort", Algo::SELECTIONSORT},

        // Three-Way MergeSort
        {"threewaymergesort", Algo::THREEWAYMERGESORT},
        {"THREEWAYMERGESORT", Algo::THREEWAYMERGESORT},
        {"Threewaymergesort", Algo::THREEWAYMERGESORT}
    };

    auto it = tabla.find(str);
    if (it != tabla.end()) return it->second;

    throw std::invalid_argument("Algoritmo no reconocido");
}

std::string_view AlgoToString(Algo alg){
    static const std::unordered_map<Algo, std::string_view> tabla = {
        {Algo::QUICKSORT, "quick sort"},
        {Algo::MERGESORT, "merge sort"},
        {Algo::INSERTIONSORT, "insertion sort"},
        {Algo::SELECTIONSORT, "selection sort"},
        {Algo::THREEWAYMERGESORT, "3 way merge sort"}
    };

    auto it = tabla.find(alg);
    if (it != tabla.end()) return it->second;

    throw std::invalid_argument("Algoritmo no reconocido");
}