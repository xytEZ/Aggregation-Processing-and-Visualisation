#ifndef NETWORK_MBED_APP_HH_
# define NETWORK_MBED_APP_HH_

# include <map>
# include <utility>
# include <string>
# include "mbed.h"
# include "IApp.hh"
# include "Timer.hh"
# include "TemperatureManager.hpp"

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

namespace Network
{
    namespace API
    {
        template <typename T, typename U>
        class INetworkAPI;
    }
}

namespace App
{
    class NetworkMBEDApp : public IApp
    {
        private :
            enum e_timer_min_state { NO_TIMER, FIRST_HALF, SECOND_HALF };
           
        private :
            GUI::IGUI                                       *_gui;
            Network::API::INetworkAPI<bool, std::string>    *_networkAPI;
            InterruptIn                                     _sw2Int;
            InterruptIn                                     _sw3Int;
            std::map<std::string, MBED::Device::IDevice *>  _devices;
            TemperatureManager<>                            _temperatureManager;
            bool                                            _sw2IntTrig;
            bool                                            _sw3IntTrig;
            Helper::Timer                                   _timer;
            e_timer_min_state                               _timerMinState;
            
        
        public :
            NetworkMBEDApp(GUI::IGUI *);
            virtual ~NetworkMBEDApp();
            virtual bool init();
            virtual void run();
            virtual bool close();
            
        private :
            void sw2Interrupt();
            void sw3Interrupt();
            void eraseDevice(std::pair<std::string, MBED::Device::IDevice *>) const;
            void triggerEvent();
            void executeMainActivity();
            void timerIsOver();
            void switchSpeakerOperation();
            void showSpeakerStatus();
            void setRGBLED(int);
            void catchTemperature(double);
            void changeTimer(const std::string&);
            std::string getRightChangeTimerMsg(const std::string&);
            double extractDegreeFromResult(const std::string&) const;
    };
}

#endif /* !NETWORK_MBED_APP_HH_ */