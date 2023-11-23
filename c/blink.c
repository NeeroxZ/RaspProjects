#include <wiringPi.h>
#include <signal.h>

#define GREEN 25
#define RED 24

int blink = 1;

void cleanup(int sign){
	blink = 0;
}

int main(void){
	signal(SIGINT , cleanup);
	signal(SIGTERM , cleanup);
	signal(SIGHUP, cleanup);
        wiringPiSetup();
        pinMode(GREEN, OUTPUT);
        pinMode(RED, OUTPUT);

        while(blink) {

                digitalWrite(GREEN, HIGH);
                delay(5000);
                digitalWrite(GREEN, LOW);
                digitalWrite(RED, HIGH);
                delay(5000);
                digitalWrite(RED, LOW);

        }
	digitalWrite(GREEN, LOW);       
	digitalWrite(RED, LOW);

	pinMode(GREEN, INPUT);
	pinMode(RED, INPUT);

        return 0;
}
