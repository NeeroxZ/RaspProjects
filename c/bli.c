#include <wiringPi.h>
#include <signal.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//GPIO PINS, BCM numbering

#define RED_BUTTON 16
#define GREEN_BUTTON 20
#define BLUE_BUTTON 21
#define RED_LED 13
#define GREEN_LED 19
#define BLUE_LED 26

void cleanup(int sign){
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);

    pinMode(RED_LED, INPUT);
    pinMode(GREEN_LED, INPUT);
    pinMode(BLUE_LED, INPUT);

    pullUpDnControl(RED_BUTTON, PUD_DOWN);
    pullUpDnControl(GREEN_BUTTON, PUD_DOWN);
    pullUpDnControl(BLUE_BUTTON, PUD_DOWN);

    exit(0);
}

int main(void){
    printf("Init Programm\n"); // Ändere print zu printf
    signal(SIGINT, cleanup);
    signal(SIGTERM, cleanup);
    signal(SIGHUP, cleanup);

    wiringPiSetup();
    
    pinMode(RED_BUTTON, INPUT);
    pinMode(GREEN_BUTTON, INPUT);

    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);

    for(;;){
        int greenButtonState = digitalRead(GREEN_BUTTON);
        printf("Green Button State: %d\n", greenButtonState);
        digitalWrite(GREEN_LED, !digitalRead(GREEN_BUTTON));
        delay(500);
    }

    pause();
    return 0;

}
