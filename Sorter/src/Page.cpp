#include "sorter\Page.h"

Page::Page(int numberPaged, size_t pagedSize){
    this->numberPage = numberPaged;
    this->pagedSize = pagedSize;
    this->quantityBytes = pagedSize*sizeof(int32_t);
    this->inicialPos = numberPage*quantityBytes;
    this->page = new int32_t[pagedSize];
}
Page::~Page(){
    delete[] page;
}