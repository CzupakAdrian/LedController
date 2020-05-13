/*
    This file contains all definitions and only it should be edited
*/
#ifdef ARDUINO
#pragma once

#include <Arduino.h>
#define NONE 0

//#define   VOICE_CONTROL                           // Will be defined after
// voice control implementation
/* ----------------------------------------------------------------- */

/* defining pins */

#define RECV_PIN1 2 // IR remote receiver pin

/* ----------------------------------------------------------------- */

/* There should be defined all codes of IR receiver */
#define CODE_TURN_ON NONE
#define CODE_TURN_OFF NONE
#define CODE_INC_SIGMA NONE
#define CODE_DEC_SIGMA NONE
#define CODE_INC_FREQ NONE
#define CODE_DEC_FREQ NONE
#define CODE_INC_INTENS NONE
#define CODE_DEC_INTENS NONE

/* ----------------------------------------------------------------- */
// parameters

#define SIGMA_UPPER_BOUND 1
#define SIGMA_LOWER_BOUND 0.05
#define SIGMA_DIFFERENCE 0.1
#define SIGMA_INIT_VALUE 0.05

#define FREQ_UPPER_BOUND 50
#define FREQ_LOWER_BOUND 0.01
#define FREQ_DIFFERENCE 1.2
#define FREQ_INIT_VALUE 0.1

#define INTENSITY_UPPER_BOUND 255
#define INTENSITY_LOWER_BOUND 0
#define INTENSITY_DIFFERENCE 25
#define INTENSITY_INIT_VALUE 255

/* ---------------------------------------------------*/
#ifdef VOICE_CONTROL
#define INPUT_PORT 0 // Port of analog signal input for frequency intensity modulating
#endif

#if (CODE_TURN_ON != NONE && CODE_TURN_OFF != NONE && CODE_INC_SIGMA != NONE && CODE_DEC_SIGMA != NONE &&              \
     CODE_INC_FREQ != NONE && CODE_DEC_FREQ != NONE && CODE_INC_INTENS != NONE && CODE_DEC_INTENS != NONE)
#define ALL_CODES_DEFINED
#endif

#endif