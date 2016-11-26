#include "Tools.hpp"
#include "Timer.hh"
 
namespace Helper
{
    const double Timer::MINUTES_TO_SECS = 60;
    
    Timer::Timer(double timerMax,
                double highest_timer_max,
                double smallest_timer_max) :
        _highest_timer_max(highest_timer_max),
        _smallest_timer_max(smallest_timer_max),
        _timerMax(timerMax * MINUTES_TO_SECS),
        _nextTimerMax(timerMax * MINUTES_TO_SECS)
    {
    }
    
    Timer::~Timer() { }
    
    void Timer::reset()
    {
        _timerMax = _nextTimerMax;
        _start = std::time(NULL);
    }
    
    bool Timer::isFinished() const { return getDiffTime() >= _timerMax; }
    double Timer::getElapsedTime() const { return getDiffTime(); }
    
    double Timer::getElapsedTimeMinuteSecondFormat() const
    {
        return toMinuteSecondFormat(getDiffTime());
    }
    
    bool Timer::addNextTimerMax()
    {
        if (_nextTimerMax < _highest_timer_max)
        {
            _nextTimerMax += 60;
            return true;
        }
        return false;
    }
    
    bool Timer::subNextTimerMax()
    {
        if (_nextTimerMax > _smallest_timer_max)
        {
            _nextTimerMax -= 60;
            return true;
        }
        return false;
    }
    
    double Timer::getTimerMaxMinuteSecondFormat() const
    {
        return toMinuteSecondFormat(_timerMax);
    }
    
    double Timer::getHighestTimerMax() const
    {
        return _highest_timer_max / MINUTES_TO_SECS;
    }
    
    double Timer::getSmallestTimerMax() const
    {
        return _smallest_timer_max / MINUTES_TO_SECS;
    }
    
    double Timer::getDiffTime() const
    {
        return std::difftime(std::time(NULL), _start);
    }
    
    double Timer::toMinuteSecondFormat(double d)
    {
        return std::floor(d / 60) + (std::fmod(d, 60) * 0.01);
    }
}