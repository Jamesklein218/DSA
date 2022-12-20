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

#define INTMAX 1 << 31
#define INTMIN ~(1 << 31)

using namespace std;

// Exercise 2
long long nthNiceNumber(int n) {
    if (n == 1) return 2;
    if (n == 2) return 5;
    vector<int> sStack;
    sStack.push_back(2);
    long long res = 0;
    for (int i = 1; i < n; i++) {
        if (i % 2 == 0) {
            sStack[0] = 2;
            int j = 1;
            while (j < sStack.size() && sStack[j] != 2)
                sStack[j++] = 2;
            if (j < sStack.size())
                sStack[j] = 5;
            else
                sStack.push_back(2);

        } else
            sStack[0] = 5;
    }

    for (int i = sStack.size() - 1; i >= 0; i--)
        res = res * 10 + sStack[i];
    return res;
}

// Exercise 2 (queue)
int numberOfTheWinner(int N, int k) {
    if (N == 1) return 1;

    queue<int> m, tmp;
    for (int i = 0; i < N; i++)
        m.push(i + 1);

    int i = k - 1;
    while (m.size() != 1) {
        i = i % m.size();
        for (int j = 0; j < i ; j++) {
            tmp.push(m.front());
            m.pop();
        }
        m.pop();
        while (!m.empty()) {
            tmp.push(m.front());
            m.pop();
        }
        while (!tmp.empty()) {
            m.push(tmp.front());
            tmp.pop();
        }
        i += k - 1;
    }
    return m.front();
}

// Exercise 4 (sliding window)
int sumOfMaxSubarray(vector<int>& nums, int k) {
    int n = nums.size();
    int sum = 0;
    deque<int> deq(k);
    int m = nums[k - 1];
    for (int i = 0; i < k; i++) {
        while (!deq.empty() && nums[i] >= nums[deq.back()])
            deq.pop_back();
        deq.push_back(i);
    }
    for (int i = k; i < n; i++) {
        sum+=nums[deq.front()];
        while (!deq.empty() && deq.front() <= i - k)
            deq.pop_front();
        while (!deq.empty() && nums[i] >= nums[deq.back()])
            deq.pop_back();
        deq.push_back(i);
    }
    sum += nums[deq.front()];
    return sum;
}

int baseballScore(string ops){
    stack<int> sStack;
    int res = 0;
    for (int i = 0; ops[i] != '\0'; i++) {
        if (ops[i] == 'C') {
            sStack.pop();
        } else if (ops[i] == '+') {
            int x1 = sStack.top();
            sStack.pop();
            int toPush = x1 + sStack.top();
            sStack.push(x1);
            sStack.push(toPush);
        } else if (ops[i] == 'D') {
            sStack.push(sStack.top() * 2);
        } else {
            sStack.push(int(ops[i] - '0'));
        }
    }
    while (!sStack.empty()) {
        res += sStack.top();
        sStack.pop();
    }
    return res;
}

// Exercise 9
vector<int> nextGreater(vector<int>& arr){
    vector<int> idxs(arr.size());
    int i = arr.size() - 1;
    idxs[i--] = -1;
    for (;i >= 0; i--) {
        int greaterIdx = i + 1;
        while (greaterIdx != -1 && arr[greaterIdx] < arr[i]) {
            greaterIdx = idxs[greaterIdx];
        }
        idxs[i] = greaterIdx;
    }

    for (int i = 0; i < arr.size(); i++) {
        if (idxs[i] != -1) {
            idxs[i] = arr[idxs[i]];
        }
    }

    return idxs;
}


// Exercise 10
string parenthesesReversal(string s) {
    int n = s.size();
    stack<int> st;
    vector<int> pair(n);
    for (int i = 0; i < n; i++) {
        if (s[i] == ')') {
            pair[i] = st.top();
            pair[st.top()] = i;
            st.pop();
        }
        if (s[i] == '(') {
            st.push(i);
        }
    }
    string res = "";
    for (int i = 0, d = 1; i < n; i += d) {
        if (s[i] == '(' || s[i] == ')') {
            int start = pair[i];
            d = -d;
            i = start;
        } else {
            res += s[i];
        }
    }
    return res;
}

// Exercise 11
string removeDuplicates(string s){
    int n = s.size();
    stack<char> str, tmp;
    for (int i = 0; i < n; i++) {
        if (str.empty() || s[i] != str.top())
            str.push(s[i]);
        else {
            str.pop();
        }
    }
    string res = "";
    while (!str.empty()) {
        res = str.top() + res;
        str.pop();
    }
    return res;
}

// Exercise 12
string deleteDuplicate(string s, int k) {
    if (k == 1) return "";
    int n = s.size();
    stack<char> key;
    stack<int> value;
    for (int i = 0; i < n; i++) {
        if (key.empty() || (key.top() != s[i])) {
            key.push(s[i]);
            value.push(1);
        } else if (key.top() == s[i]) {
            value.top()++;
            if (value.top() == k) {
                value.pop();
                key.pop();
            }
        }
    }
    string res = "";
    while (!key.empty()) {
        for (int i = 0; i < value.top(); i++)
            res = key.top() + res;
        key.pop();
        value.pop();
    }
    return res;
}

// Exercise 13: Dynamic Programming
template <typename  T>
T minimum(const T &a, const T &b) {
    return a > b ? b : a;
}
int sumOfMinSubarray(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    if (n == 2) return min(nums[0], nums[1]) + nums[0] + nums[1];
    vector<int> idxes(n), dp(n);
    stack<int> st;
    idxes[n - 1] = n - 1;
    st.push(n - 1);
    for (int i = n - 2; i >= 0; i--) {
        if (nums[i] > nums[i + 1]) {
            idxes[i] = i + 1;
        } else {
            while (!st.empty() && nums[i] <= nums[st.top()])
                st.pop();
            if (st.empty())
                idxes[i] = i;
            else
                idxes[i] = st.top();
        }
        st.push(idxes[i]);
    }

    for (int i = n - 1; i >= 0; i--) {
        if (idxes[i] == i)
            dp[i] = nums[i] * (n - i);
        else
            dp[i] = nums[i] * (idxes[i] - i) + dp[idxes[i]];
    }

    for (int i = 1; i < n; i++)
        dp[i] += dp[i - 1] % 10000;
    return dp[n - 1] % 10000;
}

