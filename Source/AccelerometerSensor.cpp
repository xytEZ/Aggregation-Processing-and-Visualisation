#include <sstream>
#include "AccelerometerSensor.hh"

namespace MBED
{
    namespace Device
    {
        namespace Sensor
        {
            AccelerometerSensor::AccelerometerSensor() : _mma(D14, D15), _name("Accelerometer") { }
            AccelerometerSensor::~AccelerometerSensor() { }
            
            std::string AccelerometerSensor::execute()
            {
                std::stringstream   ss;
                
                ss << "Lateral = " << convertToDegreeRotation(_mma.x()) 
                    << "\nLongitudinal = "<< convertToDegreeRotation(_mma.y());
                return ss.str();
            }
            
            void AccelerometerSensor::setState(int) { }
            int AccelerometerSensor::getState() const { return 0; }
            void AccelerometerSensor::setDeviceMode(int) { }
            int AccelerometerSensor::getNbDeviceMode() const { return 1; }
            const std::string& AccelerometerSensor::getDeviceName() const { return _name; }
            
            float AccelerometerSensor::convertToDegreeRotation(float f)
            {
                return f * 90;
            }
        }
    }
}