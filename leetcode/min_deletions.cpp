#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
public:
    
    int minimumDeletions(string word, int k) {
        unordered_map<int, int> freq;
        int deletions = __INT_MAX__;
        for (const auto &c: word) {
            freq[c - 'a']++;
        }

        vector<int> v;
        for(auto& val: freq) {
            v.push_back(val.second);
        }

        std::sort(v.begin(), v.end());
        int n = v.size();

        for (int i = 0; i < n; i++) {
            int x = v[i];
            int range = x + k;

            for (int j = i + 1; j < n; j++) {
                int y = v[j];
                if (y > range) {
                    x += range;
                } else {
                    x += y;
                }
                
            }

            int remain = word.size() - x;
            deletions = min(deletions, remain);

        }
        return deletions;
    }
};