//
// Created by raghavendra on 12/21/24.
//

#ifndef OVERFLOW_H
#define OVERFLOW_H
#include <string>
#include <chrono>
#include <iostream>


class Timer {
public:
    explicit Timer(std::string scope);
    ~Timer();
    void lapse();
private:
    std::string m_scope;
    std::chrono::time_point<std::chrono::system_clock> start, stop;
    std::chrono::duration<float, std::milli> m_duration{};
    int16_t breakpoint;
};


#endif //OVERFLOW_H
