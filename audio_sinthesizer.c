#include <stdio.h>
#include "pico/stdlib.h"
#include "hal_def.h"

/*********************************
*      DEFINITIONS SECTION
*********************************/
#define FREQUENCY 20000
#define PERIOD_US 1000000/FREQUENCY
#define SAMPLES 5*FREQUENCY

typedef enum{
    IDLE,
    RECORDING,
    PLAYING
}STATE_t;

/*********************************
*      VARIABLES SECTION
*********************************/
STATE_t gState = IDLE;
uint16_t my_buffer[SAMPLES];

/*********************************
*      TASKS SECTION
*********************************/
void Task_Buttons()
{
    if( gState == IDLE )
    {
        if( !GPIO_GetInput(GET_POINTER(GPIO,BUTTON_A)))
        {
            printf("Recording ON\n");
            gState = RECORDING;
        }
        if( !GPIO_GetInput(GET_POINTER(GPIO,BUTTON_B)))
        {
            printf("Playing ON\n");
            gState = PLAYING;
        }
    }
}

void Task_Recording()
{
    if( gState == RECORDING )
    {
        LED_SetColor(GET_POINTER(LED,RGB), 0.1, 0.0 , 0.0 );
        int index = 0;
        while( index < SAMPLES )
        {
            my_buffer[index++] = ADC_ReadValue( GET_POINTER(ADC,MICROPHONE) );
            sleep_us(PERIOD_US);
        }
        printf("Recording OFF\n");
        LED_SetColor(GET_POINTER(LED,RGB), 0.0, 0.0 , 0.0 );
        gState = IDLE;
    }
}

void Task_Playing()
{
    if( gState == PLAYING )
    {
        LED_SetColor(GET_POINTER(LED,RGB), 0.0, 0.0 , 0.1 );
        int index = 0;
        PWM_Enable( GET_POINTER(PWM,BUZZER_B));
        while( index < SAMPLES )
        {
            PWM_SetDuty( GET_POINTER(PWM,BUZZER_B) , my_buffer[index++] );
            sleep_us(PERIOD_US);
        }
        PWM_Disable(GET_POINTER(PWM,BUZZER_B));
        printf("Playing OFF\n");
        LED_SetColor(GET_POINTER(LED,RGB), 0.0, 0.0 , 0.0 );
        gState = IDLE;
    }
}

/*********************************
*      MAIN SECTION
*********************************/
int main()
{
    stdio_init_all();

    HAL_Init();
    PWM_Disable(GET_POINTER(PWM,BUZZER_B));

    OS_CreateTask( 100 , Task_Buttons );
    OS_CreateTask( 100 , Task_Recording);
    OS_CreateTask( 100 , Task_Playing );

    while(1)
    {
        OS_Run();
    };
}
