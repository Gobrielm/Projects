#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        std::unordered_map<string, int> m;
        int count = 0;
        int middle_count = 0;
        for (const auto& s: words) {
            std::string backwards = { s[1], s[0] };
            if (backwards == s) middle_count++;
            if (m[backwards] != 0) {
                m[backwards]--;
                count+=2;
                if (backwards == s) middle_count-=2;
            } else {
                m[s]++;
            }
        }
        if ((count) % 2 == 0 && middle_count > 0) count += 1;
        return count * 2;
    }
};