#ifndef TEMPERATURE_SENSOR_HPP_
# define TEMPERATURE_SENSOR_HPP_

# include <sstream>
# include "LM75B.h"
# include "IDevice.hh"
# include "ConvertissorTemp.hpp"

namespace MBED
{
    namespace Device
    {
        namespace Sensor
        {
            template <typename T = double, typename U = double>
            class TemperatureSensor : public IDevice
            {
                private :
                    Convertissor::IConvertissor<T, U>   *_convertissor;
                    LM75B                               _lm75b;
                    std::string                         _name;
                    
                public :
                    TemperatureSensor();
                    virtual ~TemperatureSensor();
                    virtual std::string execute();
                    virtual void setState(int);
                    virtual int getState() const;
                    virtual void setDeviceMode(int);
                    virtual int getNbDeviceMode() const;
                    virtual const std::string& getDeviceName() const;
            };
                                    
            template <typename T, typename U>
            TemperatureSensor<T, U>::TemperatureSensor() :
                _convertissor(new Convertissor::ConvertissorTemp<T, U>),
                _lm75b(D14, D15),
                _name("Temperature")
            {
            }
            
            template <typename T, typename U>
            TemperatureSensor<T, U>::~TemperatureSensor() { delete _convertissor; }
            
            template <typename T, typename U>
            std::string TemperatureSensor<T, U>::execute()
            {
                T                   value;
                std::string         result;
                std::stringstream   ss;
      
                if (_convertissor->getConvertissorMode() == 0)
                {
                    result += "Celsius temperature :\n";
                    value = _lm75b.temp();
                }
                else if (_convertissor->getConvertissorMode() == 1)
                {
                    result += "Fahrenheit temperature :\n";
                    value = _convertissor->convert(_lm75b.temp());
                }
                ss << value;
                result += ss.str();
                return result;
            }
            
            template <typename T, typename U>
            void TemperatureSensor<T, U>::setState(int) { }
            
            template <typename T, typename U>
            int TemperatureSensor<T, U>::getState() const { return 0; }
            
            template <typename T, typename U>
            void TemperatureSensor<T, U>::setDeviceMode(int deviceMode)
            {
                _convertissor->setConvertissorMode(deviceMode);
            }
            
            template <typename T, typename U>
            int TemperatureSensor<T, U>::getNbDeviceMode() const { return 2; }
            
            template <typename T, typename U>
            const std::string& TemperatureSensor<T, U>::getDeviceName() const
            {
                return _name;
            }
        }
    }
}

#endif /* !TEMPERATURE_SENSOR_HPP_ */