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
    int8_t m_edit;
    char m_chars[4];
    Alarm m_snooze;

    bool addSecond();
    int toInt() const;
  public:
    Clock();
    void useRemote(const Remote& remote);
    void update();
    char const* getChars() const;
    bool alarm() const;
};

#endif
