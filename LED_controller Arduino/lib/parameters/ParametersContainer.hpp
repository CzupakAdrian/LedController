#pragma once

#include "Parameter.hpp"

class ParametersContainer
{
  private:
    Parameter parameters[3];

  public:
    ParametersContainer(Parameter *parameters)
    {
        for (int i = 0; i < 3; i++)
        {
            this.parameters[i] = parameters[i];
        }
    }

    void increaseParameter(uint8_t parameter)
    {
        parameters[parameter]->increase();
    }

    void decreaseParameter(uint8_t parameter)
    {
        parameters[parameter]->decrease();
    }
};