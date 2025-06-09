#ifndef _HAL_TIMER_H
#define _HAL_TIMER_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <hardware/timer.h>
#include <pico/stdlib.h>

typedef enum
{
    TIMER_ALARM,
    TIMER_PERIODIC
}TIMER_TYPE_t;

typedef struct
{
    TIMER_TYPE_t type;
    union {
        repeating_timer_t repeating_timer;
        alarm_id_t alarm_id;
    };
    int64_t timeout;
    bool running;
}TIMER_t;

typedef struct
{
    TIMER_TYPE_t type;
    int timeout;
    bool (*periodic_callback)(struct repeating_timer*);
    int64_t(*alarm_callback)( alarm_id_t , void* );
}TIMER_CONFIG_t;

TIMER_t* TIMER_Init( TIMER_CONFIG_t );

void TIMER_Pause( TIMER_t* timer );

void TIMER_Resume( TIMER_t* timer, TIMER_CONFIG_t cfg );

#endif