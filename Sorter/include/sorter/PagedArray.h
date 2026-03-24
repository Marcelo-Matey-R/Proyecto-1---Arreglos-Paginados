#include "sorter\Page.h"


#ifndef PAGED_ARRAY_H
#define PAGED_ARRAY_H

class PagedArray{
    private:
    int pagedCount;
    size_t pagedSize;
    Page* pagedArr;
    public:
    PagedArray(int pagedCount, size_t pagedSize);
    PagedArray& operator[](int idx){
        return;
    }
};

#endif