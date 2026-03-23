#include <cstdint>
#include <string>
#include <string_view>
#include <random>
#include "EnumSizes.h"

#ifndef BINARYFILEMANAGER_H
#define BINARYFILEMANAGER_H

class BinaryFileManager{
    //Calculo de Bytes por array
    static constexpr size_t arraySize = 131072;
    static constexpr size_t intSize = sizeof(int32_t);
    static constexpr size_t totalBytes = intSize*arraySize;
    
    private:
    //Inicializar el random para generar numeros
    std::random_device rng{};
    std::mt19937 gen{rng()};
    std::uniform_int_distribution<int32_t> dis{INT32_MIN, INT32_MAX};

    //Tamanio del archivo
    SIZES fileSize;

    //Maximo numero de repeticiones
    size_t totalNumbers; 

    int32_t buff[arraySize];

    public:
    BinaryFileManager(SIZES fileSize);
    BinaryFileManager();
    void SetFileSize(SIZES size);
    SIZES GetFileSize(){return fileSize;}

    void GenerateFile(std::string filePath);
    bool CopyBinaryFile(const std::string &nameOrigin, const std::string &nameDestiny);
    bool CopyTxtFile(const std::string &nameOrigin, const std::string &nameDestiny);
    bool CopyInArray(const std::string &nameOrigin, int32_t* arr, size_t beginning, size_t total_bytes);
    bool UpdateFileFromArray(const std::string &fileToUpdate, int32_t* arr, size_t beginning, size_t total_bytes);
};

#endif
