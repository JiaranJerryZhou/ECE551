#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  if (this->sym != NO_SYM) {
    assert(this->left == NULL && this->right == NULL);
    theMap.insert(std::pair<unsigned, BitString>(sym, b));
  }
  else {
    assert(this->left != NULL && this->right != NULL);
    left->buildMap(b.plusZero(), theMap);
    right->buildMap(b.plusOne(), theMap);
  }
}
