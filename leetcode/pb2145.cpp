#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;
using ll = long long;
class Solution {
public:
    int numberOfArrays(vector<int>& differences, int lower, int upper) {

        ll smallest_num = lower;
        ll biggest_num = lower;
        ll last_num = lower;

        for (const auto& diff: differences) {
            ll next_num = last_num + diff;
            smallest_num = min(smallest_num, next_num);
            biggest_num = max(biggest_num, next_num);
            last_num = next_num;
        }

        int lower_diff = lower - smallest_num;
        int to_return = upper - (biggest_num + lower_diff) + 1;
        return to_return >= 0 ? to_return: 0;
    }
};

