#pragma once

#include "ParametersContainer.hpp"

template <class params_type, class return_type>
using FunctionPtr = std::function<return_type(std::vector<params_type>, ParVector<params_type>)>;
template <class params_type, class return_type>
using FunctionVector = std::vector<FunctionPtr<params_type, return_type>>;
template <class params_type, class return_type>
using FunctionVectorPtr = std::shared_ptr<FunctionVector<params_type, return_type>>;

template <class params_type, class return_type> class IntensityFunctionsContainer
{
  private:
    FunctionVectorPtr<params_type, return_type> intensityFunctions;
    uint8_t functionNum;

  public:
    IntensityFunctionContainer(IntensityFunctionContainer &&) = default;
    IntensityFunctionContainer &operator=(IntensityFunctionContainer &&) = default;

    IntensityFunctionContainer(FunctionPtr<params_type, return_type> basicFunction) : functionNum(0)
    {
        addFunction(std::move(basicFunction));
    }

    IntensityFunctionContainer(FunctionVectorPtr<params_type, return_type> functions)
        : functionNum(0), intensityFunctions(std::move(functions))
    {
    }

    void addFunction(FunctionPtr<params_type, return_type> newFunction)
    {
        for (auto func : intensityFunctions.get())
        {
            if (func == newFunction)
                return;
        }
        intensityFunctions.push_back(newFunction);
    }

    void changeIntensityFunction()
    {
        functionNum = (functionNum + 1) % intensityFunctions.size();
    }
};