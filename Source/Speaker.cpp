#include "Speaker.hh"

namespace MBED
{
    namespace Device
    {
        Speaker::Speaker() : _spkr(D6), _state(START), _name("Speaker") { }
        Speaker::~Speaker() { }
        
        std::string Speaker::execute()
        {
            for (float f = 2000; f < 10000; f += 100)
            {
                _spkr.period(1 / f);
                _spkr = 0.5;
                wait(0.02);
            }
            _spkr = 0.0;
            return "";
        }
        
        void Speaker::setState(int state) { _state = static_cast<State>(state); }
        int Speaker::getState() const { return _state; }
        void Speaker::setDeviceMode(int) { }
        int Speaker::getNbDeviceMode() const { return 1; }
        const std::string& Speaker::getDeviceName() const { return _name; }       
    }
}