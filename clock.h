#ifndef CLOCK_H
#define CLOCK_H

#include "remote.h"
#include "timer.h"

struct Alarm
{
  uint8_t m_enabled;
  uint8_t m_hour;
  uint8_t m_minute;

  Alarm() : m_enabled(false),
            m_hour(0),
            m_minute(0)
  {
  }

  int toInt() const
  {
    return m_hour * 100 + m_minute;
  }
};

class Clock
{
private:
  Timer m_timer;
  uint8_t m_hour;
  uint8_t m_minute;
  uint8_t m_second;
  bool m_alarm;
  int8_t m_edit;
  char m_chars[4];
  uint8_t m_channel;

  static const size_t ALARM_COUNT = 10;
  Alarm m_alarms[ALARM_COUNT];
  Alarm m_snooze;

  bool addSecond();
  int toInt() const;

public:
  Clock();
  void init();
  void useRemote(const Remote &remote);
  void update();
  char const *getChars() const;
  bool alarm() const;
};

#endif
