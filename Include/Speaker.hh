#ifndef SPEAKER_HH_
# define SPEAKER_HH_

# include "mbed.h"
# include "IDevice.hh"

namespace MBED
{
    namespace Device
    {
        class Speaker : public IDevice
        {
            private :
                enum State { START, STOP };
            
            private :
                PwmOut      _spkr;
                State       _state;
                std::string _name;
                
            public :
                Speaker();
                virtual ~Speaker();
                virtual std::string execute();
                virtual void setState(int);
                virtual int getState() const;
                virtual void setDeviceMode(int);
                virtual int getNbDeviceMode() const;
                virtual const std::string& getDeviceName() const;
        };
    }
}

#endif /* !SPEAKER_HH_ */