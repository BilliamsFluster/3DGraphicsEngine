#include "Timer.h"


Utils::Timer::Timer()
{
    using namespace std::chrono;
    last = steady_clock::now();
}

float Utils::Timer::Mark()
{
    using namespace std::chrono;
    const auto old = last;
    last = steady_clock::now();
    const duration<float> frameTime = last - old;
    return frameTime.count();
}

float Utils::Timer::Peek() const
{
    using namespace std::chrono;
    return duration<float>(steady_clock::now() - last).count();
}
