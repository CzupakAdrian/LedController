#include "ParameterAdder.hpp"
#include "ParameterChanger.hpp"
#include "ParameterGetter.hpp"
#include "ParameterMultiplier.hpp"
#include "unity.h"

#ifdef UNIT_TEST

void test_ParameterAdder(void)
{
    auto sigma = new LED::ParameterAdder<float>(0.5, 0.4, 0.6, 0.1);
    auto *changer = make_changer(sigma);
    auto *getter = make_getter(sigma);
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
    auto *changer = make_changer(sigma);
    auto *getter = make_getter(sigma);
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