#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <algorithm>

using namespace std;

class Solution {
    struct UnorderedTriple {
        std::array<int, 3> values;

        UnorderedTriple(int a, int b, int c) {
            values = {a, b, c};
            std::sort(values.begin(), values.end()); // canonical order
        }

        bool operator==(const UnorderedTriple& other) const noexcept {
            return values == other.values;
        }
    };

    struct UnorderedTripleHash {
        std::size_t operator()(const UnorderedTriple& t) const noexcept {
            auto h1 = std::hash<int>{}(t.values[0]);
            auto h2 = std::hash<int>{}(t.values[1]);
            auto h3 = std::hash<int>{}(t.values[2]);

            std::size_t seed = h1;
            seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= h3 + 0x9e3779b9 + (seed << 6) + (seed >> 2);

            return seed;
        }
    };

    using IntTripleSet = std::unordered_set<UnorderedTriple, UnorderedTripleHash>;

public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> v;
        const int n = nums.size();
        IntTripleSet used;
        for (int i = 0; i < n - 1; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            unordered_set<int> s;
            for (int j = i + 1; j < n; j++) {
                int num_needed = -(nums[j] + nums[i]);
                if (s.count(num_needed)) {
                    auto new_tuple = UnorderedTriple(nums[j], nums[i], num_needed);
                    if (!used.count(new_tuple)) {
                        v.push_back({num_needed, nums[j], nums[i]});
                        used.insert(new_tuple);
                    }
                }
                s.insert(nums[j]);
            }
        }
        return v;
    }
};