#include "remote.h"

const uint32_t POWER = 0xFFA25D;
const uint32_t VOLUME_UP = 0xFF906F;
const uint32_t VOLUME_DOWN = 0xFFA857;
const uint32_t CHANNEL_UP = 0x1;
const uint32_t CHANNEL_DOWN = 0x1;
const uint32_t ZERO = 0x1;
const uint32_t ONE = 0x1;
const uint32_t TWO = 0x1;
const uint32_t THREE = 0x1;
const uint32_t FOUR = 0x1;
const uint32_t FIVE = 0x1;
const uint32_t SIX = 0x1;
const uint32_t SEVEN = 0x1;
const uint32_t EIGHT = 0x1;
const uint32_t NINE = 0x1;

Remote::Remote(uint8_t pin) : m_irrecv(pin) {
  memset(&m_results, 0, sizeof(decode_results));
  m_irrecv.enableIRIn();
  m_irrecv.blink13(true);
}

void Remote::update() {
  if (m_irrecv.decode(&m_results)) {
    Serial.println(m_results.value, HEX);
    m_irrecv.resume();
  } else if (m_results.value) {
    memset(&m_results, 0, sizeof(decode_results));
  }
}

bool Remote::powerPressed() const {
  return POWER == m_results.value;
}

bool Remote::volumeUpPressed() const {
  return VOLUME_UP == m_results.value;
}

bool Remote::volumeDownPressed() const {
  return VOLUME_DOWN == m_results.value;
}

bool Remote::channelUpPressed() const {
  return CHANNEL_UP == m_results.value;
}

bool Remote::channelDownPressed() const {
  return CHANNEL_DOWN == m_results.value;
}

bool Remote::zeroPressed() const {
  return ZERO == m_results.value;
}

bool Remote::onePressed() const {
  return ONE == m_results.value;
}

bool Remote::twoPressed() const {
  return TWO == m_results.value;
}

bool Remote::threePressed() const {
  return THREE == m_results.value;
}

bool Remote::fourPressed() const {
  return FOUR == m_results.value;
}

bool Remote::fivePressed() const {
  return FIVE == m_results.value;
}

bool Remote::sixPressed() const {
  return SIX == m_results.value;
}

bool Remote::sevenPressed() const {
  return SEVEN == m_results.value;
}

bool Remote::eightPressed() const {
  return EIGHT == m_results.value;
}

bool Remote::ninePressed() const {
  return NINE == m_results.value;
}
