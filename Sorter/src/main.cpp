#include <iostream>
#include "common/BinaryFileManager.h"
#include "common/EnumSizes.h"
#include "common/EnumSorts.h"
#include "common/IOManager.h"
#include "common/Parsed.h"
#include "common/Structs.h"
#include "SortingAlgorithm.h"
#include <chrono>
#include <filesystem>

int main(int argc, char* argv[]){
    CommandResult res = Parsed::InputParser(argc, argv);
    if (std::holds_alternative<std::monostate>(res)) {
        std::cout << "Error al parsear los argumentos.\n";
        std::cout<<"argc = "<<argc<<"\n";

        return 1;
    }
    else if (std::holds_alternative<SorterData>(res)) {
        SorterData s = std::get<SorterData>(res);
        IOManager::SorterDataManager(s);
        BinaryFileManager bf = BinaryFileManager();
        bf.CopyBinaryFile(s.inputFilePath, s.outputFilePathBin);
        std::uintmax_t size = std::filesystem::file_size(s.outputFilePathBin);
        long long safeSize = static_cast<long long>(size / sizeof(int32_t)); 
        {
            PagedArray pA = PagedArray(s.pageCount, s.pageSize, safeSize, s.outputFilePathBin);
            auto start = std::chrono::steady_clock::now();
            SortingAlgorithms::Sorted(s.sortedAlgorithm, pA);
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> dur = end - start;
            std::cout<<"El tiempo durado fue de: "<<dur.count()<<'\n';
            std::cout<<"El algoritmo utilizado fue: "<<AlgoToString(s.sortedAlgorithm)<<'\n';
            std::cout<<"Las page faults fueron: "<<pA.GetPageFaults()<<'\n';
            std::cout<<"Las page hits fueron: "<<pA.GetPageHits()<<'\n';
        }
        bf.CopyTxtFile(s.outputFilePathBin, s.outputFilePathTxt);
    }
    else{
        std::cerr<<"Se puso el comando incorrecto, se puso un generator no un sorter"<<'\n';
        return 1;
    }
    return 0;
}