#include <cstdint>
#include <string>
#include <string_view>
#include <random>
#include <ostream>
#include "EnumSizes.h"

#ifndef BINARYFILEMANAGER_H
#define BINARYFILEMANAGER_H

class BinaryFileManager{
    //Calculo de Bytes por array
    static constexpr size_t arraySize = 131075;
    static constexpr size_t intSize = sizeof(int32_t);
    static constexpr size_t totalBytes = intSize*arraySize;
    
    private:
    //Inicializar el random para generar numeros
    std::random_device rng{};
    std::mt19937 gen{rng()};
    std::uniform_int_distribution<int32_t> dis{INT32_MIN, INT32_MAX};

    SIZES fileSize = SIZES::SMALL;
    size_t totalNumbers = fileSize/totalBytes; //Maximo numero de repeticiones

    int32_t buff[arraySize];

    public:
    BinaryFileManager(std::string_view fileSize);
    void SetFileSize(SIZES size);
    SIZES GetFileSize(){return fileSize;}

    void GenerateFile(std::string filePath);
    bool CopyBinaryFile(const std::string &nameOrigin, const std::string &nameDestiny);
    bool CopyTxtFile(const std::string &nameOrigin, const std::string &nameDestiny);


};

#endif
