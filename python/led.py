# Erforderliche Bibliotheken importieren
import RPi.GPIO as GPIO
import time
 
# Konvention für Pinnummerierung festlegen (BCM bzw. Board)
GPIO.setmode(GPIO.BCM)
# Pin mit seiner Nummer und als Ausgang definieren
GPIO.setup(26, GPIO.OUT)
 
# Pin auf 3,3 V schalten
GPIO.output(26, GPIO.HIGH)
# LED nach zwei Sekunden ausschalten
time.sleep(2)
# Pin auf 0 V schalten
GPIO.output(26, GPIO.LOW)
# Verwendete Pins (hier nur BCM-Pin 26) zurücksetzen
GPIO.cleanup()