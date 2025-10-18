#include <vector>
#include <unordered_map>

using namespace std;


class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> m;
        int LHS = 0;
        for (const auto& num: nums) {
            m[num]++;
        }
        
        for (const auto& [key, amt]: m) {
            if (m.count(key - 1)) {
                LHS = max(LHS, amt + m[key - 1]);
            }
        }
        return LHS;
    }
};