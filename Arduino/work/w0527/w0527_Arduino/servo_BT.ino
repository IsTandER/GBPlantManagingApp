#include <Servo.h>
#include <SoftwareSerial.h>
int servoPin = 9;
SoftwareSerial BTserial(2,3);
Servo servo;
int angle = 0;  // servo position in degrees

void setup() {
    servo.attach(servoPin);
    BTserial.begin(9600);
}

void loop() {

    // scan from 0 to 180 degrees
    if(BTserial.available()){
    char bt;
    if(bt == '1'){
    for(angle = 0; angle < 180; angle++) {
        servo.write(angle);
        delay(0);
    }
    }
    
    // now scan back from 180 to 0 degrees
    if(bt == '0'){
    for(angle = 180; angle > 0; angle--) {
        servo.write(angle);
        delay(0);
    }
    }
}
}
