#include "ParameterAdder.hpp"

template <class par_type> void LED::ParameterAdder<par_type>::increase()
{
    if (this->value + this->step <= this->upper_bound)
        this->value += this->step;
}

template <class par_type> void LED::ParameterAdder<par_type>::decrease()
{
    if (this->value - this->step >= this->lower_bound)
        this->value -= this->step;
}

template <class par_type> par_type LED::ParameterAdder<par_type>::get() const
{
    return this->value;
}