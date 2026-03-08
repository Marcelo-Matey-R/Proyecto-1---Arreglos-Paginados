#include <iostream>
#include <cstdint>
#include <string>
#include <string_view>
#include <random>
#include <memory>


#ifndef FILEGENERATOR_H
#define FILEGENERATOR_H
class FileGenerator{
    //Calculo de Bytes por array
    static constexpr size_t arraySize = 1048576;
    static constexpr size_t intSize = sizeof(int32_t);
    static constexpr size_t totalBytes = intSize*arraySize;
    
    private:
    //Inicializar el random para generar numeros
    std::random_device rng{};
    std::mt19937 gen{rng()};


    size_t fileSize = 536870912;
    size_t totalNumbers = fileSize/totalBytes; //Maximo numero de llenados al array

    std::unique_ptr<int32_t[]> buff = std::make_unique<int32_t[]>(arraySize);

    std::string fileName = "";

    public:
    FileGenerator(size_t fileSize, std::string_view fileName);
    void SetFileSize(size_t size){fileSize = size; totalNumbers = fileSize/totalBytes;}
    void SetFileName(std::string_view name){fileName = name; fileName += ".bin";}

    void GenerateFile();


};

#endif