#include <string>
#include <variant>
#include <cstdint>
#include "EnumSizes.h"
#include "EnumSorts.h"

#pragma once

struct GeneratorData{
    std::string commandType;
    SIZES fileSize;
    std::string filePath;
};

struct SorterData{
    std::string commandType;
    std::string inputFilePath;
    std::string outputFilePathBin;
    std::string outputFilePathTxt;
    Algo sortedAlgorithm;
    size_t pageSize;
    size_t pageCount;
};

using CommandResult = std::variant<std::monostate, GeneratorData, SorterData>;