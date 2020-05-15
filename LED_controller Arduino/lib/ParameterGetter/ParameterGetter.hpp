#pragma once

#define make_getter(parameter) (static_cast<LED::ParameterGetter<float> *>(parameter))

namespace LED
{
template <class par_type> class ParameterGetter
{
  public:
    virtual par_type get() const = 0;
};
} // namespace LED
