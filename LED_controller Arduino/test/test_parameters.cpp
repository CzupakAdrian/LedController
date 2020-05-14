#include "ParameterAdder.hpp"
#include "ParameterMultiplier.hpp"
#include "ParametersChanger.hpp"
#include "ParametersGetter.hpp"
#include "unity.h"

#include "Matrix.hpp"
#include "IntensityCalculator.hpp"
#include "Controllers.hpp"

#ifdef UNIT_TEST

void test_Calculators(void)
{
    auto sigma = new LED::ParameterAdder<float>(0.5, 0.4, 0.6, 0.1);
    auto freq = new LED::ParameterMultiplier<float>(0.5, 0.4, 0.6, 0.1);
    auto intensity = new LED::ParameterAdder<float>(201, 0, 255, 10);
    LED::IntensityCalculator *raiser;
    LED::IntensityCalculator *faller;
    LED::IntensityCalculator *passer;
    LED::IntensityCalculator *stiller;
    {
        LED::ParametersGetter<float> *sigmaGetter = sigma;
        LED::ParametersGetter<float> *freqGetter = freq;
        LED::ParametersGetter<float> *intensityGetter = intensity;
        raiser = new LED::Raiser(sigmaGetter, freqGetter, intensityGetter);
        faller = new LED::Faller(sigmaGetter, freqGetter, intensityGetter);
        passer = new LED::Passer(sigmaGetter, freqGetter, intensityGetter);
        stiller = new LED::Stiller(intensityGetter);
    }
}

void test_ParameterAdder(void)
{
    auto sigma = new LED::ParameterAdder<float>(0.5, 0.4, 0.6, 0.1);
    LED::ParameterChanger *changer = sigma;
    LED::ParametersGetter<float> *getter = sigma;
    TEST_ASSERT_EQUAL(0.5, getter->get());
    changer->increase();
    TEST_ASSERT_EQUAL(0.6, getter->get());
    changer->increase();
    TEST_ASSERT_EQUAL(0.6, getter->get());
    changer->decrease();
    TEST_ASSERT_EQUAL(0.5, getter->get());
    changer->decrease();
    TEST_ASSERT_EQUAL(0.4, getter->get());
    changer->decrease();
    TEST_ASSERT_EQUAL(0.4, getter->get());
}

void test_ParameterMultiplier(void)
{
    auto sigma = new LED::ParameterMultiplier<float>(0.5, 0.2, 1, 2);
    LED::ParameterChanger *changer = sigma;
    LED::ParametersGetter<float> *getter = sigma;
    TEST_ASSERT_EQUAL(0.5, getter->get());
    changer->increase();
    TEST_ASSERT_EQUAL(1, getter->get());
    changer->increase();
    TEST_ASSERT_EQUAL(1, getter->get());
    changer->decrease();
    TEST_ASSERT_EQUAL(0.5, getter->get());
    changer->decrease();
    TEST_ASSERT_EQUAL(0.25, getter->get());
    changer->decrease();
    TEST_ASSERT_EQUAL(0.25, getter->get());
}

void process()
{
    UNITY_BEGIN();
    RUN_TEST(test_ParameterAdder);
    RUN_TEST(test_ParameterMultiplier);
    test_Calculators();
    UNITY_END();
}

#ifdef ARDUINO

#include <Arduino.h>

void setup()
{
    process();
}

void loop()
{
    digitalWrite(13, LOW);
    delay(500);
    digitalWrite(13, HIGH);
    delay(500);
}

#else

int main(int argc, char **argv)
{
    process();
    return 0;
}

#endif
#endif