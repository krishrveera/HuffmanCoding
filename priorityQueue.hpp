
/* Linked List Template Class */


#include <iostream>
#include <string>
#include "HuffmanBase.hpp"
#include <vector>



struct PQNode { 
    PQNode* prev, *next;
    HuffmanNode* huffNode;

    PQNode() {
        prev = nullptr;
        next = nullptr;
        huffNode = nullptr;
    }; 
   

};

void link(PQNode* a, PQNode* b) {
    /*This process puts node a's next to b, and b's prev to a*/
    if(nullptr != a)/*Cannot dereference null...*/
        a->next = b;
    if(nullptr != b)
        b->prev = a;
}

