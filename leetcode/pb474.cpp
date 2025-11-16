#include <vector>
#include <string>
#include <set>
#include <iostream>

using namespace std;


class Solution {
    public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<vector<int>>> dp(strs.size() + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, 0))); // dp(i, m, n) = number picked
        vector<pair<int, int>> counts;

        for (const auto& s: strs) {
            pair<int, int> count = {0, 0};
            for (const auto& c: s) {
                if (c == '0') {
                    count.first++;
                } else {
                    count.second++;
                }
            }
            counts.push_back(count);
        }



        for (int i = 1; i <= strs.size(); i++) {
            for (int j = 0; j <= m; j++) {
                for (int k = 0; k <= n; k++) {
                    if (j - counts[i - 1].first >= 0 && k - counts[i - 1].second >= 0) {
                        dp[i][j][k] = max(dp[i - 1][j][k], 1 + dp[i - 1][j - counts[i - 1].first][k - counts[i - 1].second]);
                    } else {
                        dp[i][j][k] = dp[i - 1][j][k];
                    }
                }
            }
        }

        return dp[strs.size()][m][n];
    }
};

int main() {
    Solution sol;
    vector<string> v = {"10","0001","111001","1","0"};
    sol.findMaxForm(v, 5, 3);
}