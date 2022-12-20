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

#include "SLinkedList.h"
#include "Sorting.h" // Lab 3
#include "BinaryTree.h" // Lab 3

using namespace std;

// Exercise 1
template <class T>
void SLinkedList<T>::bubbleSort() {
    for (Node *p = head; p->next; p = p->next) {
        for (Node *pN = head; pN->next; pN = pN->next) {
            if (pN->data > pN->next->data) {
                T tmp(pN->data);
                pN->data = pN->next->data;
                pN->next->data = tmp;
            }
        }
        this->printList();
    }
}


struct ListNode {
    int val;
    ListNode* next;
    ListNode(int _val = 0, ListNode* _next = nullptr) : val(_val), next(_next) { }
};

// Exercise 3
// Merge two sorted lists
ListNode* mergeLists(ListNode* a, ListNode* b) {
    return nullptr;
}

// Sort and unsorted list given its head pointer
ListNode* mergeSortList(ListNode* head) {
    return nullptr;
}

// Exercise 5
template <class T>
void Sorting<T>::oddEvenSort(T *start, T *end) {
    long N = end - start;
    T *arr = start;
    bool isSorted = false; // Initially array is unsorted

    while (!isSorted)
    {
        isSorted = true;

        for (int i=1; i<=N-2; i=i+2)
        {
            if (arr[i] > arr[i+1])
            {
                swap(arr[i], arr[i+1]);
                isSorted = false;
            }
        }

        for (int i=0; i<=N-2; i=i+2)
        {
            if (arr[i] > arr[i+1])
            {
                swap(arr[i], arr[i+1]);
                isSorted = false;
            }
        }
        printArray(start, end - 1);
    }

    return;
}

template <class T>
void Sorting<T>::selectionSort(T *start, T *end)
{
    int n = end - start;
    T *arr = start;
    int i, j, min_idx;
    for (i = 0; i < n-1; i++)
    {
        min_idx = i;
        for (j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        if(min_idx!=i)
            swap(arr[min_idx], arr[i]);

        printArray(start, end);
    }
}

bool isPermutation (string a, string b) {
    if (a.size() != b.size()) return 0;
    if (a == b) return 1;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

int maximumProduct(vector<int>& nums) {
    int n = nums.size();
    if (n == 3) return nums[n - 1] * nums[n - 2] * nums[n - 3];
    sort(nums.begin(), nums.end());
    return max(nums[n - 1] * nums[n - 2] * nums[n - 3], nums[0] * nums[1] * nums[n - 1]);
}

//Helping functions goes here
int flag(int n, int m,vector<int> A, vector<int> B){
    vector<int> contain(256);
    for (int i : A) contain[i]++;
    for (int i : B) contain[i]++;

    sort(contain.begin(), contain.end(), greater<int>());

    int count = 0, num = 0;
    for (int i = 0; i < 256 && contain[i] != 0; i++) {
        if (num + contain[i] <= n) {
            num += contain[i];
            count++;
        }
    }
    return count;
}

int maxNumberOfPeople(vector<int>& rooms, vector<int>& people, int k) {
    sort(rooms.begin(), rooms.end());
    sort(people.begin(), people.end());
    size_t count = 0;
    size_t r = 0;
    for (size_t p = 0; p < people.size() && r < rooms.size(); p++) {
        while (r < rooms.size() && people[p] - k > rooms[r]) r++;
        if (rooms[r] <= people[p] + k) count++, r++;
    }
    return count;
}

class BTNode {
public:
    int val;
    BTNode *left;
    BTNode *right;
    BTNode() {
        this->left = this->right = NULL;
    }
    BTNode(int val) {
        this->val = val;
        this->left = this->right = NULL;
    }
    BTNode(int val, BTNode*& left, BTNode*& right) {
        this->val = val;
        this->left = left;
        this->right = right;
    }
};

int isP(BTNode *root) {
    if (root->left && root->right && ((root->left->val + root->right->val) % 2 == 1))
        return 1;
    return 0;
}

void transform(BTNode *root) {
    if (!root) return;
    if (root->left) {
        transform(root->left);
        root->val += root->left->val;
    }
    if (root->right) {
        transform(root->right);
        root->val += root->right->val;
    }

}

int distinctP(BTNode* root) {
    if (!root) return 0;
    return isP(root) + distinctP(root->left) + distinctP(root->right);
}

int distinctParities(BTNode* root) {
    transform(root);
    return distinctP(root);

}

int greatAncestor(BTNode* root) {
    if (!root) return 0;
    int count = greatAncestor(root->left) + greatAncestor(root->right);
    if (root->val >= (root->left ? root->left->val : 0) && root->val >= (root->right ? root->right->val : 0))
        count+=1;
    root->val = max((max(root->val, (root->left ? root->left->val : 0))), (root->right ? root->right->val : 0));
    return count;
}

// UNSOLVED
int longestPathSum(BTNode* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return root->val;

    if (!root->left) {
        int res = root->val;
        res += longestPathSum(root->right);
        root->val = 1 + root->right->val;
        return res;
    }

    if (!root->right) {
        int res = root->val;
        res += longestPathSum(root->left);
        root->val = 1 + root->left->val;
        return res;
    }

    int res = root->val;
    int l = longestPathSum(root->left), r = longestPathSum(root->right);
    if (root->left->val > root->right->val) res += l;
    else if (root->right > root->left) res += r;
    else res += max(l, r);
    root->val = 1 + max(root->left->val, root->right->val);
    return res;
}

int main() {
    return 0;
}
