#include "Parsed.h"
#include "C:\Users\casam\OneDrive\Documentos\GitHub\Proyecto-1---Arreglos-Paginados\Proyecto 1 - Arreglos Paginados\src\Structs y Enums\EnumSizes.h"
#include "C:\Users\casam\OneDrive\Documentos\GitHub\Proyecto-1---Arreglos-Paginados\Proyecto 1 - Arreglos Paginados\src\Structs y Enums\EnumSorts.h"
#include <iostream>

CommandResult Parsed::InputParser(int &argc, char* argv[]){
    if(argc < 2){
        throw std::invalid_argument("La cantidad de elementos: argc = " + std::to_string(argc) + " no esta permitida");
    }
    elements.clear();

    std::string command = argv[1];
    elements["command"] = command;

    if(command == "generator" && argc == 6){
        for(int i = 2; i < argc; i++){
            std::string val((argv[i]));
            int pos = i+1;
            if(val == "-size" && pos < argc){
                elements["size"] = argv[pos];
            }
            else if(val == "-output" && pos < argc){
                elements["output"] = argv[pos];
            }
        }
        if(elements.size() != 3){
            std::cout<<"Error comando no tiene los argumentos requeridos"<<"\n";
            return std::monostate{};
        }
        return ParsedGenerator();

    }

    else if(command == "sorter" && argc == 11){
        for(int i = 2; i < argc; i++){
            int pos = i+1;
            std::string val((argv[i]));
            if(val == "-input" && pos < argc){
                elements["input"] = argv[pos];
            }
            else if(val == "-output" && pos < argc){
                elements["output"] = argv[pos];
            }
            else if(val == "-alg" && pos < argc){
                elements["alg"] = argv[pos];
            }
            else if(val == "-pageSize" && pos < argc){
                elements["pageSize"] = argv[pos];
            }
            else if(val == "-pageCount" && pos < argc){
                elements["pageCount"] = argv[pos];
            }
        }
        if(elements.size() != 5){
            std::cout<<"Error comando no tiene los argumentos requeridos"<<"\n";
            return std::monostate{};
        }
        return ParsedSorter();
    }

    else{
        std::cout<<"Error un comando no existe o no tiene la cantidad apropiada de elementos"<<"\n";
        return std::monostate{};
    }

}

std::variant<std::monostate, GeneratorData> Parsed::ParsedGenerator(){
    GeneratorData parse;
    parse.commandType = elements["command"];
    std::string s = elements["size"];
    SIZES size;
    try{
        size = StringToSize(s);
    } catch(const std::invalid_argument &e){
        std::cout<<"Error de valor: "<<e.what()<<"\n";
        return std::monostate{};
    }
    parse.filePath = elements["output"];
    parse.fileSize = size;

    return parse;
}

std::variant<std::monostate, SorterData> Parsed::ParsedSorter(){
    SorterData parse;
    
    std::string input = elements["input"];
    std::string output = elements["output"];
    Algo alg;
    size_t pageSize;
    size_t pageCount;

    try{
        pageSize = std::stoull(elements["pageSize"]);
        pageCount = std::stoull(elements["pageCount"]);
    } catch(const std::invalid_argument &e){
        std::cout<<"Error de valor: "<<e.what()<<"\n";
        return std::monostate{};
    } catch(const std::out_of_range &e){
        std::cout<<"Error de valor: "<<e.what()<<"\n";
        return std::monostate{};
    }

    try{
        alg = StringToAlgo(elements["alg"]);
    }catch(const std::invalid_argument &e){
        std::cout<<"Error de valor: "<<e.what()<<"\n";
        return std::monostate{};
    }

    parse.commandType = elements["command"];
    parse.inputFilePath = elements["input"];
    parse.outputFilePath = elements["output"];
    parse.sortedAlgorithm = alg;
    parse.pageCount = pageCount;
    parse.pageSize = pageSize;

    return parse;
}