#include "C:\Users\casam\OneDrive\Documentos\GitHub\Proyecto-1---Arreglos-Paginados\Proyecto 1 - Arreglos Paginados\src\Structs y Enums\StructGenerator.h"
#include <unordered_map>
#include <string>

#ifndef PARSED_H
#define PARSED_H

class Parsed{
    private:
    std::unordered_map<std::string, std::string> elements;
    public:
    CommandResult InputParser(int &argc, char* argv[]);
    std::variant<std::monostate, GeneratorData> ParsedGenerator();
    std::variant<std::monostate,SorterData> ParsedSorter();
};

#endif