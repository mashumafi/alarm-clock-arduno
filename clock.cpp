#include "clock.h"

#include <avr/pgmspace.h>
#include <EEPROM.h>

const unsigned long ONE_SECOND = 1000;

Clock::Clock() : m_hour(0),
                 m_minute(0),
                 m_second(0),
                 m_alarm(false),
                 m_edit(0),
                 m_channel(0),
                 m_show_state(false),
                 m_set(false),
                 m_blink(false)
{
}

void Clock::init()
{
  EEPROM.get(0, m_alarms);
  pinMode(A1, OUTPUT);
}

bool buttonToInt(const Remote &remote, uint8_t &button)
{
  if (remote.zeroPressed())
  {
    button = 0;
  }
  else if (remote.onePressed())
  {
    button = 1;
  }
  else if (remote.twoPressed())
  {
    button = 2;
  }
  else if (remote.threePressed())
  {
    button = 3;
  }
  else if (remote.fourPressed())
  {
    button = 4;
  }
  else if (remote.fivePressed())
  {
    button = 5;
  }
  else if (remote.sixPressed())
  {
    button = 6;
  }
  else if (remote.sevenPressed())
  {
    button = 7;
  }
  else if (remote.eightPressed())
  {
    button = 8;
  }
  else if (remote.ninePressed())
  {
    button = 9;
  }
  else
  {
    return false;
  }
  return true;
}

void Clock::useRemote(const Remote &remote)
{
  if (!m_show_state)
  {
    uint8_t btn;
    if (buttonToInt(remote, btn))
    {
      uint8_t *hour, *minute;
      if (m_channel)
      {
        hour = &m_alarms[m_channel - 1].m_hour;
        minute = &m_alarms[m_channel - 1].m_minute;
      }
      else
      {
        m_set = true;
        hour = &m_hour;
        minute = &m_minute;
      }
      switch (m_edit)
      {
      case 0:
      {
        if (btn > 2)
        {
          return;
        }
        *hour = btn * 10;
        break;
      }
      case 1:
      {
        if (btn > (*hour >= 20 ? 3 : 9))
        {
          return;
        }
        *hour = *hour + btn;
        break;
      }
      case 2:
      {
        if (btn > 5)
        {
          return;
        }
        *minute = btn * 10;
        break;
      }
      case 3:
      {
        *minute = *minute + btn;
        if (m_channel)
        {
          EEPROM.put(sizeof(Alarm) * (m_channel - 1), m_alarms[m_channel - 1]);
        }
        break;
      }
      }
      m_edit = (m_edit + 1) % 4;
    }
  }
  if (m_alarm)
  {
    if (remote.powerPressed())
    {
      m_alarm = false;
    }
    else if (remote.mutePressed())
    {
      m_alarm = false;
      m_snooze.m_enabled = true;
      m_snooze.m_hour = m_hour;
      m_snooze.m_minute = m_minute + 5;
    }
  }
  else if (m_channel)
  {
    if (remote.powerPressed())
    {
      m_alarms[m_channel - 1].m_enabled = !m_alarms[m_channel - 1].m_enabled;
      EEPROM.put(sizeof(Alarm) * (m_channel - 1), m_alarms[m_channel - 1]);
    }
  }
  if (!m_edit)
  {
    if (remote.channelDownPressed())
    {
      m_channel = (m_channel + ALARM_COUNT) % (ALARM_COUNT + 1);
    }
    else if (remote.channelUpPressed())
    {
      m_channel = (m_channel + 1) % (ALARM_COUNT + 1);
    }
    else
    {
      return;
    }
    m_show_state = true;
    m_state.reset();
  }
}

void Clock::update()
{
  if (m_channel)
  {
    if (m_alarms[m_channel - 1].m_enabled)
    {
      digitalWrite(A1, HIGH);
    }
    else
    {
      digitalWrite(A1, LOW);
    }
  }
  else
  {
    digitalWrite(A1, LOW);
    for (size_t i = 0; i < ALARM_COUNT; i++)
    {
      if (m_alarms[i].m_enabled && m_alarms[i].m_enabled)
      {
        digitalWrite(A1, HIGH);
        break;
      }
    }
  }
  memset(m_chars, ' ', 4);
  if (!m_set)
  {
    if (m_blink_timer.countdown(1500))
    {
      m_blink = !m_blink;
    }
    if (m_blink)
    {
      return;
    }
  }
  if (m_show_state)
  {
    if (m_state.countdown(2000))
    {
      m_show_state = false;
    }
    else
    {
      if (m_channel)
      {
        memcpy(m_chars, "al00", 4);
        m_chars[2] += m_channel / 10;
        m_chars[3] += m_channel % 10;
      }
      else
      {
        memcpy(m_chars, "ti00", 4);
      }
      return;
    }
  }
  if (m_edit != 0 && m_channel == 0)
  {
    m_second = 0;
    m_timer.reset();
  }
  while (m_timer.countdown(ONE_SECOND))
  {
    if (addSecond())
    {
      for (size_t i = 0; i < ALARM_COUNT; i++)
      {
        if (m_alarms[i].m_enabled && m_alarms[i].toInt() == toInt())
        {
          m_snooze.m_enabled = false;
          m_alarm = true;
          break;
        }
      }
      if (m_snooze.m_enabled && m_snooze.toInt() == toInt())
      {
        m_snooze.m_enabled = false;
        m_alarm = true;
      }
    }
  }

  uint8_t *hour, *minute;
  if (m_channel)
  {
    hour = &m_alarms[m_channel - 1].m_hour;
    minute = &m_alarms[m_channel - 1].m_minute;
  }
  else
  {
    hour = &m_hour;
    minute = &m_minute;
  }

  m_chars[0] = '0' + (*hour / 10);
  if (1 != m_edit)
  {
    m_chars[1] = '0' + (*hour % 10);
  }
  if (2 != m_edit)
  {
    m_chars[2] = '0' + (*minute / 10);
  }
  if (3 != m_edit)
  {
    m_chars[3] = '0' + (*minute % 10);
  }
}

bool Clock::addSecond()
{
  m_second++;
  if (m_second == 60)
  {
    m_minute++;
    m_second = 0;
    if (m_minute == 60)
    {
      m_hour++;
      m_minute = 0;
      if (m_hour == 24)
      {
        m_hour = 0;
      }
    }
    return true;
  }
  return false;
}

char const *Clock::getChars() const
{
  return m_chars;
}

int Clock::toInt() const
{
  return m_hour * 100 + m_minute;
}

bool Clock::alarm() const
{
  return m_alarm;
}
