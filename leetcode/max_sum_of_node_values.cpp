#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;
using ll = long long;

class Solution {
public:
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        int n = nums.size();
        auto cmp = [] (const std::pair<int, ll>& p1, const std::pair<int, ll>& p2) { 
            if (p1.second == p2.second) return p1.first > p2.first;
            return p1.second > p2.second;
        };
        set<pair<int, ll>, decltype(cmp)> s(cmp);
        int smallest_xor_change = 0;
        int smallest_xor_index = -1;
        
        ll max = 0;
        int wants_to_be_xored = 0;
        for (int i = 0; i < n; i++) {
            ll temp_max = nums[i] ^ k;
            ll change = (nums[i] ^ k) - nums[i];
            if (change > 0) {
                wants_to_be_xored++;
                s.emplace(i, change);
            }

            if (change > 0) change *= -1;

            if (change > smallest_xor_change || smallest_xor_index == -1) {
                smallest_xor_change = change;
                smallest_xor_index = i;
            }
        }
        if (s.size() != 0 && wants_to_be_xored % 2 == 1) {
            ll change_on_odd_xor = next(s.end(), -1)->second + smallest_xor_change;
            if (change_on_odd_xor > 0) {
                max += smallest_xor_change;
            } else {
                s.erase(next(s.end(), -1));
            }
        }



        while (!s.empty()) {
            const auto& first = *s.begin();
            max += first.second;

            s.erase(s.begin());
        }
        for (int i = 0; i < n; i++) {
            max += nums[i];
        }
        
        return max;
    }

};
