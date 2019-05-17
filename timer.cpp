#include "timer.h"

#include <Arduino.h>

Timer::Timer() {
  reset();
}

void Timer::reset() {
  m_time = millis();
}

bool Timer::countdown(unsigned long ms) {
  unsigned long current = millis();
  unsigned long diff = current - m_time;
  if (diff >= ms) {
    m_time = current + (diff - ms);
    return true;
  }
  return false;
}
