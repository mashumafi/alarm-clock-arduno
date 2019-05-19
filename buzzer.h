#ifndef BUZZER_H
#define BUZZER_H

#include "clock.h"
#include "remote.h"
#include "timer.h"
#include "volume.h"

#include <Arduino.h>

struct Sequence
{
  const uint32_t frequency;
  const uint64_t duration;
};

namespace
{
#define FREQUENCY 64
#define DURATION 150
#define SLEEP 1000
} // namespace

class Buzzer
{
private:
  uint8_t m_pin;
  bool m_beeping;
  const Sequence m_sequence[6] = {{FREQUENCY, DURATION}, {0, DURATION}, {FREQUENCY, DURATION}, {0, DURATION}, {FREQUENCY, DURATION}, {0, SLEEP}};
  static const size_t COUNT = sizeof(m_sequence) / sizeof(Sequence);
  size_t m_index;
  Timer m_timer;

  void setBeeping(bool on);

public:
  Buzzer(uint8_t pin);
  void useClock(const Clock &clock);
  void useVolume(const Volume &volume);
};

#endif
