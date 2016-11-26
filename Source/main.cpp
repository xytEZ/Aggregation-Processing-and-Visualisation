#include <iostream>
#include "mbed.h"
#include "LCDGUI.hh"
#include "MBEDApp.hh"
#include "NetworkMBEDApp.hh"

//#define DEBUG_VERSION

bool execute_app(App::IApp *&app)
{
    if (!app->init())
        return false;
    app->run();
    return app->close();
}

int main()
{
    GUI::IGUI   *gui = new GUI::LCDGUI();
    //App::IApp   *app = new App::MBEDApp(gui);
    App::IApp   *app = new App::NetworkMBEDApp(gui);

    if (!execute_app(app))
    #ifdef DEBUG_VERSION
        gui->display("An error is occurred\n");
        gui->display("during the program");
    #endif
    delete app;
    delete gui;
}