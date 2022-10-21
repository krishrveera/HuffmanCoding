#ifndef NODE_H
#define NODE_H

// Template Class for Node Storage Object

template <class T>
class Node {
  private:
    T *data;

  public:
    Node<T> *prev;
    Node<T> *next;
  Node() {
    this->prev = nullptr;
    this->next = nullptr;
  }

  ~Node() {
    delete data; //delete prev; delete next;
  }

  Node(T *data, Node<T> *p, Node<T> *n) {
    this->data = data;
    this->prev = p;
    this->next = n;
}

  Node(T *data) {
    this->prev = nullptr;
    this->next = nullptr;
    this->data = data;
}

  Node* getNext() { return  this->next; }

  Node* getPrev() { return  this->prev; }

  bool hasPrev() { return !(this->prev == nullptr); }

  bool hasNext(){ return  !(this->next == nullptr); }

  void setPrev(Node<T> *p) {
    this->prev = p;
}
  void setNext(Node<T> *n) {
    this->next = n;
}

  void setData(T* data) {
    this->data = data;
}
  T *getData() { return this->data; }
  
};
#endif
Footer
© 2022 GitHub, Inc.
Footer navigation
Terms