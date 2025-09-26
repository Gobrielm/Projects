#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        unordered_map<int, int> m;
        for (const auto& num: nums) {
            m[num]++;
        }
        

        int total = 0;
        const auto& n = nums.size();
        for (int i = 0; i < n; i++) {
            int x = nums[i];

            m[x]--;

            for (int j = i + 1; j < n; j++) {
                int y = nums[j];

                double z = sqrt(pow(i, 2) + pow(j, 2));
                int needed_amount = (int)floor(z) == y? 2: 1;

                if (floor(z) == z && m[(int) z] >= needed_amount) {
                    total += m[(int) z] - needed_amount + 1;
                }
            }
        }
        return total;
    }
};

int main() {
    Solution sol;
    vector<int> v = {2,2,3,4};
    sol.triangleNumber(v);
}