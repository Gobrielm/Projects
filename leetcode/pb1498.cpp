#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {


public:
    int numSubseq(vector<int>& nums, int target) {
        int mod = 1000000007 , n = nums.size();
        sort(nums.begin(), nums.end(), std::less<int>());
        int left = 0, right = nums.size() - 1;
        long count = 0;
        
        int power[n];
        power[0] = 1;
        for (int i = 1; i < n; i++) {
            power[i] = (power[i - 1] * 2) % mod;
        }

        while (left <= right) {
            if (nums[left] + nums[right] > target) {
                right--;
                continue;
            } else {
                count = (count + power[right - left]) % mod;
                left++;
            }
        }

        return count;
    }
};
