#pragma once

#include "IntensityComputer.hpp"
#include "Level.hpp"
#include <Arduino.h>

template <class params_type>
class LedController

    : public IntensityComputer<params_type, int>
{
  private:
    LevelsVectorPtr<params_type> levels;

    void setMi()
    {
        auto minLevel = levels[0]->level;
        auto maxLevel = levels[0]->level;
        for (const auto &level : this.levels)
        {
            if (level->level > maxLevel)
                maxLevel = level->level;
            if (level->level < minLevel)
                minLevel = level->level;
        }
        for (auto &level : this.levels)
        {
            level->setMi(minLevel, maxLevel);
        }
    }

  public:
    LedController(LedController &&) = default;
    LedController &operator=(LedController &&) = default;

    LedController(LevelsVectorPtr<params_type> levels, ParVectorPtr<params_type> parameters,
                  FunctionVectorPtr<params_type, return_type> intensityFunctions)
        : IntensityComputer(std::move(parameters), std::move(intensityFunctions)), levels(std::move(levels))
    {
        if (!levels.empty())
            setMi();
    }

    void update()
    {
        for (auto lev : levels)
        {
            auto tempMi = std::make_unique<std::vector<params_type>>(lev.mi);
            lev.update(getCurrentIntensity(std::move(tempMi)));
        }
    }
};