#include <string>

using namespace std;

class Solution {
    public:
    int maxOperations(string s) {
        int groups = 0;
        int ops = 0;

        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == '0') {
                if ((i == s.size() - 1 || s[i + 1] == '1')) groups++;
            } else {
                ops += groups;
            }
        }
        return ops;
    }
};

int main() {
    Solution sol;
    sol.maxOperations("1001101");
}