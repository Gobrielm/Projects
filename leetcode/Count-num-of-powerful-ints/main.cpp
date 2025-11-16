#include <string>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
using ll = long long;

class Solution {
public:

    ll find_num_of_pow_nums_partial(int index, int tight, string &numStr, string& suffix, int limit, int numLength, std::vector<std::vector<ll>>& dp) {
        if (index == numLength) return 1;
        if (dp[index][tight] != -1) return dp[index][tight];

        ll count = 0;
        int lower_bound = 0;
        int upper_bound = tight ? min(limit, numStr[index] - '0'): limit;

        int suffixStartIndex = numLength - suffix.size();
        if (suffixStartIndex <= index) {
            lower_bound = suffix[index - suffixStartIndex] - '0';
            upper_bound = min(upper_bound, lower_bound);
        }

        for (int i = lower_bound; i <= upper_bound; i++) {
            count += find_num_of_pow_nums_partial(index + 1, tight && (i == numStr[index] - '0'), numStr, suffix, limit, numLength, dp);
        }
        dp[index][tight] = count;
        return count;
    }


    ll numberOfPowerfulInt(ll start, ll finish, int limit, string s) {
        string upperLimit = to_string(finish);
        string lowerLimit = to_string(start - 1);
        int upperLength = upperLimit.size(); int lowerLength = lowerLimit.size();

        ll upperCount = 0, lowerCount = 0;
        vector<vector<ll>> dp(17, vector<ll>(2, -1));

        if (s.size() <= upperLength) {
            upperCount = find_num_of_pow_nums_partial(0, 1, upperLimit, s, limit, upperLength, dp);
        }

        dp.assign(17, vector<ll>(2, -1));

        if (s.size() <= lowerLength) {
            lowerCount = find_num_of_pow_nums_partial(0, 1, lowerLimit, s, limit, lowerLength, dp);
        }

        return upperCount - lowerCount;
    }
    
};