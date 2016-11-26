#include <algorithm>
#include <functional>
#include <cstdlib>
#include <cmath>
#include "NetworkMBEDApp.hh"
#include "Joystick.hh"
#include "Speaker.hh"
#include "TemperatureSensor.hpp"
#include "RGBLED.hh"
#include "IGUI.hh"
#include "MQTTClientAPI.hh"
#include "Tools.hpp"

namespace App
{
    NetworkMBEDApp::NetworkMBEDApp(GUI::IGUI *gui) :
        _gui(gui),
        _networkAPI(new Network::API::MQTTClientAPI(
                    "doughnut.kent.ac.uk", 1883,
                    "unikent/users/abc123/mysensor/temperature", "fnp2ID", 
                    "fnp2Sender", "123passwd")),
        _sw2Int(PTC6),
        _sw3Int(PTA4),
        _sw2IntTrig(false),
        _sw3IntTrig(false),
        _timer(2),
        _timerMinState(FIRST_HALF)
    {
        _devices["Temperature"] = new MBED::Device::Sensor::TemperatureSensor<>;
        _devices["Joystick"] = new MBED::Device::Joystick;
        _devices["RGBLED"] = new MBED::Device::RGBLED;
        _devices["Speaker"] = new MBED::Device::Speaker;
    }
    
    NetworkMBEDApp::~NetworkMBEDApp()
    {
        delete _networkAPI;
        std::for_each(_devices.begin(),
                    _devices.end(),
                    std::bind1st(std::mem_fun(&NetworkMBEDApp::eraseDevice), 
                                                this));
    }
    
    bool NetworkMBEDApp::init()
    {
        if (!_networkAPI->connection())
            return false;
        _gui->init();
        wait(2.0);
        _gui->clear();
        setRGBLED(1);
        _sw2Int.mode(PullUp);
        _sw2Int.fall(this, &NetworkMBEDApp::sw2Interrupt);
        _sw3Int.mode(PullUp);
        _sw3Int.fall(this, &NetworkMBEDApp::sw3Interrupt);
        _timer.reset();
        setRGBLED(0);
        return true;
    }
    
    void NetworkMBEDApp::run()
    {
        while (1)
        {
            triggerEvent();
            executeMainActivity();
            timerIsOver();
        }
    }
    
    bool NetworkMBEDApp::close()
    {
        _gui->close();
        _gui = NULL;
        return _networkAPI->disconnection();
    }
    
    void NetworkMBEDApp::sw2Interrupt() { _sw2IntTrig = true; }
    void NetworkMBEDApp::sw3Interrupt() { _sw3IntTrig = true; }
    
    void 
    NetworkMBEDApp::eraseDevice(std::pair<std::string, MBED::Device::IDevice *> pair) const
    {
        delete pair.second;
    }
    
    void NetworkMBEDApp::triggerEvent()
    {
        if (_sw2IntTrig)
            switchSpeakerOperation();
        else if (_sw3IntTrig)
            showSpeakerStatus();
    }
    
    void NetworkMBEDApp::executeMainActivity()
    {
        std::string resultTemperature = _devices["Temperature"]->execute();
        std::string resultJoystick = _devices["Joystick"]->execute();
     
        changeTimer(resultJoystick);
        _gui->display(resultTemperature);
        wait(2.0);
        _gui->clear();
        if (_timerMinState != NO_TIMER)
            catchTemperature(extractDegreeFromResult(resultTemperature));
    }
    
    void NetworkMBEDApp::timerIsOver()
    {
        if (_timer.isFinished() && _devices["Speaker"]->getState() == 0)
        {
            if (!_networkAPI->sendData(Tools::Function::to_string(
                    _temperatureManager.getAverageTemperature())))
                #ifdef DEBUG_VERSION
                    gui->display("Data hasn't been\n");
                    gui->display("sended correctly");
                    wait(2.0);
                    gui->clear();
                #endif
            _gui->display("Time's up");
            _devices["Speaker"]->execute();
            _gui->clear();
            _timer.reset();
            _temperatureManager.reset();
            _timerMinState = FIRST_HALF;
        }
    }
    
    void NetworkMBEDApp::switchSpeakerOperation()
    {
        _devices["Speaker"]->setState(!_devices["Speaker"]->getState());
        setRGBLED(!_devices["Speaker"]->getState() ? 0 : 2);
        if (_devices["Speaker"]->getState() == 0)
        {
            _gui->display("Speaker activated");
            _timer.reset();
            _temperatureManager.reset();
            _timerMinState = FIRST_HALF;
        }
        else
        {
            _gui->display("Speaker desactivated");
            _timerMinState = NO_TIMER;
        }
        wait(2.0);
        _gui->clear();
        _sw2IntTrig = false;
    }
    
    void NetworkMBEDApp::showSpeakerStatus()
    {
        setRGBLED(1);
        _gui->display("Status speaker : \n");
        if (_devices["Speaker"]->getState() == 0)
        {   
            _gui->display("Timer max : " 
                            + Tools::Function::to_string(
                            _timer.getTimerMaxMinuteSecondFormat()) + "min\n");
            _gui->display("Elapsed time : " 
                            + Tools::Function::to_string(
                            _timer.getElapsedTimeMinuteSecondFormat()) + "min\n");
        }
        else
            _gui->display("Not activated");
        wait(2.0);
        _gui->clear();
        setRGBLED(!_devices["Speaker"]->getState() ? 0 : 2);
        _sw3IntTrig = false;
    }
    
    void NetworkMBEDApp::setRGBLED(int convertissorMode)
    {
        _devices["RGBLED"]->setDeviceMode(convertissorMode);
        _devices["RGBLED"]->execute();
    }
    
    void NetworkMBEDApp::catchTemperature(double degreeCelcius)
    {
        double  elapsedTime = _timer.getElapsedTime();
        
        if (_timerMinState == FIRST_HALF && std::fmod(elapsedTime, 60) < 30)
            _timerMinState = SECOND_HALF;
        else if (_timerMinState == SECOND_HALF 
                && std::fmod(elapsedTime, 60) >= 30)
            _timerMinState = FIRST_HALF;
        _temperatureManager.addTemperature(degreeCelcius);   
    }
    
    void NetworkMBEDApp::changeTimer(const std::string& resultJoystick)
    {
        if (resultJoystick != "")
        {
            _gui->display("The next timer is\n");
            _gui->display(getRightChangeTimerMsg(resultJoystick));
            wait(2.0);
            _gui->clear();
        }
    }
    
    std::string NetworkMBEDApp::getRightChangeTimerMsg(const std::string& resultJoystick)
    {
        if (resultJoystick == "Joystick up")
            return _timer.addNextTimerMax() ? 
                    "incremented" : "not incremented\n(limit : " 
                                    + Tools::Function::to_string(
                                    _timer.getHighestTimerMax()) 
                                    + "min)";
        else if (resultJoystick == "Joystick down")
            return _timer.subNextTimerMax() ?
                    "decremented" : "not decremented\n(limit : "
                                    + Tools::Function::to_string(
                                    _timer.getSmallestTimerMax())
                                    + "min)";
        else
            return "";
    }
    
    double 
    NetworkMBEDApp::extractDegreeFromResult(const std::string& resultTemperature) const
    {
        std::size_t found = resultTemperature.find_first_of('\n');
        
        return found == std::string::npos ? 
                0.0 : std::atof(resultTemperature.substr(found).c_str());
    }
}