#ifndef _HAL_LED_H
#define _HAL_LED_H

#include "../hardware/pwm/pwm.h"
#include "../hardware/gpio/gpio.h"

#define LED_PWM 0

typedef struct
{
#if LED_PWM
    PWM_t* red;
    PWM_t* green;
    PWM_t* blue;
#else
    GPIO_t* red;
    GPIO_t* green;
    GPIO_t* blue;
#endif
}LED_t;

typedef struct
{
#if LED_PWM
    PWM_CONFIG_t red;
    PWM_CONFIG_t green;
    PWM_CONFIG_t blue;
#else
    GPIO_CONFIG_t red;
    GPIO_CONFIG_t green;
    GPIO_CONFIG_t blue;
#endif
}LED_CONFIG_t;

LED_t* LED_Init( LED_CONFIG_t );

size_t LED_SetColor( LED_t* , float , float , float );

#endif