#include <string>

using namespace std;

class Solution {
    int remove_starting_zeros(const string& x) {
        int toReturn;
        string sub = "0";
        for (int i = 0; i < x.size(); i++) {
            if (x[i] != '0') {
                sub = x.substr(i, x.size());
                break;
            }
        }
        return stoi(sub);
    }


public:
    int compareVersion(string version1, string version2) {
        string ver1;
        string ver2;
        int i = 0, j = 0;

        while (i < version1.size() || j < version2.size()) {
            const char& a = version1.size() > i ? version1[i]: '.';
            const char& b = version2.size() > j ? version2[j]: '.';

            if (a == b && a == '.') {
                int x = remove_starting_zeros(ver1);
                int y = remove_starting_zeros(ver2);
                ver1 = ""; ver2 = "";
                if (x == y) {
                    i++; j++;
                    continue;
                }
                return x > y ? 1: -1;
            }

            if (a != '.') {
                ver1.push_back(a);
                i++;
            }
            if (b != '.') {
                ver2.push_back(b);
                j++;
            }
        }

        int x = remove_starting_zeros(ver1);
        int y = remove_starting_zeros(ver2);
        if (x == y) {
            return 0;
        }
        return x > y ? 1: -1;
    }
};

int main() {
    Solution sol;
    sol.compareVersion("11", "10");
}