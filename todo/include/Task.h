//
// Created by raghavendra on 11/28/24.
//

#ifndef TASK_H
#define TASK_H

#include <string>

enum Priority {
    LOW,
    MEDIUM,
    HIGH
};

class Task {
public:
    int m_id = -1;
    std::string title;
    std::string description;
    // Advanced Parameters
    Priority priority;

    Task(int id, std::string &title, std::string &description);

    Task(int id, std::string &title);

    Task(int id, std::string &title, std::string &description, Priority priority);

    void setPriority(Priority priority_);

    void Print() const;
};


#endif //TASK_H
