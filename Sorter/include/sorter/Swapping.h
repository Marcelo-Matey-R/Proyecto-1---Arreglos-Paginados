#include <string>
#include <cstdint>

#ifndef SWAPPING_H
#define SWAPPING_H

class Swapping{
    public:
    static bool CopyInArray(const std::string &nameOrigin, int32_t* arr, size_t beginning, size_t total_bytes); //Lee los bytes en la pagina correspondiente
    static bool UpdateFileFromArray(const std::string &fileToUpdate, int32_t* arr, size_t beginning, size_t total_bytes); //Tira los bytes de la pagina en el archivo
};

#endif