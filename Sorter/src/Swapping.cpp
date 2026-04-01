#include "Swapping.h"
#include <filesystem>
#include <fstream>
#include <iostream>


#pragma region Swapping Utilities

bool Swapping::CopyInArray(const std::string &nameOrigin, int32_t* arr, size_t beginning, size_t total_bytes){
    std::filesystem::path p = nameOrigin;
    uintmax_t n = std::filesystem::file_size(p);
    if(beginning > n){
		std::cout << "file size: " << n << '\n';
		std::cout << "total_bytes: " << total_bytes << '\n';
		std::cout << "beginning: " << beginning << '\n';
        std::cerr<<"La posicion inicial es mayor al tamanio del archivo "<<'\n';
        return false;
    }
    total_bytes = std::min(total_bytes, n - beginning);

	std::ifstream file;
	file.open(nameOrigin, std::ios::in | std::ios::binary);
	if(!file.is_open()){
		std::cerr<<"Hubo un inconveniente para abrir el archivo: "<<nameOrigin<<'\n';
		return false;
	}
	file.seekg(beginning);
	if(file.fail()){
		std::cerr<<"El puntero de lectura tuvo un fallo"<<'\n';
		return false;
	}
	file.read(reinterpret_cast<char*>(arr), total_bytes);
    if(file.gcount() < total_bytes && file.eof()){
        return true;
    }
	if(file.fail()){
		std::cerr<<"Hubo un error de lectura"<<'\n';
		return false;
	}
	
	return true;
}

bool Swapping::UpdateFileFromArray(const std::string &fileToUpdate, int32_t* arr, size_t beginning, size_t total_bytes){
    std::filesystem::path p = fileToUpdate;
    uintmax_t n = std::filesystem::file_size(p);
    if(beginning > n){
        std::cerr<<"La posicion inicial es mayor al tamanio del archivo"<<'\n';
        return false;
    }
	std::fstream file;
	file.open(fileToUpdate, std::ios::in | std::ios::out | std::ios::binary);
	if(!file.is_open()){
		std::cerr<<"Hubo un inconveniente para abrir el archivo: "<<fileToUpdate<<'\n';
		return false;
	}
	file.seekp(beginning);
	if(file.fail()){
		std::cerr<<"El puntero de escritura tuvo un fallo"<<'\n';
		return false;
	}
	file.write(reinterpret_cast<const char*>(arr), total_bytes);
	if(file.fail()){
		std::cerr<<"Hubo un error de escritura"<<'\n';
		return false;
	}
	return true;
}

#pragma endregion