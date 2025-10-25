#pragma once

class IBluetooth
{
public:
    virtual ~IBluetooth() {}

    virtual bool begin() = 0;
    virtual bool connect(const char* deviceName) = 0;
    virtual void disconnect() = 0;
    virtual bool send(const char* data) = 0;
    virtual int receive(char* buffer) = 0;
};