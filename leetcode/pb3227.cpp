#include <string>

using namespace std;

class Solution {
    inline bool is_vowel(const char& c) const {
        return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
    }

public:
    bool doesAliceWin(string s) {
        int count = 0;
        for (const auto& c: s) {
            if (is_vowel(c)) count++;
        }
        return count != 0 ;
    }
};