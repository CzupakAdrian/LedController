#pragma once

#include "Actuator.hpp"
#include "Matrix.hpp"
#include "ParameterGetter.hpp"

#ifdef ARDUINO
#include <Arduino.h>
#else
typedef unsigned char uint8_t;
#endif

#define make_raiser(sigma, freq, intensity)                                                                            \
    (new LED::Raiser(make_getter(sigma), make_getter(freq), make_getter(intensity)))

#define make_faller(sigma, freq, intensity)                                                                            \
    (new LED::Faller(make_getter(sigma), make_getter(freq), make_getter(intensity)))

#define make_passer(sigma, freq, intensity)                                                                            \
    (new LED::Passer(make_getter(sigma), make_getter(freq), make_getter(intensity)))

#define make_stiller(intensity) (new LED::Stiller(make_getter(intensity)))

namespace LED
{
class Raiser : public Actuator
{
  private:
    ParameterGetter<float> *sigma;
    ParameterGetter<float> *frequency;
    ParameterGetter<float> *intensity;

  public:
    void update(const Matrix &matrix) override;
    explicit Raiser(ParameterGetter<float> *sigma, ParameterGetter<float> *frequency, ParameterGetter<float> *intensity)
        : sigma(sigma), frequency(frequency), intensity(intensity)
    {
    }
};

class Faller : public Actuator
{
  private:
    ParameterGetter<float> *sigma;
    ParameterGetter<float> *frequency;
    ParameterGetter<float> *intensity;

  public:
    void update(const Matrix &matrix) override;
    explicit Faller(ParameterGetter<float> *sigma, ParameterGetter<float> *frequency, ParameterGetter<float> *intensity)
        : sigma(sigma), frequency(frequency), intensity(intensity)
    {
    }
};

class Passer : public Actuator
{
  private:
    ParameterGetter<float> *sigma;
    ParameterGetter<float> *frequency;
    ParameterGetter<float> *intensity;

  public:
    void update(const Matrix &matrix) override;
    explicit Passer(ParameterGetter<float> *sigma, ParameterGetter<float> *frequency, ParameterGetter<float> *intensity)
        : sigma(sigma), frequency(frequency), intensity(intensity)
    {
    }
};

class Stiller : public Actuator
{
  private:
    ParameterGetter<float> *intensity;

  public:
    void update(const Matrix &matrix) override;
    explicit Stiller(ParameterGetter<float> *intensity) : intensity(intensity)
    {
    }
};

} // namespace LED
