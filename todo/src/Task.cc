//
// Created by raghavendra on 11/28/24.
//
#include "../include/Task.h"
#include <iostream>


Task::Task(const int id, std::string &title, std::string &description): m_id(id),
                                                                        title(std::move(title)),
                                                                        description(std::move(description)),
                                                                        priority(LOW) {
}

Task::Task(const int id, std::string &title): priority(LOW) {
    m_id = id;
    title = std::move(title);
}

void Task::Print() const {
    std::cout << m_id << " " << title << " " << description << " " << priority << std::endl;
}

Task::Task(const int id, std::string &title, std::string &description, const Priority priority): m_id(id),
    title(std::move(title)),
    description(std::move(description)),
    priority(priority) {
}

void Task::setPriority(const Priority priority_) {
    priority = priority_;
}
