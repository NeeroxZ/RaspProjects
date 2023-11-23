#include <stdio.h>
#include <pigpio.h>
#include <unistd.h>
#include <signal.h>


#define LED_GREEN 26 // GPIO-Pin für die LED GRÜN
#define LED_RED 19 // GPIO-Pin für die LED GRÜN
#define BUTTON_PIN 20

void cleanup(int sign){
        gpioWrite(LED_GREEN, PI_LOW); // LED ausschalten
        gpioWrite(LED_RED, PI_LOW); // LED ausschalten

        gpioSetMode(LED_GREEN, PI_INPUT);
        gpioSetMode(LED_RED, PI_INPUT);
}

int main(void) {
    if (gpioInitialise() < 0) {
        fprintf(stderr, "Error initializing pigpio\n");
        return 1;
    }

    gpioSetMode(BUTTON_PIN, PI_INPUT);
    gpioSetPullUpDown(BUTTON_PIN, PI_PUD_UP);
    
    int lastButtonState = PI_HIGH; // Annahme, dass der Button am Anfang nicht gedrückt wird

     while (1) {
        int buttonState = gpioRead(BUTTON_PIN);

        if (buttonState != lastButtonState) {
            printf("Button State: %d\n", buttonState);
            lastButtonState = buttonState;
            gpioSetMode(LED_GREEN, PI_OUTPUT);
            gpioWrite(LED_GREEN, PI_HIGH); // LED einschalten
        }

        gpioWrite(LED_GREEN, PI_LOW); // LED ausschalten
        gpioWrite(LED_RED, PI_LOW); // LED ausschalten

        gpioDelay(100000); // Pause von 100ms
    }


    gpioTerminate();

    return 0;
}
