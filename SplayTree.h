//
// Created by Khoa on 20/12/2022.
//

#ifndef DSALAB_SPLAYTREE_H
#define DSALAB_SPLAYTREE_H

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

/*
 * Implementation of Splay Tree
 *
 * Splay Tree is a self - adjusted Binary Search Tree
 * in which every operation on element rearranges the tree so
 * that the element is placed at the root position of the tree.
 *
 * Splaying an element, is the process of bringing it to the root
 * position by performing suitable rotation operations
 */
template <class T>
class SplayTree {
protected:
    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class SplayTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };

    /// Variable
    Node *root;
    int nE;

    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
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
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
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

    /*
     * Insert a Node to the Tree
     *
     * Algorithm is similar to Binary Search Tree
     */
    Node* insert(Node *&p, T value) {
        if (!p) {
            p = new Node(value);
            return p;
        }
        if (p->value >= value)
            insert(p->left, value);
        else insert(p->right, value);
    }

    void remove(Node *&p, T value){
        if (!p) return;
        if (p->val == value) {
            if (p->left && p->right) {
                Node *temp = p->right;
                while (temp->left) temp = temp->left;
                p->val = temp->val;
                remove(p->right, p->val);
            } else if (p->left) {
                Node *temp = p;
                p = p->left;
                delete temp;
                temp = nullptr;
            } else if (p->right) {
                Node *temp = p;
                p = p->right;
                delete temp;
                temp = nullptr;
            } else {
                delete p;
                p = nullptr;
            }
        } else if (p->value > value) {
            remove(p->left, value);
        } else {
            remove(p->right, value);
        }
    }
    void splay(Node *src, Node *des) {
        // To be implemented
    }

public:
    /*
     * Insert into the Splay Tree
     *
     * Inserting have 4 steps:
     *      Step 1 - Check whether tree is Empty.
     *      Step 2 - If tree is Empty then insert the newNode as Root node and exit from the operation.
     *      Step 3 - If tree is not Empty then insert the newNode as leaf node using Binary Search tree
     *                  insertion logic.
     *      Step 4 - After insertion, Splay the newNode
     */
    void insert(T value) {
        Node *insertNode = insert(root, value);
        if (insertNode == root) return;
        splay(root, value);
    }

    /*
     * Remove into the Splay Tree
     *
     * The deletion operation in splay tree is similar to deletion operation in Binary Search Tree.
     * But before deleting the element, we first need to splay that element and then delete it from
     * the root position. Finally, join the remaining tree using binary search tree logic.
     */
    void remove(T value) {
        // To be implemented
    }
};

#endif //DSALAB_SPLAYTREE_H
