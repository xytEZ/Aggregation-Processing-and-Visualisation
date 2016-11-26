#include "Joystick.hh"

namespace MBED
{
    namespace Device
    {
        Joystick::Joystick() :
            _up(A2),
            _down(A3),
            _left(A4),
            _right(A5),
            _center(D4),
            _name("Joystick")
        {
            _eventMsgs[0] = std::make_pair(&Joystick::joystickUpIsReadable,
                                             std::string("Joystick up"));
            _eventMsgs[1] = std::make_pair(&Joystick::joystickDownIsReadable,
                                             std::string("Joystick down"));
            _eventMsgs[2] = std::make_pair(&Joystick::joystickLeftIsReadable,
                                             std::string("Joystick left"));
            _eventMsgs[3] = std::make_pair(&Joystick::joystickRightIsReadable,
                                             std::string("Joystick right"));
            _eventMsgs[4] = std::make_pair(&Joystick::joystickCenterIsReadable,
                                             std::string("Joystick center"));
        }
        
        Joystick::~Joystick() { }
        
        std::string Joystick::execute()
        {
            for (int i = 0; i < 5; ++i)
            {
                if ((this->*_eventMsgs[i].first)())
                    return _eventMsgs[i].second;
            }
            return "";
        }
        
        void Joystick::setState(int) { }
        int Joystick::getState() const { return 0; }
        void Joystick::setDeviceMode(int) { }
        int Joystick::getNbDeviceMode() const { return 1; }
        const std::string& Joystick::getDeviceName() const { return _name; }
        int Joystick::joystickUpIsReadable() { return _up.operator int(); }
        int Joystick::joystickDownIsReadable() { return _down.operator int(); }
        int Joystick::joystickLeftIsReadable() { return _left.operator int(); }
        int Joystick::joystickRightIsReadable() { return _right.operator int(); }
        int Joystick::joystickCenterIsReadable() { return _center.operator int(); }
    }
}