#pragma once

namespace LED
{
class ParameterChanger
{
  public:
    virtual void increase() = 0;
    virtual void decrease() = 0;
};
} // namespace LED

#define make_changer(parameter)  (static_cast<LED::ParameterChanger *>(parameter))
