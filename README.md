# Proyecto-1---Arreglos-Paginados
Este proyecto implementa un sistema de arreglos paginados con dos programas principales:

- `Generator`: genera el archivo binario de entrada.
- `Sorter`: ordena los datos del archivo binario.

## Requisitos

Para compilar el proyecto se necesita:

- CMake 4.x o superior
- Un compilador C++ compatible con CMake
- En este proyecto se uso MSYS2 con `g++` y `mingw32-make`

## Estructura del proyecto

- `Generator/`: código fuente del generador
- `Sorter/`: código fuente del algoritmo de ordenamiento
- `LibbCommon/`: librería compartida
- `Files/`: archivos de entrada y salida
- `build/`: carpeta generada por CMake

## Ejecucion



## Compilación

Desde la raíz del proyecto:

```bash
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

## Ejecucion

### Generator:

```bash
./build/Generator/Generator.exe generator -size <SiZE> -output <Nombre del archivo>
```
SIZE puede ser Small, Medium o Large

### Sorter

```bash
./build/Sorter/Sorter.exe sorter -input Files/input/<Nombre del archivo>.bin -output <nombre del archivo> -alg Algo -pageSize <SIZE> -pageCount <Count>
```
Algo puede ser quicksort, threewaymergesort, mergesort, insertionsort y selectionsort
