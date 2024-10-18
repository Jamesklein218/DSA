//
// Created by Khoa on 28/11/2022.
//

#ifndef DSALAB_AVLTREE_H
#define DSALAB_AVLTREE_H

#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue { LH = -1, EH = 0, RH = 1 };

void printNSpace(int n) {
  for (int i = 0; i < n - 1; i++)
    cout << " ";
}

void printInteger(int &n) { cout << n << " "; }

template <class T> class AVLTree {
public:
  class Node;

private:
  Node *root;

protected:
  int getHeightRec(Node *node) {
    if (node == NULL)
      return 0;
    int lh = this->getHeightRec(node->pLeft);
    int rh = this->getHeightRec(node->pRight);
    return (lh > rh ? lh : rh) + 1;
  }

public:
  AVLTree() : root(nullptr) {}
  ~AVLTree() {}
  int getHeight() { return this->getHeightRec(this->root); }
  void printTreeStructure() {
    int height = this->getHeight();
    if (this->root == NULL) {
      cout << "NULL\n";
      return;
    }
    queue<Node *> q;
    q.push(root);
    Node *temp;
    int count = 0;
    int maxNode = 1;
    int level = 0;
    int space = pow(2, height);
    printNSpace(space / 2);
    while (!q.empty()) {
      temp = q.front();
      q.pop();
      if (temp == NULL) {
        cout << " ";
        q.push(NULL);
        q.push(NULL);
      } else {
        cout << temp->data;
        q.push(temp->pLeft);
        q.push(temp->pRight);
      }
      printNSpace(space);
      count++;
      if (count == maxNode) {
        cout << endl;
        count = 0;
        maxNode *= 2;
        level++;
        space /= 2;
        printNSpace(space / 2);
      }
      if (level == height)
        return;
    }
  }

  void rotateLeft(Node *&pR) {
    Node *p = pR->pRight;
    pR->pRight = p->pLeft;
    p->pLeft = pR;
    pR = p;
  }

  void rotateRight(Node *&pR) {
    Node *p = pR->pLeft;
    pR->pLeft = p->pRight;
    p->pRight = pR;
    pR = p;
  }

  bool balanceLeft(Node *&pR) {
    switch (pR->balance) {
    case EH: // Case 1
      pR->balance = LH;
      return true;
    case RH: // Case 2
      pR->balance = EH;
      return false;
    default: // Case 3: case LH
      switch (pR->pLeft->balance) {
      case EH: // Case 3.1
        rotateRight(pR);
        pR->balance = RH;
        pR->pRight->balance = LH;
        return true;
      case LH: // Case 3.2
        rotateRight(pR);
        pR->balance = pR->pRight->balance = EH;
        return false;
      default: // Case 3.3
        rotateLeft(pR->pLeft);
        rotateRight(pR);
        if (pR->balance == EH) {
          pR->pLeft->balance = pR->pRight->balance = EH;
        } else if (pR->balance == LH) {
          pR->pLeft->balance = EH;
          pR->pRight->balance = RH;
        } else {
          pR->pLeft->balance = LH;
          pR->pRight->balance = EH;
        }
        pR->balance = EH;
      }
    }
    return false;
  }

  bool balanceRight(Node *&pR) {
    switch (pR->balance) {
    case EH: // Case 1
      pR->balance = RH;
      return true;
    case LH: // Case 2
      pR->balance = EH;
      return false;
    default: // Case 3: case RH
      switch (pR->pRight->balance) {
      case EH: // Case 3.1
        rotateLeft(pR);
        pR->balance = LH;
        pR->pLeft->balance = RH;
        return true;
      case RH: // Case 3.2
        rotateLeft(pR);
        pR->balance = pR->pLeft->balance = EH;
        return false;
      default: // Case 3.3
        rotateRight(pR->pRight);
        rotateLeft(pR);
        if (pR->balance == EH) {
          pR->pRight->balance = pR->pLeft->balance = EH;
        } else if (pR->balance == RH) {
          pR->pRight->balance = EH;
          pR->pLeft->balance = LH;
        } else {
          pR->pRight->balance = RH;
          pR->pLeft->balance = EH;
        }
        pR->balance = EH;
      }
    }
    return false;
  }

  bool insert(Node *&p, const T &value) {
    if (!p) {
      p = new Node(value);
      return true;
    } else if (value < p->data) {
      if (insert(p->pLeft, value))
        return balanceLeft(p);
    } else {
      if (insert(p->pRight, value))
        return balanceRight(p);
    }
    return false; // Not necessarily
  }

  void insert(const T &value) { insert(root, value); }

  bool remove(Node *&p, const T &value) {
    if (!p) {
      return false;
    }
    if (p->data == value) {
      if (p->pLeft && p->pRight) {
        Node *pT = p->pLeft;
        while (pT->pRight)
          pT = pT->pRight;
        p->data = pT->data;
        if (remove(p->pLeft, p->data))
          return !balanceRight(p);
      } else if (p->pLeft) {
        Node *pT = p;
        p = p->pLeft;
        delete pT;
        pT = nullptr;
        return true;
      } else if (p->pRight) {
        Node *pT = p;
        p = p->pRight;
        delete pT;
        pT = nullptr;
        return true;
      } else {
        delete p;
        p = nullptr;
        return true;
      }
    } else if (value < p->data) {
      if (remove(p->pLeft, value))
        return !balanceRight(p);
    } else if (remove(p->pRight, value))
      return !balanceLeft(p);

    return false;
  }

  void remove(const T &value) { remove(root, value); }

  void printInorder(Node *p) {
    if (!p)
      return;
    printInorder(p->pLeft);
    cout << p->data << " ";
    printInorder(p->pRight);
  }

  void printInorder() { printInorder(root); }

  bool search(Node *p, const T &value) {
    if (!p)
      return false;
    if (p->data == value)
      return true;
    return search(p->pLeft, value) || search(p->pRight, value);
  }

  bool search(const T &value) { return search(root, value); }

  class Node {
  private:
    T data;
    Node *pLeft, *pRight;
    BalanceValue balance;
    friend class AVLTree<T>;

  public:
    Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
    ~Node() {}
  };
};

#endif // DSALAB_AVLTREE_H
