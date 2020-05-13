#pragma once

#include "IntensityFunctionsContainer.hpp"
#include "ParametersContainer.hpp"
#include <Arduino.h>

class TimeBasedFunctions
{
  public:
    static const unsigned int MI = 0;
    static const unsigned int SIGMA = 0;
    static const unsigned int FREQ = 1;
    static const unsigned int INTENSITY = 2;

    template <class return_type> static return_type fall(std::vector<float> inputVariables, ParVectorPtr<float> params)
    {
        float x = ((int)(millis() * params[FREQ].get() / 4 + inputVariables[MI].get())) % 255 - 128;
        return (return_type)(params[INTENSITY].get() * exp(-pow(x / 128, 2) / (2 * params[SIGMA].get())));
    }
    template <class return_type> static return_type rise(std::vector<float> inputVariables, ParVectorPtr<float> params)
    {
        float tempParams[] = {255 - inputVariables[MI].get(), params[SIGMA].get(), params[FREQ].get(),
                              params[INTENSITY].get()};
        return fall(tempParams);
    }
    template <class return_type> static return_type pass(std::vector<float> inputVariables, ParVectorPtr<float> params)
    {
        return max(fall(inputVariables, params), rise(inputVaraibles, params));
    }
    template <class return_type> static return_type still(std::vector<float> inputVariables, ParVectorPtr<float> params)
    {
        return (return_type)params[INTENSITY].get();
    }
}
