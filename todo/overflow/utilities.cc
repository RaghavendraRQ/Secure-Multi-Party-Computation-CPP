//
// Created by raghavendra on 12/21/24.
//
#include "utilities.h"


Timer::Timer(std::string  scope): m_scope(std::move(scope)){
    start = std::chrono::high_resolution_clock::now();
    breakpoint = 0;
}

Timer::~Timer() {
    stop = std::chrono::high_resolution_clock::now();
    m_duration = stop - start;
    const float ms = m_duration.count();
    std::cout << "\033[34m[Timer] " << m_scope << ": " << ms << " milli seconds\033[0m\n";
}

void Timer::lapse() {
    stop = std::chrono::high_resolution_clock::now();
    m_duration = stop - start;
    const float ms = m_duration.count();
    std::cout << "\033[34m[Timer] " << m_scope << " (lap - " << ++breakpoint << "): "<< ms << " milli seconds\033[0m\n";
}

int RandomNumber::generate(const int& min,const int& max) {
    static std::mt19937 ring = _initializeRing();
    std::uniform_int_distribution<int> dist(min, max);
    return dist(ring);
}

static std::mt19937 RandomNumber::_initializeRing() {
    std::random_device rd;
    return std::mt19937(rd());
}

