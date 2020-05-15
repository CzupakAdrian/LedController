#pragma once

#ifdef ARDUINO
#include <Arduino.h>
#else
typedef unsigned char uint8_t;
#endif

#define max_size 5

namespace LED
{
class Matrix;
struct Bulb
{
  public:
    float x;
    float y;
    float z;
    int pin;

    Bulb(const float x, const float y, const float z, const int pin) : x(x), y(y), z(z), pin(pin)
    {
    }
};

class Matrix
{
  private:
    Bulb *bulbs[max_size]{};
    uint8_t count{};
    float max_X{}, max_Y{}, max_Z{};
    float min_X{}, min_Y{}, min_Z{};

  public:
    bool addBulb(const float x, const float y, const float z, const int pin);
    float minX() const;
    float minY() const;
    float minZ() const;
    float maxX() const;
    float maxY() const;
    float maxZ() const;
    uint8_t size() const;
    float x(const int index) const;
    float y(const int index) const;
    float z(const int index) const;
    int pin(const int index) const;
};
} // namespace LED