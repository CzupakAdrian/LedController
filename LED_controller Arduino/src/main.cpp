#ifndef UNIT_TEST
#include "header.hpp"

#define Z0_PIN 0
#define Z1_PIN 1
#define Z2_PIN 2
#define Z3_PIN 3
#define Z4_PIN 4
/*----------------------------------------------------------------------*/
/* functions declarations */

// void TaskReadControls(void *pvParameters);
void TaskControlLevel(void *pvParameters);

/*----------------------------------------------------------------------*/
/* main functions */

void setup()
{
    // pinMode(RECV_PIN1, INPUT);
    Serial.begin(9600);

    xTaskCreate(TaskControlLevel, (const char *)"levelControl", 128, NULL, 2, NULL);

    // xTaskCreate(TaskReadControls, (const char *)"readControls", 128, NULL, 1, NULL);
}

void loop()
{
}

/*----------------------------------------------------------------------*/
/* functions definitions */

void TaskControlLevel(void *pvParameters)
{
    // setup
    LED::LedController<3, 4> *controller;
    {
        auto matrix = LED::Matrix();
        matrix.addBulb(0, 0, 0, Z0_PIN);
        matrix.addBulb(0, 0, 1, Z1_PIN);
        matrix.addBulb(0, 0, 2, Z2_PIN);
        matrix.addBulb(0, 0, 3, Z3_PIN);
        matrix.addBulb(0, 0, 4, Z4_PIN);
        controller = new LED::LedController<3, 4>(matrix);
    }
    {
        auto sigma = new LED::ParameterAdder<float>(0.5, 0, 2, 0.1);
        auto freq = new LED::ParameterMultiplier<float>(0.5, 0.05, 10, 1.5);
        auto intensity = new LED::ParameterAdder<float>(205, 0, 255, 25);

        // inicjalizacja parametrów
        controller->add(make_changer(sigma));
        controller->add(make_changer(freq));
        controller->add(make_changer(intensity));

        // inicjalizacja aktuatorów
        controller->add(make_raiser(sigma, freq, intensity));
        controller->add(make_faller(sigma, freq, intensity));
        controller->add(make_passer(sigma, freq, intensity));
        controller->add(make_stiller(intensity));
    }
    // loop
    for (;;)
    {
        controller->update();
        vTaskDelay(1);
    }
}
/*
#ifdef ALL_CODES_DEFINED
void TaskReadControls(void *pvParameters)
{
    // setup
    IRcontroll controller();
    vTaskDelay(10);

    // loop
    for (;;)
    {
        controller.executeCommand(parameters, controller.decodeCommand());
        vTaskDelay(5);
    }
}
#else
void TaskReadControls(void *pvParameters)
{
    // setup

    IRrecv irrecv(RECV_PIN1);
    decode_results results;
    irrecv.enableIRIn();
    vTaskDelay(10);

    // loop
    for (;;)
    {

        if (irrecv.decode(&results))
        {
            Serial.println(results.value, HEX);
            irrecv.resume();
        }

        vTaskDelay(10);
    }
}
#endif
*/
#endif /* UNIT_TEST */