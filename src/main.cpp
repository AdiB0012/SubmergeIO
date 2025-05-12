#include <Arduino.h>
#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define IN1 18
#define IN2 19
#define ENA 23

const int pwmFreq = 30000;
const int pwmChannel = 0;
const int pwmResolution = 8;

int pwmDutyCicle = 170;

BluetoothSerial SerialBT;

void setupPWM();
void handleBluetoothInput(String input);

void setup()
{
    Serial.begin(115200);
    SerialBT.begin("ESP32_BT");
    Serial.println("The device started, now you can pair it with bluetooth!");

    pinMode(LED_BUILTIN, OUTPUT);
    setupPWM(); 
}

void loop() {
    if (SerialBT.available()) {
        String command = SerialBT.readStringUntil('\n');
        handleBluetoothInput(command);
    }
}

void setupPWM() {
    ledcSetup(pwmChannel, pwmFreq, pwmResolution);
    ledcAttachPin(ENA, pwmChannel);
    ledcWrite(pwmChannel, pwmDutyCicle);
}

void handleBluetoothInput(String input) {
    Serial.print("Received: ");
    Serial.println(input);

    char direction = input.charAt(0);
    int speed = input.substring(2).toInt();

    if (speed < 0) speed = 0;
    if (speed > 255) speed = 255;

    if (direction == 'F') {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        //digitalWrite(LED_BUILTIN, HIGH);
        Serial.println(direction);
    }
    else if (direction == 'B') {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        //digitalWrite(LED_BUILTIN, LOW);
    }

    ledcWrite(pwmChannel, speed);
    Serial.println(speed);
}
