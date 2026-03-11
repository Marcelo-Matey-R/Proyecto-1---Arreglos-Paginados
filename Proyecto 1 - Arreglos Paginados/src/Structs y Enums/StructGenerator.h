#include <string>
#include <variant>
#include <cstdint>
#include "C:\Users\casam\OneDrive\Documentos\GitHub\Proyecto-1---Arreglos-Paginados\Proyecto 1 - Arreglos Paginados\src\Structs y Enums\EnumSizes.h"
#include "C:\Users\casam\OneDrive\Documentos\GitHub\Proyecto-1---Arreglos-Paginados\Proyecto 1 - Arreglos Paginados\src\Structs y Enums\EnumSorts.h"

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

using CommandResult = std::variant<std::monostate, std::variant<std::monostate, GeneratorData>, std::variant<std::monostate, SorterData>>;