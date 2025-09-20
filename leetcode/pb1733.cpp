#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:



    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) { // Friendships are 1 -indexed

        unordered_set<int> to_teach; // Every person that needs to learn something
        for (const auto& friendship: friendships) {
            unordered_set<int> shared_langs;

            bool can_communicate = false;

            for (const auto& lang: languages[friendship[0] - 1]) {
                shared_langs.insert(lang);
            }

            for (int lang: languages[friendship[1] - 1]) {
                if (shared_langs.count(lang)) {
                    can_communicate = true;
                    break;
                }
            }

            if (!can_communicate) {
                to_teach.insert(friendship[0] - 1); // 0-index
                to_teach.insert(friendship[1] - 1); // 0-index
            }
        }

        // Gets count of each language
        int max_count = 0;
        vector<int> count(n + 1, 0);
        for (const auto& node: to_teach) {
            for (int lang: languages[node]) {
                count[lang]++;
                max_count = max(max_count, count[lang]);
            }
        }

        return to_teach.size() - max_count;
    }
};