#include <stdio.h>
#include <pigpio.h>
#include <unistd.h>

#define LED_PIN 26 // GPIO-Pin für die LED

int main(void) {
    if (gpioInitialise() < 0) {
        fprintf(stderr, "Error initializing pigpio\n");
        return 1;
    }

    gpioSetMode(LED_PIN, PI_OUTPUT);
    gpioWrite(LED_PIN, PI_HIGH); // LED einschalten

    sleep(2); // Warte 2 Sekunden

    gpioWrite(LED_PIN, PI_LOW); // LED ausschalten

    gpioTerminate();

    return 0;
}