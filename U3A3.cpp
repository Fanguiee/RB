#include "nnxt.h"
#define N 100

enum dir {f_links, f_rechts, f_oben};
enum drehung {d_links, d_umdrehen, d_rechts};

struct Robot1 {
    uint8_t position = 4;
    dir ausrichtung = f_oben;//
} Robots;

uint8_t zustand = 4;

int main(){
    while(1) {
    switch (zustand) {
        case 3:
        case 4:
            if(taster == L) {
                drehen(d_links); fahren(f_links);
                zustand = 3;
            }
            if(taster == R) {
                drehen(d_rechts); fahren(f_rechts);
                zustand = 5;
            } break;
        case 5:
    }
    Delay(N);
    }
   	return 0;
}

void fahren(dir a) {
    if (a == links)
        Robot1.position--;
    if (a == rechts)
        Robot1.position++;
}

void drehen(drehung b) {
    if(b == d_links)
        Robot1.ausrichtung = f_links;
    if(b == d_rechts)
        Robot1.ausrichtung = f_rechts;
    if(b == d_umdrehen) {
        if(Robot1.ausrichtung == f_links)
            Robot1.ausrichtung = f_rechts;
        if(Robot1.ausrichtung == f_rechts)
            Robot1.ausrichtung = f_links;
    }
}
