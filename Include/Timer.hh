#ifndef TIMER_HH_
# define TIMER_HH_

# include <ctime>

namespace Helper
{
    class Timer
    {
        public :
            static const double MINUTES_TO_SECS;
        
        private :
            double      _highest_timer_max;
            double      _smallest_timer_max;
            double      _timerMax;
            double      _nextTimerMax;
            std::time_t _start;
        
        public :
            Timer(double, double = 1800, double = 60);
            ~Timer();
            void reset();
            bool isFinished() const;
            double getElapsedTime() const;
            double getElapsedTimeMinuteSecondFormat() const;
            bool addNextTimerMax();
            bool subNextTimerMax();
            double getTimerMaxMinuteSecondFormat() const;
            double getHighestTimerMax() const;
            double getSmallestTimerMax() const;
            
        private :
            double getDiffTime() const;
            static double toMinuteSecondFormat(double);
    };
}

#endif /* !TIMER_HH_ */