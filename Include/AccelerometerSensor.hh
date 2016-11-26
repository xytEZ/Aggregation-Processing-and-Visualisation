#ifndef ACCELEROMETER_SENSOR_HH_
# define ACCELEROMETER_SENSOR_HH_

# include "MMA7660.h"
# include "IDevice.hh"

namespace MBED
{
    namespace Device
    {
        namespace Sensor
        {
            class AccelerometerSensor : public IDevice
            {
                private :
                    MMA7660     _mma;
                    std::string _name;
                
                public :
                    AccelerometerSensor();
                    virtual ~AccelerometerSensor();
                    virtual std::string execute();
                    virtual void setState(int);
                    virtual int getState() const;
                    virtual void setDeviceMode(int);
                    virtual int getNbDeviceMode() const;
                    virtual const std::string& getDeviceName() const;
                    
                private :
                    static float convertToDegreeRotation(float);
            };
        }
    }
}

#endif /* !ACCELEROMETER_SENSOR_HH_ */