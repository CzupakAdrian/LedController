#pragma once
#include "Matrix.hpp"

namespace LED
{
class Actuator
{
  public:
    virtual void update(const Matrix &matrix) = 0;
};
} // namespace LED