#ifndef JOYSTICK_HH_
# define JOYSTICK_HH_

# include "mbed.h"
# include "IDevice.hh"

# include <utility>

namespace MBED
{
    namespace Device
    {
        class Joystick : public IDevice
        {
            private :
                typedef std::pair<int (Joystick::*)(),
                                  std::string> EventMsgs[5];
            
            private :
                DigitalIn   _up;
                DigitalIn   _down;
                DigitalIn   _left;
                DigitalIn   _right;
                DigitalIn   _center;
                EventMsgs   _eventMsgs;
                std::string _name;

            public :
                Joystick();
                virtual ~Joystick();
                virtual std::string execute();
                virtual void setState(int);
                virtual int getState() const;
                virtual void setDeviceMode(int);
                virtual int getNbDeviceMode() const;
                virtual const std::string& getDeviceName() const;
                
            private :
                int joystickUpIsReadable();
                int joystickDownIsReadable();
                int joystickLeftIsReadable();
                int joystickRightIsReadable();
                int joystickCenterIsReadable();   
        };
    }
}

#endif /* !JOYSTICK_HH_ */