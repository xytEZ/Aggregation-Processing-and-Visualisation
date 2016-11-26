#ifndef RGB_LED_HH_
# define RGB_LED_HH_

# include "mbed.h"
# include "IDevice.hh"

namespace MBED
{
    namespace Device
    {
        class RGBLED : public IDevice
        {
            private :
                enum ConvertissorMode
                {
                    LCD_GREEN_LIGHT,
                    LCD_YELLOW_LIGHT,
                    LCD_RED_LIGHY
                };
            
            private :
                PwmOut              _r;
                PwmOut              _g;
                PwmOut              _b;
                ConvertissorMode    _convertissorMode;
                std::string         _name;
                
            public :
                RGBLED();
                virtual ~RGBLED();
                virtual std::string execute();
                virtual void setState(int);
                virtual int getState() const;
                virtual void setDeviceMode(int);
                virtual int getNbDeviceMode() const;
                virtual const std::string& getDeviceName() const;
                
            private :
                void setColorToGreen();
                void setColorToYellow();
                void setColorToRed();
        };
    }
}

#endif /* !RGB_LED_HH_ */