#include "common\BinaryFileManager.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <chrono>
#include <string>
#include <string_view>
#include <charconv>
#include <filesystem>

#pragma region Constructores

BinaryFileManager::BinaryFileManager(SIZES fileSize){
    SetFileSize(fileSize);
}
BinaryFileManager::BinaryFileManager(){
	SetFileSize(SIZES::SMALL);
}

#pragma endregion

#pragma region Setter

void BinaryFileManager::SetFileSize(SIZES size){
	fileSize = size;

	totalNumbers = fileSize/totalBytes;
}

#pragma endregion

#pragma region Generate File

void BinaryFileManager::GenerateFile(std::string filePath){
    //Creacion del archivo de salida, el truc es para abrirlo sin nada dentro
	std::ofstream file; 
    file.open(filePath, std::ios::out | std::ios::trunc | std::ios::binary );

	if(!file.is_open()){
		std::cerr<<"Error de apertura"<<"\n";
		return;
	}

	try{	
		//Creacion del archivo
		for(size_t count = 0; count < totalNumbers; count++){ //Cantidad de llenados del buffer
			for(size_t i = 0; i < arraySize-3; i+=4){//llenados del buffer en espacios de 4
				buff[i] = dis(gen);
				buff[i+1] = dis(gen);
				buff[i+2] = dis(gen);
				buff[i+3] = dis(gen);
			}

			file.write(reinterpret_cast<const char*>(&buff[0]), totalBytes); //escritura de todo el buffer lleno en el archivo
		}

	}catch(const std::filesystem::filesystem_error &e){ //atrapar por si hubo algun error del archivo
		std::cerr<<"el archivo no sse puedo generar debido a: "<<e.what()<<'\n';
		return;
	}

	return;
}

#pragma endregion

#pragma region Copy Binary File

bool BinaryFileManager::CopyBinaryFile(const std::string &nameOrigin, const std::string &nameDestiny){
	//Verifica la existencia del archivo de destino
	if(std::filesystem::exists(nameDestiny)){

		//Si el destino existe entonces verificamos si es el mismo que el de origen
		if(std::filesystem::equivalent(nameOrigin, nameDestiny)){
			std::cerr<<"los dos archivos son el mismo"<<'\n';
			return false;
		}

		try{
			//Si el archivo no existe entonces borramos el original para sobreescribirlo
			std::filesystem::remove(nameDestiny);
		}catch(const std::filesystem::filesystem_error &e){
			std::cerr<<"No se pudo borrar debido a: "<<e.what()<<'\n';
			return false;
		}
	}

	try{
		//Copia del archivo
		std::filesystem::copy_file(nameOrigin, nameDestiny, std::filesystem::copy_options::overwrite_existing);
	}catch(const std::filesystem::filesystem_error &e){
		std::cerr<<"No se pudo copiar debido a: "<<e.what()<<'\n';
		return false;
	}

    return true;

}

#pragma endregion

#pragma region Copy Txt File

bool BinaryFileManager::CopyTxtFile(const std::string &nameOrigin, const std::string &nameDestiny){
	//creacion del archivo de lectura y escritura
	std::ifstream origin; 
	std::ofstream destiny;

	//Abrimos los dos archivos y verificamos si se abrieron correctamente
	origin.open(nameOrigin, std::ios::in | std::ios::binary);
	destiny.open(nameDestiny, std::ios::out);

	if(!origin.is_open() || !destiny.is_open()){
        std::cerr<<"Error al abrir alguno de los archivos"<<"\n";
        return false;
    }

	/*
		String para inyectar a los numeros en ascci
		Para ello primero le reservamos los espacios de memoria que representan un numeros enteros
	*/
	std::string str; 
	str.reserve(12 * arraySize);


	//Loop para leer y escribir en el archivo
	while(true){

		//Limpiamos el string de inyeccion primero para que no hayan datos anteriormente creados
		str.clear();

		//Leemos el archivo de origen y metemos la informacion en buffer
		try{
			origin.read(reinterpret_cast<char*>(&buff[0]), totalBytes);
		}catch(const std::filesystem::filesystem_error &e){
			std::cerr<<"Error en la lectura del archivo debido a: "<<e.what()<<'\n';
		}
		
		//cantidad de bytes leidos por iteracion
		size_t numberByte = origin.gcount(); 
			
		//si no hay bytes entonces se termino la lectura
		if(numberByte == 0) break; 

		//Cantidad de numeros a escribir
		size_t numElements = numberByte/sizeof(int32_t); 

		//buffer temporal para el pasado de los numeros a la string de inyeccion
		char temp[13]{}; 

		//Escribimos la cantidad de elemetos
		for(size_t i = 0; i < numElements; i++){
			std::to_chars_result res = std::to_chars(temp, temp+12, buff[i]); //convertimos los numeros en chars

			/*
				Si hay un error de codigo, entonces decimos cual y retornarmos falso

				Si no hay un error entonces vemos la posicion del puntero, en caso que la siguiente posicion sea menor al total
				de espacios entonces agregamos el espacio y avanzamos el puntero, por ultimo agregamos todo el numero al string de inyeccion
				caso contrario mandamos que hubo un error y devolvemos false
			*/

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

		//escribimos en el archivo de destino
		destiny.write(str.data(), str.size()); 
	}

	//si hubo algun error devolvemos un fallos y false
	if(destiny.fail()){
		std::cerr<<"fallo de escritura"<<'\n';
		return false;
	}

	return true;
}

#pragma endregion