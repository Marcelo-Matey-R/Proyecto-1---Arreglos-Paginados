#include "FileGenerator.h"
#include <fstream>
#include <cstdint>
#include <chrono>
#include <string>
#include <string_view>


FileGenerator::FileGenerator(size_t fileSize, std::string_view fileName){
    SetFileName(fileName);
    SetFileSize(fileSize);
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

		file.write(reinterpret_cast<const char*>(buff.get()), totalBytes);

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