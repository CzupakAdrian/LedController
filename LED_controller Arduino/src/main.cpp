#include "header.hpp"

/*----------------------------------------------------------------------*/
/* functions declarations */

void TaskReadControls(void *pvParameters);
void TaskControlLevel(void *pvParameters);
int ada;

/*----------------------------------------------------------------------*/
/* main functions */

void setup()
{
    pinMode(RECV_PIN1, INPUT);
    Serial.begin(9600);

    xTaskCreate(TaskControlLevel, (const char *)"levelControl", 128, NULL, 2, NULL);

    xTaskCreate(TaskReadControls, (const char *)"readControls", 128, NULL, 1, NULL);
}

void loop()
{
}

/*----------------------------------------------------------------------*/
/* functions definitions */

uint8_t maxLevel()
{
    auto mx = levels[0].level;
    for (auto lev : levels)
    {
        if (lev.level > mx)
            mx = lev.level;
    }
    return mx;
}

void TaskControlLevel(void *pvParameters)
{
    // setup
    auto ledController = BasicController.getInstance();
    vTaskDelay(10);

    // loop
    for (;;)
    {
        ledController->update();
        vTaskDelay(1);
    }
}

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
    /*
    IRrecv irrecv(RECV_PIN1);
    decode_results results;
    irrecv.enableIRIn();
    vTaskDelay(10);
*/
    // loop
    for (;;)
    {
        /*
        if (irrecv.decode(&results))
        {
            Serial.println(results.value, HEX);
            irrecv.resume();
        }
    */
        vTaskDelay(10);
    }
}
#endif