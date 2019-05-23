#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>

template <typename InputDigitalPin>
class Light
{
public:
  Light()
  {
    InputDigitalPin::pinMode();
  }

  uint8_t getBrightness() const
  {
    return map(InputDigitalPin::analogRead(), 0, 1024, 0, 100);
  }
};

#endif
