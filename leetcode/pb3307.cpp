#include <vector>
#include <deque>
#include <iostream>
#include <cmath>

using namespace std;
using ll = long long;

class Solution {
public:
    char kthCharacter(long long k, vector<int>& operations) {
        if (k == 1) return 'a';
        int num_operations = 0;
        ll pow2 = 1;
        while (pow2 < k) {
            pow2 *= 2;
            num_operations++;
        }

        deque<int> operations_to_execute;
        ll prev_k = k;
        num_operations--; // 0 -INDEX
        pow2 /= 2;
        while (prev_k > 1) {
            prev_k = prev_k - max(pow2, 1LL);
            operations_to_execute.push_front(num_operations);
            while (pow2 >= prev_k) {
                pow2 /= 2;
                num_operations--;
            }
        }

        char letter = 'a';
        for (int i = 0; i < operations_to_execute.size(); i++) {
            int level = operations_to_execute[i];
            if (operations[level] == 1) {
                if (letter == 'z') {
                    letter = 'a';
                } else {
                    letter++;
                }
                
                
            }
        }

        return letter;
    }
};
