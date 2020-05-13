#pragma once

typedef void (*function)(float &, float, float);

class Parameter
{
  private:
    float value;
    float lowerBound;
    float upperBound;
    function increaser;
    function decreaser;
    float difference;

  public:
    Parameter(float value, float lowerBound, float upperBound, function increaser, function decreaser, float difference)
        : value(value), lowerBound(lowerBound), upperBound(upperBound), increaser(increaser), decreaser(decreaser),
          difference(difference)
    {
    }

    float get()
    {
        return value;
    }
    void increase()
    {
        increaser(value, upperBound, difference);
    }
    void decrease()
    {
        decreaser(value, lowerBound, difference);
    }
};