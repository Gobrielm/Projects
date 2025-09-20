#include <cmath>
#include <iostream>

class Solution {
    


public:

    int makeTheIntegerZero(int num1, int num2) {
        for (int k = 1; k <= 60; k++) {
            long long x = num1 - 1LL * num2 * k;
            if (x < k) {
                return -1;
            } else {
                int fx = __builtin_popcountll(x);
                if (k >= fx) {
                    return k;
                }
            }
        }
        return -1;
    }
};
