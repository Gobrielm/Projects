#include <vector>
#include <list>
#include <unordered_map>

const int MOD = 1e9 + 7;

using namespace std;

class Solution {
    public:
    int specialTriplets(vector<int>& nums) {
        int n = nums.size();
        int total = 0;
        unordered_map<int, int> counts;
        unordered_map<int, int> countsInc;
        for (const int& num: nums) {
            counts[num]++;
        }

        for (int i = 0; i < n; i++) {
            const int& num = nums[i];
            int target = num * 2;

            int leftCount = countsInc[target];
            countsInc[num]++;
            
            long long rightCount = counts[target] - countsInc[target];
            total = (total + (leftCount * rightCount % MOD)) % MOD;
            
        }
        return total;
    }
};

int main() {
    Solution sol;
    vector<int> v = {0, 1, 0, 0};
    sol.specialTriplets(v);
}