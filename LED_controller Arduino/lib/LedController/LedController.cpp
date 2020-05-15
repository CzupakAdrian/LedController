#include "LedController.hpp"

template <int par_num, int act_num> LED::LedController<par_num, act_num>::LedController(Matrix &matrix) : matrix(matrix)
{
}

template <int par_num, int act_num> void LED::LedController<par_num, act_num>::add(Actuator *&&act)
{
    actuators[act_size] = act;
    act_size++;
}

template <int par_num, int act_num> void LED::LedController<par_num, act_num>::add(ParameterChanger *&&par)
{
    parameters[par_size] = par;
    par_size++;
}

template <int par_num, int act_num> void LED::LedController<par_num, act_num>::changeActuator()
{
    if (++current_act != act_size)
        current_act = 0;
}

template <int par_num, int act_num> void LED::LedController<par_num, act_num>::update()
{
    actuators[current_act]->update(matrix);
}

template <int par_num, int act_num> void LED::LedController<par_num, act_num>::increase(const int index)
{
    parameters[index]->increase();
}

template <int par_num, int act_num> void LED::LedController<par_num, act_num>::decrease(const int index)
{
    parameters[index]->decrease();
}