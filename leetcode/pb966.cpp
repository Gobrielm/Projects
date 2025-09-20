#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cctype>
#include <array>
#include <algorithm>

using namespace std;

class Solution {
    

    string to_lower_string(string s) {
        for (char &c: s) {
            c = tolower(c);
        }
        return s;
    }

    string remove_vowels(string s) {
        string toReturn;
        for (const char &c: s) {
            if (!(c == 'a' || c == 'e' || c == 'i' || c == 'u' || c == 'o')) {
                toReturn.push_back(c);
            } else {
                toReturn.push_back('.');
            }
        }
        return toReturn;
    }

public:
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        unordered_set<string> perfect_words;
        unordered_map<string, string> lower_case_words;
        unordered_map<string, string> no_vowels_words;

        for (auto s: wordlist) {
            perfect_words.insert(s);

            string lower_case = to_lower_string(s);
            if (!lower_case_words.count(lower_case)) lower_case_words[lower_case] = s;
            
            string no_vowels = remove_vowels(lower_case);
            if (!no_vowels_words.count(no_vowels)) no_vowels_words[no_vowels] = s;

        }
        vector<string> search_results;
        for (const auto& s: queries) {
            string lower = to_lower_string(s);
            string no_vowels_str = remove_vowels(lower);
            if (perfect_words.count(s)) {
                search_results.push_back(s);
            } else if (lower_case_words.count(lower)) {
                search_results.push_back(lower_case_words[lower]);
            } else if (no_vowels_words.count(no_vowels_str)) {
                const string& result = no_vowels_words[no_vowels_str];
                search_results.push_back(no_vowels_words[no_vowels_str]);
            } else {
                search_results.push_back("");
            }
        }
        return search_results;
    }
};
