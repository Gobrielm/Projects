#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {

public:
    int triangleNumber(vector<int>& nums) {
        if (nums.size() < 3) return 0;
        // a + b < c, b + c < a, c + a < b, if sorted, a < b, and b < c
        /*
            Chooses 1 side to start, finds a range where nums[l] is the smallest leg possible, and nums[r] is the biggest possible
            Treats nums[r] as 2nd iterator-ish
        
        */


        sort(nums.begin(), nums.end());
        const auto& n = nums.size();
        int count = 0;
        for (int i = (n - 1); i >= 2; i--) {
            int l = 0, r = i - 1;

            while (l != r) {
                if (nums[l] + nums[r] > nums[i]) {
                    count += (r - l);
                    r--;
                } else {
                    l++;
                }
            }
        }
        return count;
    }
};