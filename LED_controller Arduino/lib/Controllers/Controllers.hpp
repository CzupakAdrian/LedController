#pragma once

#include "Actuator.hpp"
#include "Matrix.hpp"
#include "ParametersGetter.hpp"

#ifndef ARDUINO
typedef unsigned char uint8_t;
#endif
namespace LED
{
class Raiser : public Actuator
{
  private:
    ParametersGetter<float> *sigma;
    ParametersGetter<float> *frequency;
    ParametersGetter<float> *intensity;

  public:
    void update(const Matrix &matrix) override;
    Raiser(ParametersGetter<float> *sigma, ParametersGetter<float> *frequency, ParametersGetter<float> *intensity)
        : sigma(sigma), frequency(frequency), intensity(intensity)
    {
    }
};

class Faller : public Actuator
{
  private:
    ParametersGetter<float> *sigma;
    ParametersGetter<float> *frequency;
    ParametersGetter<float> *intensity;

  public:
    void update(const Matrix &matrix) override;
    Faller(ParametersGetter<float> *sigma, ParametersGetter<float> *frequency, ParametersGetter<float> *intensity)
        : sigma(sigma), frequency(frequency), intensity(intensity)
    {
    }
};

class Passer : public Actuator
{
  private:
    ParametersGetter<float> *sigma;
    ParametersGetter<float> *frequency;
    ParametersGetter<float> *intensity;

  public:
    void update(const Matrix &matrix) override;
    Passer(ParametersGetter<float> *sigma, ParametersGetter<float> *frequency, ParametersGetter<float> *intensity)
        : sigma(sigma), frequency(frequency), intensity(intensity)
    {
    }
};

class Stiller : public Actuator
{
  private:
    ParametersGetter<float> *intensity;

  public:
    void update(const Matrix &matrix) override;
    Stiller(ParametersGetter<float> *intensity) : intensity(intensity)
    {
    }
};

} // namespace LED

#define make_raiser(sigma, freq, intensity)                                                                            \
    (new LED::Raiser(make_getter(sigma), make_getter(freq), make_getter(intensity)))

#define make_faller(sigma, freq, intensity)                                                                            \
    (new LED::Faller(make_getter(sigma), make_getter(freq), make_getter(intensity)))

#define make_passer(sigma, freq, intensity)                                                                            \
    (new LED::Passer(make_getter(sigma), make_getter(freq), make_getter(intensity)))

#define make_stiller(intensity) (new LED::Stiller(make_getter(intensity)))