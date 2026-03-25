#include "sorter\Page.h"

Page::Page(int numberPaged, size_t pagedSize){
    this->numberPage = numberPaged; ///numero de pagina
    this->pagedSize = pagedSize; //tamanio del archivo
    this->quantityBytes = pagedSize*sizeof(int32_t); //cantidad bytes a leer
    this->inicialPos = numberPage*quantityBytes; //posicion inicial en el archivo
    this->page = new int32_t[pagedSize]{}; //genera el array donde se guardan los numeros, se inicializan en 0
    this->modified = false;
}
Page::~Page(){
    delete[] page;
}