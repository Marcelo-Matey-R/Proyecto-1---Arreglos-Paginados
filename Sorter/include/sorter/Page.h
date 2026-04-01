#include <cstdint> 
#ifndef PAGED_MANAGER_H
#define PAGED_MANAGER_H

class Page{
    private:
    long long numberPage;
    size_t pagedSize;
    size_t inicialPos;
    size_t quantityBytes;
    bool modified;
    long long lastUsed;
    public:
    int32_t* page;
    Page(long long numberPage, size_t pagedSize, size_t fileBytes);
    ~Page();
    size_t GetQuantityBytes(){return quantityBytes;}
    int GetNumberPage(){return numberPage;}
    size_t GetInicialPos(){return inicialPos;}
    bool GetModified(){return modified;}
    long long GetLastUsed(){return lastUsed;}
    void SetModified(bool m){this->modified = m;}
    void SetLastUsed(long long i){this->lastUsed = i;}
};

#endif