#ifndef SYDE223_A3_AVL_TREE_H
#define SYDE223_A3_AVL_TREE_H
#include "binary-search-tree.h"
#include <queue>
#include <stack>
using namespace std;
class AVLTree: public BinarySearchTree
{
public:
    // Overriden insert and remove functions
    // Do not modify these definitions

    //The AVL tree should be kept balanced after calling just insert or remove.
    bool insert(DataType val);
    bool remove(DataType val);

    // Define additional functions and attributes below if you need
    stack<Node*> createStack(DataType val);
    int getHeight(Node* node);
    bool equal(Node* node);

    void RightRotate(Node** ptr, Node* grandparent);
    void LeftRotate(Node** ptr, Node* grandparent);
    void LeftRightRotate(Node** ptr, Node* grandparent);
    void RightLeftRotate(Node** ptr, Node* grandparent);
};

#endif //SYDE223_A3_AVL_TREE_H
