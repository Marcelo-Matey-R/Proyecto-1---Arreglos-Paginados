#include <cstdint>
#include <string>
#include <string_view>
#include <random>
#include <ostream>

#ifndef BINARYFILEMANAGER_H
#define BINARYFILEMANAGER_H
enum SIZES : size_t {SMALL = 536870912, MEDIUM = 1073741824, LARGE = 2147483648};
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

    std::string fileName = "";

    public:
    BinaryFileManager(std::string_view fileSize, std::string_view fileName);
    void SetFileSize(SIZES size);
    SIZES stringToSize(std::string_view str);
    size_t GetFileSize(){return fileSize;}
    void SetFileName(std::string_view name);
    std::string GetFileName(){return fileName;}

    void GenerateFile();
    bool CopyBinaryFile(std::string name);
    bool CopyTxtFile(std::string name);


};

#endif
