#include "nnxt.h"
#include "events.h"
#include <stdio.h>
#define N 100
#define EV_TASTER_L     0
#define EV_TASTER_R     1
#define EV_STARTZUSTAND 2

enum drehung {links, umdrehen, rechts};
char msg1[10];
char msg2[10];
uint32_t time_left = 0;

void fahren(uint8_t);
void drehen(enum drehung);

void task1() {
    sensor_touch_clicked_t touch_l_old, touch_l_new, touch_r_old, touch_r_new = SensorTouch_released;

    while(1) {
        Touch_Clicked(Port_0, &touch_r_new);
        if(touch_r_new == SensorTouch_clicked && touch_r_old == SensorTouch_released)
            setEvent(EV_TASTER_R);
        else
            clearEvent(EV_TASTER_R);
        touch_r_old = touch_r_new;

        Touch_Clicked(Port_3, &touch_l_new);
        if(touch_l_new == SensorTouch_clicked && touch_l_old == SensorTouch_released)
            setEvent(EV_TASTER_L);
        else
            clearEvent(EV_TASTER_L);
        touch_l_old = touch_l_new;

        Delay(N);
    }
}

void task2() {
    uint8_t zustand = 4;
    setTimer(&timer, 5000, EV_STARTZUSTAND);

    while(1) {
    switch (zustand) {
        case 1:
			if(eventIsSet(EV_TASTER_L)) {
				startTimer(&timer);
            }
            if(eventIsSet(EV_TASTER_R)) {
				cancelTimer(&timer);
                drehen(umdrehen); fahren(1);
                zustand = 8;
                startTimer(&timer);
            }
            if(eventIsSet(EV_STARTZUSTAND)) {
                drehen(umdrehen); fahren(3); drehen(links);
                zustand = 4;
                clearEvent(EV_STARTZUSTAND);
                startTimer(&timer);
            } break;
		case 2:
			if(eventIsSet(EV_TASTER_L)) {
                cancelTimer(&timer);
                fahren(1);
                zustand = 1;
				startTimer(&timer);
            }
            if(eventIsSet(EV_TASTER_R)) {
				cancelTimer(&timer);
                drehen(umdrehen); fahren(1);
                zustand = 9;
                startTimer(&timer);
            }
            if(eventIsSet(EV_STARTZUSTAND)) {
                drehen(umdrehen); fahren(2); drehen(links);
                zustand = 4;
                clearEvent(EV_STARTZUSTAND);
                startTimer(&timer);
            } break;
        case 3:
			if(eventIsSet(EV_TASTER_L)) {
				cancelTimer(&timer);
                fahren(1);
                zustand = 2;
				startTimer(&timer);
            }
            if(eventIsSet(EV_TASTER_R)) {
				cancelTimer(&timer);
                drehen(umdrehen); fahren(1);
                zustand = 10;
                startTimer(&timer);
            }
            if(eventIsSet(EV_STARTZUSTAND)) {
                drehen(umdrehen); fahren(1); drehen(links);
                zustand = 4;
                clearEvent(EV_STARTZUSTAND);
                startTimer(&timer);
            } break;
        case 4:
			if(eventIsSet(EV_TASTER_L)) {
                cancelTimer(&timer);
                drehen(links); fahren(1);
                zustand = 3;
				startTimer(&timer);
            }
            if(eventIsSet(EV_TASTER_R)) {
				cancelTimer(&timer);
                drehen(rechts); fahren(1);
                zustand = 5;
				startTimer(&timer);
            }
            if(eventIsSet(EV_STARTZUSTAND)) {
                clearEvent(EV_STARTZUSTAND);
                startTimer(&timer);
            } break;
        case 5:
			if(eventIsSet(EV_TASTER_L)) {
                cancelTimer(&timer);
                drehen(umdrehen); fahren(1);
                zustand = 11;
				startTimer(&timer);
            }
            if(eventIsSet(EV_TASTER_R)) {
				cancelTimer(&timer);
                fahren(1);
                zustand = 6;
                startTimer(&timer);
            }
            if(eventIsSet(EV_STARTZUSTAND)) {
                drehen(umdrehen); fahren(1); drehen(rechts);
                zustand = 4;
                clearEvent(EV_STARTZUSTAND);
				startTimer(&timer);
            } break;
        case 6:
			if(eventIsSet(EV_TASTER_L)) {
                cancelTimer(&timer);
                drehen(umdrehen); fahren(1);
                zustand = 12;
				startTimer(&timer);
            }
            if(eventIsSet(EV_TASTER_R)) {
				cancelTimer(&timer);
                fahren(1);
                zustand = 7;
                startTimer(&timer);
            }
            if(eventIsSet(EV_STARTZUSTAND)) {
                drehen(umdrehen); fahren(2); drehen(rechts);
                zustand = 4;
                clearEvent(EV_STARTZUSTAND);
                startTimer(&timer);
            } break;
        case 7:
			if(eventIsSet(EV_TASTER_L)) {
                cancelTimer(&timer);
                drehen(umdrehen); fahren(1);
                zustand = 13;
				startTimer(&timer);
            }
            if(eventIsSet(EV_TASTER_R)) {
                startTimer(&timer);
            }
            if(eventIsSet(EV_STARTZUSTAND)) {
                drehen(umdrehen); fahren(3); drehen(rechts);
                zustand = 4;
                clearEvent(EV_STARTZUSTAND);
                startTimer(&timer);
            } break;
        case 8:
			if(eventIsSet(EV_TASTER_L)) {
                cancelTimer(&timer);
                drehen(umdrehen); fahren(1);
                zustand = 1;
				startTimer(&timer);
            }
            if(eventIsSet(EV_TASTER_R)) {
				cancelTimer(&timer);
                fahren(1);
                zustand = 9;
                startTimer(&timer);
            }
            if(eventIsSet(EV_STARTZUSTAND)) {
                fahren(2); drehen(links);
                zustand = 4;
                clearEvent(EV_STARTZUSTAND);
                startTimer(&timer);
            } break;
        case 9:
			if(eventIsSet(EV_TASTER_L)) {
                cancelTimer(&timer);
                drehen(umdrehen); fahren(1);
                zustand = 2;
				startTimer(&timer);
            }
            if(eventIsSet(EV_TASTER_R)) {
				cancelTimer(&timer);
                fahren(1);
                zustand = 10;
                startTimer(&timer);
            }
            if(eventIsSet(EV_STARTZUSTAND)) {
                fahren(1); drehen(links);
                zustand = 4;
                clearEvent(EV_STARTZUSTAND);
                startTimer(&timer);
            } break;
        case 10:
			if(eventIsSet(EV_TASTER_L)) {
                cancelTimer(&timer);
                drehen(umdrehen); fahren(1);
                zustand = 3;
				startTimer(&timer);
            }
            if(eventIsSet(EV_TASTER_R)) {
				cancelTimer(&timer);
                fahren(1);
                zustand = 5;
                startTimer(&timer);
            }
            if(eventIsSet(EV_STARTZUSTAND)) {
                drehen(links);
                zustand = 4;
                clearEvent(EV_STARTZUSTAND);
                startTimer(&timer);
            } break;
        case 11:
			if(eventIsSet(EV_TASTER_L)) {
                cancelTimer(&timer);
                fahren(1);
                zustand = 3;
				startTimer(&timer);
            }
            if(eventIsSet(EV_TASTER_R)) {
				cancelTimer(&timer);
                drehen(umdrehen); fahren(1);
                zustand = 5;
                startTimer(&timer);
            }
            if(eventIsSet(EV_STARTZUSTAND)) {
                drehen(rechts);
                zustand = 4;
                clearEvent(EV_STARTZUSTAND);
                startTimer(&timer);
            } break;
        case 12:
			if(eventIsSet(EV_TASTER_L)) {
                cancelTimer(&timer);
                fahren(1);
                zustand = 11;
				startTimer(&timer);
            }
            if(eventIsSet(EV_TASTER_R)) {
				cancelTimer(&timer);
                drehen(umdrehen); fahren(1);
                zustand = 6;
                startTimer(&timer);
            }
            if(eventIsSet(EV_STARTZUSTAND)) {
                fahren(1); drehen(rechts);
                zustand = 4;
                clearEvent(EV_STARTZUSTAND);
                startTimer(&timer);
            } break;
        case 13:
			if(eventIsSet(EV_TASTER_L)) {
                cancelTimer(&timer);
                fahren(1);
                zustand = 12;
				startTimer(&timer);
            }
            if(eventIsSet(EV_TASTER_R)) {
				cancelTimer(&timer);
                drehen(umdrehen); fahren(1);
                zustand = 7;
                startTimer(&timer);
            }
            if(eventIsSet(EV_STARTZUSTAND)) {
                fahren(2); drehen(rechts);
                zustand = 4;
                clearEvent(EV_STARTZUSTAND);
                startTimer(&timer);
            } break;
    }
    sprintf(msg1, "%2d", zustand);
    sprintf(msg2, "%4d", time_left);
    NNXT_LCD_DisplayStringAtLine(0, msg1);
    NNXT_LCD_DisplayStringAtLine(1, msg2);
    Delay(N);
    }
}

