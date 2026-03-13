#include "Parsed.h"
#include "C:\Users\casam\OneDrive\Documentos\GitHub\Proyecto-1---Arreglos-Paginados\Proyecto 1 - Arreglos Paginados\src\Structs y Enums\EnumSizes.h"
#include "C:\Users\casam\OneDrive\Documentos\GitHub\Proyecto-1---Arreglos-Paginados\Proyecto 1 - Arreglos Paginados\src\Structs y Enums\EnumSorts.h"
#include <variant>
#include <iostream>

CommandResult Parsed::InputParser(int argc, char* argv[]){
    if(argc < 2){
        throw std::invalid_argument("La cantidad de elementos: argc = " + std::to_string(argc) + " no esta permitida");
        return std::monostate{};
    }
    
    std::unordered_map<std::string, std::string> elements;

    std::string command = argv[1];
    elements["command"] = command;

    if(command == "generator" && argc == 6){
        for(int i = 2; i < argc; i++){
            std::string val((argv[i]));
            int pos = i+1;
            if(val == "-sizes" && pos < argc){
                if(argv[pos] == "-output"){
                    std::cerr<<"El path del sizes no existe"<<'\n';
                    return std::monostate{};
                }
                elements["size"] = argv[pos];
            }
            else if(val == "-output" && pos < argc){
                elements["output"] = argv[pos];
            }
        }
        if(elements.size() != 3){
            std::cerr<<"Error comando no tiene los argumentos requeridos"<<" "<<elements.size()<<"\n";
            for(const auto& pair : elements){
                std::cerr<<pair.first<<" "<<pair.second<<'\n';
            } 
            return std::monostate{};
        }
      
        auto tmp2 = ParsedGenerator(elements);

        if (std::holds_alternative<GeneratorData>(tmp2)) return std::get<GeneratorData>(tmp2);

        else {std::cerr<<"lolazo"; return std::monostate{};}

    }

    else if(command == "sorter" && argc == 11){
        for(int i = 2; i < argc; i++){
            int pos = i+1;
            std::string val((argv[i]));
            if(val == "-input" && pos < argc){
                if(argv[pos] == "-output"){
                    std::cerr<<"El path del input no existe"<<'\n';
                    return std::monostate{};
                }

                elements["input"] = argv[pos];
            }
            else if(val == "-output" && pos < argc){
                if(argv[pos] == "-alg"){
                    std::cerr<<"El path del output no existe"<<'\n';
                    return std::monostate{};
                }
                elements["output"] = argv[pos];
            }
            else if(val == "-alg" && pos < argc){
                if(argv[pos] == "-pageSize"){
                    std::cerr<<"El path del alg no existe"<<'\n';
                    return std::monostate{};
                }
                elements["alg"] = argv[pos];
            }
            else if(val == "-pageSize" && pos < argc){
                if(argv[pos] == "-pageCount"){
                    std::cerr<<"El path del pageSize no existe"<<'\n';
                    return std::monostate{};
                }
                elements["pageSize"] = argv[pos];
            }
            else if(val == "-pageCount" && pos < argc){
                elements["pageCount"] = argv[pos];
            }
        }
        if(elements.size() != 6){
            std::cerr<<"Error comando no tiene los argumentos requeridos"<<"\n";
            return std::monostate{};
        }
        for(const auto& pair : elements){
            std::cerr<<pair.first<<" "<<pair.second<<"\n\n";
        } 
        auto tmp1 = ParsedSorter(elements);

        if (std::holds_alternative<SorterData>(tmp1)) return std::get<SorterData>(tmp1);

        else return std::monostate{};
    }

    else{
        std::cerr<<"Error un comando no existe o no tiene la cantidad apropiada de elementos"<<"\n";
        return std::monostate{};
    }

} 

std::variant<std::monostate, GeneratorData> Parsed::ParsedGenerator(const std::unordered_map<std::string, std::string> &elements){
    GeneratorData parse;
    parse.commandType = elements.at("command");
    std::string s = elements.at("size");
    SIZES size;
    try{
        size = StringToSize(s);
    } catch(const std::invalid_argument &e){
        std::cout<<"Error de valor: "<<e.what()<<"\n";
        return std::monostate{};
    }
    parse.filePath = elements.at("output");
    parse.fileSize = size;

    return parse;
}

std::variant<std::monostate, SorterData> Parsed::ParsedSorter(const std::unordered_map<std::string, std::string> &elements){
    SorterData parse;
    
    std::string input = elements.at("input");
    std::string output = elements.at("output");
    Algo alg;
    size_t pageSize;
    size_t pageCount;

    try{
        pageSize = std::stoull(elements.at("pageSize"));
        pageCount = std::stoull(elements.at("pageCount"));
    } catch(const std::invalid_argument &e){
        std::cerr<<"Error de valor: "<<e.what()<<"\n";
        return std::monostate{};
    } catch(const std::out_of_range &e){
        std::cerr<<"Error de valor: "<<e.what()<<"\n";
        return std::monostate{};
    }

    try{
        alg = StringToAlgo(elements.at("alg"));
    }catch(const std::invalid_argument &e){
        std::cerr<<"Error de valor: "<<e.what()<<"\n";
        return std::monostate{};
    }

    parse.commandType = elements.at("command");
    parse.inputFilePath = elements.at("input");
    parse.outputFilePath = elements.at("output");
    parse.sortedAlgorithm = alg;
    parse.pageCount = pageCount;
    parse.pageSize = pageSize;

    return parse;
}