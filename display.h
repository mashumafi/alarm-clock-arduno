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

  Timer m_show;

public:
  Display();
  void update();
  void useClock(const Clock &clock);
  template<typename Pin>
  void useLight(const Pin &light)
  {
    m_sevseg.setBrightness(light.getBrightness());
  }
  void useVolume(const Volume &volume);
};

#endif
