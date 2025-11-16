#include <vector>

using namespace std;
using ll = long long;

class Solution {
public:
    ll get_subarrays_from_row_zeros(const int& n) const {
        return (n * (n + 1LL)) / 2LL;
    }   


    long long zeroFilledSubarray(vector<int>& nums) {
        long long count = 0;
        int in_row = 0;
        for (const auto& num: nums) {
            if (num == 0) {
                in_row++;
            } else {
                count += get_subarrays_from_row_zeros(in_row);
                in_row = 0;
            }
        }
        count += get_subarrays_from_row_zeros(in_row);

        return count;
    }
};