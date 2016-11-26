#ifndef CONVERTISSOR_TEMP_HPP_
# define CONVERTISSOR_TEMP_HPP_

# include "IConvertissor.hpp"

namespace Convertissor
{
    template <typename T = double, typename U = double>
    class ConvertissorTemp : public IConvertissor<T, U>
    {
        private :
            enum ConvertissorMode
            {
                FAHRENHEIT_TO_CELSIUS,
                CELSIUS_TO_FAHRENHEIT
            };
            
        private :
            ConvertissorMode    _convertissorMode;
            
        public :
            ConvertissorTemp();
            virtual ~ConvertissorTemp();
            virtual void setConvertissorMode(int);
            virtual int getConvertissorMode() const;
            virtual T convert(const U&) const;
            
        private :
            T convertFahrenheitToCelsius(const U&) const;
            T convertCelsiusToFahrenheit(const U&) const;
    };
    
    template <typename T, typename U>
    ConvertissorTemp<T, U>::ConvertissorTemp() :
        _convertissorMode(FAHRENHEIT_TO_CELSIUS)
    {
    }
    
    template <typename T, typename U>
    ConvertissorTemp<T, U>::~ConvertissorTemp() { }
    
    template <typename T, typename U>
    void ConvertissorTemp<T, U>::setConvertissorMode(int convertissorMode)
    {
        _convertissorMode = static_cast<ConvertissorMode>(convertissorMode);
    }
    
    template <typename T, typename U>
    int ConvertissorTemp<T, U>::getConvertissorMode() const { return _convertissorMode; }
    
    template <typename T, typename U>
    T ConvertissorTemp<T, U>::convert(const U& value) const
    {
        if (_convertissorMode == FAHRENHEIT_TO_CELSIUS)
            return convertFahrenheitToCelsius(value);
        else if (_convertissorMode == CELSIUS_TO_FAHRENHEIT)
            return convertCelsiusToFahrenheit(value);
        else
            return NULL;
    }
    
    template <typename T, typename U>
    T ConvertissorTemp<T, U>::convertFahrenheitToCelsius(const U& value) const
    {
        return (value - 32) / 1.8;
    }
    
    template <typename T, typename U>
    T ConvertissorTemp<T, U>::convertCelsiusToFahrenheit(const U& value) const
    {
        return (value * 1.8) + 32;
    }
}

#endif /* !CONVERTISSOR_TEMP_HPP_ */