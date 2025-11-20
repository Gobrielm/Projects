#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
    struct SolutionCompare {
        bool operator()(const vector<int>& v1, const vector<int>& v2) const {
            if (v1[0] == v2[0]) return v1[1] > v2[1];
            return v1[0] < v2[0];
        }
    };

public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        int n = intervals.size();
        sort(intervals.begin(), intervals.end(), SolutionCompare());
        int totalPlaced = 0;
        
        vector<int> setIntersections(n, 0);

        for (int i = n - 1; i >= 0; i--) {
            const auto& interval = intervals[i];
            const int& L = interval[0];

            int needed = 2 - setIntersections[i];
            
            for (int s = L; s < L + needed; s++) {
                for (int j = 0; j < i; j++) {
                    if (setIntersections[j] < 2 && s <= intervals[j][1]) {
                        setIntersections[j]++;
                    }
                }

                totalPlaced++;
            }

        }

        return totalPlaced;
    }
};