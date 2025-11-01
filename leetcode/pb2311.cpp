#include <string>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
    public:
       
    int longestSubsequence(string s, int k) {
        int n = s.size();
        int L = -1;
        int R = -1;

        int currentSum = 0;
        vector<int> v;
        string subseq = "";

        while (L < n - 1 && R < n - 1) {

            L++;
            subseq = subseq + s[L];
            currentSum *= 2;
            if (s[L] != '0') {
                currentSum++;
            }

            while (currentSum > k && R < n - 1) {
                R++;
                if (subseq[R] == '1') {
                    currentSum -= pow(2, subseq.size() - 1 - R);
                    v.push_back(R);
                }
                
            }
        }

        return subseq.size() - v.size();
    }
};

int main() {
    Solution sol;
    cout << sol.longestSubsequence("1001010", 5);
}