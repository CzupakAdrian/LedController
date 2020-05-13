#pragma once
#include <Arduino.h>

class Level
{
  public:
    level_type level;
    uint8_t pin;
    params_type mi;

    Level(uint8_t level, uint8_t pin) : level(level), pin(pin), mi(0)
    {
        pinMode(pin, OUTPUT);
    }
    void setMi(uint8_t minLevel, uint8_t maxLevel)
    {
        mi = (params_type)(255 * (float)(level - minLevel) / (float)(maxLevel - minLevel));
    }
    void update(int newIntensity)
    {
        analogWrite(pin, newIntensity);
    }
};