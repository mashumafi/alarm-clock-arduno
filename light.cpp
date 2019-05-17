#include "light.h"

Light::Light(uint8_t output, uint8_t input) :
  m_output(output),
  m_input(input) {
  pinMode(m_output, OUTPUT);
  digitalWrite(m_output, HIGH);
  pinMode(m_input, INPUT);
}

uint8_t Light::getBrightness() const {
  return map(analogRead(m_input), 0, 1024, 0, 100);
}
