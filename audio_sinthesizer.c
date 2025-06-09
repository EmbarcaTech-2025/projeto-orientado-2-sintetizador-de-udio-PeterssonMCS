#include <stdio.h>
#include "pico/stdlib.h"
#include "hal_def.h"

/*********************************
*      DEFINITIONS SECTION
*********************************/
#define FREQUENCY 8000
#define PERIOD_US 1000000/FREQUENCY
#define SAMPLES 2*FREQUENCY

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
void Task_Display()
{
    D1306_Show( GET_POINTER(D1306,OLED) );
}

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

void Task_LED()
{
    switch( gState )
    {
        case IDLE:
            LED_SetColor(GET_POINTER(LED,RGB), 0.0, 0.0 , 0.0 );
        break;
        case RECORDING:
            LED_SetColor(GET_POINTER(LED,RGB), 0.1, 0.0 , 0.0 );
        break;
        case PLAYING:
            LED_SetColor(GET_POINTER(LED,RGB), 0.0, 0.1 , 0.0 );
        break;
    }
}

void Task_Recording()
{
    if( gState == RECORDING )
    {
        int index = 0;
        while( index < SAMPLES )
        {
            my_buffer[index++] = ADC_ReadValue( GET_POINTER(ADC,MICROPHONE) );
            sleep_us(PERIOD_US);
        }
        printf("Recording OFF\n");
        gState = IDLE;
    }
}

void Task_Playing()
{
    if( gState == PLAYING )
    {
        int index = 0;
        PWM_Enable( GET_POINTER(PWM,BUZZER_B));
        while( index < SAMPLES )
        {
            PWM_SetDuty( GET_POINTER(PWM,BUZZER_B) , my_buffer[index++] );
            sleep_us(PERIOD_US);
        }
        PWM_Disable(GET_POINTER(PWM,BUZZER_B));
        printf("Playing OFF\n");
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

   // OS_CreateTask( 100 , Task_Display );
    OS_CreateTask( 100 , Task_Buttons );
    OS_CreateTask( 100 , Task_LED );
    OS_CreateTask( 100 , Task_Recording);
    OS_CreateTask( 100 , Task_Playing );

    while(1)
    {
        OS_Run();
    };
}
