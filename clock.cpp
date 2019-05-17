#include "clock.h"

#include <avr/pgmspace.h>

const unsigned long ONE_SECOND = 1000;

const size_t ALARM_COUNT = 10;
const PROGMEM Alarm ALARMS[ALARM_COUNT];

Clock::Clock():
  m_hour(12),
  m_minute(34),
  m_second(0),
  m_alarm(false) {
}

void Clock::useRemote(const Remote& remote) {
}

void Clock::update() {
  m_alarm = false;
  while (m_timer.countdown(ONE_SECOND)) {
    if (addSecond()) {
      for (size_t i = 0; i < ALARM_COUNT; i++) {
        if (ALARMS[i].m_enabled && ALARMS[i].toInt() == toInt()) {
          m_alarm = true;
          break;
        }
      }
    }
  }
}

bool Clock::addSecond() {
  m_second++;
  if (m_second == 60) {
    m_minute++;
    m_second = 0;
    if (m_minute == 60) {
      m_hour++;
      m_minute = 0;
      if (m_hour >= 24) {
        m_hour = 0;
      }
    }
    return true;
  }
  return false;
}

int Clock::toInt() const {
  return m_hour * 100 + m_minute;
}

bool Clock::alarm() const {
  return m_alarm;
}
