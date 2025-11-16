#include <vector>

using namespace std;

class Solution {

    enum TILESTATUS {
        GUARDED,
        GUARD,
        WALL,
        NOT_GUARDED,
    };

    public:
        int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
            vector<vector<TILESTATUS>> grid(m, vector<TILESTATUS>(n, NOT_GUARDED));
            for (const auto& wallVector: walls) {
                grid[wallVector[0]][wallVector[1]] = WALL;
            }
            for (const auto& guardVector: guards) {
                grid[guardVector[0]][guardVector[1]] = GUARD;
            }


            for (const auto& guardVector: guards) {
                int x = guardVector[0];
                int y = guardVector[1];

                // Down
                for (int i = x + 1; i < m; i++) {
                    if (grid[i][y] == GUARD || grid[i][y] == WALL) {
                        break;
                    }
                    grid[i][y] = GUARDED;
                }

                // Up
                for (int i = x - 1; i >= 0; i--) {
                    if (grid[i][y] == GUARD || grid[i][y] == WALL) {
                        break;
                    }
                    grid[i][y] = GUARDED;
                }

                // Right
                for (int j = y + 1; j < n; j++) {
                    if (grid[x][j] == GUARD || grid[x][j] == WALL) {
                        break;
                    }
                    grid[x][j] = GUARDED;
                }

                // Left
                for (int j = y - 1; j >= 0; j--) {
                    if (grid[x][j] == GUARD || grid[x][j] == WALL) {
                        break;
                    }
                    grid[x][j] = GUARDED;
                }
            }

            int tile_not_guarded = 0;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (grid[i][j] == NOT_GUARDED) {
                        tile_not_guarded++;
                    }
                }
            }

            return tile_not_guarded;
        }
    };