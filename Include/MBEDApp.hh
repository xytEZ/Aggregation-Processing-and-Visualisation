#ifndef MBED_APP_HH_
# define MBED_APP_HH_

# include <vector>
# include <string>
# include "mbed.h"
# include "IApp.hh"

namespace MBED
{
    namespace Device
    {
        class IDevice;
    }
}

namespace GUI
{
    class IGUI;
}

namespace App
{
    class MBEDApp : public IApp
    {
        private :
            GUI::IGUI                               *_gui;
            InterruptIn                             _sw2Int;
            InterruptIn                             _sw3Int;
            std::vector<MBED::Device::IDevice *>    _devices;
            bool                                    _sw2IntTrig;
            bool                                    _sw3IntTrig;
            int                                     _indexDevice;
            int                                     _modeDevice;
        
        public :
            MBEDApp(GUI::IGUI *);
            virtual ~MBEDApp();
            virtual bool init();
            virtual void run();
            virtual bool close();
            
        private :
            void sw2Interrupt();
            void sw3Interrupt();
            void eraseDevice(MBED::Device::IDevice *) const;
            void triggerDeviceEvent();
            void performInteractionWithDevice();
            float adaptatingDisplayBySpecificDevice() const;
            void setDevice();
            void setDeviceMode();
            void setRGBLED();
    };
}

#endif /* !MBED_APP_HH_ */