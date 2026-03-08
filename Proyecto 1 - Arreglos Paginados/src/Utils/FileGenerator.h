#include <cstdint>
#include <string>
#include <string_view>
#include <random>
#include <ostream>

#ifndef FILEGENERATOR_H
#define FILEGENERATOR_H
class FileGenerator{
    //Calculo de Bytes por array
    static constexpr size_t arraySize = 32768;
    static constexpr size_t intSize = sizeof(int32_t);
    static constexpr size_t totalBytes = intSize*arraySize;
    
    private:
    //Inicializar el random para generar numeros
    std::random_device rng{};
    std::mt19937 gen{rng()};


    size_t fileSize = 536870912;
    size_t totalNumbers = fileSize/totalBytes; //Maximo numero de repeticiones

    int32_t buff[arraySize];

    std::string fileName = "";

    public:
    FileGenerator(size_t fileSize, std::string_view fileName);
    void SetFileSize(size_t size){fileSize = (size == 512) ? size*1048576 : size*1073741824; totalNumbers = fileSize/totalBytes;}
    size_t GetFileSize(){return fileSize;}
    void SetFileName(std::string_view name);
    std::string GetFileName(){return fileName;}

    void GenerateFile();
    bool CopyBinaryFile(std::string name);
    bool CopyTxtFile(std::string name);


};

#endif