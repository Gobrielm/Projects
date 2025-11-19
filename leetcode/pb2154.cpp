#include <vector>
#include <algorithm>

using namespace std;


class Solution {
    public:
    int findFinalValue(vector<int>& nums, int original) {
        sort(nums.begin(), nums.end());

        while(true) {
            auto pt = lower_bound(nums.begin(), nums.end(), original);
            if (pt == nums.end()) pt--;
            if (*pt != original) return original;

            original *= 2;
        }
    }
};