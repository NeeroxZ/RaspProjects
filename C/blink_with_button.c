#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

#define BUTTON_PIN 20
#define GREEN_LED 26
#define RED_LED 19


void cleanup(int sign){
    gpioWrite(BUTTON_PIN, PI_LOW);
    gpioWrite(GREEN_LED, PI_LOW);
    gpioWrite(RED_LED, PI_LOW);

      gpioSetMode(GREEN_LED, PI_INPUT);
    gpioSetMode(RED_LED, PI_INPUT);

    gpioSetMode(BUTTON_PIN, PI_INPUT);
    gpioSetPullUpDown(BUTTON_PIN, PI_PUD_DOWN);

    gpioTerminate();
    exit(0);
}

int main(void){
    if (gpioInitialise() < 0) {
        fprintf(stderr, "Error initializing pigpio\n");
        return 1;
    }

    gpioSetSignalFunc(SIGINT, cleanup);
    gpioSetSignalFunc(SIGTERM, cleanup);
    gpioSetSignalFunc(SIGHUP, cleanup);

    gpioSetMode(BUTTON_PIN, PI_INPUT);
    gpioSetPullUpDown(BUTTON_PIN, PI_PUD_UP);

    gpioSetMode(GREEN_LED, PI_OUTPUT);
    gpioSetMode(RED_LED, PI_OUTPUT);


    int lastButtonState = PI_HIGH; // Annahme, dass der Button am Anfang nicht gedrückt wird

    while (1) {
        int buttonState = gpioRead(BUTTON_PIN);

        if (buttonState == 0) {
            printf("Button State: %d\n", buttonState);
            gpioWrite(GREEN_LED, !buttonState); // Die LED leuchtet, wenn der Button gedrückt wird
            gpioDelay(100000);
        }else{
            gpioWrite(GREEN_LED, PI_LOW);
            gpioWrite(RED_LED, PI_HIGH); // Die LED leuchtet, wenn der Button nicht gedrückt wird 
            gpioDelay(200000);
            gpioWrite(RED_LED, PI_LOW);
        }
        
        gpioDelay(200000);
    }

    return 0;
}
