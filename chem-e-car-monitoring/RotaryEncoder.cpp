#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(int pinA, int pinB, float wheelDiameter)
  : pinA_(pinA), pinB_(pinB), wheelDiameter_(wheelDiameter),
    state_(0), position_(0), prevPosition_(0),
    prevTime_(0), distance_(0), speed_(0), acceleration_(0) {
}

void IRAM_ATTR onEncoderChange() {
  static RotaryEncoder* encoderPtr = nullptr;
  
  if (encoderPtr != nullptr) {
    if (digitalRead(encoderPtr->pinB_))
      encoderPtr->position_--;
    else
      encoderPtr->position_++;
  }
}

void RotaryEncoder::begin() {
  pinMode(pinA_, INPUT_PULLUP);
  pinMode(pinB_, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(pinA_), onEncoderChange, CHANGE);
  
  prevTime_ = millis();
}

void RotaryEncoder::update() {
  unsigned long currentTime = millis();
  unsigned long deltaTime = currentTime - prevTime_;
  
  if (deltaTime >= 10) {  // Update every 10 milliseconds
    distance_ = (position_ - prevPosition_) * wheelDiameter_;
    speed_ = distance_ * 1000 / deltaTime;  // Conversion to seconds
    acceleration_ = (speed_ - speed_) * 1000 / deltaTime;  // Conversion to seconds
    
    prevPosition_ = position_;
    prevTime_ = currentTime;
  }
}

float RotaryEncoder::getDistance() {
  return distance_;
}

float RotaryEncoder::getSpeed() {
  return speed_;
}

float RotaryEncoder::getAcceleration() {
  return acceleration_;
}