#include "display.h"

Display::Display() {
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

void Display::update() {
  m_sevseg.refreshDisplay();
}

void Display::useClock(const Clock& clock) {
  m_sevseg.setNumber(clock.toInt());
}

void Display::useLight(const Light& light) {
  m_sevseg.setBrightness(light.getBrightness());
}

void Display::useVolume(const Volume& volume) {
  if(volume.changed()) {
    volume.getLevel();
  }
}
