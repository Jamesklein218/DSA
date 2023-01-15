#include "main.h"

using namespace std;
class Solution {
public:
    static vector<int> getOrder(vector<vector<int>>& tasks) {
        for (int i = 0; i < tasks.size(); i++) tasks[i].push_back(i);

        auto sort_cmp = [](const vector<int> &a, const vector<int> &b) {
            return a[0] < b[0];
        };
        auto pq_cmp = [](const vector<int> &a, const vector<int> &b) {
            return a[1] > b[1];
        };

        vector<int> res;

        sort(tasks.begin(), tasks.end(), sort_cmp);

        priority_queue<vector<int>, vector<vector<int> >, decltype(pq_cmp)> pq ( pq_cmp);

        int p = 0;
        int time = 0;

        while (p < tasks.size() || !pq.empty()) {
            while (p < tasks.size() && tasks[p][0] <= time) {
                pq.push(tasks[p++]);
            }
            if (pq.empty()) time++;
            else {
                vector<int> todo = pq.top();
                pq.pop();
                time += todo[1];
                res.push_back(todo[2]);
            }
        }
        return res;
    }
};
int main() {
    vector<vector<int> > input{
            {7, 10},
            {7, 12},
            {7, 4},
            {7, 5},
            {7, 2}
    };
    vector<int> res = Solution::getOrder(input);
    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << " ";
    }
    return 0;
}