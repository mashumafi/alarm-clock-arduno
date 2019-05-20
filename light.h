#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>

class Light
{
private:
  uint8_t m_input;

public:
  Light(uint8_t input);
  uint8_t getBrightness() const;
};

#endif
