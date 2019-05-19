#ifndef TIMER_H
#define TIMER_H

class Timer
{
private:
  unsigned long m_time;

public:
  Timer();
  void reset();
  bool countdown(unsigned long ms);
};

#endif
