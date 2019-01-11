#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t myqueue;
  for (int i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      myqueue.push(new Node(i, counts[i]));
    }
  }
  while (myqueue.size() > 1) {
    Node * a = myqueue.top();
    myqueue.pop();
    Node * b = myqueue.top();
    myqueue.pop();
    Node * c = new Node(a, b);
    myqueue.push(c);
  }
  Node * root = myqueue.top();
  return root;
}
