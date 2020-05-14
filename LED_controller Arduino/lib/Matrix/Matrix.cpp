#include "Matrix.hpp"

bool LED::Matrix::addBulb(const float x, const float y, const float z, const int pin)
{
    if (count == max_size)
        return false;
    bulbs[count] = new Bulb(x, y, z, pin);
    count++;
    this->min_X = this->bulbs[0]->x;
    this->max_X = this->bulbs[0]->x;
    this->min_Y = this->bulbs[0]->y;
    this->max_Y = this->bulbs[0]->y;
    this->min_Z = this->bulbs[0]->z;
    this->max_Z = this->bulbs[0]->z;
    for (int i = 0; i < count; i++)
    {
        if (this->bulbs[i]->x > this->max_X)
            this->max_X = this->bulbs[i]->x;
        if (this->bulbs[i]->x < this->min_X)
            this->min_X = this->bulbs[i]->x;
        if (this->bulbs[i]->y > this->max_Y)
            this->max_Y = this->bulbs[i]->y;
        if (this->bulbs[i]->y < this->min_Y)
            this->min_Y = this->bulbs[i]->y;
        if (this->bulbs[i]->z > this->max_Z)
            this->max_Z = this->bulbs[i]->z;
        if (this->bulbs[i]->z < this->min_Z)
            this->min_Z = this->bulbs[i]->z;
    }
    return true;
}