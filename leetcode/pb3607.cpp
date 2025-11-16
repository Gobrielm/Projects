#include <vector>
#include <set>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
    public:
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        vector<set<int>> powerGrids;
        vector<int> nodeToPowerGrid(c + 1, -1); // 1's based
        
        vector<vector<int>> grid(c + 1, vector<int>());

        for (const auto& connection: connections) {
            grid[connection[0]].push_back(connection[1]);
            grid[connection[1]].push_back(connection[0]);
        }
        
        unordered_set<int> visited;
        queue<int> q;
        for (int i = 1; i <= c; i++) {
            if (nodeToPowerGrid[i] != -1) continue;

            nodeToPowerGrid[i] = powerGrids.size();
            set<int> powerGrid;
            powerGrid.insert(i);
            
            visited.insert(i);
            q.push(i);

            while(!q.empty()) {
                int node = q.front(); q.pop();

                nodeToPowerGrid[node] = nodeToPowerGrid[i];
                powerGrid.insert(node);

                for (const auto& other: grid[node]) {
                    if (visited.count(other)) continue;
                    q.push(other);
                    visited.insert(other);
                }
            }

            powerGrids.push_back(powerGrid);
        }
        vector<int> toReturn;

        for (const auto& query: queries) {
            int node = query[1];
            int gridInd = nodeToPowerGrid[node];
            if (gridInd == -1) {
                toReturn.push_back(-1);
                continue;
            }

            set<int> &grid = powerGrids[gridInd];

            if (query[0] == 1) {
                if (grid.empty()) {
                    toReturn.push_back(-1);
                } else if (grid.count(node)) {
                    toReturn.push_back(node);
                } else {
                    toReturn.push_back(*grid.begin());
                }
            } else {
                if (!grid.count(node)) {
                    continue;
                }
                grid.erase(node);
            }
        }

        return toReturn;
    }
};


int main() {
    Solution sol;
    vector<vector<int>> v = {{2, 1}};
    vector<vector<int>> qu = {{1,1},{1,2},{1,2},{2,2},{1,2},{2,1},{1,2},{2,1},{2,1},{1,1}};
    sol.processQueries(2, v, qu);
}