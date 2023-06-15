#IFNDEF ROTARY_ENCODER_H_
#DEFINE ROTARY_ENCODER_H_

#include <Arduino.h>

class RotaryCounter{
  public:
    int counterValue = 0;
    int encoderPinA;
    int encoderPinB;
    unsigned long lastTime = 0;


    RotaryCounter(int encoderPinA, int encoderPinB)
    {
        this->encoderPinA = encoderPinA;
        this->encoderPinB = encoderPinB;
    }
    
    void begin()
    {
        pinMode(encoderPinA, INPUT_PULLUP);
        pinMode(encoderPinB, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(encoderPinLeft), LCounter, CHANGE);
    }

    void reset()
    {
        counterValue = 0;
    }

    void update()
    {
        if (millis() - lastTime > 100)
        {
            Serial.println(counterValue);
            lastTime = millis();
        }
    }

    // Function interrupt encoder
    void IRAM_ATTR interruptEvent(){
        if (digitalRead(encoderPinA))
        {
            if (digitalRead(encoderPinB))
            {
                counterValue++;
            }
            else
            {
                counterValue--;
            }
        }
        else
        {
            if (digitalRead(encoderPinB))
            {
                counterValue--;
            }
            else
            {
                counterValue++;
            }
        }
    }
};

#ENDIF