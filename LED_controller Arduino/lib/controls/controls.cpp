#ifdef ARDUINO
#include "controls.hpp"

IRcontroll::IRcontroll()
{
    irrecv = new IRrecv(RECV_PIN1);
    irrecv->enableIRIn();
}

void IRcontroll::executeCommand(Parameters *prms, Command comm)
{
    switch (comm)
    {
    case INCREASE_SIGMA:
        prms->increaseSigma();
        break;
    case DECREASE_SIGMA:
        prms->decreaseSigma();
        break;
    case INCREASE_FREQ:
        prms->increaseFreq();
        break;
    case DECREASE_FREQ:
        prms->decreaseFreq();
        break;
    case INCREASE_INTENSITY:
        prms->increaseIntensity();
        break;
    case DECREASE_INTENSITY:
        prms->decreaseIntensity();
        break;
    case NEXT_PROGRAM:
        prms->changeIntensityFunction();
        break;
    default:
        break;
    }
}

Command IRcontroll::decodeCommand()
{
    if (irrecv->decode(&results))
    {
        irrecv->resume();
        return irCodeToCommand(results.value);
    }
    else
    {
        return NOTHING;
    }
}

#ifdef ALL_CODES_DEFINED
Command IRcontroll::irCodeToCommand(const uint32_t lastCode)
{
    Command comm = NOTHING;
    switch (static_cast<Code>(lastCode))
    {
    case TURN_ON:
        /* tu może resumeLightControll(), czy coś tego typu */
        break;
    case TURN_OFF:
        /* tu stopLightControll() */
        break;
    case INC_SIGMA:
        comm = INCREASE_SIGMA;
        break;
    case DEC_SIGMA:
        comm = DECREASE_SIGMA;
        break;
    case INC_FREQ:
        comm = INCREASE_FREQ;
        break;
    case DEC_FREQ:
        comm = DECREASE_FREQ;
        break;
    case INC_INTENS:
        comm = INCREASE_INTENSITY;
        break;
    case DEC_INTENS:
        comm = DECREASE_INTENSITY;
        break;
    default:
        comm = NOTHING;
        break;
    }
    return comm;
}
#else
Command IRcontroll::irCodeToCommand(const uint32_t lastCode)
{
    Command comm = NOTHING;
    return comm;
}
#endif
#endif
