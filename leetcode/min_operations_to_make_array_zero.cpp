#include <vector>
#include <cmath>

using namespace std;
using ll = long long;

class Solution {

public:

    ll minOperations(ll x) {
        if (x == 0) return 0;
        ll total = 0, base = 1, depth = 1;
        while (base <= x) {
            ll amount = min(base * 4 - 1, x) - base + 1; // Number in range [4^k, 4^(k+1) - 1], each has depth k+1
            total += amount * depth; // Step is the current depth starting at 1
            depth++;
            base*= 4;
        }
        return total;
    }

    ll minOperations(vector<vector<int>>& queries) {
        ll total = 0;
        for (auto& q: queries) {
            int l = q[0], r = q[1];
            total += (minOperations(r) - minOperations(l - 1) + 1) / 2.0;
        }
        return total;
    }
};
