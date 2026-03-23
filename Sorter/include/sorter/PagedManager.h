#include <cstdint> 
#ifndef PAGED_MANAGER_H
#define PAGED_MANAGER_H

class PagedManager{
    private:
    int numberPage;
    size_t pagedSize;
    size_t inicialPos;
    size_t quantityBytes;
    public:
    int32_t* page;
    PagedManager(int numberPage, size_t pagedSize);
    ~PagedManager();
    size_t GetQuantityBytes(){return quantityBytes;}
    int GetNumberPage(){return numberPage;}
    size_t GetInicialPos(){return inicialPos;}
};

#endif