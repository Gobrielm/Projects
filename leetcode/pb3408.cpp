#include <vector>
#include <unordered_map>
#include <set>
#include <queue>

using namespace std;


class TaskManager {
    struct cmp {
        bool operator()(const tuple<int,int,int>& t1, const tuple<int,int,int>& t2) const {
            if (get<2>(t1) == get<2>(t2))
                return get<1>(t1) > get<1>(t2);
            return get<2>(t1) > get<2>(t2);
        }
    };
    set<tuple<int, int, int>, cmp> task_set; // userId, taskId, priority
    unordered_map<int, int> tasks; // Task ID -> Priority
    unordered_map<int, int> task_id_to_user_id;

    bool task_is_valid(int taskId) const {
        return task_id_to_user_id.count(taskId);
    }

public:
    TaskManager(vector<vector<int>>& tasks) {
        for (const auto& task: tasks) {
            add(task[0], task[1], task[2]);
        }
    }
    
    void add(int userId, int taskId, int priority) {
        task_set.emplace(userId, taskId, priority);
        tasks[taskId] = priority;
        task_id_to_user_id[taskId] = userId;
    }
    
    void edit(int taskId, int newPriority) {
        int userId = task_id_to_user_id[taskId];
        int old_prty = tasks[taskId];
        task_set.erase(tuple<int, int, int>(userId, taskId, old_prty));
        tasks[taskId] = newPriority;
        task_set.emplace(userId, taskId, newPriority);
    }
    
    void rmv(int taskId) {
        int userId = task_id_to_user_id[taskId];
        int old_prty = tasks[taskId];
        task_set.erase(tuple<int, int, int>(userId, taskId, old_prty));
        tasks.erase(taskId);
        task_id_to_user_id.erase(taskId);
    }
    
    int execTop() {
        if (task_set.empty()) return -1;
        auto first = *task_set.begin();

        rmv(get<1>(first));
        return get<0>(first);
    }
};

/**
 * Your TaskManager object will be instantiated and called as such:
 * TaskManager* obj = new TaskManager(tasks);
 * obj->add(userId,taskId,priority);
 * obj->edit(taskId,newPriority);
 * obj->rmv(taskId);
 * int param_4 = obj->execTop();
 */