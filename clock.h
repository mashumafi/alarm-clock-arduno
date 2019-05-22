#ifndef CLOCK_H
#define CLOCK_H

#include "remote.h"
#include "timer.h"

struct Time
{
  uint8_t m_hour;
  uint8_t m_minute;

  Time() : m_hour(0),
           m_minute(0)
  {
  }

  Time(uint8_t hour, uint8_t minute) : m_hour(hour),
                                       m_minute(minute)
  {
  }

  int toInt() const
  {
    return m_hour * 100 + m_minute;
  }

  uint16_t addMinutes(uint16_t p_minutes)
  {
    uint16_t minutes = m_minute + p_minutes;
    m_minute = minutes % 60;
    uint16_t hours = m_hour + minutes / 60;
    m_hour = hours % 24;
    return hours / 24;
  }

  bool operator<(const Time &other)
  {
    return m_hour < other.m_hour || (m_hour == other.m_hour && m_minute < other.m_minute);
  }
};

struct Alarm
{
  uint8_t m_enabled;
  Time m_time;

  Alarm() : m_enabled(false)
  {
  }
};

class Clock
{
private:
  Timer m_timer;
  Time m_time;
  uint8_t m_second;
  bool m_alarm;
  int8_t m_edit;
  char m_chars[4];
  uint8_t m_channel;

  static const size_t ALARM_COUNT = 10;
  Alarm m_alarms[ALARM_COUNT];
  Alarm m_snooze;

  Timer m_state;
  bool m_show_state;

  bool m_set;
  bool m_blink;
  Timer m_blink_timer;

  Timer m_home_timer;

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
