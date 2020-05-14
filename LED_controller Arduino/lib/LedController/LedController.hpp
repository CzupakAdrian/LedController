#pragma once

#include "Actuator.hpp"
#include "Matrix.hpp"
#include "ParameterChanger.hpp"

namespace LED
{
template <int par_num, int act_num> class LedController
{
  private:
    Actuator *actuators[act_num];
    int act_size;
    int current_act;
    Matrix matrix;
    ParameterChanger *parameters[par_num];
    int par_size;

  public:
    void add(Actuator *&&act)
    {
        actuators[act_size] = act;
        act_size++;
    }
    void add(ParameterChanger *&&par)
    {
        parameters[par_size] = par;
        par_size++;
    }
    void changeActuator()
    {
        if (++current_act != act_size)
            current_act = 0;
    }
    void update()
    {
        actuators[current_act]->update(matrix);
    }
    void increase(const int index)
    {
        parameters[index]->increase();
    }
    void decrease(const int index)
    {
        parameters[index]->decrease();
    }
    LedController(Matrix &matrix) : matrix(matrix)
    {
    }
};
} // namespace LED