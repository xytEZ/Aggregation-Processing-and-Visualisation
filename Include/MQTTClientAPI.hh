#ifndef MQTT_CLIENT_API_HH_
# define MQTT_CLIENT_API_HH_

# include "MQTTEthernet.h"
# include "MQTTClient.h"
# include "INetworkAPI.hpp"

namespace Network
{
    namespace API
    {
        class MQTTClientAPI : public INetworkAPI<bool, std::string>
        {
            private :
                MQTTEthernet                            _ipstack;
                MQTT::Client<MQTTEthernet, Countdown>   _client;
                std::string                             _hostname;
                int                                     _port;
                std::string                             _topic;
                std::string                             _clientID;
                std::string                             _username;
                std::string                             _password;
            
            public :
                MQTTClientAPI(const std::string&, int,
                        const std::string&, const std::string&,
                        const std::string&, const std::string&);
                virtual ~MQTTClientAPI();
                virtual bool connection();
                virtual bool sendData(const std::string&);
                virtual std::string receiveData();
                virtual bool disconnection();
        };
    }
}

#endif /* !MQTT_CLIENT_API_HH_ */