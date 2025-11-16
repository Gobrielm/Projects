#include <vector>

using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, 0); // dp = the number of coins used when you have k amount left
        
        for (int i = 1; i <= amount; i++) {
            int smallestCoinsUsed = __INT_MAX__;
            for (int j = 0; j < coins.size(); j++) {
                if (i - coins[j] >= 0 && dp[i - coins[j]] != __INT_MAX__) {
                    smallestCoinsUsed = min(smallestCoinsUsed, dp[i - coins[j]] + 1);
                }
                
            }
            dp[i] = smallestCoinsUsed;
        }

        if (dp[amount] == __INT_MAX__) return -1;
        return dp[amount];
    }
};