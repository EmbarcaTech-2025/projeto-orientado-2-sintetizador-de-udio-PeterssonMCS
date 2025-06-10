#include "led.h"

LED_t* LED_Init( LED_CONFIG_t cfg )
{
    LED_t* led;

    led = (LED_t*)malloc( sizeof ( LED_t ) );
    
    assert( led != NULL );

#if LED_PWM
    led->red = PWM_Init( cfg.red );
    led->green = PWM_Init( cfg.green );
    led->blue = PWM_Init( cfg.blue );
#else
    led->red = GPIO_Init( cfg.red );
    led->green = GPIO_Init( cfg.green );
    led->blue = GPIO_Init( cfg.blue );
#endif
    return led;
}

size_t LED_SetColor( LED_t* led , float red , float green , float blue )
{
    assert( red >= 0 && red <= 1.0);
    assert( green >= 0 && green <= 1.0);
    assert( blue >= 0 && blue <= 1.0);
#if LED_PWM  
    PWM_SetDuty( led->red , red );
    PWM_SetDuty( led->green , green );
    PWM_SetDuty( led->blue , blue );
#else
    GPIO_SetOutput( led->red , red );
    GPIO_SetOutput( led->green , green );
    GPIO_SetOutput( led->blue , blue );
#endif
}
