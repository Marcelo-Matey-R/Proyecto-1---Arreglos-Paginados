#include "Structs.h"
#include <unordered_map>
#include <string>

#ifndef PARSED_H
#define PARSED_H

class Parsed{
    public:
    static CommandResult InputParser(int argc, char* argv[]);
    private:
    static std::variant<std::monostate, GeneratorData> ParsedGenerator(const std::unordered_map<std::string, std::string> &elements);
    static std::variant<std::monostate,SorterData> ParsedSorter(const std::unordered_map<std::string, std::string> &elements);
};

#endif