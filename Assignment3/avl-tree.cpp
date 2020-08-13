#include "avl-tree.h"
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

typedef BinarySearchTree::Node Node;


stack<Node*> AVLTree::createStack(DataType val) {
    //create a stack starting from the root node
    Node* temp = getRootNode();
    stack<Node*> nodes;

    //continue inserting items into the stack until temp is NULL
    while (temp != NULL) {
        nodes.push(temp);
        //go to right children
        if (val > temp->val)
          temp = temp->right;
        //go to left children
        else
          temp = temp->left;
    }
    //return the stack to the function
    return nodes;
}

int AVLTree::getHeight(Node* node) {
    //if node does not exist return 0;
    if (node == NULL) {
      return 0;
    }
    //use recursion to find the heigh of the node, each time, until they reach the end of the AVL tree
    else
    {
        return 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
}

bool AVLTree::equal(Node* node) {
    //if the node is empty then the two sides are equal
    if (node == NULL) {
      return true;
    }
    //if the difference between heights is greater than abs(1), then the two sides are not equal
    if (abs(getHeight(node->right) - getHeight(node->left)) > 1)
      return false;
    //if less than, then it balanced
    else
      return true;
}

bool AVLTree::remove(DataType val)
{
    bool result = BinarySearchTree::remove(val);

    Node* root = getRootNode();
    Node** rootaddress = getRootNodeAddress();

    stack<Node*> stckNode;
    
    Node* curr;
    Node* parent;
    Node* grandparent= root;

    if (!result) {
      //if removal does not work, return false
      return false;
    }
    else {
        //if tree is empty, then it is balanced and returns true
        if (root == NULL) {
          return true;
        }

        //create stack
        stckNode = createStack(val);

        //determine the curr variable by going through all scenarios 
        while (grandparent != NULL && stckNode.size() > 0) {
            grandparent = stckNode.top();
            stckNode.pop();
            if (grandparent->left == NULL && grandparent->right == NULL) {
                curr = grandparent;
                
                if (stckNode.size() > 0) {
                    parent = stckNode.top();
                    stckNode.pop();
                } else {
                    continue;
                }

                if (stckNode.size() > 0) {
                    grandparent = stckNode.top();
                } else {
                    stckNode.push(parent);
                    continue;
                }

                stckNode.push(parent);
            } else if (grandparent->left != NULL && grandparent->left->left == NULL && grandparent->left->right == NULL  && grandparent->right == NULL) {
                curr = grandparent->left;
                parent = grandparent;

                if (stckNode.size() > 0) {
                    grandparent = stckNode.top();
                } else {
                    continue;
                }
            } else if (grandparent->right != NULL && grandparent->right->right == NULL && grandparent->right->left == NULL && grandparent->left == NULL) {

                curr = grandparent->right;
                parent = grandparent;
                if (stckNode.size() > 0) {
                    grandparent = stckNode.top();
                } else {
                    continue;
                }
            }
            //determine parent variable
            if (getHeight(grandparent->left) > getHeight(grandparent->right))
             parent = grandparent->left;
            else
             parent = grandparent->right;
            
            //determine curr variable
            if (getHeight(parent->left) > getHeight(parent->right)) 
              curr = parent->left;
            else
              curr = parent->right;

            //determine which rotation to use based on grandparent, parent and curr
            if (!equal(grandparent)) {
                if (grandparent->left == parent) {
                    if (parent->right == curr) {
                        LeftRightRotate(rootaddress, grandparent);
                    } else {
                        RightRotate(rootaddress, grandparent);
                    }
                } else {
                    if (parent->right == curr) {
                        LeftRotate(rootaddress, grandparent);
                    } else {
                        RightLeftRotate(rootaddress, grandparent);
                    }
                }
            }
        }
        return true;
  }
}

bool AVLTree::insert(DataType val)
{
    bool result = BinarySearchTree::insert(val);

    Node* root = getRootNode();
    Node** rootaddress = getRootNodeAddress();

    stack<Node*> stckNode;
    Node* current;
    Node* parent;
    Node* grandparent = root;

    if (root->val == val) {
      return true;
    }
    
    if(!result) {
      return false;
    }
    else {
        stckNode = createStack(val);
        while (grandparent != NULL && stckNode.size() > 2) {

            current = stckNode.top();
            stckNode.pop();
            parent = stckNode.top();
            stckNode.pop();
            grandparent = stckNode.top();
            stckNode.pop();

            if (!equal(grandparent)) {
                if (grandparent->left == parent) {
                    if (parent->right == current) {
                        LeftRightRotate(rootaddress, grandparent);
                    } else {
                        RightRotate(rootaddress, grandparent);
                    }
                }
                else {
                    if (parent->right == current) {
                        LeftRotate(rootaddress, grandparent);
                    } else {
                        RightLeftRotate(rootaddress, grandparent);
                    }
                }
            }
            stckNode.push(grandparent);
            stckNode.push(parent);
        }
        return true;
    }
}


void AVLTree::RightRotate(Node** ptr, Node* grandparent) {

    Node* parent = grandparent->left;
    grandparent->left = parent->right;
    parent->right = grandparent;

    
    if (*ptr == grandparent) {
        *ptr = parent;
        Node** root = getRootNodeAddress();
        root = &parent;
    }
    else {
        
        Node* curr = *ptr;
        Node **grandparentPtr = NULL;
        do{
            if (grandparent->val < curr->val) {
                grandparentPtr = &curr->left;
                curr = curr->left;
            }
            if(grandparent->val > curr->val)  {
                grandparentPtr = &curr->right;
                curr = curr->right;
            }
        } while (curr->val != grandparent->val);
        *grandparentPtr = parent;
    }
}


void AVLTree::LeftRotate(Node** ptr, Node* grandparent){

    Node *parent = grandparent->right;
    grandparent->right = parent->left;
    parent->left = grandparent;

    if (*ptr == grandparent) {
        *ptr = parent;
        Node** root = getRootNodeAddress();
        root = &parent;
    }
    else {
        Node *curr = *ptr;
        Node **grandparentPtr = NULL;
        do {
            if (grandparent->val > curr->val)  {
                grandparentPtr = &curr->right;
                curr = curr->right;
            }
            else if (grandparent->val < curr->val) {
                grandparentPtr = &curr->left;
                curr = curr->left;
            }
        } while (curr->val != grandparent->val);

        *grandparentPtr = parent;
    }
}


void AVLTree::LeftRightRotate(Node** ptr, Node* grandparent) {
    Node *parent = grandparent->left;

    //rotate left
    LeftRotate(ptr, parent);

    //rotate right
    RightRotate(ptr, grandparent);
}


void AVLTree::RightLeftRotate(Node** ptr, Node* grandparent) {

    Node *parent = grandparent->right;

    //rotate right
    RightRotate(ptr, parent);
    //rotate left
    LeftRotate(ptr, grandparent);
}





