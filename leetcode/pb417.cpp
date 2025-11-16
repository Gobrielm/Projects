#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
    int m, n;
    vector<vector<int>> directions = {{1,0}, {-1,0}, {0,-1}, {0,1}};

public:
    void dfs(int i, int j, vector<vector<int>>& heights, vector<vector<bool>>& visited) {
        visited[i][j] = true;

        for (const auto& d: directions) {
            int x = i + d[0];
            int y = j + d[1];

            if (x < 0 || x >= m || y < 0 || y >= n) continue;
            if (visited[x][y]) continue;
            if (heights[x][y] < heights[i][j]) continue; // Only go up
            dfs(x, y, heights, visited);
        }
    }


    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        m = heights.size();
        n = heights[0].size();

        vector<vector<bool>> pacific(m, vector<bool>(n, false));
        vector<vector<bool>> atlantic(m, vector<bool>(n, false));

        for (int j = 0; j < n; j++) {
            dfs(0, j, heights, pacific);
            dfs(m-1, j, heights, atlantic);
        }

        for (int i = 0; i < m; i++) {
            dfs(i, 0, heights, pacific);
            dfs(i, n-1, heights, atlantic);
        }

        vector<vector<int>> v;
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                if (pacific[x][y] && atlantic[x][y]) v.push_back({x, y});
            }
        }
        return v;
    }
};