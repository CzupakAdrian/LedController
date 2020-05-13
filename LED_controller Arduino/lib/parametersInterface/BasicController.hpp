#pragma once

#include "LedController.hpp"
#include "ParChangers.hpp"
#include "TimeBasedFunctions.hpp"
#include "setup.hpp"

/* In function yourParameters() are defined pins and their levels */

class BasicController : private LedController<float>
{
  private:
    LevelsVectorPtr<float> levVec;
    ParVectorPtr<float> parVec;
    FunctionVectorPtr<float, int> funcVec;

    BasicController(LevelsVectorPtr levVec, ParVectorPtr parVec, FunctionVectorPtr funcVec)
        : LedController(levVec, parVec, funcVec) levVec(levVec), parVec(parVec), funcVec(funcVec)
    {
    }

    void update() override
    {
        for (auto lev : levels)
        {
            auto tempMi = std::make_unique<std::vector<params_type>>(lev.mi);
            lev.update(getCurrentIntensity(tempMi));
        }
    }

  public:
    static std::unique_ptr<BasicController> getInstance()
    {
        auto levVec = yourLevels();
        auto parVec = basicParameters();
        auto funcVec = basicIntensityFunctions();

        auto ledController =
            std::make_unique<BasicController>(std::move(LevVec), std::move(ParVec), std::move(funcVec));

        return std::move(ledController);
    }

    void increaseSigma()
    {
        parVec[SIGMA]->increase();
    }
    void decreaseSigma()
    {
        parVec[SIGMA]->decrease();
    }
    void increaseFreq()
    {
        parVec[FREQ]->increase();
    }
    void decreaseFreq()
    {
        parVec[FREQ]->decrease();
    }
    void increaseIntensity()
    {
        parVec[INTENSITY]->increase();
    }
    void decreaseIntensity()
    {
        parVec[INTENSITY]->decrease();
    }

    void update()
    {
        LedController::update()
    }
    void changeIntensityFunction()
    {
        IntensityFunctionsContainer::changeIntensityFunction();
    }

  private:
    static std::shared_ptr<LevelsVector<float>> yourLevels()
    {
        using makeLev = std::make_unique<Level<float>>;

        auto levVec = std::make_shared<LevelsVector<float>>();

        auto level4 = makeLev(3, 4);
        auto level3 = makeLev(5, 3);
        auto level2 = makeLev(11, 2);
        auto level1 = makeLev(10, 1);
        auto level0 = makeLev(9, 0);

        levVec.push_back(std::move(level0));
        levVec.push_back(std::move(level1));
        levVec.push_back(std::move(level2));
        levVec.push_back(std::move(level3));
        levVec.push_back(std::move(level4));

        return std::move(levVec);
    }

    static std::shared_ptr<ParVector<float>> basicParameters()
    {
        using makePar = std::make_unique<Parameter<float>>;

        auto parVec = std::make_shared<ParVector<float>>();

        auto sigma = makePar(SIGMA_INIT_VALUE, SIGMA_LOWER_BOUND, SIGMA_UPPER_BOUND, ParChangers::increaseByAdding,
                             ParChangers::decreaseByAdding, SIGMA_DIFFERENCE);
        auto freq = makePar(FREQ_INIT_VALUE, FREQ_LOWER_BOUND, FREQ_UPPER_BOUND, ParChangers::increaseByMultiplying,
                            ParChangers::decreaseByMultiplying, FREQ_DIFFERENCE);
        auto intensity = makePar(INTENSITY_INIT_VALUE, INTENSITY_LOWER_BOUND, INTENSITY_UPPER_BOUND,
                                 ParChangers::increaseByAdding, ParChangers::decreaseByAdding, INTENSITY_DIFFERENCE);

        parVec.push_back(sigma);
        parVec.push_back(freq);
        parVec.push_back(intensity);

        return std::move(parVec);
    }

    static std::shared_ptr<FunctionVector<float, int>> basicIntensityFunctions()
    {
        auto funcVec = std::make_shared<FunctionVector<float, int>>();

        funcVec.push_back(TimeBasedFunctions::rise);
        funcVec.push_back(TimeBasedFunctions::fall);
        funcVec.push_back(TimeBasedFunctions::pass);
        funcVec.push_back(TimeBasedFunctions::still);

        return std::move(funcVec);
    }
}