#include <vector>
#include <string>

using namespace std;


class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> v;
        for (int i = 1; i < 10; i++) {
            lexicalOrder(v, i, n);
        }
        return v;
    }


    void lexicalOrder(vector<int>& v, const int& i, const int& n) {
        if (i > n) return;
        v.push_back(i);
        for (int j = 0; j < 10; j++) {
            lexicalOrder(v, (i * 10) + j, n);
        }
    }
};