//
// Created by raghavendra on 11/28/24.
//

#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <iostream>

#include "Task.h"
#include <algorithm>
#include <vector>

class TaskManager {
    int m_ids = 0;

public:
    std::vector<Task *> tasks;

    TaskManager() = default;

    ~TaskManager() {
        for (const auto task: tasks)
            delete task;
        tasks.clear();
        m_ids = 0;
        std::cout << "TaskManager Destructor" << std::endl;
    }

    Task*  addTask(std::string &title, std::string &description);

    void removeTaskById(int id);

    void removeAllTasks();

    void printAllTasks() const;

    [[nodiscard]] Task *getTaskById(int id) const;
};

#endif //TASKMANAGER_H
