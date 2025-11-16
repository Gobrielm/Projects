#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        sort(tasks.begin(), tasks.end(), greater<int>());
        sort(workers.begin(), workers.end(), greater<int>()); // Descending Order
        int tasks_completed = 0;
        int i = 0;
        for (auto& worker: workers) {
            while (i < tasks.size() && tasks[i] > worker) {
                i++;
            }
            if (i == tasks.size()) break;

            tasks_completed++;
            worker = -1;
            tasks[i] = __INT_MAX__;
        }

        i = 0;
        //Pills now
        for (auto& worker: workers) {
            if (worker == -1) continue;

            while (i < tasks.size() && tasks[i] > (worker + strength)) {
                i++;
            }
            if (i == tasks.size()) break;

            tasks_completed++;
            worker = -1;
            tasks[i] = __INT_MAX__;
            pills--;
            if (pills == 0) break;
        }


        return tasks_completed;
    }
};

int main() {
    Solution sol;
    vector<int> tasks = {10,15,30};
    vector<int> workers = {0,10,10,10,10};
    sol.maxTaskAssign(tasks,workers,3,10);
}