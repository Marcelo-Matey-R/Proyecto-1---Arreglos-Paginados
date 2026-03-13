#include <string>
#include <variant>
#include <cstdint>
#include "Structs y Enums\EnumSizes.h"
#include "Structs y Enums\EnumSorts.h"

#pragma once

struct GeneratorData{
    std::string commandType;
    SIZES fileSize;
    std::string filePath;
};

struct SorterData{
    std::string commandType;
    std::string inputFilePath;
    std::string outputFilePath;
    Algo sortedAlgorithm;
    size_t pageSize;
    size_t pageCount;
};

using CommandResult = std::variant<std::monostate, GeneratorData, SorterData>;