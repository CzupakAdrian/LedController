#pragma once

namespace LED
{
template <class par_type> class Parameter
{
  protected:
    par_type value;
    par_type lower_bound;
    par_type upper_bound;

  public:
    explicit Parameter(par_type value, par_type lower_bound, par_type upper_bound)
        : value(value), lower_bound(lower_bound), upper_bound(upper_bound)
    {
    }
};
} // namespace LED