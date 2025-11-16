#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:

    long count_subtree(long curr, long next, int n) {
        if (next > n) {
            if (curr > n) return 0;
            return n - curr + 1;
        }
        
        return (next - curr) + count_subtree(curr * 10, next * 10, n);
    }

    int findKthNumberHelper(long curr, long n, long k) {
        if (k == 0) return curr / 10;

        for (long i = max(1L, curr); i < curr + 10; i++) {

            long count = count_subtree(i, i + 1, n);
            if (count >= k) {
                return findKthNumberHelper(i * 10, n, k - 1);
            }

            k -= count;
        }
        return -1;
    }

    int findKthNumber(int n, int k) {
        return findKthNumberHelper(0, n, k);
        long count = 0;
    }

    
};

int main() {
    Solution sol;
    cout << sol.findKthNumber(1000000000, 1000000000);
    // sol.findKthNumber(2000, 2);
}
