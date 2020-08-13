#include "binary-search-tree.h"
#include <iostream>
#include <queue>

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

using namespace std;

BinarySearchTree::Node::Node(DataType newval)
{
    val = newval;
    right = NULL;
    left = NULL;
}

int BinarySearchTree::getNodeDepth(Node* n) const
{
    int left_depth = 0, right_depth = 0;
    if(n == NULL)
        return 0;
    left_depth = 1 + getNodeDepth(n->left);
    right_depth = 1 + getNodeDepth(n->right);
    if(left_depth > right_depth)
        return left_depth;
    else
        return right_depth;
}

BinarySearchTree::BinarySearchTree()
{
    root_ = NULL;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree()
{
    std::queue<Node*> preOrderQueue;
    Node *currentNode = root_;
    if(root_ != NULL)
        preOrderQueue.push(root_);
    while(!preOrderQueue.empty())
    {
        currentNode = preOrderQueue.front();
        preOrderQueue.pop();
        if(currentNode->left != NULL)
            preOrderQueue.push(currentNode->left);
        if(currentNode->right != NULL)
            preOrderQueue.push(currentNode->right);
        delete currentNode;
    }
}

unsigned int BinarySearchTree::size() const
{
    return size_;
}

DataType BinarySearchTree::max() const
{
    Node* current_node = root_;
    while(current_node->right != NULL)
        current_node = current_node->right;
    return current_node->val;
}

DataType BinarySearchTree::min() const
{
    Node* current_node = root_;
    while(current_node->left != NULL)
        current_node = current_node->left;
    return current_node->val;
}

unsigned int BinarySearchTree::depth() const
{
    return getNodeDepth(root_) - 1;
}

void BinarySearchTree::print() const
{
    std::queue<Node*> preOrderQueue;
    Node *currentNode = root_;
    if(root_ != NULL)
        preOrderQueue.push(root_);
    std::cout << "(";
    while(!preOrderQueue.empty())
    {
        currentNode = preOrderQueue.front();
        preOrderQueue.pop();
        if(currentNode->left != NULL)
            preOrderQueue.push(currentNode->left);
        if(currentNode->right != NULL)
            preOrderQueue.push(currentNode->right);
        std::cout << currentNode->val << " ";
    }
    std::cout << ")" << std::endl;
}

bool BinarySearchTree::exists(DataType val) const
{
    Node* temp = root_;
    bool not_there = false;
    while(temp != NULL)
    {
        if(val == temp->val)
            return true;
        else if(val < temp->val)
            temp = temp->left;
        else
            temp = temp->right;
    }
    return false;
}

Node* BinarySearchTree::getRootNode()
{
    return root_;
}

Node** BinarySearchTree::getRootNodeAddress()
{
    return &root_;
}

bool BinarySearchTree::insert(DataType val)
{
    if(root_ == NULL)
    {
        root_ = new Node(val);
        size_++;
        return true;
    }
    else
    {
        Node* temp = root_;
        Node* parent;
        while(temp != NULL)
        {
            if(val == temp->val)
                return false;
            else if(val < temp->val)
            {
                parent = temp;
                temp = temp->left;
            }
            else
            {
                parent = temp;
                temp = temp->right;
            }
        }
        Node* newnode = new Node(val);
        if(val <= parent->val)
            parent->left = newnode;
        else
            parent->right = newnode;
        size_++;
        return true;
    }
}

Node* findPredecessor(Node* ptr) {
    while (ptr->right != NULL)
        ptr = ptr->right;
    return ptr;
}

bool BinarySearchTree::remove(DataType val)
{
    if(root_ == NULL)
        return false;
    else
    {
        Node* temp = root_;
        Node* parent = root_;
        bool found = false;
        bool is_left_child = false;
        while(temp != NULL)
        {
            if(val == temp->val)
            {
                found = true;
                break;
            }
            else if(val < temp->val)
            {
                parent = temp;
                temp = temp->left;
                is_left_child = true;
            }
            else
            {
                parent = temp;
                temp = temp->right;
                is_left_child = false;
            }
        }
        if(!found)
            return false;
        else
        {
            if(temp->left != NULL && temp->right != NULL)
            {
                Node* predecessor = temp->left;
                while (predecessor->right != NULL)
                    predecessor = predecessor->right;
                int predecessor_value = predecessor->val;
                remove(predecessor_value);
                temp->val = predecessor_value;
                size_--;
                return true;
            }
            if(temp->left != NULL)
            {
                if(temp == root_)
                {
                    root_ = temp->left;
                }
                if(is_left_child)
                    parent->left = temp->left;
                else
                    parent->right = temp->left;
                delete temp;
                size_--;
                return true;
            }
            else if(temp->right != NULL)
            {
                if(temp == root_)
                    root_ = temp->right;
                if(is_left_child)
                    parent->left = temp->right;
                else
                    parent->right = temp->right;
                delete temp;
                size_--;
                return true;
            }
            else
            {
                if(temp == root_)
                {
                    delete root_;
                    root_ = NULL;
                    size_--;
                    return true;
                }
                if(is_left_child)
                    parent->left = NULL;
                else
                    parent->right = NULL;
                delete temp;
                size_--;
                return true;
            }
        }
    }
    return false;
}
