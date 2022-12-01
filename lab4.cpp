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

#include "BinaryTree.h"
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
    static void printPreorder(BSTNode *root) {
        if (!root) return;
        cout << root->val << " ";
        printInorder(root->left);
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
    vector<int> arr;
    insertInOrder(arr, root);
    int l = 0, r = arr.size() - 1;

    bool isFound = false;
    while (l < r) {
        if (arr[l] + arr[r] == k) {
            isFound = true;
            break;
        } else if (arr[l] + arr[r] < k) {
            l++;
        } else {
            r--;
        }
    }
    return isFound;
}

// Exercise 6: Author: Nguyen Tran Khoi
BSTNode* increasingBST(BSTNode* root) {
    // STUDENT ANSWER
    if (!root) {
        return root;
    }

    BSTNode* newRoot = nullptr;
    BSTNode* tail = nullptr;

    newRoot = increasingBST(root->left);
    tail = newRoot;

    while (tail && tail->right) {
        tail = tail->right;
    }

    if (tail) {
        tail->right = new BSTNode(root->val);
        tail = tail->right;
    } else {
        newRoot = new BSTNode(root->val);
        tail = newRoot;
    }

    tail->right = increasingBST(root->right);

    return newRoot;
}
// Exercise 7
void insertInOrderQueue(queue<int> &q, BSTNode *root) {
    if (!root) return;
    insertInOrderQueue(q, root->left);
    q.push(root->val);
    insertInOrderQueue(q, root->right);
}
int absolute(int a) {
    return a >= 0 ? a : -a;
}
int minimumAbsolute(BSTNode* root) {
    queue<int> q;
    insertInOrderQueue(q, root);
    int currVal;
    int minDiff = ~(1 << 31);
    while (!q.empty()) {
        currVal = q.front();
        q.pop();
        if (abs(currVal - q.front()) < minDiff) {
            minDiff = abs(currVal - q.front());
        }
    }

    return minDiff;
}

// Exercise 8
int uniqueBST(int n) {
    if (n == 1 || n == 0) return 1;
    vector<int> dp(n + 1);
    fill(dp.begin(), dp.end(), 0);
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i] = (dp[i] + (dp[i - j] * dp[j - 1])) % 2002;
        }
    }

    return dp[n];
}

// Exercise 9
int rangeCount(BSTNode* root, int lo, int hi) {
    if (!root) return 0;
    return ((lo <= root->val && root->val <= hi) ? 1 : 0) +
            rangeCount(root->left, lo, hi) +
            rangeCount(root->right, lo, hi);
}

// Exercise 10
int singleChild(BSTNode* root) {
    if (!root || (!root->left && !root->right)) return 0;
    if (!root->left || !root->right)
        return 1 + singleChild(root->left) + singleChild(root->right);
    return singleChild(root->left) + singleChild(root->right);
}

// Exercise 11: Author: Nguyen Tran Khoi
BSTNode* subtreeWithRange(BSTNode* root, int lo, int hi) {
    if (!root) {
        return nullptr;
    }

    if (root->val < lo) {
        return subtreeWithRange(root->right, lo, hi);
    } else if (root->val > hi) {
        return subtreeWithRange(root->left, lo, hi);
    }

    root->left = subtreeWithRange(root->left, lo, hi);
    root->right = subtreeWithRange(root->right, lo, hi);
    return root;
}

// Exercise 12
int inRange(BSTNode* root, int lo, int hi) {
    if (!root) return 0;
    return ((lo <= root->val && root->val <= hi) ? 1 : 0) +
           inRange(root->left, lo, hi) +
           inRange(root->right, lo, hi);
}

int main() {
    int arr[] = {0, 3, 5, 1, 2, 4};
    int lo = 1, hi = 3;
    BSTNode* root = BSTNode::createBSTree(arr, arr + sizeof(arr)/sizeof(int));
    root = subtreeWithRange(root, lo, hi);
    BSTNode::printPreorder(root);
    BSTNode::deleteTree(root);

    return 0;
}
