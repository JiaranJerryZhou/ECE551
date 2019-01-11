
#include <iostream>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V>
{
 private:
  class Node
  {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node(const K & key, const V & value) : key(key), value(value), left(NULL), right(NULL){};
  };
  Node * root;

 public:
  BstMap() : root(NULL){};

  Node * addHelper(Node * current, const K & key, const V & value) {
    if (current == NULL) {
      Node * ans = new Node(key, value);
      return ans;
    }
    if (key == current->key) {
      current->value = value;
    }
    else if (key < current->key) {
      Node * newleft = addHelper(current->left, key, value);
      current->left = newleft;
    }
    else {
      Node * newright = addHelper(current->right, key, value);
      current->right = newright;
    }
    return current;
  }

  virtual void add(const K & key, const V & value) { root = addHelper(root, key, value); }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * current = root;
    while (current != NULL) {
      if (key == current->key) {
        return current->value;
      }
      else if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    throw std::invalid_argument("cannot find target key\n");
  }

  Node * removeHelper(Node * current, const K & key) {
    if (current == NULL) {
      return NULL;
    }
    if (key < current->key) {
      current->left = removeHelper(current->left, key);
      return current;
    }
    else if (key > current->key) {
      current->right = removeHelper(current->right, key);
      return current;
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
        current->value = tmp->value;
        current->left = removeHelper(current->left, key);
        return current;
      }
    }
  }
  virtual void remove(const K & key) { root = removeHelper(root, key); }

  void printHelper(Node * current) {
    if (current != NULL) {
      std::cout << current->data << " ";
      printHelper(current->left);
      printHelper(current->right);
    }
  }

  void print() { printHelper(root); }

  void copyHelper(Node * current) {
    if (current != NULL) {
      add(current->key, current->value);
      copyHelper(current->left);
      copyHelper(current->right);
    }
  }

  BstMap(const BstMap & rhs) : root(NULL) {
    Node * current = rhs.root;
    copyHelper(current);
  }

  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      BstMap * tmp = new BstMap(rhs);
      destroy(root);
      root = tmp->root;
      tmp->root = NULL;
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

  virtual ~BstMap() { destroy(root); }
};
