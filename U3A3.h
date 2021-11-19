#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED
#include <stdbool.h>

typedef uint16_t EventType;
typedef struct {
    uint32_t startTime;
    uint32_t time;
    EventType event;
    bool active;
} TimerType;

volatile uint16_t events = 0;
volatile TimerType timer;
//volatile TimerType timer[8];

/*
void setEvent(EventType);
bool eventIsSet(EventType);
void clearEvent(EventType);

void setTimer(volatile TimerType *, uint32_t, EventType);
void startTimer(volatile TimerType *);
void cancelTimer(volatile TimerType *);
*/
void setEvent(EventType ev) {
    taskENTER_CRITICAL();
    events |= (1 << ev);
    taskEXIT_CRITICAL();
}

bool eventIsSet(EventType ev) {
    taskENTER_CRITICAL();
     if((events & (1 << ev)) != 0) {
         taskEXIT_CRITICAL();
         return true;
     } else {
         taskEXIT_CRITICAL();
         return false;
     }
}

void clearEvent(EventType ev) {
    taskENTER_CRITICAL();
    events &= ~(1 << ev);
    taskEXIT_CRITICAL();
}

void setTimer(volatile TimerType *timer, uint32_t time, EventType ev) {
    timer->time = time;
    timer->event = ev;
    timer->active = false;
}
void startTimer(volatile TimerType *timer) {
    timer->startTime = GetSysTime();
    timer->active = true;
}
void cancelTimer(volatile TimerType *timer) {
    timer->active = false;
}

#endif /* EVENTS_H_INCLUDED */
