#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <Arduino.h>

class RotaryEncoder {
public:
  RotaryEncoder(int pinA, int pinB, float wheelDiameter);
  
  void begin();
  void update();
  
  float getDistance();
  float getSpeed();
  float getAcceleration();
  
private:
  int pinA_;
  int pinB_;
  float wheelDiameter_;
  
  volatile int state_;
  volatile long position_;
  volatile long prevPosition_;
  
  unsigned long prevTime_;
  
  float distance_;
  float speed_;
  float acceleration_;
};

#endif