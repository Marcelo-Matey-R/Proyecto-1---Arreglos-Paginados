#include <cstdint> 
#ifndef PAGED_MANAGER_H
#define PAGED_MANAGER_H

class Page{
    private:
    int numberPage;
    size_t pagedSize;
    size_t inicialPos;
    size_t quantityBytes;
    public:
    int32_t* page;
    Page(int numberPage, size_t pagedSize);
    ~Page();
    size_t GetQuantityBytes(){return quantityBytes;}
    int GetNumberPage(){return numberPage;}
    size_t GetInicialPos(){return inicialPos;}
};

#endif