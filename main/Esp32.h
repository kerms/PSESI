/*************************************************************************************************
Parent class for Neck and Wrist
*************************************************************************************************/

#ifndef DEF_ESP32
#define DEF_ESP32
#define MAX_WAIT_FOR_TIMER 10


class Esp32{
public:


static unsigned int waitFor(unsigned long *timer, unsigned long period){  //Wait for a certain amount of time and return the number of perdiod it had run between two executions. period in microseconds and timer the number of timer. From Franck Wajsbürt
  //static unsigned long waitForTimer[MAX_WAIT_FOR_TIMER];
  unsigned long newTime = micros() / period;
  int delta = newTime - *timer;
  if ( delta < 0 ) delta += 1 + (0xFFFFFFFF / period);
  if ( delta ) *timer = newTime;
  //Serial.println(delta);
  return delta;
}

virtual std::string toString()=0;


};

#endif