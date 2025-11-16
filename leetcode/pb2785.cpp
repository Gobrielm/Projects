#include <string>
#include <unordered_map>
#include <cctype>
#include <algorithm>

using namespace std;

class Solution {
    

public:
    bool is_vowel(const char& c) const {
        char lower_c = tolower(c);
        return (lower_c == 'a' || lower_c == 'e' || lower_c == 'i' || lower_c == 'o' || lower_c == 'u');
    }

    string sortVowels(string s) {
        string vowels;
        for (const auto& c: s) {
            if (is_vowel(c)) {
                vowels.push_back(c);
            }
        }
        sort(vowels.begin(), vowels.end(), std::less<char>());

        int count = 0;
        for (int i = 0; i < s.size(); i++) {
            if (is_vowel(s[i])) {
                s[i] = vowels[count++];
            }
        }

        return s;
    }
};