struct LRUNode{
    int idx;
    long long pageNumber;
    LRUNode* prev;
    LRUNode* next;
    LRUNode(int idx, long long pageNumber){
        this->idx = idx;
        this->pageNumber = pageNumber;
        this->next = nullptr;
        this->prev = nullptr;
    }    
};