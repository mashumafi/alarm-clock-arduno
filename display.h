#ifndef DISPLAY_H
#define DISPLAY_H

#include "clock.h"
#include "light.h"
#include "volume.h"

#include <SevSeg.h>

class Display
{
private:
  SevSeg m_sevseg;
  enum State
  {
    TIME,
    VOLUME
  } m_state;

public:
  Display();
  void update();
  void useClock(const Clock &clock);
  void useLight(const Light &light);
  void useVolume(const Volume &volume);
};

#endif
