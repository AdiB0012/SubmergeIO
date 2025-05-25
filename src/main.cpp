#include <Arduino.h>
#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define IN1 18
#define IN2 19
#define ENA 23
#define PWM_CHANNEL 0

const int pwmFreq = 30000;
const int pwmResolution = 8;

int pwmDutyCicle = 170;

BluetoothSerial SerialBT;

void setupPWM();
void setupPins();
void handleBluetoothInput(String input);

void setup()
{
    Serial.begin(115200);
    SerialBT.begin("ESP32_BT");
    Serial.println("The device started, now you can pair it with bluetooth!");

    setupPins();
    setupPWM(); 
}

void loop() {
    if (SerialBT.available()) {
        String command = SerialBT.readStringUntil('\n');
        handleBluetoothInput(command);
    }
}

void setupPWM() {
    ledcSetup((uint8_t)PWM_CHANNEL, pwmFreq, pwmResolution);
    ledcAttachPin(ENA, (uint8_t)PWM_CHANNEL);
    ledcWrite((uint8_t)PWM_CHANNEL, pwmDutyCicle);
}

void setupPins()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENA, OUTPUT);
}

void handleBluetoothInput(String input) {
    Serial.print("Received: ");
    Serial.println(input);

    char direction = input.charAt(0);
    int speed = input.substring(2).toInt();

    if (speed < 0) {
        speed = 0;
    }
    else if (speed > 255) {
        speed = 255;
    }
    else {
        ledcWrite((uint8_t)PWM_CHANNEL, speed);
        Serial.println(speed);
    }

    if (direction == 'F') {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
    }
    else if (direction == 'B') {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
    }
}
