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

#include "Heap.h"
#include "Sorting.h"

using namespace std;
template<class T>
void Heap<T>::reheapDown(int position) {
    int left = (position << 1) + 1;
    while (left < count) {
        if (left + 1 < count && elements[left] < elements[left + 1])
            left++;
        if (elements[left] > elements[position]) return;

        T temp(std::move(elements[position]));
        elements[position] = std::move(elements[left]);
        elements[left] = std::move(temp);

        position = left;
        left = (position << 1) + 1;
    }
}

// Exercise 1
template<class T>
int Heap<T>::size(){
    return count;
}

template<class T>
bool Heap<T>::isEmpty(){
    return count == 0;
}

template<class T>
T Heap<T>::peek(){
    if (count <= 0) return (T)-1;
    return elements[0];
}

template<class T>
bool Heap<T>::contains(T item){
    for (int i = 0; i < count; i++)
        if (elements[i] == item)
            return true;

    return false;
}

template<class T>
bool Heap<T>::pop(){
    if (count <= 0) return false;

    // Swap
    T temp(std::move(elements[0]));
    elements[0] = std::move(elements[count - 1]);
    elements[count - 1] = std::move(temp);

    count--;

    reheapDown(0);

    return true;
}

// Exercise 2
template<class T>
void Heap<T>::push(T item){
    count++;
    ensureCapacity(count);
    elements[count - 1] = item;
    reheapUp(count - 1);
}

template<class T>
void Heap<T>::ensureCapacity(int minCapacity){
    int newCap = (minCapacity + 10 - 1) / 10 * 10;
    if (newCap > capacity) {
        T *newElements = new T[newCap];
        for (int i = 0; i < count; ++i)
            newElements[i] = std::move(elements[i]);
        if (elements) delete[] elements;
        elements = newElements;
        capacity = newCap;
    }
}

template<class T>
void Heap<T>::reheapUp(int position){
    while (position > 0 && position < count) {
        int index = (position - 1) >> 1;
        if (elements[index] > elements[position]) return;

        T temp(std::move(elements[position]));
        elements[position] = std::move(elements[index]);
        elements[index] = std::move(temp);

        position = index;
    }
}

// Exercise 3
void reheapDown(int maxHeap[], int numberOfElements, int index) {
    int leftIndex = (index << 1) + 1;
    while (leftIndex < numberOfElements) {
        if (leftIndex + 1 < numberOfElements && maxHeap[leftIndex] < maxHeap[leftIndex + 1])
            leftIndex++;
        if (maxHeap[index] > maxHeap[leftIndex]) break;

        std::swap(maxHeap[index], maxHeap[leftIndex]);

        index = leftIndex;
        leftIndex = (index << 1) + 1;
    }
}

void reheapUp(int maxHeap[], int numberOfElements, int index) {
    while (index > 0 && index < numberOfElements) {
        int newIndex = (index - 1) >> 1;
        if (maxHeap[newIndex] > maxHeap[index]) return;

        std::swap(maxHeap[index], maxHeap[newIndex]);

        index = newIndex;
    }
}

// Exercise 4: 0.9/10
template<class T>
void Heap<T>::remove(T item) {
    int index = getItem(item);
    if (index == -1) return;
    swap(elements[index], elements[count - 1]);
    count--;
    reheapDown(index);
    reheapUp(index);
}

template<class T>
int Heap<T>::getItem(T item) {
    for (int i = 0; i < count; i++)
        if (elements[i] == item)
            return i;
    return -1;
}

template<class T>
void Heap<T>::clear() {
    count = 0;
    capacity = 10;
}

// Exercise 6: From hackerrank
int minWaitingTime(int n, int arrvalTime[], int completeTime[]) {
    vector<pair<int, int> > v(n);

    for (int i = 0; i < n; i++)
        v[i] = pair<int, int>(arrvalTime[i], completeTime[i]);

    sort(v.begin(), v.end());
    int sum = 0;
    set<pair<int, int> > q;
    int t = v[0].first;
    int it = 0;
    while (it < n || q.size()) {
        while (it < n && v[it].first <= t) {
            q.insert(pair<int, int>(v[it].second, it));
            ++it;
        }
        if (q.empty()) {
            t = v[it].first;
        } else {
            int i = q.begin()->second;
            q.erase(q.begin());
            t += v[i].second;
            sum += t-v[i].first;
        }
    }

    return sum;
}

// Exercise 7
class PrinterQueue
{
    map<int, queue<string> > m;
    priority_queue<int> p;
public:
    // your methods

    void addNewRequest(int priority, string fileName)
    {
        if (m.find(priority) == m.end()) {
            queue<string> q;
            q.push(fileName);
            m.insert(pair<int, queue<string> >(priority, q));
        } else {
            m[priority].push(fileName);
        }
        p.push(priority);
    }

    void print()
    {
        if (p.empty()) {
            cout << "No file to print" << endl;
            return;
        }
        int out = p.top();
        p.pop();
        map<int, queue<string> >::iterator it = m.find(out);
        if (it == m.end() || it->second.empty())
            cout << "No file to print" << endl;
        else {
            cout << it->second.front() << endl;
            it->second.pop();
        }
    }
};

// Exercise 8
int reduceSum(vector<int>& nums) {
    if (nums.size() <= 1) return 0;
    priority_queue <int, vector<int>, greater<int> > pq(nums.begin(), nums.end());

    int sum = 0;
    while (pq.size() > 1) {
        int currSum = 0;
        currSum += pq.top();
        pq.pop();
        currSum += pq.top();
        pq.pop();
        pq.push(currSum);
        sum += currSum;
    }
    return sum;
}

// Exercise 9
int leastAfter(vector<int>& nums, int k) {
    if (nums.size() == 0) return 0;
    priority_queue <int, vector<int>, greater<int> > pq(nums.begin(), nums.end());

    for (int i = 0; i < k; i++) {
        int out = pq.top();
        pq.pop();
        pq.push(out * 2);
    }

    return pq.top();
}

// Exercise 10: O(kN)
int uglyNumberIndex(int n) {
    vector<int> primes {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};

    priority_queue<int, vector<int>, greater<int> > p;
    for (int i : primes) p.push(i);
    int res = 1;
    for (int i = 0; i < n;) {
        res = p.top();
        p.pop();
        if (res != p.top()) {
            i++;
            for (int j = 0; j < primes.size(); ++j)
                p.push(primes[j] * res);
        }
    }
    return res;
}

// Leetcode: O(log(k)N)
struct triple{
    int val;
    int prime;
    int p;
    triple(int x, int y, int z):val(x), prime(y), p(z){};
};
int nthSuperUglyNumber(int n, vector<int>& primes) {
    vector<int>dp(n);
    dp[0] = 1;
    auto cmp = [](triple* t1, triple* t2){ return t1->val > t2->val; };
    priority_queue<triple*, vector<triple*>, decltype(cmp)>pq(cmp);
    for(int i = 0; i < primes.size(); i++) pq.push(new triple(primes[i], primes[i], 1));
    for(int i = 1; i < n; i++){
        dp[i] = pq.top()->val;
        while(pq.top()->val == dp[i]){
            triple* t = pq.top();
            pq.pop();
            pq.push(new triple(t->prime * dp[t->p], t->prime, t->p + 1));
        }
    }
    return dp[n - 1];
}


int main() {
    int n = 5000;
    cout << uglyNumberIndex(n);

    return 0;
}