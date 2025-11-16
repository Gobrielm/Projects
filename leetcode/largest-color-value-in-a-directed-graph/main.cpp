#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>

using namespace std;

class Node {
    int num;
    char color;
    vector<int> colors;
    vector<Node*> adj;
    int visited = 0;

    public:
    Node(): colors(26, 0) {
        num = -1;
        color = '0';

    }

    Node(int _num, char _color): colors(26, 0) {
        num = _num;
        color = _color;
    }

    int dfs() {
        if (visited == 0) {
            visited = 1;
            for (Node* node: adj) {
                int val = node->dfs();
                if (val == -1) {
                    return -1;
                }
                for (int c = 0; c < 26; c++) {
                    colors[c] = max(node->colors[c], colors[c]);
                }
            }
            ++colors[color - 'a'];
            visited = 2;
        }   
        return visited == 1 ? -1: colors[color - 'a'];
    }

    void add_adj(Node* node) {
        adj.push_back(node);
    }

    int get_num() {
        return num;
    }

    char get_color() {
        return color;
    }

};


class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        unordered_map<int, Node*> m;
        for (int n = 0; n < colors.length(); n++) {
            m[n] = new Node(n, colors[n]);
        }
        for (int i = 0; i < edges.size(); i++) {
            Node* this_node = m[edges[i][0]];
            Node* other = m[edges[i][1]];
            this_node -> add_adj(other);
        }

        int largest = 0;
        for (auto p = m.begin(); p != m.end(); p++) {
            Node* this_node = (p -> second);
            int val = this_node->dfs();
            if (val == -1) {
                return -1;
            }
            largest = max(val, largest);
        }

        for (int n = 0; n < colors.length(); n++) {
            delete m[n];
        }

        return largest;
    }
};