#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
    int get_manhatten_dist(unordered_map<char, int> &m) {
        return abs(m['N'] - m['S']) + abs(m['W'] - m['E']);
    }

public:
    int maxDistance(string s, int k) {
        unordered_map<char, int> previous_distances;

        int biggest_dist = 0;
        for (const auto& c: s) {
            previous_distances[c]++;
            int dist = get_manhatten_dist(previous_distances);

            if (dist + (2 * k) < biggest_dist) continue;

            int k_for_this = k;

            int change = min(min(previous_distances['N'], previous_distances['S']), k_for_this);
            k_for_this -= change;
            dist += change * 2;

            change = min(min(previous_distances['W'], previous_distances['E']), k_for_this);
            k_for_this -= change;
            dist += change * 2;

            biggest_dist = max(dist, biggest_dist);
        }

        return biggest_dist;
    }
};

