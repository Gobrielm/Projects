#include <vector>
#include <algorithm>

using namespace std;

class Solution {

    struct SolutionComp {

        bool operator()(const vector<int>& v1, const vector<int>& v2) const {
            if (v1[0] == v2[0]) return v1[1] < v2[1];
            return v1[0] < v2[0];
        }

    };

    public:

    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), SolutionComp());

        int rangeR = points[0][1];
        int arrows = 1;

        for (const auto& pt: points) {

            // In range
            if (pt[0] <= rangeR) {
                rangeR = min(pt[1], rangeR);
            } else {
                rangeR = pt[1];
                arrows++;
            }

        }

        return arrows;
    }
};