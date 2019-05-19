#ifndef REMOTE_H
#define REMOTE_H

#include <IRremote.h>

class Remote
{
private:
  IRrecv m_irrecv;
  decode_results m_results;
  void reset();

public:
  Remote(uint8_t pin);
  void init();
  void update();
  bool powerPressed() const;
  bool volumeUpPressed() const;
  bool volumeDownPressed() const;
  bool mutePressed() const;
  bool channelUpPressed() const;
  bool channelDownPressed() const;
  bool selectPressed() const;
  bool zeroPressed() const;
  bool onePressed() const;
  bool twoPressed() const;
  bool threePressed() const;
  bool fourPressed() const;
  bool fivePressed() const;
  bool sixPressed() const;
  bool sevenPressed() const;
  bool eightPressed() const;
  bool ninePressed() const;
};

#endif
