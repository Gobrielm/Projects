#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
public:
    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
        sort(queries.begin(), queries.end());
        priority_queue<int> available; // Biggest first
        priority_queue<int, vector<int>, greater<int>> assigned; // Smallest on top
        int count = 0;

        for (int time = 0, k = 0; time < nums.size(); time++) {
            // First add greadily
            while (!assigned.empty() && assigned.top() < time) {
                assigned.pop();
            }
            while (k < queries.size() && queries[k][0] <= time) {
                available.push(queries[k++][1]);
            }
            while (assigned.size() < nums[time] && !available.empty() && available.top() >= time) {
                assigned.push(available.top()); 
                available.pop();
                count++;
            }



            if (assigned.size() < nums[time])
                return -1;
        }
        return queries.size() - count;
    }
};


int main() {
    vector<int> v = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
    vector<vector<int>> v2 = {{1, 9}, {1, 9}, {1, 9}, {0, 1}, {0, 1}, {0, 1}, {2, 10}, {2, 10}, {2, 10}};
    Solution sol;
    int num = sol.maxRemoval(v, v2);
    cout << num;
}