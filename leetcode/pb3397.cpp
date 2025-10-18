#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());

        int biggestElement = nums[0] - k;
        int uniqueNums = 1;
        int newNum = 0;
        for (int i = 1; i < nums.size(); i++) {
            newNum = nums[i] - k;
            if (newNum <= biggestElement) {
                newNum = biggestElement + 1;
                if (newNum > nums[i] + k) continue;
            }

            uniqueNums++;
            biggestElement = newNum;
        }

        return uniqueNums;
    }
};