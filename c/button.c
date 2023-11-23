#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>

#include <signal.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define BUTTON_PIN 20
#define LED_PIN 24

void cleanup(int sign){
    gpioWrite(BUTTON_PIN, PI_LOW);
    gpioWrite(LED_PIN, PI_LOW);

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

    gpioSetMode(LED_PIN, PI_OUTPUT);

    int lastButtonState = PI_HIGH; // Annahme, dass der Button am Anfang nicht gedrückt wird

    while (1) {
        int buttonState = gpioRead(BUTTON_PIN);

        if (buttonState != lastButtonState) {
            printf("Button State: %d\n", buttonState);
            lastButtonState = buttonState;
        }

        gpioWrite(LED_PIN, !buttonState); // Die LED leuchtet, wenn der Button nicht gedrückt wird
        gpioDelay(100000); // Pause von 100ms
    }

    return 0;
}
