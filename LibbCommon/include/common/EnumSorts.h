#include <string_view>
#include <unordered_map>
#include <string>

#pragma once

enum class Algo { QUICKSORT, MERGESORT, THREEWAYMERGESORT, INSERTIONSORT, SELECTIONSORT };

Algo StringToAlgo(std::string_view str);

std::string_view AlgoToString(Algo alg);