void task3() {
    while(1) {
        if( timer.active == true ) {
            time_left = (GetSysTime() - timer.startTime);
            if(time_left > timer.time) {
                timer.active = false;
                setEvent(timer.event);
            }
        }
        Delay(N);
    }
}

int main() {
    MotorPortInit(Port_A);
    MotorPortInit(Port_B);
    SensorConfig(Port_0, SensorTouch);
    SensorConfig(Port_3, SensorTouch);

    CreateTask(task1);
    CreateTask(task2);
    CreateTask(task3);
    StartTask(task1);
    StartTask(task2);
    StartTask(task3);

    StartScheduler();

    return 0;
}

void fahren(uint8_t schritte) {
    for(uint8_t i = 0; i < schritte; i++) {
        Motor_Drive(Port_A, Motor_dir_forward, 35);
        Motor_Drive(Port_B, Motor_dir_forward, 35);
        Delay(1000);
    }
    Motor_Stop(Port_A, Motor_stop_break);
    Motor_Stop(Port_B, Motor_stop_break);
}

void drehen(enum drehung x) {
    if(x == links) {
        Motor_Drive(Port_A, Motor_dir_forward, 35);
        Motor_Drive(Port_B, Motor_dir_backward, 35);
        Delay(1300);
    }
    if(x == umdrehen) {
        Motor_Drive(Port_A, Motor_dir_forward, 35);
        Motor_Drive(Port_B, Motor_dir_backward, 35);
        Delay(2000);
    }
    if(x == rechts) {
        Motor_Drive(Port_A, Motor_dir_backward, 35);
        Motor_Drive(Port_B, Motor_dir_forward, 35);
        Delay(1300);
    }
    Motor_Stop(Port_A, Motor_stop_break);
    Motor_Stop(Port_B, Motor_stop_break);
}
