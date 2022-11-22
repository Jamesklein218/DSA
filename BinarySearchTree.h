//
// Created by Khoa on 23/11/2022.
//

#ifndef CPPCODEBASECLION_BINARYSEARCHTREE_H
#define CPPCODEBASECLION_BINARYSEARCHTREE_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template<class T>
class BinarySearchTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    //Helping function
    void add(Node *&p, T value) {
        if (!p) {
            p = new Node(value);
            return;
        }
        if (p->value >= value)
            add(p->pLeft, value);
        else add(p->pRight, value);
    }
    void add(T value){
        add(root, value);
    }
    void deleteNode(Node *&p, T value){
        if (!p) return;
        if (p->value == value) {
            if (p->pLeft && p->pRight) {
                Node *temp = p->pRight;
                while (temp->pLeft) temp = temp->pLeft;
                p->value = temp->value;
                deleteNode(p->pRight, p->value);
            } else if (p->pLeft) {
                Node *temp = p;
                p = p->pLeft;
                delete temp;
                temp = nullptr;
            } else if (p->pRight) {
                Node *temp = p;
                p = p->pRight;
                delete temp;
                temp = nullptr;
            } else {
                delete p;
                p = nullptr;
            }
        } else if (p->value > value) {
            deleteNode(p->pLeft, value);
        } else {
            deleteNode(p->pRight, value);
        }
    }
    void deleteNode(T value){
        deleteNode(root, value);
    }
    string inOrderRec(Node* root) {
        stringstream ss;
        if (root != nullptr) {
            ss << inOrderRec(root->pLeft);
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }

    string inOrder(){
        return inOrderRec(this->root);
    }

    class Node
    {
    private:
        T value;
        Node* pLeft, * pRight;
        friend class BinarySearchTree<T>;
    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
};


#endif //CPPCODEBASECLION_BINARYSEARCHTREE_H
