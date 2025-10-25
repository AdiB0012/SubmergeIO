#pragma once

#include "BluetoothBle.hpp"
#include "BluetoothClassic.hpp"
#include "IBluetooth.hpp"

enum class BluetoothType
{
    Classic,
    BLE
};

class BluetoothFactory
{
public:
    static IBluetooth* create(BluetoothType btType)
    {
        if (BluetoothType::Classic == btType)
        {
            return new BluetoothClassic();
        }
        else
        {
            return new BluetoothBle();
        }
    }
};
