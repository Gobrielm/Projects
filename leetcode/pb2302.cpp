#include <vector>
#include <unordered_set>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

class Solution {

public:
    long long countSubarrays(vector<int>& nums, long long k /* 1 - indexed*/) {
        const int n = nums.size();
        ll count = 0;
        ll total = 0;
        for (int i = 0, j = 0; j < n; j++) {
            total += nums[j];
            while (i <= j && total * (j - i + 1) >= k) {
                total -= nums[i];
                i++;
            }
            count += j - i + 1;
        }
        

        return count;
    }
};

int main() {
    Solution sol;
    vector<int> v = {1,1,1};
    sol.countSubarrays(v, 5);
}