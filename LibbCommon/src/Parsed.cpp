#include "common\Parsed.h"
#include "common\EnumSizes.h"
#include "common\EnumSorts.h"
#include <variant>
#include <iostream>

#pragma region InputParser

CommandResult Parsed::InputParser(int argc, char* argv[]){
    if(argc < 2){
        std::cerr<<"La cantidad de elementos: argc = " + std::to_string(argc) + " no esta permitida"<<'\n';
        return std::monostate{};
    }
    
    std::unordered_map<std::string, std::string> elements;

    std::string command = argv[1];
    elements["command"] = command;

    if(command == "generator" && argc == 6){
        for(int i = 2; i < argc; i++){
            std::string val((argv[i]));
            if(val == "-size" && (i+1) < argc){
                if(argv[i+1] == "-output"){
                    std::cerr<<"El path del sizes no existe"<<'\n';
                    return std::monostate{};
                }
                elements["size"] = argv[++i];
            }
            else if(val == "-output" && (i+1) < argc){
                elements["output"] = argv[++i];
            }
        }
        if(elements.size() != 3){
            std::cerr<<"Error comando no tiene los argumentos requeridos"<<" "<<elements.size()<<"\n";
            return std::monostate{};
        }
      
        auto tmp2 = ParsedGenerator(elements);
        
        if (std::holds_alternative<GeneratorData>(tmp2)) return std::get<GeneratorData>(tmp2);

        else {std::cerr<<"lolazo"; return std::monostate{};}

    }

    else if(command == "sorter" && argc == 12){
        for(int i = 2; i < argc; i++){
            std::string val((argv[i]));
            if(val == "-input" && (i+1) < argc){
                if(argv[i+1] == "-output"){
                    std::cerr<<"El path del input no existe"<<'\n';
                    return std::monostate{};
                }

                elements["input"] = argv[++i];
            }
            else if(val == "-output" && (i+1) < argc){
                if(argv[(i+1)] == "-alg"){
                    std::cerr<<"El path del output no existe"<<'\n';
                    return std::monostate{};
                }
                elements["output"] = argv[++i];
            }
            else if(val == "-alg" && (i+1) < argc){
                if(argv[(i+1)] == "-pageSize"){
                    std::cerr<<"El path del alg no existe"<<'\n';
                    return std::monostate{};
                }
                elements["alg"] = argv[++i];
            }
            else if(val == "-pageSize" && (i+1) < argc){
                if(argv[(i+1)] == "-pageCount"){
                    std::cerr<<"El path del pageSize no existe"<<'\n';
                    return std::monostate{};
                }
                elements["pageSize"] = argv[++i];
            }
            else if(val == "-pageCount" && (i+1) < argc){
                elements["pageCount"] = argv[++i];
            }
        }
        if(elements.size() != 6){
            std::cerr<<"Error comando no tiene los argumentos requeridos"<<"\n";
            return std::monostate{};
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
#pragma endregion


#pragma region Parseos del tipo de comando
std::variant<std::monostate, GeneratorData> Parsed::ParsedGenerator(const std::unordered_map<std::string, std::string> &elements){
    GeneratorData parse;
    parse.commandType = elements.at("command");
    std::string s = elements.at("size");
    SIZES size;
    try{
        size = StringToSize(s);
    } catch(const std::invalid_argument &e){
        std::cerr<<"Error de valor: "<<e.what()<<"\n";
        return std::monostate{};
    }
    parse.filePath = elements.at("output");
    parse.fileSize = size;

    return parse;
}

std::variant<std::monostate, SorterData> Parsed::ParsedSorter(const std::unordered_map<std::string, std::string> &elements){
    SorterData parse;
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
    parse.outputFilePathBin = output;
    parse.outputFilePathTxt = output;
    parse.sortedAlgorithm = alg;
    parse.pageCount = pageCount;
    parse.pageSize = pageSize;

    return parse;
}
#pragma endregion