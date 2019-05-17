#ifndef VOLUME_H
#define VOLUME_H

#include "remote.h"
#include "timer.h"

class Volume {
  private:
    uint16_t m_level;
    bool m_changed;
    Timer m_timer;
  public:
    Volume();
    uint16_t getValue() const;
    uint16_t getLevel() const;
    void useRemote(const Remote& remote);
    bool changed() const;
};

#endif
