#ifndef TEMPERATURE_MANAGER_HPP_
# define TEMPERATURE_MANAGER_HPP_

# include <list>
# include <numeric>

template <typename T = double>
class TemperatureManager
{
    private :
        std::list<T>    _temperatures;
        
    public :
        TemperatureManager();
        ~TemperatureManager();
        void reset();
        int size() const;
        void addTemperature(const T&);
        T getAverageTemperature() const;
};

template <typename T>
TemperatureManager<T>::TemperatureManager() { }

template <typename T>
TemperatureManager<T>::~TemperatureManager() { }

template <typename T>
void TemperatureManager<T>::reset() { _temperatures.clear(); }

template <typename T>
int TemperatureManager<T>::size() const { return _temperatures.size(); }

template <typename T>
void TemperatureManager<T>::addTemperature(const T& temperature) { _temperatures.push_back(temperature); }

template <typename T>
T TemperatureManager<T>::getAverageTemperature() const
{
    return std::accumulate(_temperatures.begin(), _temperatures.end(), 0.0) / _temperatures.size();
}

#endif /* !TEMPERATURE_MANAGER_HPP_ */