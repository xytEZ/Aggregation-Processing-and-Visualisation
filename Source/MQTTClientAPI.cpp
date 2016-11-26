#include "MQTTClientAPI.hh"

namespace Network
{
    namespace API
    {   
        namespace
        {
            MQTT::Message   g_msg;
            int             g_arrived_count = 0;
            
            void message_arrived(MQTT::MessageData& md)
            {
                g_msg = MQTT::Message(md.message);
                ++g_arrived_count;
            }
            
            MQTT::Message get_global_msg() { return g_msg; }
            
            void delete_payload()
            {
                if (g_msg.payload)
                    delete g_msg.payload;
            }
        }
    
        MQTTClientAPI::MQTTClientAPI(const std::string& hostname, int port,
                        const std::string& topic, const std::string& clientID,
                        const std::string& username, const std::string& password) :
            _client(_ipstack),
            _hostname(hostname),
            _port(port),
            _topic(topic),
            _clientID(clientID),
            _username(username),
            _password(password)
        {
        }
        
        MQTTClientAPI::~MQTTClientAPI() { delete_payload(); }
        
        bool MQTTClientAPI::connection()
        {
            MQTTPacket_connectData   data = MQTTPacket_connectData_initializer;
            
            if (_ipstack.connect(const_cast<char *>(_hostname.c_str()), _port) != 0)
                return false;
            data.MQTTVersion = 3;
            data.clientID.cstring = const_cast<char *>(_clientID.c_str());
            data.username.cstring = const_cast<char *>(_username.c_str());
            data.password.cstring = const_cast<char *>(_password.c_str());
            return _client.connect(data) == 0
                && _client.subscribe(_topic.c_str(), MQTT::QOS2, &message_arrived) == 0;
        }
        
        bool MQTTClientAPI::sendData(const std::string& msg)
        {
            MQTT::Message message;
        
            message.qos = MQTT::QOS0;
            message.retained = false;
            message.dup = false;
            message.payload = const_cast<char *>(msg.c_str());
            message.payloadlen = msg.size();
            if (_client.publish(_topic.c_str(), message) != 0)
                return false;
            while (g_arrived_count < 1)
                _client.yield(100);
            --g_arrived_count;
            return true;
        }
        
        std::string MQTTClientAPI::receiveData()
        {
            if (get_global_msg().payload)
            {
                std::string payload = static_cast<char *>(get_global_msg().payload);
                
                --g_arrived_count;
                delete_payload();
                return payload;
            }
            return "";
        }
        
        bool MQTTClientAPI::disconnection()
        {
            return _client.unsubscribe(_topic.c_str()) == 0
                && _client.disconnect() == 0 
                && _ipstack.disconnect() == 0;
        }
    }
}