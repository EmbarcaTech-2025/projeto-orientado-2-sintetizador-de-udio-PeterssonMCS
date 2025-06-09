#include "timer.h"

TIMER_t* TIMER_Init(TIMER_CONFIG_t cfg)
{
    TIMER_t* timer = malloc(sizeof(TIMER_t));
    assert(timer != NULL);

    timer->type = cfg.type;
    timer->timeout = cfg.timeout;
    timer->running = true;

    if(cfg.type == TIMER_PERIODIC) 
    {
        bool started = add_repeating_timer_ms(cfg.timeout, cfg.periodic_callback, NULL, &timer->repeating_timer);
        assert(started);
    } else {
        timer->alarm_id = add_alarm_in_ms(cfg.timeout, cfg.alarm_callback, NULL, false);
    }

    return timer;
}

void TIMER_Pause(TIMER_t* timer)
{
    if(timer == NULL || !timer->running)
        return;

    if(timer->type == TIMER_PERIODIC) {
        cancel_repeating_timer(&timer->repeating_timer);
    } else {
        cancel_alarm(timer->alarm_id);
    }

    timer->running = false;
}

void TIMER_Resume( TIMER_t* timer, TIMER_CONFIG_t cfg )
{
    if(timer == NULL || timer->running)
        return;

    if(cfg.type == TIMER_PERIODIC) 
    {
        bool started = add_repeating_timer_ms(cfg.timeout, cfg.periodic_callback, NULL, &timer->repeating_timer);
        assert(started);
    } else {
        timer->alarm_id = add_alarm_in_ms(cfg.timeout, cfg.alarm_callback, NULL, false);
    }

    timer->running = true;
}