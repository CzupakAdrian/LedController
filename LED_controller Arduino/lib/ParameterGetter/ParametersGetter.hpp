#pragma once

namespace LED
{
template <class par_type> class ParametersGetter
{
  public:
    virtual par_type get() const = 0;
};
} // namespace LED

//using make_getter(parameter) = static_cast<LED::ParametersGetter *>(parameter);
#define make_getter(parameter) (static_cast<LED::ParametersGetter<float> *>(parameter))