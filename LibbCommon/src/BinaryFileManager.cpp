#include "common\BinaryFileManager.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <chrono>
#include <string>
#include <string_view>
#include <charconv>
#include <filesystem>

BinaryFileManager::BinaryFileManager(std::string_view fileSize){
    SetFileSize(StringToSize(fileSize));
}


void BinaryFileManager::SetFileSize(SIZES size){
	fileSize = size;

	totalNumbers = fileSize/totalBytes;
	
}

void BinaryFileManager::GenerateFile(std::string filePath){
    std::ofstream file; //Crear la variable del file
    file.open(filePath, std::ios::out | std::ios::trunc | std::ios::binary );

	if(!file.is_open()){
		std::cerr<<"Error de apertura"<<"\n";
		return;
	}
	auto start = std::chrono::steady_clock::now();
	try{	
			for(size_t count = 0; count < totalNumbers; count++){
				for(size_t i = 0; i < arraySize-3; i+=4){
					buff[i] = dis(gen);
					buff[i+1] = dis(gen);
					buff[i+2] = dis(gen);
					buff[i+3] = dis(gen);
				}

				file.write(reinterpret_cast<const char*>(&buff[0]), totalBytes);
			}

	}catch(const std::filesystem::filesystem_error &e){
		std::cerr<<"el archivo no sse puedo generar debido a: "<<e.what()<<'\n';
		return;
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> dur = end-start;
	std::cout<<"tiempo: "<<dur.count()<<"\n";
	return;
}


bool BinaryFileManager::CopyBinaryFile(const std::string &nameOrigin, const std::string &nameDestiny){
	auto start = std::chrono::steady_clock::now();
	if(std::filesystem::exists(nameDestiny)){
		if(std::filesystem::equivalent(nameOrigin, nameDestiny)){
			std::cerr<<"los dos archivos son el mismo"<<'\n';
			return false;
		}
		try{
			std::filesystem::remove(nameDestiny);
		}catch(const std::filesystem::filesystem_error &e){
			std::cerr<<"No se pudo borrar debido a: "<<e.what()<<'\n';
			return false;
		}
	}
	try{
		std::filesystem::copy_file(nameOrigin, nameDestiny, std::filesystem::copy_options::overwrite_existing);
	}catch(const std::filesystem::filesystem_error &e){
		std::cerr<<"No se pudo copiar debido a: "<<e.what()<<'\n';
		return false;
	}
	auto end = std::chrono::steady_clock::now();

	std::chrono::duration<double> dur = std::chrono::duration<double>::zero();
	dur += std::chrono::duration_cast<std::chrono::duration<double>>(end-start);
	std::cout<<"tiempo copia .bin: "<<dur.count()<<"\n";

    return true;

}

bool BinaryFileManager::CopyTxtFile(const std::string &nameOrigin, const std::string &nameDestiny){
	if(!std::filesystem::exists(nameOrigin)){std::cerr<<"El path " + nameOrigin + " no existe"<<'\n'; return false;}
	if(!std::filesystem::exists(nameDestiny)){std::cerr<<"El path " + nameDestiny + " no existe"<<'\n'; return false;}
	if(std::filesystem::equivalent(nameOrigin, nameDestiny)){std::cerr<<"El path " + nameDestiny + "y el path" + nameOrigin + "son el mismo"<<'\n'; return false;}

	std::ifstream origin;
	std::ofstream destiny;

	origin.open(nameOrigin, std::ios::in | std::ios::binary);
	destiny.open(nameDestiny, std::ios::out);

	//almacenamiento de numeros
	std::string str; 
	str.reserve(12 * arraySize);

    if(!origin.is_open() || !destiny.is_open()){
        std::cerr<<"Error al abrir alguno de los archivos"<<"\n";
        return false;
    }

	auto start = std::chrono::steady_clock::now();

	while(true){
		str.clear();


		origin.read(reinterpret_cast<char*>(&buff[0]), totalBytes);
			
		size_t numberByte = origin.gcount(); //cantidad de bytes leidos por iteracion
			
		if(numberByte == 0) break; //si no hay bytes entonces se termino la lectura

		if(origin.bad()){
			std::cerr<<"No se pudo leer bien"<<"\n";
			return false;
		}

		size_t numElements = numberByte/sizeof(int32_t); //Cantidad de numeros
		char temp[13]{};
		for(size_t i = 0; i < numElements; i++){
			std::to_chars_result res = std::to_chars(temp, temp+12, buff[i]);

			if(res.ec != std::errc()){
				std::cerr<<std::make_error_code(res.ec).message() << '\n';
				return false;
				}
			else{
					size_t len = res.ptr - temp;
					if(len+1 <= 13){
						temp[len] = ' ';
						++len;
						str.append(temp, len);
					}
					else{
						std::cerr<<"Error de tamnio, se excede el tamanio de temp"<<'\n';
						return false;
					}
			}
				
		}

		destiny.write(str.data(), str.size());
	}
	if(destiny.fail()){
		std::cerr<<"fallo de escritura"<<'\n';
		return false;
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> dur = end-start;
	std::cout<<"tiempo de copiar a lectura humana: "<<dur.count()<<"\n";

	return true;
}
