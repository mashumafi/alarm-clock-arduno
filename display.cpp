#include "display.h"

Display::Display()
{
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = true;
  byte hardwareConfig = COMMON_CATHODE;
  bool updateWithDelays = true;
  bool leadingZeros = true;
  bool disableDecPoint = false;

  m_sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
                 updateWithDelays, leadingZeros, disableDecPoint);
}

void Display::update()
{
  if (m_show.countdown(16))
  {
    m_sevseg.refreshDisplay();
  }
}

void Display::useClock(const Clock &clock)
{
  if (TIME == m_state)
  {
    m_sevseg.setChars(clock.getChars());
  }
}

void Display::useVolume(const Volume &volume)
{
  if (volume.changed())
  {
    char str[4] = {' ', ' ', ' ', ' '};
    byte index = 0;
    byte level = volume.getLevel();
    for (; level >= 2; level -= 2)
    {
      str[index] = 'O';
      index++;
    }
    if (level == 1)
    {
      str[index] = 'I';
    }
    m_sevseg.setChars(str);
    m_state = VOLUME;
  }
  else
  {
    m_state = TIME;
  }
}
