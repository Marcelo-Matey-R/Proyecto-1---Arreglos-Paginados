#include <iostream>
#include <variant>
#include "Structs y Enums\StructGenerator.h"
#include "Parsed\Parsed.h"
#include "Structs y Enums\EnumSorts.h"


int main(int argc, char* argv[]){
    CommandResult res = Parsed::InputParser(argc, argv);
    if (std::holds_alternative<std::monostate>(res)) {
        //std::cout << "Error al parsear los argumentos.\n";
        //std::cout<<"argc = "<<argc<<"\n";
        for(int i = 0; i < argc; i++){
            std::cout<<argv[i]<<"\n";
        } 
        return 1;
    }

    if (std::holds_alternative<GeneratorData>(res)) {
        GeneratorData g = std::get<GeneratorData>(res);

        std::cout << "Command: " << g.commandType << "\n";
        std::cout << "File path: " << g.filePath << "\n";
        std::cout << "File size: " << g.fileSize << "\n";
    }

    else if (std::holds_alternative<SorterData>(res)) {
        SorterData s = std::get<SorterData>(res);

        std::cout << "Command: " << s.commandType << "\n";
        std::cout << "Input: " << s.inputFilePath << "\n";
        std::cout << "Output: " << s.outputFilePath << "\n";
        std::cout << "Algorithm: " << AlgoToString(s.sortedAlgorithm) << "\n";
        std::cout << "PageSize: " << s.pageSize << "\n";
        std::cout << "PageCount: " << s.pageCount << "\n";
    }
    
}