#ifndef INETWORK_API_HPP_
# define INETWORK_API_HPP_

# include <string>

namespace Network
{
    namespace API
    {
        template <typename T, typename U>
        class INetworkAPI
        {
            public :
                virtual ~INetworkAPI() { }
                virtual bool connection() = 0;
                virtual T sendData(const std::string&) = 0;
                virtual U receiveData() = 0;
                virtual bool disconnection() = 0;
        };
    }
}

#endif /* !INETWORK_API_HPP_ */