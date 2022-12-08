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

        swap(maxHeap[index], maxHeap[leftIndex]);

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

// Exercise 4: 0.9/1
template<class T>
void Heap<T>::remove(T item) {
    int index = getItem(item);
    if (index == -1) return;
    swap(elements[index], elements[count - 1]);
    count--;
    for (int i = count / 2 - 1; i >= 0; i--)
        reheapDown(i);

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

/*
 * HASH AND SEARCH
 */

// Exercise 1: Author: Khang Phung
int foldShift(long long key, int addressSize)
{
    int sum = 0;
    string Skey = std::to_string(key);
    int size = Skey.size();
    for (int i = 0; i < size; i += addressSize)
    {
        string s = Skey.substr(i, addressSize);
        sum += std::stoi(s);
    }
    int modulo = pow(10, addressSize);
    return sum % modulo;
}

int rotation(long long key, int addressSize)
{
    string s = std::to_string(key);
    string last = s.substr(s.size() - 1);
    s.pop_back();
    s = last + s;
    int mod = pow(10, addressSize);
    return foldShift(std::stoll(s), addressSize) % mod;
}
// Exercise 2
long int midSquare(long int seed)
{
    long int square = seed * seed;
    long int res = 0;
    square /= 10;
    square /= 10;
    res += (square % 10);
    square /= 10;
    res += (square % 10) * 10;
    square /= 10;
    res += (square % 10) * 100;
    square /= 10;
    res += (square % 10) * 1000;
    square /= 10;
    return res;
}
long int moduloDivision(long int seed, long int mod)
{
    return seed % mod;
}
long int digitExtraction(long int seed,int* extractDigits,int size)
{
    string seedstr = to_string(seed);
    long int res = 0;
    for (int i = 0; i < size; i++) {
        res *= 10;
        res += (long int)(seedstr[extractDigits[i]] - '0');
    }

    return res;
}
// Exercise 3
int pairMatching(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int l = 0, r = nums.size() - 1;
    int count = 0;
    while (l < r) {
        if (nums[l] + nums[r] < target)
            l++;
        else if (nums[l] + nums[r] > target)
            r--;
        else {
            count++;
            l++;
            r--;
        }
    }
    return count;
}

// Exercise 4
// Recursive
int binarySearchRec(int arr[], int left, int right, int x) {
    if (left > right) return -1;
    int mid = (left + right) / 2;

    cout << "We traverse on index: " << mid << endl;
    if (arr[mid] == x)
        return mid;
    else if (x < arr[mid])
        return binarySearchRec(arr, left, mid - 1, x);
    return binarySearchRec(arr, mid + 1, right, x);
}
// Iterative
int binarySearch(int arr[], int left, int right, int x) {
    while (left <= right) {
        int mid = (left + right) / 2;
        cout << "We traverse on index: " << mid << endl;
        if (arr[mid] == x)
            return mid;
        else if (x < arr[mid])
            right = mid - 1;
        left = mid + 1;
    }
    return -1;
}

// Exercise 5
bool findPairs(int arr[], int n, pair<int,int>& pair1, pair<int, int>& pair2)
{
    map<int, pair<int, int> > m;
    for (int i= 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (m.find(arr[i] + arr[j]) != m.end()) {
                pair1 = m[arr[i] + arr[j]];
                pair2 = pair<int, int>(arr[i], arr[j]);
                return true;
            } else
                m.insert(pair<int, pair<int, int> >(arr[i] + arr[j], pair<int, int> (arr[i], arr[j])));
        }
    }
    return false;
}

// Exercise 6
int interpolationSearch(int arr[], int left, int right, int x)
{
    if (left > right || x < arr[left] || x > arr[right]) return -1;
    int pos = left + (((double) (right - left) / (arr[right] - arr[left])) * (x - arr[left]));

    cout << "We traverse on index: " << pos << endl;
    if (arr[pos] == x)
        return pos;
    else if (x < arr[pos])
        return interpolationSearch(arr, left, pos - 1, x);
    return interpolationSearch(arr, pos + 1, right, x);
}

int main() {
    int arr[] = { 1,2,3,4,5,6,7,8,9 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 0;
    int result = interpolationSearch(arr, 0, n - 1, x);
    (result == -1) ? cout << "Element is not present in array"
                   : cout << "Element is present at index " << result;

    return 0;
}