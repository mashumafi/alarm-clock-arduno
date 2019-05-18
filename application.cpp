#include "application.h"

const uint8_t BUZZER_PIN = A0;
const uint8_t LIGHT_OUTPUT = A5;
const uint8_t LIGHT_INPUT = A4;
const uint8_t REMOTE_PIN = A2;

Application::Application() :
  m_buzzer(BUZZER_PIN),
  m_clock(),
  m_light(LIGHT_OUTPUT, LIGHT_INPUT),
  m_remote(REMOTE_PIN) {
}

void Application::init() {
  m_remote.init();
}

void Application::update() {
  // update inputs
  m_remote.update();

  m_clock.useRemote(m_remote);
  m_clock.update();

  m_volume.useRemote(m_remote);

  // update outputs
  m_buzzer.useClock(m_clock);
  m_buzzer.useRemote(m_remote);
  m_buzzer.useVolume(m_volume);

  m_display.useClock(m_clock);
  m_display.useLight(m_light);
  m_display.useVolume(m_volume);
  m_display.update();
}
