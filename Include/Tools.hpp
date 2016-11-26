#ifndef TOOLS_HPP_
# define TOOLS_HPP_

# include <cstdlib>
# include <iomanip>
# include <sstream>
# include <cstring>

namespace Tools
{
    namespace Function
    {
        template <typename T>
        std::string to_string(const T& value)
        {
            std::stringstream   ss;
            
            ss << value;
            return ss.str();
        }
    }
}

#endif /* !TOOLS_HPP_ */