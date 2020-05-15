#ifndef UNIT_TEST
#include "header.hpp"

/*----------------------------------------------------------------------*/
/* things to be changed */

//#define READ_CODES // if defined prints received signals codes on serial port
#define Z0_PIN 10
#define Z1_PIN 9
#define Z2_PIN 5
#define Z3_PIN 6
#define Z4_PIN 3
#define RECV_PIN 2

#define SIGMA_INDEX 0
#define FREQ_INDEX 1
#define INTENSITY_INDEX 2

#define STILLER_INDEX 0

/*----------------------------------------------------------------------*/
/* variables declarations */

LED::LedController<3, 4> *controller;

/*----------------------------------------------------------------------*/
/* functions declarations */

void execCode(unsigned long &ir_code);
void TaskReadControls(void *pvParameters);
void TaskControlLevel(void *pvParameters);

/*----------------------------------------------------------------------*/
/* main functions */

void setup()
{
    pinMode(RECV_PIN, INPUT);
    Serial.begin(9600);

#ifndef READ_CODES
    xTaskCreate(TaskControlLevel, (const char *)"levelControl", 128, NULL, 2, NULL);
#endif /* READ_CODES */
    xTaskCreate(TaskReadControls, (const char *)"readControls", 128, NULL, 1, NULL);
}

void loop()
{
}

/*----------------------------------------------------------------------*/
/* functions definitions */

void TaskControlLevel(void *pvParameters)
{
    // setup
    {
        // LED table initialization
        auto matrix = LED::Matrix();
        matrix.addBulb(0, 0, 0, Z0_PIN);
        matrix.addBulb(0, 0, 1, Z1_PIN);
        matrix.addBulb(0, 0, 2, Z2_PIN);
        matrix.addBulb(0, 0, 3, Z3_PIN);
        matrix.addBulb(0, 0, 4, Z4_PIN);
        controller = new LED::LedController<3, 4>(matrix);
    }
    {
        // parameters initialization
        auto sigma = new LED::ParameterAdder<float>(0.5, 0, 2, 0.1);
        auto freq = new LED::ParameterMultiplier<float>(0.5, 0.05, 10, 1.5);
        auto intensity = new LED::ParameterAdder<float>(205, 0, 255, 25);

        controller->add(make_changer(sigma));
        controller->add(make_changer(freq));
        controller->add(make_changer(intensity));

        // actuators initialization
        controller->add(make_stiller(intensity));
        controller->add(make_raiser(sigma, freq, intensity));
        controller->add(make_faller(sigma, freq, intensity));
        controller->add(make_passer(sigma, freq, intensity));
    }
    vTaskDelay(10);

    // loop
    for (;;)
    {
        controller->update();
        vTaskDelay(1);
    }
}

#ifdef READ_CODES
void TaskReadControls(void *pvParameters)
{
    // setup
    IRrecv irrecv(RECV_PIN);
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
        vTaskDelay(1);
    }
}
#else
void TaskReadControls(void *pvParameters)
{
    // setup
    IRrecv irrecv(RECV_PIN);
    decode_results results;
    irrecv.enableIRIn();
    vTaskDelay(10);

    // loop
    for (;;)
    {
        if (irrecv.decode(&results))
        {
            execCode(results.value);
            irrecv.resume();
        }
        vTaskDelay(3);
    }
}
#endif

void execCode(unsigned long &ir_code)
{
    switch (ir_code)
    {
    case IR11:
        controller->decrease(SIGMA_INDEX);
        break;
    case IR12:
        controller->increase(SIGMA_INDEX);
        break;
    case IR21:
        controller->decrease(FREQ_INDEX);
        break;
    case IR22:
        controller->increase(FREQ_INDEX);
        break;
    case IR31:
        controller->decrease(INTENSITY_INDEX);
        break;
    case IR32:
        controller->increase(INTENSITY_INDEX);
        break;
    case IR23:
        controller->changeActuator();
        break;
    case IR41:
        controller->changeActuator(STILLER_INDEX);
        break;
    case IR51:
        controller->changeActuator(1);
        break;
    case IR52:
        controller->changeActuator(2);
        break;
    case IR53:
        controller->changeActuator(3);
        break;
        // ...
    }
}
#endif /* UNIT_TEST */