#include "buzzer.h"

Buzzer::Buzzer(uint8_t pin) : m_pin(pin),
                              m_beeping(false)
{
  pinMode(m_pin, OUTPUT);
}

void Buzzer::setBeeping(bool beeping)
{
  m_beeping = beeping;
  m_index = 0;
  m_timer.reset();
  noTone(m_pin);
}

void Buzzer::useClock(const Clock &clock)
{
  if (clock.alarm())
  {
    setBeeping(true);
  }
}

void Buzzer::useRemote(const Remote &remote)
{
  if (remote.powerPressed())
  {
    setBeeping(!m_beeping);
  }
}

void Buzzer::useVolume(const Volume &volume)
{
  if (m_beeping)
  {
    if (m_timer.countdown(m_sequence[m_index].duration))
    {
      m_index = (m_index + 1) % (COUNT);
      uint32_t frequency = m_sequence[m_index].frequency * volume.getValue();
      if (frequency)
      {
        tone(m_pin, frequency);
      }
      else
      {
        noTone(m_pin);
      }
    }
  }
}
