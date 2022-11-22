#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <string>
#include <cstring>
#include <climits>
#include <utility>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <functional>
#include <algorithm>

#include "BinarySearchTree.h"

using namespace std;

class BSTNode {
public:
    int val;
    BSTNode *left;
    BSTNode *right;
    BSTNode() {
        this->left = this->right = nullptr;
    }
    BSTNode(int val) {
        this->val = val;
        this->left = this->right = nullptr;
    }
    BSTNode(int val, BSTNode*& left, BSTNode*& right) {
        this->val = val;
        this->left = left;
        this->right = right;
    }

    static void insert(BSTNode *& root, int value) {
        if (!root) root = new BSTNode(value);
        else if (root->val > value) insert(root->left, value);
        else insert(root->right, value);
    }
    static BSTNode *createBSTree(int *begin, int *end) {
        int *arr = begin, size = end - begin;
        BSTNode *root = nullptr;
        for (size_t i = 0; i < size; ++i)
            insert(root, arr[i]);
        return root;
    }
    static void printInorder(BSTNode *root) {
        if (!root) return;
        printInorder(root->left);
        cout << root->val << " ";
        printInorder(root->right);
    }
    static void deleteTree(BSTNode *& root) {
        if (!root) return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
        root = nullptr;
    }
};

// Exercise 2
int getLevel(BSTNode* root, int value, int level) {
    if (!root) return 0;
    if (root->val == value) return level;
    if (root->val > value) return getLevel(root->left, value, level + 1);
    return getLevel(root->right, value, level + 1);
}

vector<int> levelAlterTraverse(BSTNode* root) {
    vector<int> res;
    vector<int> container;
    if (!root) return res;
    queue<BSTNode *> q;

    int currentLevel = 1;
    bool isLeftFirst = true;
    q.push(root);
    while (!q.empty()) {
        BSTNode* tmp = q.front();

        if (getLevel(root, tmp->val, 1) != currentLevel) {
            if (!isLeftFirst) {
                reverse(container.begin(), container.end());
            }

            for (size_t i = 0; i < container.size(); ++i)
                res.push_back(container[i]);
            container.clear();
            isLeftFirst = !isLeftFirst;
            currentLevel++;

        }
        container.push_back(tmp->val);

        if (tmp->left) q.push(tmp->left);
        if (tmp->right) q.push(tmp->right);

        q.pop();
    }

    if (!container.empty()) {
        if (!isLeftFirst) {
            reverse(container.begin(), container.end());
        }

        for (size_t i = 0; i < container.size(); ++i)
            res.push_back(container[i]);
        container.clear();
        isLeftFirst = !isLeftFirst;
        currentLevel++;
    }

    return res;

}

// Exercise 3
int enlarging(BSTNode* root, int prevMax = 0) {
    if (!root) return 0;
    int maxRight = enlarging(root->right, prevMax);

    root->val = root->val + max(prevMax,(maxRight != 0 ? maxRight : 0));
    int maxLeft = enlarging(root->left, root->val);
    return (maxLeft != 0 ? maxLeft : root->val);
}

BSTNode* enlarge(BSTNode* root) {
    enlarging(root);
    return root;
}

// Exercise 4
void insertInOrder(vector<int> &arr, BSTNode *root) {
    if (!root) return;
    insertInOrder(arr, root->left);
    arr.push_back(root->val);
    insertInOrder(arr, root->right);
}
int kthSmallest(BSTNode* root, int k) {
    vector<int> arr;
    insertInOrder(arr, root);
    return arr[k - 1];
}

// Exercise 5
bool findTarget(BSTNode* root, int k) {

}

int main() {
    int arr[] = {6, 9, 2, 13, 0, 20};
    int k = 2;
    BSTNode* root = BSTNode::createBSTree(arr, arr + sizeof(arr)/sizeof(int));
    cout << findTarget(root, k);
    BSTNode::deleteTree(root);

    return 0;
}
