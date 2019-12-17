#include "echo.h"
#include <Arduino.h>
 
void echo_init()
{
    pinMode(PIN_ULTRASONIC_TRIG, OUTPUT);
    pinMode(PIN_ULTRASONIC_ECHO_BACK, INPUT);
    pinMode(PIN_ULTRASONIC_ECHO_LEFT, INPUT);
    pinMode(PIN_ULTRASONIC_ECHO_FRONT, INPUT);
    pinMode(PIN_ULTRASONIC_ECHO_RIGHT, INPUT);

    #ifdef TEST_ECHO
        Serial.begin(9600);
    #endif
}

pin_t direction_to_echo_pin(direction_t dir)
{
    if(dir == DIRECTION_ID_FRONT)
        return PIN_ULTRASONIC_ECHO_FRONT;
    else if(dir == DIRECTION_ID_BACK)
        return PIN_ULTRASONIC_ECHO_BACK;
    else if(dir == DIRECTION_ID_LEFT)
        return PIN_ULTRASONIC_ECHO_LEFT;
    else if(dir == DIRECTION_ID_RIGHT)
        return PIN_ULTRASONIC_ECHO_RIGHT;

    return 0;
}

float echo_test_mm(uint8_t pin)
{
	long duration;
	float myout;

	digitalWrite(PIN_ULTRASONIC_TRIG, LOW);
    delayMicroseconds(5);
    digitalWrite(PIN_ULTRASONIC_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_ULTRASONIC_TRIG, LOW);
 
    pinMode(pin, INPUT);

    #ifdef ECHO_PULSEIN_LIMIT
    duration = pulseIn(pin, HIGH, ECHO_PULSEIN_LIMIT);
    #else
    duration = pulseIn(pin, HIGH);
    #endif

    myout = (duration);
    myout *= (0.171821f);
    
    return myout;
}

#ifdef TEST_ECHO
void echo_print_all()
{
   
        char buf[1024];
        int offset = 0;

        offset += sprintf(buf+offset, "F: %4d ",(int) echo_test_mm(PIN_ULTRASONIC_ECHO_FRONT));
        delay(10);
        offset += sprintf(buf+offset, "R: %4d ",(int) echo_test_mm(PIN_ULTRASONIC_ECHO_RIGHT));
        delay(10);
        offset += sprintf(buf+offset, "B: %4d ",(int) echo_test_mm(PIN_ULTRASONIC_ECHO_BACK));
        delay(10);
        offset += sprintf(buf+offset, "L: %4d ",(int) echo_test_mm(PIN_ULTRASONIC_ECHO_LEFT));
        delay(10);

        Serial.println(buf);
}
#endif
