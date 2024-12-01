//
// Created by raghavendra on 11/28/24.
//

#include "../include/TaskManager.h"


Task* TaskManager::addTask(std::string &title, std::string &description) {
    auto new_task = new Task(++m_ids, title, description);
    tasks.emplace_back(new_task);
    return new_task;
}

void TaskManager::removeAllTasks() {
    tasks.clear();
}

void TaskManager::printAllTasks() const {
    for (const auto task: tasks) {
        task->Print();
    }
}

Task *TaskManager::getTaskById(const int id) const {
    for (const auto task: tasks)
        if (task->m_id == id)
            return task;
    return nullptr;
}

void TaskManager::removeTaskById(const int id) {
    const auto task = getTaskById(id);
    tasks.erase(std::ranges::find(tasks, task));
}
