#include <vector>
#include <algorithm>

using namespace std;

class Solution {

public:
    int largestPerimeter(vector<int>& nums) {
        sort(nums.begin(), nums.end(), std::less<int>()); // Ascending

        // Tranverse backwards to find biggest triangle first
        for (int i = nums.size() - 3; i >= 0; i--) {
            const auto& s1 = nums[i];
            const auto& s2 = nums[i + 1];
            const auto& s3 = nums[i + 2];
            
            // (s1 + s2) > s3 is not given
            // (s2 + s3) > s1 is given
            // (s1 + s3) > s2 is given
            
            if ((s1 + s2) > s3) {
                return s1 + s2 + s3;
            }
        }
        return 0;
    }
};