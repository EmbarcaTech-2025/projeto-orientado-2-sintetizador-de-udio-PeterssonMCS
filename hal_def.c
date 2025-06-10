#include "hal_def.h"
#include <stdio.h>

const int kPinList[PIN_LIST_MAX] = { 
    #define MACRO( NAME , PIN ) PIN,
    PIN_LIST( MACRO )
    #undef MACRO 
};

HAL_LIST(GEN_VAR)
HAL_LIST(GET_VAR)

void HAL_Init()
{
    HAL_LIST( HAL_INIT )
}

bool periodic_callback( struct repeating_timer* timer )
{
    OS_Tick();
    return true;
}

GEN_CFG( TIMER )
{
    bool success = false;
    switch( id )
    {
        case TIMER_OS_ID:
            cfg->type = TIMER_PERIODIC;
            cfg->timeout = 1;
            cfg->periodic_callback = periodic_callback;
            cfg->alarm_callback = NULL;
            success = true;
        break;
        default:
            success = false;
        break;
    }
    return success;
}

GEN_CFG( LED )
{
    bool success = false;
    switch( id )
    {
        case LED_RGB_ID:
    
            cfg->red.pin = kPinList[RGB_RED_ID];
            cfg->red.direction = 1;
            cfg->red.logic = 1;
            cfg->red.mode = 1;
            
            cfg->green.pin = kPinList[RGB_GREEN_ID];
            cfg->green.direction = 1;
            cfg->green.logic = 1;
            cfg->green.mode = 1;

            cfg->blue.pin = kPinList[RGB_BLUE_ID];
            cfg->blue.direction = 1;
            cfg->blue.logic = 1;
            cfg->blue.mode = 1;

            success = true;
        break;
        default:
            success = false;
        break;
    }
    return success;
}

GEN_CFG( PWM )
{
    bool success = false;
    switch( id )
    {
        case PWM_BUZZER_B_ID:
            cfg->pin = kPinList[BUZZER_B_ID];
            cfg->divider = 5.0f;
            cfg->period = 1250;
            cfg->duty = 625;
            success = true;
        break;
        default:
            success = false;
        break;
    }
    return success;
}

GEN_CFG( GPIO )
{
    bool success = false;
    switch( id )
    {
        case GPIO_BUTTON_A_ID:
            cfg->pin = kPinList[BUTTON_A_ID];
            cfg->direction = 0;
            cfg->logic = 1;
            cfg->mode = 1;
            success = true;
        break;
        case GPIO_BUTTON_B_ID:
            cfg->pin = kPinList[BUTTON_B_ID];
            cfg->direction = 0;
            cfg->logic = 1;
            cfg->mode = 1;
            success = true;
        break;
        default:
            success = false;
        break;
    }
    return success;
}

GEN_CFG( ADC )
{
    bool success = false;
    switch( id )
    {
        case ADC_MICROPHONE_ID:
            cfg->pin = kPinList[MICROPHONE_ID];
            success = true;
        break;
        default:
            success = false;
        break;
    }
    return success;
}