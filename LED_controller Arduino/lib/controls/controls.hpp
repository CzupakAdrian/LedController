#ifdef ARDUINO
#pragma once

#include <IRremote.h>

#include "parameters.hpp"

typedef enum Command
{
    INCREASE_SIGMA,
    DECREASE_SIGMA,
    INCREASE_FREQ,
    DECREASE_FREQ,
    INCREASE_INTENSITY,
    DECREASE_INTENSITY,
    NEXT_PROGRAM,
    NOTHING
} Command;

#ifndef ALL_CODES_DEFINED
#pragma message("Undefined IR codes in 'setup.h'")
#endif

class IRcontroll
{
  private:
    IRrecv *irrecv;
    decode_results results;
#ifdef ALL_CODES_DEFINED
    typedef enum Code : uint32_t
    {
        TURN_ON = CODE_TURN_ON,
        TURN_OFF = CODE_TURN_OFF,
        INC_SIGMA = CODE_INC_SIGMA,
        DEC_SIGMA = CODE_DEC_SIGMA,
        INC_FREQ = CODE_INC_FREQ,
        DEC_FREQ = CODE_DEC_FREQ,
        INC_INTENS = CODE_INC_INTENS,
        DEC_INTENS = CODE_DEC_INTENS
    } Code;
#else
    typedef enum Code : uint32_t
    {
        WORKS = 0x12345678
    } Code;
#endif

    Command irCodeToCommand(const uint32_t lastCode);

  public:
    IRcontroll();

    static void executeCommand(Parameters *prms, Command comm);

    Command decodeCommand();
};
#endif