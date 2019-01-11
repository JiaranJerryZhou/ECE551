#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "ll.h"

void testList(void) {
  //check for initialization
  LinkedList<int> list1;
  LinkedList<int> list2;
  assert(list1.getSize() == 0);
  std::cout << "default constructor pass" << std::endl;
  //check for addBack
  list1.addBack(10);
  assert(list1[0] == 10);
  assert(list1.head->data == 10);
  assert(list1.tail->data == 10);
  list1.addBack(-10);
  list1.addBack(5);
  list1.addBack(5);
  assert(list1.head->data == 10);
  assert(list1.tail->data == 5);
  assert(list1[0] == 10);
  assert(list1[1] == -10);
  assert(list1[2] == 5);
  assert(list1[3] == 5);
  assert(list1.getSize() == 4);
  std::cout << "addBack pass\n";
  //check for addFront
  list2.addFront(10);
  assert(list2[0] == 10);
  assert(list2.head->data == 10);
  assert(list2.tail->data == 10);
  list2.addFront(-10);
  list2.addFront(5);
  list2.addFront(5);
  assert(list2.head->data == 5);
  assert(list2.tail->data == 10);
  assert(list2[0] == 5);
  assert(list2[1] == 5);
  assert(list2[2] == -10);
  assert(list2[3] == 10);
  assert(list2.getSize() == 4);
  std::cout << "addfront pass\n";
  //check for find
  assert(list1.find(1) == -1);
  assert(list1.find(5) == 2);
  assert(list2.find(5) == 0);
  std::cout << "find pass" << std::endl;
  //check for remove
  assert(list1.remove(1) == false);
  assert(list1.remove(10) == true);
  assert(list1[0] == -10);
  assert(list1.head->data == -10);
  list2.remove(10);
  assert(list2[2] == -10);
  assert(list2.tail->data == -10);
  list2.addBack(5);
  list2.remove(5);
  assert(list2[1] == -10);
  list2.remove(5);
  assert(list2[1] == 5);
  std::cout << "remove passed" << std::endl;
  //check for copy
  LinkedList<int> list3(list1);
  LinkedList<int> list4;
  LinkedList<int> list5(list4);
  assert(list5.getSize() == 0);
  assert(list3.getSize() == 3);
  list1.remove(-10);
  assert(list3[0] == -10);  //check for deep copy
  assert(list3.getSize() == 3);
  std::cout << "copy passed" << std::endl;
  //check for = if it is deep copy
  list3 = list2;
  assert(list3.getSize() == 2);
  list2.addFront(6);
  assert(list3[0] == -10);
  assert(list3.getSize() == 2);
  list3 = list4;
  assert(list3.getSize() == 0);

  //check for remove an empty list and a list with one node
  assert(list4.remove(0) == false);
  list4.addFront(0);
  assert(list4.find(0) == 0);
  assert(list4.remove(0) == true);
  assert(list4.getSize() == 0);
  assert(list4.find(0) == -1);
  list4.addBack(0);
  assert(list4.find(0) == 0);
  assert(list4.remove(0) == true);
  assert(list4.getSize() == 0);
  assert(list4.find(0) == -1);
  //check for remove duplicate
  list4.addFront(5);
  list4.addBack(5);
  list4.addBack(5);
  assert(list4.remove(5) == true);
  assert(list4.find(5) == 0);
  assert(list4.getSize() == 2);
  assert(list4.remove(5) == true);
  assert(list4.remove(5) == true);
  assert(list4.getSize() == 0);
  assert(list4.find(5) == -1);
  //check for pointers
  list4.addFront(1);
  list4.addFront(2);
  list4.addFront(3);  //(3,2,1)
  list4.remove(2);
  assert(list4.head->next == list4.tail);
  assert(list4.tail->prev == list4.head);
  //check for iterator
  for (LinkedList<int>::iterator it = list1.begin(); it != list1.end(); ++it) {
    std::cout << *it << std::endl;
  }
}

int main(void) {
  testList();
  return EXIT_SUCCESS;
}
