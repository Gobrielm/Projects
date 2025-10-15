#include <vector>

using namespace std;

class Solution {
public:
    int maxIncreasingSubarrays(vector<int>& nums) {
        if (nums.size() == 2) return 1;
        int maxK = 0;

        int count = 0;
        int prevLength = 0;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i - 1]) {
                if (count == 0) count = 1;
                count++;
            } else {
                if (count == 0) count = 1;
                maxK = max(maxK, count / 2);
                maxK = max(maxK, min(count, prevLength));
                prevLength = count;
                count = 0;
            }
        }

        maxK = max(maxK, count / 2);
        maxK = max(maxK, min(count, prevLength));

        return maxK;
    }
};