#pragma once

#include <Arduino.h>

enum class Direction
{
    FORWARD,
    BACKWARD
};

class MotorDriver
{
public:
    MotorDriver(uint8_t in1, uint8_t in2, uint8_t ena, uint8_t pwm_channel);
    void begin();
    void setSpeed(uint8_t speed);
    void setDirection(Direction direction);
    void stop();

private:
    int8_t m_in1, m_in2, m_ena, m_pwmChannel;
    static const int PWM_FREQ = 30000;
    static const uint8_t PWM_RES = 8U;
    static const uint8_t PWM_DUTY_CICLE = 170U;
};