#include <vector>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
public:
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
        int tracker1 = tops[0];
        int tracker2 = bottoms[0];
        int to_track = -1;
        int n = tops.size();
        for (int i = 1; i < n; i++) {
            int top = tops[i];
            int bot = bottoms[i];
            if ((top == tracker1 || bot == tracker1) && (top == tracker2 || bot == tracker2)) {
                
            } else if (top == tracker1 || bot == tracker1) {
                if (to_track == 2) return -1;
                to_track = 1;
            } else if (top == tracker2 || bot == tracker2) {
                if (to_track == 1) return -1;
                to_track = 2;
            } else {
                return -1; // No matching
            }
        }
        
        int top_count = 0;
        int bot_count = 0;
        for (int i = 0; i < n; i++) {
            if (tops[i] == bottoms[i]) continue;
            if (tops[i] == tracker1) {
                top_count++;
            } else {
                bot_count++;
            }
        }

        int top_count_b = 0;
        int bot_count_b = 0;
        for (int i = 0; i < n; i++) {
            if (tops[i] == bottoms[i]) continue;
            if (tops[i] == tracker2) {
                top_count_b++;
            } else {
                bot_count_b++;
            }
        }

        if (to_track == -1) {
            return min(min(top_count_b, bot_count_b), min(top_count, bot_count));
        } else if (to_track == 1){
            return min(top_count, bot_count);
        }

        return min(top_count_b, bot_count_b);
    }   
};

// int main() {
//     Solution sol;
//     vector<int> v1 = {2, 1, 2, 4, 2, 2};
//     vector<int> v2 = {5, 2, 6, 2, 3, 2};
//     sol.minDominoRotations(v1, v2);
// }