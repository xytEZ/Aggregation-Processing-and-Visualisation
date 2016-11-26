#include "LCDGUI.hh"

namespace GUI
{
    LCDGUI::LCDGUI() : _lcd(D11, D13, D12, D7, D10) { }
    LCDGUI::~LCDGUI() { }
    
    void LCDGUI::init()
    {
        clear();
        display(" Author : Fabien PHAM\n");
        display(" Login : fnp2\n");
        //display(" Project name : fnp2_a3\n");
        display(" Project name : fnp2_a5\n");
        wait(2.0);
        clear();
        /*display("Device available :\n");
        display("Accelerometer, RGB,\n");
        display("Temperature, Joystick");*/
        display("Use of Speaker, RGB, \n");
        display("Temperature, Joystick \n");
        display("and MQTT protocol");
    }
    
    void LCDGUI::display(const std::string& msg) { _lcd.printf(msg.c_str()); }
    
    void LCDGUI::clear()
    {
        _lcd.cls();
        _lcd.locate(0, 3);
    }
    
    void LCDGUI::close()
    {
        clear();
        display("\n");
        display("Good bye !!!");
    }
}