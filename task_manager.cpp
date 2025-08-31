#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>

using namespace std;

class TaskManager {
private:
    struct Task {
        int userId, taskId, priority;
        Task() : userId(0), taskId(0), priority(0) {}
        Task(int userId, int taskId, int priority)
            : userId(userId), taskId(taskId), priority(priority) {}
        bool operator<(const Task& other) const {
            if (priority != other.priority)
                return priority > other.priority;
            return taskId > other.taskId;
        }
    };
    map<Task, int> sortedTasks;
    unordered_map<int, Task> taskMap;
public:
    TaskManager(vector<vector<int>>& tasks) {
        for (auto& task : tasks) {
            int userId = task[0], taskId = task[1], priority = task[2];
            add(userId, taskId, priority);
        }
    }
    void add(int userId, int taskId, int priority) {
        Task task(userId, taskId, priority);
        sortedTasks[task] = userId;
        taskMap[taskId] = task;
    }
    void edit(int taskId, int newPriority) {
        auto it = taskMap.find(taskId);
        if (it != taskMap.end()) {
            Task task = it->second;
            sortedTasks.erase(task);
            task.priority = newPriority;
            sortedTasks[task] = task.userId;
            taskMap[taskId] = task;
        }
    }
    void rmv(int taskId) {
        auto it = taskMap.find(taskId);
        if (it != taskMap.end()) {
            Task task = it->second;
            sortedTasks.erase(task);
            taskMap.erase(taskId);
        }
    }
    int execTop() {
        if (sortedTasks.empty()) return -1;
        auto it = sortedTasks.begin();
        Task top = it->first;
        sortedTasks.erase(it);
        taskMap.erase(top.taskId);
        return top.userId;
    }
};

int main() {
    vector<vector<int>> initTasks = {{1, 101, 10}, {2, 102, 20}, {3, 103, 15}};
    TaskManager taskManager(initTasks);
    taskManager.add(4, 104, 5);
    taskManager.edit(102, 8);
    cout << taskManager.execTop() << endl;
    taskManager.rmv(101);
    taskManager.add(5, 105, 15);
    cout << taskManager.execTop() << endl;
    return 0;
}