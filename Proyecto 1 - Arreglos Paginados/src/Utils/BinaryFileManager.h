#include <cstdint>
#include <string>
#include <string_view>
#include <random>
#include <ostream>
#include "C:\Users\casam\OneDrive\Documentos\GitHub\Proyecto-1---Arreglos-Paginados\Proyecto 1 - Arreglos Paginados\src\Structs y Enums\EnumSizes.h"

#ifndef BINARYFILEMANAGER_H
#define BINARYFILEMANAGER_H

class BinaryFileManager{
    //Calculo de Bytes por array
    static constexpr size_t arraySize = 32768;
    static constexpr size_t intSize = sizeof(int32_t);
    static constexpr size_t totalBytes = intSize*arraySize;
    
    private:
    //Inicializar el random para generar numeros
    std::random_device rng{};
    std::mt19937 gen{rng()};


    SIZES fileSize = SIZES::SMALL;
    size_t totalNumbers = fileSize/totalBytes; //Maximo numero de repeticiones

    int32_t buff[arraySize];

    public:
    BinaryFileManager(std::string_view fileSize, std::string_view fileName);
    void SetFileSize(SIZES size);
    SIZES GetFileSize(){return fileSize;}

    void GenerateFile(std::string filePath);
    bool CopyBinaryFile(std::string nameOrigin, std::string nameDestiny);
    bool CopyTxtFile(std::string nameOrigin, std::string nameDestiny);


};

#endif
