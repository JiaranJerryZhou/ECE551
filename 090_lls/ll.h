#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
//YOUR CODE GOES HERE
void testList();
template<typename T>
class LinkedList
{
 private:
  class Node
  {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(T()), next(NULL), prev(NULL){};
  };
  Node * head;
  Node * tail;
  int size;

 public:
  class iterator
  {
    Node * current;

   public:
    iterator() : current(NULL) {}
    iterator(Node * c) : current(c) {}
    iterator & operator++() {
      current = current->next;
      return *this;
    }
    bool operator==(const iterator & rhs) const {
      if (current == rhs.current) {
        return true;
      }
      return false;
    }
    bool operator!=(const iterator & rhs) const { return (current != rhs.current); }
    T & operator*() { return current->data; }
  };
  iterator begin() { return iterator(head); }
  iterator end() { return iterator(NULL); }
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  void addFront(const T & item) {
    Node * tmp = new Node();
    tmp->data = item;
    if (head != NULL) {
      tmp->next = head;
      head->prev = tmp;
      head = tmp;
    }
    else {
      head = tmp;
      tail = tmp;
    }
    size++;
  }
  void addBack(const T & item) {
    Node * tmp = new Node();
    tmp->data = item;
    if (tail != NULL) {
      tmp->prev = tail;
      tail->next = tmp;
      tail = tmp;
    }
    else {
      tail = tmp;
      head = tmp;
    }
    size++;
  }
  bool remove(const T & item) {
    //handle next pointers
    Node ** curr = &head;
    while (*curr != NULL && (*curr)->data != item) {
      curr = &(*curr)->next;
    }
    //find the item
    if (*curr != NULL) {
      Node * tmp = *curr;
      *curr = (*curr)->next;
      if (*curr == NULL) {
        tail = tmp->prev;
      }
      else {
        tmp->next->prev = tmp->prev;
      }
      delete tmp;
      size--;
      return true;
    }
    //not find
    else {
      return false;
    }
    //handle prev pointers
    /*Node ** curr2 = curr1;
    if (*curr2 != NULL && (*curr2)->data != item) {
      curr2 = &(*curr2)->prev;
    }
    Node * tmp = *curr2;
    *curr2 = (*curr2)->prev;
    size--;
    delete tmp;
    return true;
    */
  }

  int getSize() const { return size; }

  T & operator[](int index) {
    if (index < 0 || index >= getSize()) {
      throw std::out_of_range("invalid index");
    }
    Node * tmp = head;
    for (int i = 0; i < index; i++) {
      tmp = tmp->next;
    }
    return tmp->data;
  }
  T & operator[](int index) const {
    if (index < 0 || index >= getSize()) {
      throw std::out_of_range("invalid index");
    }
    Node * tmp = head;
    for (int i = 0; i < index; i++) {
      tmp = tmp->next;
    }
    return tmp->data;
  }
  int find(const T & item) const {
    Node * tmp = head;
    int index = 0;
    while (tmp != NULL) {
      //Node * next = tmp->next;
      if (tmp->data == item) {
        return index;
      }
      index++;
      tmp = tmp->next;
    }
    return -1;
  }
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * curr = rhs.head;
    while (curr != NULL) {
      addBack(curr->data);
      curr = curr->next;
    }
    /*
    Node * curr = rhs.head;
    Node * next = head;
    Node * prev = head;
    while (curr != NULL){
      if(curr == rhs.head){
	head = new Node();
	head->data = curr->data;
      }
      else{
	next = new Node();
	next->data = curr->data;
	next->prev = prev;
	prev->next = next;
	prev = next;
      }
      curr = curr->next;
    }
    tail = next;
    */
  }
  LinkedList & operator=(const LinkedList & rhs) {
    LinkedList * tmp = new LinkedList();
    Node * curr = rhs.head;
    while (curr != NULL) {
      tmp->addBack(curr->data);
      curr = curr->next;
    }
    while (head != NULL) {
      Node * erase = head->next;
      delete head;
      head = erase;
    }
    head = tmp->head;
    tmp->head = NULL;
    tail = tmp->tail;
    tmp->tail = NULL;
    size = rhs.size;
    delete tmp;
    return *this;
  }

  ~LinkedList() {
    while (head != NULL) {
      Node * tmp = head->next;
      delete head;
      head = tmp;
    }
  }
  friend void testList();
};

#endif
