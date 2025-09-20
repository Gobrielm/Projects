#include <vector>
#include <random>
#include <algorithm>
#include <queue>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size();
        int n_squard = pow(n, 2);
        queue<int> q; //One's indexed
        unordered_map<int, int> m; //key is one's indexed
        m[1] = 0;

        q.push(1);

        while (q.size() != 0) {
            int curr = q.front(); q.pop();
            int rolls = m[curr];
            for (int i = 1; i <= 6; i++) {
                int index = curr + i;
                if (index > n_squard) continue;
                
                if (index == n_squard) {
                    return m[curr] + 1;
                }

                int space_value = get_space_value(board, index);

                if (space_value == n_squard) {
                    return m[curr] + 1;
                }

                if (space_value == -1 && m.count(index) == 0) {
                    m[index] = rolls + 1;
                    q.push(index);
                } else if (space_value != -1 && m.count(space_value) == 0) {
                    m[space_value] = rolls + 1;
                    q.push(space_value);
                }

                
            }
        }
        return -1;
    }

    int get_space_value(vector<vector<int>>& board, int index) {
        int n = board.size();
        index -= 1; //0 index it
        int row = (n - 1) - int(index / n);
        int col;
        //Goes right
        if ((row + (n % 2 + 1)) % 2 == 0) {
            col = index % n;
        //Goes Left
        } else {
            col = (n - 1) - index % n;
        }

        return board[row][col];
    }
};

int main() {
    vector<vector<int>> board = {
        {1, 1, -1},
        {1, 1, 1},
        {-1, 1, 1},
    };

    Solution solution;
    int rolls = solution.snakesAndLadders(board);
    cout << "Minimum number of rolls: " << rolls << endl;

    return 0;
}