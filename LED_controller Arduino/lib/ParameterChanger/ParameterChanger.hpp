#pragma once

#define make_changer(parameter) (static_cast<LED::ParameterChanger *>(parameter))

namespace LED
{
class ParameterChanger
{
  public:
    virtual void increase() = 0;
    virtual void decrease() = 0;
};
} // namespace LED
