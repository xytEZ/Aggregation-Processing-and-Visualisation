#ifndef IGUI_HH_
# define IGUI_HH_

# include <string>

namespace GUI
{
    class IGUI
    {
        public :
            virtual ~IGUI() { }
            virtual void init() = 0;
            virtual void display(const std::string&) = 0;
            virtual void clear() = 0;
            virtual void close() = 0;
    };
}

#endif /* !IGUI_HH_ */