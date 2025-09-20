#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    struct Vector2Hash {
        bool operator()(const vector<int>& v1, const vector<int>& v2) const {
            if (v1[2] == v2[2]) return v1[0] < v2[0];
            return v1[2] < v2[2];
        }
    };

    int countValidPairs(int threshold, vector<int>& nums) {
        int count = 0;
        for (int i = 0; i < nums.size() - 1;) {
            if (nums[i + 1] - nums[i] <= threshold) {
                count++;
                i += 2;
            } else {
                i++;
            }
        }
        return count;
    }

    int minimizeMax(vector<int>& nums, int p) {
        if (p == 0) return 0;
        sort(nums.begin(), nums.end()); // Smallest first
        
        int left = 0; // Smallest Threshold
        int right = nums[nums.size() - 1] - nums[0]; // largest Threshold
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            int pairs = countValidPairs(mid, nums);

            if (pairs >= p) {
                right = mid;
            } else {
                left = mid + 1;
            }
            
        }
        return left;
    }
};

int main() {
    Solution sol;
    vector<int> v = {2,2,4,5,5,6,8};
    cout << sol.minimizeMax(v, 3);
}