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
    this->freePos = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

PagedArray::~PagedArray(){
    for(int i = 0; i < pagedCount; i++){
        SavePage(i);
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
            victim = PopLRU();
        }
        if(!SavePage(victim)){
            std::cout<<victim<<'\n';
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
        auto it = pageToNode.find(numberPaged);
        if(it != pageToNode.end()){
            MoveToFront(it->second);
        }
        else{
            throw std::runtime_error("Error a la hora de encontrar la pagina");
        }
    }

    pagedArr[paged]->SetModified(true);
    pagedArr[paged]->SetLastUsed(count);
    return pagedArr[paged]->page[posNum];
    
}

int PagedArray::FindPage(long long numberPaged){
    auto page = pages.find(numberPaged);
    if(page != pages.end()) return page->second;
    return -1;
}

int PagedArray::FindFreeSpace(){
    if(freePos < pagedCount){
        return freePos++;
    }

    return -1;
}

bool PagedArray::LoadPage(int idx, long long pageNumber){
    size_t fileBytes = totalInts * sizeof(int32_t);
    Page* p = new Page(pageNumber, pagedSize, fileBytes);
    
    if(Swapping::CopyInArray(filePath, p->page, p->GetInicialPos(), p->GetQuantityBytes())){
        pagedArr[idx] = p;
        pages[pageNumber] = idx;
        LRUNode* node = new LRUNode(idx, pageNumber);
        PushFront(node);
        pageToNode[pageNumber] = node;
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

    Page* p = pagedArr[idx];
    long long pageNumber = p->GetNumberPage();

    if(pagedArr[idx]->GetModified()){
        if(!Swapping::UpdateFileFromArray(filePath, pagedArr[idx]->page, pagedArr[idx]->GetInicialPos(), pagedArr[idx]->GetQuantityBytes())){
            return false;
        }
    }

    auto it = pageToNode.find(pageNumber);
    if(it == pageToNode.end()){
        std::cerr << "Error a la hora de encontrar la pagina a eliminar\n";
        return false;
    }

    LRUNode* node = it->second;
    RemoveNode(node);
    pageToNode.erase(it);
    delete node;

    pages.erase(pageNumber);
    delete p;
    pagedArr[idx] = nullptr;
    return true;
}

void PagedArray::PushFront(LRUNode* node){
    node->next = head;
    node->prev = nullptr;

    if(head != nullptr){
        head->prev = node;
    }
    else{
        tail = node;
    }
    head = node;
}

void PagedArray::RemoveNode(LRUNode* node){
    if(node->prev != nullptr){
        node->prev->next = node->next;
    }
    else{
        head = node->next;
    }

    if(node->next != nullptr){
        node->next->prev = node->prev;
    }
    else{
        tail = node->prev;
    }
    node->prev = nullptr;
    node->next = nullptr;
}

void PagedArray::MoveToFront(LRUNode* node){
    if(node == head) return;
    RemoveNode(node);
    PushFront(node);
}

int PagedArray::PopLRU(){
    if(tail == nullptr){
        return -1;
    }

    return tail->idx;
}