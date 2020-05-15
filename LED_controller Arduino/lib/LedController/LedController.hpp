#pragma once

#include "Actuator.hpp"
#include "Matrix.hpp"
#include "ParameterChanger.hpp"


namespace LED
{
template <int par_num, int act_num> class LedController
{
  private:
    Actuator *actuators[act_num]{};
    int act_size{};
    int current_act{};
    Matrix matrix;
    ParameterChanger *parameters[par_num]{};
    int par_size{};

  public:
    void add(Actuator *&&act);
    void add(ParameterChanger *&&par);
    void changeActuator();
    void update();
    void increase(const int index);
    void decrease(const int index);
    explicit LedController(Matrix &matrix);
};
} // namespace LED