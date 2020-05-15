#ifdef UNITY_TEST && ARDUINO

#include "header.hpp"
#include "unity.h"

#define Z0_PIN 10
#define Z1_PIN 9
#define Z2_PIN 5
#define Z3_PIN 6
#define Z4_PIN 3
#define RECV_PIN 2

void TaskReadControls(void *pvParameters);

void setup()
{
    Serial.begin(9600);
    xTaskCreate(TaskReadControls, (const char *)"readControls", 128, NULL, 1, NULL);
}

void loop()
{
}

void TaskReadControls(void *pvParameters)
{
    // setup
    IRrecv irrecv(RECV_PIN);
    decode_results results;
    irrecv.enableIRIn();

    // loop
    for (;;)
    {
        if (recv.decode(&results))
        {
            Serial.println(results.value, HEX);
            irrecv.resume();
        }
    }
}

#endif /* UNITY_TEST && ARDUINO */