#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    struct SolutionCompare {
        bool operator()(const vector<int>& v1, const vector<int>& v2) const { 
            // Sort by biggest y first, then smallest x
            if (v1[1] == v2[1]) {
                return v1[0] < v2[0];
            }
            return v1[1] > v2[1];
        }
    };


    int numberOfPairs(vector<vector<int>>& points) {
        std::sort(points.begin(), points.end(), SolutionCompare());
        const auto& n = points.size();
        int pair_count = 0;

        for (int i = 0; i < n; i++) {
            const auto& pt1 = points[i];
            int x_left_limit = pt1[0];
            int x_right_limit = __INT_MAX__;

            for (int j = i + 1; j < n; j++) {
                const auto& pt2 = points[j];
                int x = pt2[0];
                if (x >= x_left_limit && x < x_right_limit) {
                    pair_count++;
                    x_right_limit = x;
                    if (x_right_limit == x_left_limit) break;
                }

            }
        }

        return pair_count;
    }

};