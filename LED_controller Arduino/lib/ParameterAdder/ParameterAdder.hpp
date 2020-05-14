#pragma once

#include "Parameter.hpp"
#include "ParameterChanger.hpp"
#include "ParametersGetter.hpp"

namespace LED
{
template <class par_type>
class ParameterAdder : public ParameterChanger, public ParametersGetter<par_type>, public Parameter<par_type>
{
  private:
    par_type step;

  public:
    void increase() override
    {
        if (this->value + this->step <= this->upper_bound)
            this->value += this->step;
    }

    void decrease() override
    {
        if (this->value - this->step >= this->lower_bound)
            this->value -= this->step;
    }

    par_type get() const override
    {
        return this->value;
    }

    ParameterAdder(const par_type &init_val, const par_type &lower_bound, const par_type &upper_bound,
                   const par_type &step)
        : Parameter<par_type>(init_val, lower_bound, upper_bound), step(step)
    {
    }
};
} // namespace LED