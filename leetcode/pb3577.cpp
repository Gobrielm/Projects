#include <vector>

using namespace std;

int MOD = 1e9 + 7;

class Solution {

    int factoralMOD(int n) {
        long long tot = n;
        for (int i = n - 1; i > 0; i--) {
            tot = (tot * i) % MOD;
        }
        return tot;
    }

    public:
    int countPermutations(vector<int>& complexity) {
        int firstInd = complexity[0];
        for (int i = 1; i < complexity.size(); i++) {
            if (complexity[i] <= firstInd) {
                return 0;
            }
        }

        return factoralMOD(complexity.size() - 1);
    }
};