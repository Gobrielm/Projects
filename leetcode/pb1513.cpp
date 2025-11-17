#include <string>

using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;

class Solution {
    public:
    int numSub(string s) {
        ll sum = 0;
        ll len = 0;
        int R = 0;
        const int n = s.size();

        while (R < n) {


            while (R != n && s[R] == '0') {
                R++;
            }

            while (R != n && s[R] == '1') {
                R++;
                len++;
                sum += len;
                sum %= MOD;
            }

            len = 0;
            R++;
        }


        return sum % MOD;
    }
};