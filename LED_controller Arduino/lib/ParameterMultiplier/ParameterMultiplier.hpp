#pragma once

#include "Parameter.hpp"
#include "ParameterChanger.hpp"
#include "ParameterGetter.hpp"

namespace LED
{
template <class par_type>
class ParameterMultiplier : public ParameterChanger, public ParameterGetter<par_type>, public Parameter<par_type>
{
  private:
    par_type step;

  public:
    void increase() override;
    void decrease() override;
    par_type get() const override;
    ParameterMultiplier(const par_type &init_val, const par_type &lower_bound, const par_type &upper_bound,
                        const par_type &step)
        : Parameter<par_type>(init_val, lower_bound, upper_bound), step(step)
    {
    }
};
} // namespace LED