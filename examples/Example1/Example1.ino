#include <Arduino.h>
#include <Device.hpp>

// Define a simple LED device class
class LEDDevice
{
public:
    LEDDevice(int pin) : ledPin(pin) {}

    void setup()
    {
        pinMode(ledPin, OUTPUT);
        digitalWrite(ledPin, LOW);
    }

    void turnOn()
    {
        digitalWrite(ledPin, HIGH);
    }

    void turnOff()
    {
        digitalWrite(ledPin, LOW);
    }

    String getState()
    {
        return digitalRead(ledPin) == HIGH ? "On" : "Off";
    }

private:
    int ledPin;
};

LEDDevice led(13); // Using the built-in LED on pin 13
Device<LEDDevice> *myDevice = nullptr;

void setup()
{
    // Device Information
    Information info(1, "LED Device", "Device-Model", "Arduino", "A simple LED device");

    // Device Properties
    std::list<Property<LEDDevice>> properties;
    properties.push_back(Property("State", "LED State", "string", &LEDDevice::getState));

    // Device Actions
    std::list<Action<LEDDevice>> actions;
    actions.push_back(Action("Turn On", "Turns on the LED", &LEDDevice::turnOn));
    actions.push_back(Action("Turn Off", "Turns off the LED", &LEDDevice::turnOff));

    // Create the Device object
    myDevice = new Device<LEDDevice>(info, properties, actions);

    // Setup the LED device
    led.setup();

    // Start serial communication
    Serial.begin(115200);
}

void loop()
{
    static String receivedCommand = "";
    while (Serial.available() > 0)
    {
        char incomingChar = (char)Serial.read();

        if (incomingChar == '\n')
        {
            myDevice->processIncomingCommand(receivedCommand, led);
            receivedCommand = "";
        }
        else
        {
            receivedCommand += incomingChar;
        }
    }
}
