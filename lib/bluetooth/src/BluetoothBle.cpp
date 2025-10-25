#include <Arduino.h>
#include "BluetoothClassic.hpp"

BluetoothClassic::BluetoothClassic() 
    : m_connected(false) {}

BluetoothClassic::~BluetoothClassic() 
{
    disconnect();
}

bool BluetoothClassic::begin()
{
    return false;
}

bool BluetoothClassic::connect(const char* deviceName)
{
    return false;
}

void BluetoothClassic::disconnect()
{
}

bool BluetoothClassic::send(const char* data)
{
    return false;
}

int BluetoothClassic::receive(char* buffer)
{
    return 0;
}
