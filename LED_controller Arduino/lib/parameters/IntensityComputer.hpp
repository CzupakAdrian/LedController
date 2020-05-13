#pragma once

#include "IntensityFunctionsContainer.hpp"
#include "ParametersContainer.hpp"

template <class params_type, class return_type>
class IntensityComputer : public IntensityFunctionsContainer<params_type, return_type>,
                          public ParametersContainer<params_type>
{
  public:
    IntensityComputer(IntensityComputer &&) = default;
    IntensityComputer &operator=(IntensityComputer &&) = default;

    IntensityComputer(ParVectorPtr<params_type> parameters,
                      FunctionVectorPtr<params_type, return_type> intensityFunctions)
        : ParametersContainer(std::move(parameters)), IntensityFunctionsContainer(std::move(intensityFunctions))
    {
    }

    return_type getCurrentIntensity(std::unique_ptr<std::vector<params_type>> inputVariables)
    {
        return intensityFunctions[functionNum](std::move(inputVariables), parameters);
    }

    return_type getCurrentIntensity()
    {
        auto inputVariables = std::make_unique<std::vector<params_type>>();
        return getCurrentIntensity(std::move(inputVariables));
    }
};