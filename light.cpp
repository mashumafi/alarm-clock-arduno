#include "light.h"

Light::Light(uint8_t input) : m_input(input)
{
  pinMode(m_input, INPUT);
}

uint8_t Light::getBrightness() const
{
  return map(analogRead(m_input), 0, 1024, 0, 100);
}
