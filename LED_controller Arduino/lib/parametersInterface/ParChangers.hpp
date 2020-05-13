#pragma once

namespace ParChangers
{

template <class params_type> void increaseByAdding(params_type &value, params_type upperBound, params_type difference)
{
    params_type newValue = value + difference;
    if (newValue <= upperBound)
        value = newValue;
}

template <class params_type>
float increaseByMultiplying(params_type &value, params_type upperBound, params_type difference)
{
    params_type newValue = value * difference;
    if (newValue <= upperBound)
        value = newValue;
}

template <class params_type> void decreaseByAdding(params_type &value, params_type lowerBound, params_type difference)
{
    params_type newValue = value - difference;
    if (newValue >= upperBound)
        value = newValue;
}

template <class params_type>
float decreaseByMultiplying(params_type &value, params_type lowerBound, params_type difference)
{
    params_type newValue = value / difference;
    if (newValue >= upperBound)
        value = newValue;
}
} // namespace ParChangers