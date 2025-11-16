#include <vector>
#include <unordered_set>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {

public:

    int countMaxOrSubsets(vector<int>& nums) {
        int n = nums.size();
        int max = 0;
        for (const auto& num: nums) {
            int temp = max | num;
            if (temp != max) {
                max = temp;
            }
        }
        int count = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            int temp_max = 0;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {  // check if element i is included
                    temp_max = temp_max | nums[i];
                }
            }
            if (temp_max == max) {
                count++;
            }
        }
        return count;
    }
};

int main() {
    vector<int> v = {3,1};
    Solution sol;
    sol.countMaxOrSubsets(v);
}