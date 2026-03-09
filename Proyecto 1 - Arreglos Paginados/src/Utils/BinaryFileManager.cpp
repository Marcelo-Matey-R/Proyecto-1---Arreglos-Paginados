#include "FileGenerator.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <chrono>
#include <string>
#include <string_view>
#include <filesystem>

FileGenerator::FileGenerator(std::string_view fileSize, std::string_view fileName){
    SetFileName(fileName);
    SetFileSize(stringToSize(fileSize));
}
SIZES stringToSize(std::string_view str) {
    if (str == "SMALL")  return SIZES::SMALL;
    if (str == "MEDIUM") return SIZES::MEDIUM;
    if (str == "LARGE")  return SIZES::LARGE;
    
    // Manejo de error si el string no coincide
    throw std::invalid_argument("Tamaño no válido");
}
void FileGenerator::SetFileSize(SIZES size){
	fileSize = size;
	
}

void FileGenerator::SetFileName(std::string_view name){
	fileName = name;
	std::filesystem::path file(fileName);
	file.replace_extension(".bin");
}

void FileGenerator::GenerateFile(){
    std::ofstream file; //Crear la variable del file
    file.open(fileName, std::ios::out | std::ios::trunc | std::ios::binary );

	if(!file.is_open()){
		std::cout<<"error"<<"\n";

		return;
	}
	auto start = std::chrono::steady_clock::now();
	for(size_t count = 0; count < totalNumbers; count++){
		for(size_t i = 0; i < arraySize-3; i+=4){
			buff[i] = gen();
			buff[i+1] = gen();
			buff[i+2] = gen();
			buff[i+3] = gen();
		}

		file.write(reinterpret_cast<const char*>(&buff[0]), totalBytes);

		if(file.fail()){
			std::cout<<"Error de escritura"<<"\n";
			file.close();
			return;
		}
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> dur = end-start;
	std::cout<<"tiempo: "<<dur.count()<<"\n";
	file.close();
}


bool FileGenerator::CopyBinaryFile(std::string name){
	std::ifstream origin;
	std::ofstream destiny;

	origin.open(fileName, std::ios::in | std::ios::binary);
	destiny.open(name, std::ios::out | std::ios::binary);

    if(!origin.is_open() || !destiny.is_open()){
        std::cout<<"Error al abrir alguno de los archivos"<<"\n";
		origin.close();
		destiny.close();
        return false;
    }

    destiny << origin.rdbuf();

    if(destiny.fail()){
        std::cout<<"Error de escritura"<<"\n";
		origin.close();
		destiny.close();
        return false;
    }
	origin.close();
	destiny.close();
    return true;

}

bool FileGenerator::CopyTxtFile(std::string name){
	std::ifstream origin;
	std::ofstream destiny;

	//asegura la extension de la ruta
	std::filesystem::path f(name);
	f.replace_extension(".txt");

	origin.open(fileName, std::ios::in | std::ios::binary);
	destiny.open(name, std::ios::out);

	//almacenamiento de numeros
	std::string str; 
	str.reserve(11 * totalBytes);

    if(!origin.is_open() || !destiny.is_open()){
        std::cout<<"Error al abrir alguno de los archivos"<<"\n";
		origin.close();
		destiny.close();
        return false;
    }

	auto start = std::chrono::steady_clock::now();
	while(true){
		str.clear();


		origin.read(reinterpret_cast<char*>(&buff[0]), totalNumbers);
		
		size_t numberByte = origin.gcount(); //cantidad de bytes leidos por iteracion
		
		if(numberByte == 0) break; //si no hay bytes entonces se termino la lectura

		if(origin.bad()){
			std::cout<<"No se pudo leer bien"<<"\n";
			origin.close();
			destiny.close();
			return false;
		}

		size_t numElements = numberByte/sizeof(int32_t); //Cantidad de numeros
		
		for(size_t i = 0; i < numElements; i++){

			//pasar de numeros a texto y almacernar los numeros en el string
			str.append(std::to_string(buff[i])); 
			str += ' ';
		}

		destiny.write(str.data(), str.size());
		
		if(destiny.fail()){
			std::cout<<"Error de escritura"<<"\n";
			origin.close();
			destiny.close();
			return false;
    	}	
		
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> dur = end-start;
	std::cout<<"tiempo: "<<dur.count()<<"\n";
	origin.close();
	destiny.close();

	return true;
}
