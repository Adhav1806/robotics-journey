#include <Servo.h>

Servo myServo;

int trig = 10;
int echo = 8;
int thetapin = 9;
float readval;
int theta;
unsigned long dur;
float dist;

void setup() {
  myServo.attach(thetapin);
  myServo.write(0);
  delay(1000);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop() {
  for (int theta = 0; theta <= 180; theta++) {
    myServo.write(theta);
    Serial.print("Angle is ");
    Serial.println(theta);
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    dur = pulseIn(echo, HIGH, 38000);
    dist = dur / 58;
    Serial.print("Distance is ");
    Serial.println(dist);
    delay(15);
  }
  for (int theta = 180; theta >= 0; theta--) {
    myServo.write(theta);
    Serial.print("Angle is ");
    Serial.println(theta);
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    dur = pulseIn(echo, HIGH, 38000);
    dist = dur / 58;
    Serial.print("Distance is ");
    Serial.println(dist);
    delay(15);
  }
}