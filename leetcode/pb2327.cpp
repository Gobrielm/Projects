#include <queue>
#include <deque>
#include <iostream>
#include <cmath>

using namespace std;
using ll = long long;

class Solution {
public:
    static constexpr int mod = 1000000007;


    int peopleAwareOfSecret(int n, int delay, int forget) {
        int delay_mod = delay;
        int adding_mod = forget - delay + 1;
        vector<ll> delaying(delay_mod);
        vector<ll> adding(adding_mod);
        delaying[(1) % delay_mod] = 1;

        for (int day = 2; day <= n; day++) {
            // Delete old adders
            adding[(day + 1) % adding_mod] = 0; // Get rid of next day adders

            // Move delayers to adders
            adding[day % adding_mod] = delaying[day % delay_mod] % mod;
            delaying[day % delay_mod] = 0;

            // Add with current day and last day
            for (int i = 0; i < (adding_mod - 1); i++) {
                int idx = ((day - i) % adding_mod + adding_mod) % adding_mod;
                delaying[day % delay_mod] += adding[idx];
                delaying[day % delay_mod] % mod;
            }
        }

        ll total = 0;
        for (const auto& amount: delaying) {
            total += amount;
        }
        for (const auto& amount: adding) {
            total += amount;
        }
        return total % mod;
    }
};
