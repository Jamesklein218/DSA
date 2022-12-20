//
// Created by Khoa on 20/12/2022.
//

#ifndef DSALAB_DLINKEDLIST_H
#define DSALAB_DLINKEDLIST_H

#include <string>

/*
 * Implementation of Doubly Linked-List
 *
 * Singly Linked List can only traverse through in one direction.
 * Doubly Linked List fixes that issue by providing another
 * pointer points to the previous elements. Every other implementation
 * is similar to Singly Linked List
 */
template <class T>
class DLinkedList {
protected:
    class Node {
    public:
        T       val;
        Node*   prev;
        Node*   next;
        Node(const T& val, Node *prev = nullptr, Node *next = nullptr)
        : val(val), prev(prev), next(next) {}
    };

    Node* head;
    Node* tail;
    int nE;
public:
    DLinkedList(): head(nullptr), tail(nullptr), nE(0) {}

    /*
     * Insert an element into the Linked-List
     */
    void insert(const T& val, int index) {
        if (head) {
            if (index) {
                Node *tmp = head;
                while (tmp->next && index > 1) {
                    tmp = tmp->next;
                    index--;
                }
                tmp->next = new Node(val, tmp, tmp->next);
                if (tmp == tail) tail = tmp->next;
            } else {
                head = new Node(val, nullptr, head);
            }
        } else {
            head = new Node(val, nullptr, head);
            tail = head;
        }

        nE++;
    }

    /*
     * Remove element at index "index"
     */
    void remove(int index) {
        if (head) {
            if (index) {
                Node *tmp = head;
                while (tmp->next && index > 1) {
                    tmp = tmp->next;
                    index--;
                }
                Node *deleteNode = tmp->next;
                tmp->next = tmp->next->next;
                if (tail == deleteNode) tail = tmp;
                delete deleteNode;
                deleteNode = nullptr;
            } else {
                Node *deleteNode = head;
                head = head->next;
                if (tail == deleteNode) tail = head;
                delete deleteNode;
                deleteNode = nullptr;
            }
            nE--;
        }
    }

    /*
     * Insert last element
     */
    void push_back(const T& val) {
        insert(val, nE);
    }

    /*
     * Remove last elements
     */
    void pop_back() {
        remove(nE - 1);
    }

    /*
    * Insert first element
    */
    void push_front(const T& val) {
        insert(val, 0);
    }

    /*
     * Remove first elements
     */
    void pop_front() {
        remove(0);
    }

    /*
     * Return if the list is empty or not
     */
    bool empty() {
        return nE == 0;
    }

    /*
     * Size of the list
     */
    int size() {
        return nE;
    }

    std::string toString() {
        Node *walker = head;
        std::string res = "[";
        while (walker && walker != tail) {
            res += std::to_string(walker->val) + ",";
            walker = walker->next;
        }
        if (walker) res += std::to_string(walker->val);
        res += "]";
        return res;
    }
};

#endif //DSALAB_DLINKEDLIST_H
