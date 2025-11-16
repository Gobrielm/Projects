#include <vector>
#include <deque>
#include <stack>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    void create_non_prime_stack(vector<int>& stack, vector<int>& nums) {
        for (int index = 0; index < nums.size(); index++) {
            int num = nums[index];
            while (!stack.empty()) {
                int top = stack.back();

                int g = gcd(top, num);
                if (g == 1) break;
                stack.pop_back();
                long long merged = (long long)top / g * num;
                num = (int)merged;
            }
            stack.push_back(num);

        }
    }


public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {
        vector<int> stack;
        create_non_prime_stack(stack, nums);

        return stack;
    }
};
