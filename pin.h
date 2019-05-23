#include <Arduino.h>

template <uint8_t pin, uint8_t mode>
class Pin
{
public:
    static void pinMode()
    {
        ::pinMode(pin, mode);
    }

    operator uint8_t() const
    {
        return pin;
    }
};

template <uint8_t pin>
class InputDigitalPin : public Pin<pin, INPUT>
{
public:
    static uint8_t digitalRead()
    {
        return ::digitalRead(pin);
    }
};

template <uint8_t pin>
class OutputDigitalPin : public Pin<pin, OUTPUT>
{
public:
    static void digitalWrite(uint8_t val)
    {
        ::digitalWrite(pin, val);
    }
};

template <uint8_t pin>
class InputAnalogPin : public InputDigitalPin<pin>
{
public:
    static int analogRead()
    {
        return ::analogRead(pin);
    }
};

template <uint8_t pin>
class OutputAnalogPin : public OutputDigitalPin<pin>
{
public:
    static void analogWrite(int val)
    {
        ::analogWrite(pin, val);
    }
};