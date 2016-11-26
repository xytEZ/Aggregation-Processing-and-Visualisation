#ifndef LCD_GUI_HH_
# define LCD_GUI_HH_

# include "C12832.h"
# include "IGUI.hh"

namespace GUI
{
    class LCDGUI : public IGUI
    {
        private :
            C12832  _lcd;
        
        public :
            LCDGUI();
            virtual ~LCDGUI();
            virtual void init();
            virtual void display(const std::string&);
            virtual void clear();
            virtual void close();
    };
}

#endif /* !LCD_GUI_HH_ */