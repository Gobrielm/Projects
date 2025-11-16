#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

class Solution {

public:
    vector<int> avoidFlood(vector<int>& rains) {
        unordered_map<int, int> whenWasLakeFilled;
        set<int> dryDays;

        vector<int> v(rains.size(), 1); // rains is 1-indexed
        
        for (int i = 0; i < rains.size(); i++) {
            const auto& rain = rains[i];
            if (rain == 0) {
                dryDays.insert(i);
            } else {
                v[i] = -1;
                if (whenWasLakeFilled.count(rain)) {
                    auto it = dryDays.lower_bound(whenWasLakeFilled[rain]);
                    if (it == dryDays.end()) return {};

                    v[*it] = rains[i];

                    dryDays.erase(it);
                }
                whenWasLakeFilled[rain] = i;
            }
            
        }
        return v;
    }
};