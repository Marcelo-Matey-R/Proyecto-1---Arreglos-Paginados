#include <iostream>
#include "common/BinaryFileManager.h"
#include "common/EnumSizes.h"
#include "common/EnumSorts.h"
#include "common/IOManager.h"
#include "common/Parsed.h"
#include "common/Structs.h"
#include <chrono>


int main(int argc, char* argv[]){
    CommandResult res = Parsed::InputParser(argc, argv);
    if (std::holds_alternative<std::monostate>(res)) {
        std::cout << "Error al parsear los argumentos.\n";
        std::cout<<"argc = "<<argc<<"\n";

        return 1;
    }

    if (std::holds_alternative<GeneratorData>(res)) {
        std::cout<<"entro"<<'\n';
        GeneratorData g = std::get<GeneratorData>(res);
        IOManager::GeneratorDataManager(g);
        auto start = std::chrono::steady_clock::now();
        BinaryFileManager bf = BinaryFileManager(g.fileSize);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> dur = end - start;
        std::cout << "Tiempo: " << dur.count() << "s" << std::endl;
        std::cout << "Tamanio del archivo: "<<g.fileSize<<'\n';

        bf.GenerateFile(g.filePath);
        
    }

    else{
        std::cerr<<"Se puso el comando incorrecto, se puso un sorter no un generator"<<'\n';
        return 1;
    }
    return 0;
}