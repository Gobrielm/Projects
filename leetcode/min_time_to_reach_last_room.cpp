#include <vector>
#include <cmath>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    struct Tile {
        int x;
        int y;
        int time;

        Tile(int p_x = 0, int p_y = 0, int p_time = 0) {
            x = p_x;
            y = p_y;
            time = p_time;
        }

        bool operator==(const Tile& rhs) const {
            return x == rhs.x && y == rhs.y;
        }

        bool operator()(const Tile& tile1, const Tile& tile2) const {
            if (tile1.time == tile2.time) {
                if (tile1.x == tile2.x) return tile1.y < tile2.y;
                return tile1.x < tile2.x;
            }
            return tile1.time > tile2.time;
        }

        struct TileHash {
            std::size_t operator()(const Tile& t) const noexcept {
                std::size_t h1 = std::hash<int>()(t.x);
                std::size_t h2 = std::hash<int>()(t.y);
                return h1 ^ (h2 << 1);
            }
        };
    };

    bool is_in_range(const Tile& tile, const vector<vector<int>>& moveTime) const {
        if (moveTime.empty() || moveTime.front().empty()) return false;
        return tile.x >= 0 && tile.y >= 0 && tile.x < moveTime.size() && tile.y < moveTime[0].size();
    }

    int minTimeToReach(vector<vector<int>>& moveTime) {
        int n = moveTime.size();
        int m = moveTime.front().size();

        priority_queue<Tile, vector<Tile>, Tile> q;
        unordered_set<Tile, Tile::TileHash> visited;
        q.push(Tile(0, 0, -1));

        while (!q.empty()) {
            const auto curr = q.top(); q.pop();
            if (visited.count(curr)) continue;
            visited.insert(curr);
            if (curr.x == (n - 1) && curr.y == (m - 1)) return curr.time + 1;

            Tile other = Tile(curr.x + 1, curr.y);
            if (!visited.count(other) && is_in_range(other, moveTime)) {
                int new_time = max(moveTime[other.x][other.y], curr.time + 1);
                other.time = new_time;
                q.push(other);
            }
            other = Tile(curr.x - 1, curr.y);
            if (!visited.count(other) && is_in_range(other, moveTime)) {
                int new_time = max(moveTime[other.x][other.y], curr.time + 1);
                other.time = new_time;
                q.push(other);
            }
            other = Tile(curr.x, curr.y + 1);
            if (!visited.count(other) && is_in_range(other, moveTime)) {
                int new_time = max(moveTime[other.x][other.y], curr.time + 1);
                other.time = new_time;
                q.push(other);
            }
            other = Tile(curr.x, curr.y - 1);
            if (!visited.count(other) && is_in_range(other, moveTime)) {
                int new_time = max(moveTime[other.x][other.y], curr.time + 1);
                other.time = new_time;
                q.push(other);
            }
        }

        return -1;
    }
};
