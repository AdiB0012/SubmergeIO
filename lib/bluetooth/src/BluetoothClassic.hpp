#pragma once

#include <BluetoothSerial.h>
#include "IBluetooth.hpp"

class BluetoothClassic : public IBluetooth
{
public:
    bool begin() override;
    bool connect(const char* deviceName) override;
    void disconnect() override;
    bool send(const char* data) override;
    int receive(char* buffer) override;
    
private:
    BluetoothSerial m_serialBt;
    bool m_connected;
};