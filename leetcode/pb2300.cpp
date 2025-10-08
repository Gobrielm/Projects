#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
using ll = long long;
class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        const int& m = potions.size();
        sort(potions.begin(), potions.end(), std::less<int>());
        vector<int> successfulPairsVector(spells.size());
        
        for (int i = 0; i < spells.size(); i++) {
            ll spell = spells[i];
            ll min_potion = (success + spell - 1) / spell;

            auto it = lower_bound(potions.begin(), potions.end(), min_potion);
            successfulPairsVector[i] = (m - distance(potions.begin(), it));
        }

        return successfulPairsVector;
    }
};
