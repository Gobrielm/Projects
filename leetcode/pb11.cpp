#include <vector>
#include <queue>

using namespace std;

class Solution {


public:
    int maxArea(vector<int>& height) {
        int f = 0;
        int l = height.size() - 1;
        int max_area = 0;

        while (f != l) {
            const auto& h1 = height[f];
            const auto& h2 = height[l];

            max_area = max(max_area, min(h1, h2) * (l - f));
            if (h1 > h2) {
                l--;
            } else {
                f++;
            }
        }
        return max_area;
    }
};

