#ifndef IDEVICE_HH_
# define IDEVICE_HH_

# include <string>

namespace MBED
{
    namespace Device
    {
        class IDevice
        {
            public :
                virtual ~IDevice() { }
                virtual std::string execute() = 0;
                virtual void setState(int) = 0;
                virtual int getState() const = 0;
                virtual void setDeviceMode(int) = 0;
                virtual int getNbDeviceMode() const = 0;
                virtual const std::string& getDeviceName() const = 0;
        };
    }
}

#endif /* !IDEVICE_HH_ */