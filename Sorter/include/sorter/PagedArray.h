#include "Page.h"
#include <cstdio>
#include <filesystem>
#include <queue>


#ifndef PAGED_ARRAY_H
#define PAGED_ARRAY_H

class PagedArray{
    private:
    size_t pagedCount;
    size_t pagedSize;
    long long totalInts;
    Page** pagedArr;
    std::string filePath;
    long long pageFaults;
    long long pageHits;
    long long count;
    int FindPage(int numberPaged); //Encuentra la existencia de la pagina que tenga dicho numero de pagina
    int SelectPageToChange(); //Selecciona la pagina a ser eliminada devolviendo el idx
    int FindFreeSpace(); //Encuentra si hay algun lugar no utilizado en el pagedArr entonces devuelve el indice, caso contrario devuelve -1
    bool LoadPage(int idx, long long pageNumber); //Carga la pagina del disco a la memoria en la posicion idx
    bool SavePage(int idx); //Carga la pagina pagedArr[idx] de la memoria al disco
    public:
    PagedArray(size_t pagedCount, size_t pagedSize, long long totalInts, const std::string &filePath);
    int32_t& operator[](long long idx);
    ~PagedArray();
    long long GetPageHits(){return pageHits;}
    long long GetPageFaults(){return pageFaults;}
    long long GetTotalInts(){return totalInts;}
};

#endif