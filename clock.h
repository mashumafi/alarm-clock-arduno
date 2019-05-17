#ifndef CLOCK_H
#define CLOCK_H

#include "remote.h"
#include "timer.h"

struct Alarm {
  bool m_enabled;
  uint8_t m_hour;
  uint8_t m_minute;

  Alarm():
    m_enabled(false),
    m_hour(0),
    m_minute(0) {
  }

  int toInt() const {
    return m_hour * 100 + m_minute;
  }
};

class Clock {
  private:
    Timer m_timer;
    uint8_t m_hour;
    uint8_t m_minute;
    uint8_t m_second;
    bool m_alarm;

    bool addSecond();
  public:
    Clock();
    void useRemote(const Remote& remote);
    void update();
    int toInt() const;
    bool alarm() const;
};

#endif
