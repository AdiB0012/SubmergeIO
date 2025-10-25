#include "MotorDriver.hpp"

MotorDriver::MotorDriver(uint8_t in1, uint8_t in2, uint8_t ena, uint8_t pwmChannel)
    : m_in1(in1), m_in2(in2), m_ena(ena), m_pwmChannel(pwmChannel) {}

void MotorDriver::begin()
{
    pinMode(m_in1, OUTPUT);
    pinMode(m_in2, OUTPUT);
    pinMode(m_ena, OUTPUT);

    ledcSetup(m_pwmChannel, PWM_FREQ, PWM_RES);
    ledcAttachPin(m_ena, m_pwmChannel);
    ledcWrite(m_pwmChannel, PWM_DUTY_CICLE);
}

void MotorDriver::setSpeed(uint8_t speed)
{
    ledcWrite(m_pwmChannel, speed);
}

void MotorDriver::setDirection(Direction direction)
{
    switch(direction)
    {
        case Direction::FORWARD:
            digitalWrite(m_in1, HIGH);
            digitalWrite(m_in2, LOW);
            break;

        case Direction::BACKWARD:
            digitalWrite(m_in1, LOW);
            digitalWrite(m_in2, HIGH);
            break;

        default:
            break;
    }
}

void MotorDriver::stop()
{
    digitalWrite(m_in1, LOW);
    digitalWrite(m_in2, LOW);
}