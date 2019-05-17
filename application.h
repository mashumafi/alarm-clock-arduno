#ifndef APPLICATION_H
#define APPLICATION_H

#include "buzzer.h"
#include "clock.h"
#include "display.h"
#include "light.h"
#include "remote.h"
#include "volume.h"

class Application {
  private:
    Buzzer m_buzzer;
    Clock m_clock;
    Display m_display;
    Light m_light;
    Remote m_remote;
    Volume m_volume;
  public:
    Application();
    void update();
};

#endif
