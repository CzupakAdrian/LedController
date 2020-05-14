#pragma once

#define max_size 5

namespace LED
{
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
    Bulb *bulbs[max_size];
    unsigned char count;
    float max_X, max_Y, max_Z;
    float min_X, min_Y, min_Z;

  public:
    bool addBulb(const float x, const float y, const float z, const int pin);
    float minX() const
    {
        return min_X;
    }
    float minY() const
    {
        return min_Y;
    }
    float minZ() const
    {
        return min_Z;
    }
    float maxX() const
    {
        return max_X;
    }
    float maxY() const
    {
        return max_Y;
    }
    float maxZ() const
    {
        return max_Z;
    }
    unsigned char size() const
    {
        return count;
    }
    float x(const int index) const
    {
        return bulbs[index]->x;
    }
    float y(const int index) const
    {
        return bulbs[index]->y;
    }
    float z(const int index) const
    {
        return bulbs[index]->z;
    }
    float pin(const int index) const
    {
        return bulbs[index]->pin;
    }
    Matrix() : count(0)
    {
    }
};
} // namespace LED