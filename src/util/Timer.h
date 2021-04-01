#ifndef MINECPP_TIMER_H
#define MINECPP_TIMER_H

#include <chrono>


class Timer {

    using SecondsDuration = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::high_resolution_clock::time_point m_lastUpdate;
    std::chrono::high_resolution_clock::duration m_delta;

public:
    Timer();

    void update();

    double now();
    double delta();

};


#endif //MINECPP_TIMER_H
