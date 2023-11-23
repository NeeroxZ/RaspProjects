#include <wiringPi.h>
#include <signal.h>

#define GREEN 25
#define RED 24

int blink = 1;

// Diese Funktion wird aufgerufen, wenn ein Signal (z.B. Strg+C) empfangen wird
void cleanup(int sign){
    blink = 0;
}

int main(void){
    // Signal-Handler für Strg+C, Strg+Z und SIGHUP registrieren
    signal(SIGINT, cleanup);
    signal(SIGTERM, cleanup);
    signal(SIGHUP, cleanup);

    // Initialisiere die WiringPi-Bibliothek
    wiringPiSetup();

    // Setze den Modus der Pins auf Ausgang
    pinMode(GREEN, OUTPUT);
    pinMode(RED, OUTPUT);

    // Schleife, die solange läuft wie 'blink' gleich 1 ist
    while(blink) {
        // Grün leuchtet, Rot aus
        digitalWrite(GREEN, HIGH);
        delay(5000); // Warte 5 Sekunden
        digitalWrite(GREEN, LOW);

        // Rot leuchtet, Grün aus
        digitalWrite(RED, HIGH);
        delay(5000); // Warte 5 Sekunden
        digitalWrite(RED, LOW);
    }

    // Schalte die LEDs aus
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, LOW);

    // Setze den Modus der Pins auf Eingang
    pinMode(GREEN, INPUT);
    pinMode(RED, INPUT);

    return 0;
}
