#include <iostream>
#include <variant>
#include "common\Structs.h"
#include "common\Parsed.h"
#include "common\EnumSorts.h"
#include "common\IOManager.h"
#include "common\BinaryFileManager.h"
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

        bf.GenerateFile(g.filePath);
        
    }

    else if (std::holds_alternative<SorterData>(res)) {
        SorterData s = std::get<SorterData>(res);
        IOManager::SorterDataManager(s);
    }
    
}