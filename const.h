#ifndef CONST_H
#define CONST_H

#include "type.h"

/* All actions */
typedef enum {
        ACTION_START,  /* Start of a rap */
        ACTION_READ,   /* Read from input */
        ACTION_INC,    /* Increment a memory */
        ACTION_DEC,    /* Decrement a memory */
        ACTION_OUTPUT, /* Output as decimal */
        ACTION_ASCII,  /* Output as ASCII */
        ACTION_JMP,    /* Force jump */
        ACTION_JLS,    /* Jump if less */
        ACTION_JLE,    /* Jump if less or equal */
        ACTION_JGT,    /* Jump if greater */
        ACTION_JGE,    /* Jump if greater or equal */
        ACTION_JEQ,    /* Jump if equal */
        ACTION_JNE,    /* Jump if not equal */
} ACTION_ENUM;

#endif // ifndef CONST_H
