#include "Page.h"
#include <algorithm>

Page::Page(long long numberPaged, size_t pagedSize, size_t fileBytes){
    this->numberPage = numberPaged; ///numero de pagina
    this->pagedSize = pagedSize; //tamanio del archivo
    size_t pageBytes = pagedSize * sizeof(int32_t);
    size_t initialPos = static_cast<size_t>(numberPaged) * pageBytes;
    //cantidad bytes a leer
    if(initialPos >= fileBytes-1){
        this->quantityBytes = 0;
    } else {
        this->quantityBytes = (pageBytes < fileBytes - initialPos) ? pageBytes : fileBytes - initialPos;
    }
    this->inicialPos = initialPos; //posicion inicial en el archivo
    this->page = new int32_t[pagedSize]{}; //genera el array donde se guardan los numeros, se inicializan en 0
    this->modified = false;
}
Page::~Page(){
    delete[] page;
}