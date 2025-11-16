#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
    public:
    int minCost(string colors, vector<int>& neededTime) {
        int n = colors.size();
        int removed = 0;

        for (int i = 1; i < n; i++) {
            int maximum = 0;
            // Remove all except max
            while (i < n && colors[i] == colors[i - 1]) {
                removed += neededTime[i - 1];
                maximum = max(maximum, neededTime[i - 1]);
                i++;
            }

            removed += neededTime[i - 1];
            maximum = max(maximum, neededTime[i - 1]);
            if (maximum != 0) removed -= maximum;
        }

        return removed;
    }
};

