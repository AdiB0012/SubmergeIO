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
    bool isInitialized = false;

    if (m_serialBt.begin("ESP32_ProjectX"))
    {
        isInitialized = true;
    }

    return isInitialized;
}

bool BluetoothClassic::connect(const char* deviceName)
{
}

void BluetoothClassic::disconnect()
{
    if (m_connected)
    {
        m_serialBt.end();
        m_connected = false;
    }
}

bool BluetoothClassic::send(const char* data)
{
    if (!m_connected)
        m_connected = m_serialBt.hasClient();

    if (m_connected)
    {
        m_serialBt.println(data);
    }
}

int BluetoothClassic::receive(char* buffer)
{
    int length;

    if (!m_connected)
        m_connected = m_serialBt.hasClient();

    if (m_serialBt.available())
    {
        String command = m_serialBt.readStringUntil('\n');
        length = command.length();
        command.toCharArray(buffer, length + 1);
        buffer[length] = '\0';

        Serial.printf("Received: %s\n", buffer);
    }
    
    return length;
}
