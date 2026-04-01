#include "PagedArray.h"
#include "common/BinaryFileManager.h"
#include "Swapping.h"
#include <iostream>

PagedArray::PagedArray(size_t pagedCount, size_t pagedSize, long long totalInts, const std::string &filePath){
    this->pagedCount = pagedCount;
    this->pagedSize = pagedSize;
    this->filePath = filePath;
    this->pagedArr = new Page*[pagedCount]{};
    this->count = 0;
    this->pageHits = 0;
    this->pageFaults = 0;
    this->totalInts = totalInts;
}

PagedArray::~PagedArray(){
    for(int i = 0; i < pagedCount; i++){
        delete pagedArr[i];
    }
    delete[] pagedArr;
}

int32_t& PagedArray::operator[](long long idx){
    count++;
    long long numberPaged = idx/pagedSize; //numero de pagina
    long long posNum = idx%pagedSize; //posicion del numero dentro de la pagina
    long long paged = FindPage(numberPaged);

    if(paged == -1){
        pageFaults++;
        int victim = FindFreeSpace();
        if(victim == -1){
            victim = SelectPageToChange();
        }
        if(!SavePage(victim)){
            throw std::runtime_error("Error a la hora de cargar la pagina al disco");
        }
        if(!LoadPage(victim, numberPaged)){
            std::cout<<"idx: "<<idx<<'\n';
            std::cout<<"numberPaged: "<<numberPaged<<'\n';
            throw std::runtime_error("Error al cargar la pagina en memoria");
        }
        paged = victim;
    }

    else{
        pageHits++;
    }

    pagedArr[paged]->SetModified(true);
    pagedArr[paged]->SetLastUsed(count);
    return pagedArr[paged]->page[posNum];
    
}

int PagedArray::FindPage(int numberPaged){
    for(int i = 0; i < pagedCount; i++){
        if(pagedArr[i] == nullptr){
            continue;
        }
        if(pagedArr[i]->GetNumberPage() == numberPaged){
            return i;
        }
    }
    return -1;
}

int PagedArray::FindFreeSpace(){
    for(int i = 0; i < pagedCount; i++){
        if(pagedArr[i] == nullptr){
            return i;
        }
    }
    return -1;
}

bool PagedArray::LoadPage(int idx, long long pageNumber){
    size_t fileBytes = totalInts * sizeof(int32_t);
    Page* p = new Page(pageNumber, pagedSize, fileBytes);
    
    if(Swapping::CopyInArray(filePath, p->page, p->GetInicialPos(), p->GetQuantityBytes())){
        pagedArr[idx] = p;
        return true;
    }
    else{
        delete p;
        return false;
    }
}

bool PagedArray::SavePage(int idx){
    if(pagedArr[idx] == nullptr){
        return true;
    }
    if(pagedArr[idx]->GetModified()){
        if(!Swapping::UpdateFileFromArray(filePath, pagedArr[idx]->page, pagedArr[idx]->GetInicialPos(), pagedArr[idx]->GetQuantityBytes())){
            return false;
        }
    }
    delete pagedArr[idx];
    pagedArr[idx] = nullptr;
    return true;
}

int PagedArray::SelectPageToChange(){
    int leastUsed = 0;
    long long min = LLONG_MAX;
    for(int i = 0; i < pagedCount; i++){
        if(pagedArr[i] == nullptr) continue;

        long long pUsed = pagedArr[i]->GetLastUsed();
        if(pUsed < min){
            min = pUsed;
            leastUsed = i;
        }
    }
    return leastUsed;
}