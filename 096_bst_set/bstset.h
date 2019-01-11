#include <iostream>

#include "set.h"

template<typename T>
class BstSet : public Set<T>
{
 private:
  class Node
  {
   public:
    T key;
    Node * left;
    Node * right;
    Node(const T & key) : key(key), left(NULL), right(NULL){};
  };
  Node * root;

 public:
  BstSet() : root(NULL){};

  Node * addHelper(Node * current, const T & key) {
    if (current == NULL) {
      Node * ans = new Node(key);
      return ans;
    }
    if (key < current->key) {
      Node * newleft = addHelper(current->left, key);
      current->left = newleft;
    }
    else {
      Node * newright = addHelper(current->right, key);
      current->right = newright;
    }
    return current;
  }

  virtual void add(const T & key) { root = addHelper(root, key); }

  virtual bool contains(const T & key) const {
    Node * current = root;
    while (current != NULL) {
      if (key == current->key) {
        return true;
      }
      else if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    return false;
  }

  Node * removeHelper(Node * current, const T & key) {
    if (current == NULL) {
      return NULL;
    }
    if (key < current->key) {
      current->left = removeHelper(current->left, key);
    }
    else if (key > current->key) {
      current->right = removeHelper(current->right, key);
    }
    else {
      if (current->left == NULL) {
        Node * tmp = current->right;
        delete current;
        return tmp;
      }
      else if (current->right == NULL) {
        Node * tmp = current->left;
        delete current;
        return tmp;
      }
      else {
        Node * tmp = current->left;
        while (tmp->right != NULL) {
          tmp = tmp->right;
        }
        current->key = tmp->key;
        current->left = removeHelper(current->left, key);
      }
    }
    return current;
  }

  virtual void remove(const T & key) { root = removeHelper(root, key); }

  void printHelper(Node * current) {
    if (current != NULL) {
      std::cout << current->key << " ";
      printHelper(current->left);
      printHelper(current->right);
    }
  }

  void print() { printHelper(root); }

  void copyHelper(Node * current) {
    if (current != NULL) {
      add(current->key);
      copyHelper(current->left);
      copyHelper(current->right);
    }
  }

  BstSet(const BstSet & rhs) : root(NULL) {
    Node * current = rhs.root;
    copyHelper(current);
  }

  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      BstSet * tmp = new BstSet(rhs);
      std::swap(root, tmp->root);
      delete tmp;
    }
    return *this;
  }

  void destroy(Node * current) {
    if (current != NULL) {
      destroy(current->left);
      destroy(current->right);
      delete current;
    }
  }

  virtual ~BstSet() { destroy(root); }
};
