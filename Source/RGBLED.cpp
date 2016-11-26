#include "RGBLED.hh"

namespace MBED
{
    namespace Device
    {
        RGBLED::RGBLED() :
            _r(D5),
            _g(D8),
            _b(D9),
            _convertissorMode(LCD_GREEN_LIGHT),
            _name("RGB LED")
        {
        }
        
        RGBLED::~RGBLED() { }
        
        std::string RGBLED::execute()
        {
            switch (_convertissorMode)
            {
                case LCD_GREEN_LIGHT :
                    setColorToGreen();
                    break;
                case LCD_YELLOW_LIGHT :
                    setColorToYellow();
                    break;
                default :
                    setColorToRed();
                    break;
            }
            return "";
        }
        
        void RGBLED::setState(int) { }
        int RGBLED::getState() const { return 0; }
        
        void RGBLED::setDeviceMode(int deviceMode)
        { 
            _convertissorMode = static_cast<ConvertissorMode>(deviceMode);
        }
        
        int RGBLED::getNbDeviceMode() const { return 1; }
        const std::string& RGBLED::getDeviceName() const { return _name; }
        
        void RGBLED::setColorToGreen()
        {
            _r = 1.0;
            _g = 0.0;
            _b = 0.0;
        }
        
        void RGBLED::setColorToYellow()
        {
            _r = 0.0;
            _g = 1.0;
            _b = 0.0;
        }
        
        void RGBLED::setColorToRed()
        {
            _r = 0.0;
            _g = 0.0;
            _b = 1.0;
        }
    }
}