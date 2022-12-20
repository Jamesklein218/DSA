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

using namespace std;

string maxNumberFromArr(vector<int> arr) {
    vector<string> s;
    for (int i= 0; i < arr.size(); i++)
        s.push_back(to_string(arr[i]));
    sort(s.begin(), s.end(), greater<string>());
    string res = "";
    for (string str : s)
        res += str;
    return res;
}

string refactorCode(string s) {
    stack<int> stk;
    string tmp;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
            if (tmp == "cse") {
                stk.push(0);
                s[i] = '<';
            } else {
                if (s.empty())
                    return s;
                int val = stk.top() + 1;
                stk.pop();
                if (val < 3) {
                    stk.push(val);
                    s[i] = ',';
                } else {
                    s[i] = '>';
                }
            }

            tmp = "";
        } else tmp += s[i];
    }

    return s;
}

void printHailstone(int number){

    if (number == 1) {
        cout << number;
        return;
    }
    cout << number << " ";
    if (number % 2 == 0)
        printHailstone(number /= 2);
    else
        printHailstone(number * 3 + 1);
}

class Node {
    int data;
    Node* next;
public:
    Node(): data(0), next(nullptr){}
    Node(int data, Node* next)
    {
        this->data = data;
        this->next = next;
    }
    int getData()
    {
        return this->data;
    }
    void setData(int data)
    {
        this->data = data;
    }
    Node* getNext()
    {
        return this->next;
    }
    void setNext(Node* next)
    {
        this->next = next;
    }
};

void reduceDuplicate(Node*& root) {
    if (!root || !root->getNext()) return;
    Node *newRoot = new Node(root->getData(), nullptr);
    Node *p = newRoot;
    root = root->getNext();
    while (root && root->getNext()) {
        while (root->getNext() && root->getData() == root->getNext()->getData()) {
            root = root->getNext();
        }
        p->setNext(new Node(root->getData(), nullptr));
        p = p->getNext();
        root = root->getNext();
    }

    if (root) p->setNext(new Node(root->getData(), nullptr));
    root = newRoot;
}
void printList(Node *p) {
    Node *tmp = p;
    while (tmp) {
        cout << tmp->getData() << " ";
        tmp = tmp->getNext();
    }
}

void sortString(string& s) {
    int n = (int)s.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = minIdx; j < n; j++) {
            if (s[j] < s[minIdx])
                minIdx = j;
        }
        if (minIdx != i)
            swap(s[i], s[minIdx]);
    }
}

bool isPermutation(string a, string b) {
    if (a.size() != b.size()) return false;
    if (a.size() == 0) return true;
    sortString(a);
    sortString(b);
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

string parenthesesReversal(string s) {
    return "";
}

class BSTNode { public:
    int val; BSTNode *left; BSTNode *right; BSTNode() {
        this->left = this->right = nullptr; }
    BSTNode(int val) { this->val = val;
        this->left = this->right = nullptr; }
    BSTNode(int val, BSTNode*& left, BSTNode*& right) { this->val = val;
        this->left = left;
        this->right = right; }
};

int reduceSum(vector<int>& nums) {
    make_heap(nums.begin(), nums.end(), greater<int>());
    int cost = 0;
    while (nums.size() > 1) {
        int sum = nums[0];
        pop_heap(nums.begin(), nums.end(), greater<int>());
        nums.pop_back();
        sum += nums[0];
        pop_heap(nums.begin(), nums.end(), greater<int>());
        nums.pop_back();
        nums.push_back(sum);
        cost += sum;
    }
    return cost;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    return 0;
}