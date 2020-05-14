#include "Controllers.hpp"

#ifdef ARDUINO
#include <Arduino.h>
namespace LED
{
void actuate(uint8_t pin, int value)
{
    analogWrite(pin, value);
}
} // namespace LED
#else
#include "math.h"

unsigned long mS = 0;
unsigned long millis()
{
    return ++mS;
}
#define max(a, b) ((a) > (b) ? (a) : (b))
namespace LED
{
void actuate(uint8_t pin, int value)
{
    return;
}
} // namespace LED
#endif

void LED::Raiser::update(const Matrix &matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        float mi = 255 - (float)(255 * (float)(matrix.z(i) - matrix.minZ()) / (float)(matrix.maxZ() - matrix.minZ()));
        float x = ((int)(millis() * this->frequency->get() / 4 + mi)) % 255 - 128;
        float val = (int)(this->intensity->get() * exp(-pow(x / 128, 2) / (2 * this->sigma->get())));
        actuate(matrix.pin(i), val);
    }
}

void LED::Faller::update(const Matrix &matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        float mi = (float)(255 * (float)(matrix.z(i) - matrix.minZ()) / (float)(matrix.maxZ() - matrix.minZ()));
        float x = ((int)(millis() * this->frequency->get() / 4 + mi)) % 255 - 128;
        float val = (int)(this->intensity->get() * exp(-pow(x / 128, 2) / (2 * this->sigma->get())));
        actuate(matrix.pin(i), val);
    }
}

void LED::Passer::update(const Matrix &matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        float miF = (float)(255 * (float)(matrix.z(i) - matrix.minZ()) / (float)(matrix.maxZ() - matrix.minZ()));
        float miR = 255 - miF;
        float xF = ((int)(millis() * this->frequency->get() / 4 + miF)) % 255 - 128;
        float xR = ((int)(millis() * this->frequency->get() / 4 + miR)) % 255 - 128;
        float val = max((int)(this->intensity->get() * exp(-pow(xF / 128, 2) / (2 * this->sigma->get()))),
                        (int)(this->intensity->get() * exp(-pow(xR / 128, 2) / (2 * this->sigma->get()))));
        actuate(matrix.pin(i), val);
    }
}

void LED::Stiller::update(const Matrix &matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        actuate(matrix.pin(i), this->intensity->get());
    }
}