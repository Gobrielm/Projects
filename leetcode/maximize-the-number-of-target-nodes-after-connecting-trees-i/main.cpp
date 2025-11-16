#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Node {
    int i;
    vector<Node*> connections;

    public:

    Node(int _i = 0) {
        i = _i;
    }

    void add_connection(Node* other) {
        connections.push_back(other);
        other->connections.push_back(this);
    }

    int get_total_connections(int dist_out) {
        if (dist_out == 0) {
            return 1;
        } else if (dist_out < 0) {
            return 0;
        }
        unordered_map<int, int> m;
        m[i] = 0;
        queue<Node*> q;
        q.push(this);
        Node* current;
        while (q.size() != 0) {
            current = q.front();
            q.pop();

            for (Node* x: current -> connections) {
                if (m.count(x -> i) == 0) {
                    m[x -> i] = m[current -> i] + 1;
                    if (m[x -> i] < dist_out) {
                         q.push(x);
                    }
                }
            }
        }
        return m.size();
    }
};


class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2, int k) {
        unordered_map<int, Node*> tree1;
        unordered_map<int, Node*> tree2;
        
        for (vector<int> e: edges1) {
            int a = e[0];
            int b = e[1];
            if (tree1.count(a) == 0) {
                tree1[a] = new Node(a);
            }
            if (tree1.count(b) == 0) {
                tree1[b] = new Node(b);
            }
            tree1[a]->add_connection(tree1[b]);
        }

        for (vector<int> e: edges2) {
            int a = e[0];
            int b = e[1];
            if (tree2.count(a) == 0) {
                tree2[a] = new Node(a);
            }
            if (tree2.count(b) == 0) {
                tree2[b] = new Node(b);
            }
            tree2[a]->add_connection(tree2[b]);
        }
        int n = tree1.size(); //Biggest value found in tree1
        int m = tree2.size(); //Biggest value found in tree2


        int biggest_connection = 0;
        for (int i = 0; i < m; i++) {
            int temp = tree2[i] -> get_total_connections(k - 1);
            biggest_connection = max(biggest_connection, temp);
        }

        vector<int> toReturn;
        for (int i = 0; i < n; i++) {
             int temp = tree1[i] -> get_total_connections(k);
            toReturn.push_back(temp + biggest_connection);
        }
        return toReturn;
    }
};