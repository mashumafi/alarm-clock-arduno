#include "volume.h"

Volume::Volume():
  m_level(4) {
}

uint16_t Volume::getLevel() const {
  return m_level;
}

uint16_t Volume::getValue() const {
  return 1 << m_level;
}

void Volume::useRemote(const Remote& remote) {
  if (remote.volumeUpPressed()) {
    m_level = min(8, m_level + 1);
  } else if (remote.volumeDownPressed()) {
    m_level = max(1, m_level - 1);
  } else {
    if (m_timer.countdown(1000)) {
      m_changed = false;
    }
    return;
  }
  m_changed = true;
  m_timer.reset();
}

bool Volume::changed() const {
  return m_changed;
}
