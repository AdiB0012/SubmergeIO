#pragma once

#include "IBluetooth.hpp"

class BluetoothBle : public IBluetooth
{
public:
    bool begin() override;
    bool connect(const char* deviceName) override;
    void disconnect() override;
    bool send(const char* data) override;
    int receive(char* buffer) override;

private:
    bool m_connected;
};