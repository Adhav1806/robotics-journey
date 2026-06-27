#include <Servo.h>
Servo myServo;
int readpin = A1;
int readpin2 = A5;
int servopin = 9;
int fvolt1;
int fvolt2;
int diff;
int fval;

void setup() {
pinMode(readpin, INPUT);
Serial.begin(9600);
myServo.attach(servopin);

}

int sensor1(){
  int readval1 = analogRead(readpin);
  Serial.println(readval1);
  return readval1;
}

int sensor2(){
  int readval2 = analogRead(readpin2);
  Serial.println(readval2);
  return readval2;
}

void loop() { 
  fvolt1 = sensor1();
  fvolt2 = sensor2();
  diff = fvolt1 - fvolt2;
  fval = map(diff, -1023, 1023, 0, 180);
  myServo.write(fval);
  delay(30);
}
