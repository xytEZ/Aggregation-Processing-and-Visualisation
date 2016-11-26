#include <algorithm>
#include <functional>
#include <cstddef>
#include "MBEDApp.hh"
#include "AccelerometerSensor.hh"
#include "TemperatureSensor.hpp"
#include "Joystick.hh"
#include "RGBLED.hh"
#include "IGUI.hh"

namespace App
{
    MBEDApp::MBEDApp(GUI::IGUI *gui) :
        _gui(gui),
        _sw2Int(PTC6),
        _sw3Int(PTA4),
        _sw2IntTrig(false),
        _sw3IntTrig(false),
        _indexDevice(0),
        _modeDevice(0)
    {
        _devices.push_back(new MBED::Device::Sensor::AccelerometerSensor);
        _devices.push_back(new MBED::Device::Sensor::TemperatureSensor<>);
        _devices.push_back(new MBED::Device::Joystick);
        _devices.push_back(new MBED::Device::RGBLED);
    }
    
    MBEDApp::~MBEDApp()
    {
        std::for_each(_devices.begin(),
                    _devices.end(),
                    std::bind1st(std::mem_fun(&MBEDApp::eraseDevice), this));
    }
    
    bool MBEDApp::init()
    {
        _gui->init();
        wait(2.0);
        _gui->clear();
        _gui->display("Currently used device :\n");
        _gui->display("\"" + _devices[_indexDevice]->getDeviceName() + "\"");
        setRGBLED();
        wait(2.0);
        _gui->clear();
        _sw2Int.mode(PullUp);
        _sw2Int.fall(this, &MBEDApp::sw2Interrupt);
        _sw3Int.mode(PullUp);
        _sw3Int.fall(this, &MBEDApp::sw3Interrupt);
        return true;
    }
    
    void MBEDApp::run()
    {   
        while (1)
        {
            triggerDeviceEvent();
            performInteractionWithDevice();
        }
    }
    
    bool MBEDApp::close()
    {
        _gui->close();
        _gui = NULL;
        return true;
    }
    
    void MBEDApp::sw2Interrupt() { _sw2IntTrig = true; }
    void MBEDApp::sw3Interrupt() { _sw3IntTrig = true; }
    void MBEDApp::eraseDevice(MBED::Device::IDevice *device) const { delete device; }

    void MBEDApp::triggerDeviceEvent()
    {
        if (_sw2IntTrig)
            setDevice();
        else if (_sw3IntTrig)
            setDeviceMode();
    }
    
    void MBEDApp::performInteractionWithDevice()
    {
        _gui->display(_devices[_indexDevice]->execute());
        wait(adaptatingDisplayBySpecificDevice());
        _gui->clear();
    }
    
    float MBEDApp::adaptatingDisplayBySpecificDevice() const
    {
        return _devices[_indexDevice]->getDeviceName() == "Accelerometer"
                || _devices[_indexDevice]->getDeviceName() == "Joystick" ?
                0.250 : 1.0;
    }

    void MBEDApp::setDevice()
    {
        ++_indexDevice;
        if (_indexDevice == _devices.size() - 1)
            _indexDevice = 0;
        _modeDevice = 0;
        _gui->display("New device used :\n\"" + _devices[_indexDevice]->getDeviceName() + "\"");
        setRGBLED();
        wait(2.0);
        _gui->clear();
        _sw2IntTrig = false;
    }
    
    void MBEDApp::setDeviceMode()
    {
        if (_devices[_indexDevice]->getNbDeviceMode() == 1)
        {
            _gui->display("No mode exist for :\n\"" + _devices[_indexDevice]->getDeviceName() + "\"");
            wait(2.0);
            _gui->clear(); 
        }
        else
        {
            ++_modeDevice;
            if (_modeDevice == _devices[_indexDevice]->getNbDeviceMode())
                _modeDevice = 0;
            _devices[_indexDevice]->setDeviceMode(_modeDevice);
        }
        _sw3IntTrig = false;
    }
    
    void MBEDApp::setRGBLED()
    {
        if (_devices[_indexDevice]->getDeviceName() == "Accelerometer")
            _devices[_devices.size() - 1]->setDeviceMode(0);
        else if (_devices[_indexDevice]->getDeviceName() == "Temperature")
            _devices[_devices.size() - 1]->setDeviceMode(1);
        else if (_devices[_indexDevice]->getDeviceName() == "Joystick")
            _devices[_devices.size() - 1]->setDeviceMode(2);
        _devices[_devices.size() - 1]->execute();
    }
}