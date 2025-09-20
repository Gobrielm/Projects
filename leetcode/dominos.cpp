#include <string>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
    bool idx_in_range(int idx, const string& dominoes) {
        return idx >= 0 && idx < dominoes.size();
    }

    string pushDominoes(string dominoes) {
        unordered_set<int> s;
        s.insert(-1); s.insert(dominoes.size());

        queue<pair<int, int>> q;
        for (int i = 0; i < dominoes.size(); i++) {
            if (dominoes[i] != '.') {
                q.emplace(i, 0);
                s.insert(i);
            }
        }
        string day_dominoes = dominoes; // Reads from here
        int current_day = 0;
        while (!q.empty()) {
            auto pair = q.front(); q.pop();
            int idx = pair.first;
            int day = pair.second;
            if (current_day != day) {
                current_day = day;
                day_dominoes = dominoes;
            }

            if (day_dominoes[idx] == '.') {

                char right = idx_in_range(idx - 1, day_dominoes) ? day_dominoes[idx - 1]: '.';
                char left = idx_in_range(idx + 1, day_dominoes) ? day_dominoes[idx + 1]: '.';
                
                if (left == '.' && right == 'R') {
                    dominoes[idx] = right;
                } else if (right == '.' && left == 'L') {
                    dominoes[idx] = left;
                } else if (left == right) {
                    dominoes[idx] = left;
                }

            }

            if (!s.count(idx - 1) && dominoes[idx] == 'L') { // Going left
                q.emplace(idx - 1, current_day + 1);
                s.insert(idx - 1);
            }

            if (!s.count(idx + 1) && dominoes[idx] == 'R') { // Going right
                q.emplace(idx + 1, current_day + 1);
                s.insert(idx + 1);
            }
        }
        return dominoes;
    }
};
