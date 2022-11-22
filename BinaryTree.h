//
// Created by Khoa on 18/11/2022.
//

#ifndef CPPCODEBASECLION_BINARYTREE_H
#define CPPCODEBASECLION_BINARYTREE_H

#include<iostream>
#include<string>
using namespace std;

template<class K, class V>
class BinaryTree
{
public:
    class Node;

private:
    Node *root;

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    class Node
    {
    private:
        K key;
        V value;
        Node *pLeft, *pRight;
        friend class BinaryTree<K, V>;

    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };

    void addNode(string posFromRoot, K key, V value)
    {
        if(posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }

        Node* walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l-1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if(posFromRoot[l-1] == 'L')
            walker->pLeft = new Node(key, value);
        if(posFromRoot[l-1] == 'R')
            walker->pRight = new Node(key, value);
    }

    // STUDENT ANSWER BEGIN
    int countTwoChildrenNode(Node *p) {
        if (!p) return 0;
        return (int)(p->pLeft && p->pRight) + countTwoChildrenNode(p->pLeft) + countTwoChildrenNode(p->pRight);
    }
    int countTwoChildrenNode()
    {
        return countTwoChildrenNode(root);
    }

    int getHeight(Node *p) {
        if (!p) return 0;
        return 1 + std::max(getHeight(p->pLeft), getHeight(p->pRight));
    }
    int getHeight() {
        return getHeight(root);
    }
    string preOrder(Node *p) {
        if (!p) return "";
        string res = to_string(p->value) + " ";
        res += (preOrder(p->pLeft) + preOrder(p->pRight));
        return res;
    }
    string preOrder() {
        return preOrder(root);
    }

    string inOrder(Node *p) {
        if (!p) return "";
        string res = inOrder(p->pLeft);
        res += to_string(p->value) + " ";
        res += inOrder(p->pRight);
        return res;
    }
    string inOrder() {
        return inOrder(root);
    }

    string postOrder(Node *p) {
        if (!p) return "";
        string res = postOrder(p->pLeft);
        res += postOrder(p->pRight);
        res += to_string(p->value)+ " ";
        return res;
    }
    string postOrder() {
        return postOrder(root);
    }

    int sumOfLeafs(Node *p) {
        if (!p) return 0;
        if (!p->pLeft && !p->pRight) return p->value;
        return sumOfLeafs(p->pLeft) + sumOfLeafs(p->pRight);
    }
    int sumOfLeafs(){
        return sumOfLeafs(root);
    }

    void BFS() {
        if (!this->root) {
            return;
        }

        queue<Node*> q;
        q.push(this->root);

        while (!q.empty()) {
            Node* walker = q.front();
            q.pop();

            cout << walker->value << " ";

            if (walker->pLeft)
                q.push(walker->pLeft);
            if (walker->pRight)
                q.push(walker->pRight);
        }
    }
};

#endif //CPPCODEBASECLION_BINARYTREE_H
