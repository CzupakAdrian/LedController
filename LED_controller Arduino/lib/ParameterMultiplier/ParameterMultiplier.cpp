#include "ParameterMultiplier.hpp"

template <class par_type> void LED::ParameterMultiplier<par_type>::increase()
{
    if (this->value * this->step <= this->upper_bound)
        this->value *= this->step;
}

template <class par_type> void LED::ParameterMultiplier<par_type>::decrease()
{
    if (this->value / this->step >= this->lower_bound)
        this->value /= this->step;
}

template <class par_type> par_type LED::ParameterMultiplier<par_type>::get() const
{
    return this->value;
}