// Exercise 14
bool tripleIndexSLM(vector<int>& nums) {
    int n = nums.size();
    if (n < 3) return false;

    vector<int> slm(2, (1 << 31));
    slm[0] = nums[0];
    for (int i = 0; i < n; i++) {
        if (nums[i] < slm[0])
            slm[0] = nums[i];
        else if (nums[i] > slm[1])
            slm[1] = nums[i];
        else if (slm[0] < nums[i] && nums[i] < slm[1]) {
            return true;
        }
    }
    return false;
}

// Exercise 15
bool isValidParentheses (string s){
    int n = s.size();
    stack<char> st;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{')
            st.push(s[i]);
        else if (s[i] == ')') {
            if (!st.empty() && st.top() == '(') st.pop();
            else return false;
        } else if (s[i] == ']') {
            if (!st.empty() && st.top() == '[') st.pop();
            else return false;
        } else if (s[i] == '}')
            if (!st.empty() && st.top() == '{') st.pop();
            else return false;
    }
    if (!st.empty()) return false;
    return true;
}

// Exercise 5 Author: Duy Minh, Reference: https://www.geeksforgeeks.org/koko-eating-bananas/
int chk(vector<int> A, int n) {
    long long int res = 0;
    for(int i=0;(size_t)i<A.size();i++) {
        int a = A[i]/n;
        double b = (double)A[i]/n;
        if(a==b) res+=a;
        else res+=a+1;
    }
    return res;
}
int boxRequire(vector<int>& A, int K) {
    int start = 1;
    int end = A[0];
    for(int i=0;(size_t)i<A.size();i++) {
        if(A[i] >= end) {
            end = A[i];
        }
    }

    while (start < end) {
        int mid = start + (end - start) / 2;
        if (chk(A, mid) <= K) {
            end = mid;
        }
        else {
            start = mid + 1;
        }
    }
    return end;
}

// Exercise 8: Not correct
bool isMaxPoint(vector<int> &nums, int idx) { // O(1)
    if ((idx == 0 && nums[idx] > nums[idx + 1])
        || ((idx == (int)nums.size() - 1) && (nums[idx] > nums[idx - 1])))
        return true;
    if (((nums[idx - 1] < nums[idx]) && (nums[idx] >= nums[idx + 1]))
        || ((nums[idx - 1] <= nums[idx]) && (nums[idx] > nums[idx + 1])))
        return true;
    return false;
}
bool isMinPoint(vector<int> &nums, int idx) { // O(1)
    if ((idx == 0 && nums[idx] < nums[idx + 1])
        || ((idx == (int)nums.size() - 1) && (nums[idx] < nums[idx - 1])))
        return true;
    if ((nums[idx - 1] >= (int)nums[idx] && nums[idx] < nums[idx + 1])
        || ((nums[idx - 1] > nums[idx]) && (nums[idx] <= nums[idx + 1])))
        return true;
    return false;
}
int mountainWithoutValley(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];
    if (n == 2) return nums[0] + nums[1];
    vector<int> prevMin(n), dpL(n), dpR(n);
    int currMinValIdx = 0;
    dpL[0] = nums[0], dpR[n - 1] = nums[n - 1], prevMin[0] = 0;
    for (int i = 1; i < n; i++) {
        if (isMinPoint(nums, i)) {
            prevMin[i] = currMinValIdx;
            while (nums[i] < nums[currMinValIdx] && currMinValIdx != prevMin[currMinValIdx])
                currMinValIdx = prevMin[currMinValIdx];

            dpL[i] = (i - currMinValIdx) * nums[i] + (currMinValIdx ? dpL[currMinValIdx] : nums[i]);

            currMinValIdx = i;
        } else
            dpL[i] = dpL[i - 1] + nums[i];
    }

    prevMin.clear();
    currMinValIdx = n - 1, prevMin[n - 1] = n - 1;
    for (int i = n - 2; i >= 0; i--) {
        if (isMinPoint(nums, i)) {
            prevMin[i] = currMinValIdx;
            while (nums[i] < nums[currMinValIdx] && currMinValIdx != prevMin[currMinValIdx])
                currMinValIdx = prevMin[currMinValIdx];
            dpR[i] = (currMinValIdx - i) * nums[i] + (currMinValIdx != n - 1 ? dpR[currMinValIdx] : nums[i]);
            currMinValIdx = i;
        } else
            dpR[i] = dpR[i + 1] + nums[i];
    }

    int res = (1 << 31);
    for (int i = 0; i < n; i++) {
        if (isMaxPoint(nums, i)) {
            int climax = nums[i];
            if (i > 0)
                climax += dpL[i - 1];
            if (i < n - 1)
                climax += dpR[i + 1];
            res = climax > res ? climax : res;
        }
    }

    return res;
}

int main() {



    vector<int> nums {5, 3, 9, 10, 8, 4, 10, 4, 6, 3, 7};
    cout << mountainWithoutValley(nums);

//    vector<int> nums {1891, 4518, 1065, 4265, 2554, 2400, 1740, 943, 4162, 2251, 3287, 2706, 2331, 3642, 824, 1233, 795, 1073, 4582, 917};
//    cout << mountainWithoutValley(nums);

    return 0;
}