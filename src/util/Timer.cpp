#include "Timer.h"


Timer::Timer() :
        m_delta() {
    m_lastUpdate = std::chrono::high_resolution_clock::now();
}

void Timer::update() {
    auto now = std::chrono::high_resolution_clock::now();
    m_delta = now - m_lastUpdate;
    m_lastUpdate = now;
}

double Timer::now() {
    return std::chrono::duration_cast<SecondsDuration>(
            m_lastUpdate.time_since_epoch()).count();
}

double Timer::delta() {
    return std::chrono::duration_cast<SecondsDuration>(m_delta).count();
}



