#include "sorter\PagedManager.h"

PagedManager::PagedManager(int numberPaged, size_t pagedSize){
    this->numberPage = numberPaged;
    this->pagedSize = pagedSize;
    this->quantityBytes = pagedSize*sizeof(int32_t);
    this->inicialPos = numberPage*quantityBytes;
    this->page = new int32_t[pagedSize];
}
PagedManager::~PagedManager(){
    delete[] page;
}