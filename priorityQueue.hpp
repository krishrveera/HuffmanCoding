
/* Linked List Template Class */
#ifndef HUFFMANPQ_H
#define HUFFMANPQ_H

#include <iostream>
#include <string>
#include "HuffmanBase.hpp"
#include <vector>



class HuffmanPQ {
 protected:
    
    LinkedHuffNode * head,* tail;
    size_t length;

    void link(LinkedHuffNode* a, LinkedHuffNode* b) {
    /*This process puts node a's next to b, and b's prev to a*/
    if(nullptr != a)/*Cannot dereference null...*/
        a->next = b;
    if(nullptr != b)
        b->prev = a;
}

 public:
    /* Initialize Deque */
    HuffmanPQ() {
      this->head = nullptr;
      this->tail = nullptr;
      this->length = 0;
    }
    /* Removes Node Deque */ 
    ~HuffmanPQ() { 
      LinkedHuffNode* DequePtr = this->tail;
      LinkedHuffNode* above;
      while (nullptr != DequePtr) {
        above = DequePtr;
        DequePtr = DequePtr->prev;
        if (nullptr != above) delete above;
      }
    }

    size_t getLength() {
      return this->length;
    }

    /**
     * @brief Method to add an existing program element to the Deque
     * 
     * @param dataPtr 
     */
    void pushRight(LinkedHuffNode* dataPtr) {
      //std::cout<<*this<<std::endl;
        bool insertion = false;
        if(this->head == nullptr) {
            this->head= dataPtr;
            this->tail= dataPtr;
            this->length++;
            insertion = true;
        }   
        else if(this->tail == this->head) {

            if (this->head->getFrequency() > dataPtr->getFrequency()) { // HEAD has less priority, swap them
                /*Create Linkage*/
                this->link(dataPtr, this->head);

                this->tail = this->head;
                this->head = dataPtr;
                insertion = true;
                this->length++;
            }
            else {
                /*Create Linkage*/
                this->tail = dataPtr;
                this->link(this->head, this->tail);
                insertion = true;
                this->length++;
            }
        } else  {
            /*
                Our list has multiple nodes, back->front approach until we find our insertion spot
            */
            LinkedHuffNode *current = this->tail;
            while(dataPtr->getFrequency() < current->getFrequency() && insertion==false) {
                //Our current node has not found the right insertion spot, and we haven't reached the end of the list
                if (current != this->head) { 

                    current = current->getPrev();
                }
                //Our current node has not found the right insertion spot, and we have reached our head node.
                else {
                    /*Create Linkage*/
                    this->link(dataPtr, this->head);
                    this->head = dataPtr;
                    insertion = true; 
                    this->length++; 
                }
            }
            // WE found our spot!
            if(!insertion) {
                /*
                * Point our new nodes nodes to the current and the currents next node
                * Point the next nodes previous to our new node
                * Point our current nodes next node to our new node
                */
                if(current == this->tail) {// Insertion at end of list (tail)
                    /*Create Linkage*/
                    this->link(this->tail, dataPtr);
                    this->tail = dataPtr;
                    this->length++;
                }
                // Insertion in middle of list
                else {
                    LinkedHuffNode* temp = current->getNext();
                    this->link(current, dataPtr);
                    this->link(dataPtr, temp);
                    insertion = true;
                    this->length++;
                }
            }
        }

      
    }
    
    /**
     * @brief to view the element at the top of the Deque
     * Warning! This variable is meant to be used for inqiury, not for usage in a program.
     * @return Node<T>* 
     */

    LinkedHuffNode* peekFront() {
        return this->head; /* Could create a new here, ask Corsova*/
    }

    /**
     * @brief to remove an element from the top of the Deque
     * 
     * @return Node<T>* 
     */

    LinkedHuffNode* pop() {// o   HEAD o - o - o - o TAIL
      //std::cout<<*this<<std::endl;
      /* Change the Tail, and free the old Tails memory. Reflect this change in the total. */   
      if(this->length == 0) {
        throw std::runtime_error("Error: Cannot remove from empty queue...");
      }
      LinkedHuffNode* old_head = this->head;
      if ( nullptr != old_head && old_head->hasNext() ) {
          this->head = old_head->next;
          link(nullptr, this->head);
          this->length--;
      }
      else { /* Single Node List */
          this->head = nullptr; this->tail = nullptr;
          this->length = 0;
      }
      return old_head;
      delete old_head;
    }
    
    /**
     * @brief to verify whether the top fo the Deque is empty
     * 
     * @return true 
     * @return false 
     */

    bool isEmpty() {
        return nullptr == this->head;
    }
    friend std::ostream& operator<<(std::ostream& out, const HuffmanPQ& d) {
      LinkedHuffNode* curr = d.head;
      out<<"Deque: " << &d << "\n";    
      while(nullptr != curr) {
        out<< "Node Data: "<<  (curr->getCharacter()) << ":" << (curr->getFrequency())<< "\n";
        curr = curr->next;
      }
      return out;
    }
    

};

#endif
