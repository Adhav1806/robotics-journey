#include <Servo.h>

Servo myServo;

int trig = 10;
int echo = 8;
int thetapin = 9;
float readval;
int theta;
unsigned long dur;
float dist;
int sweepdir = 1;

void setup() {
    Serial.begin(9600);
    myServo.attach(thetapin);
    myServo.write(0);
    delay(1000);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

float sensorScan(){
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    dur = pulseIn(echo, HIGH, 38000);
    if (dur == 0) return -1;
    dist = dur / 58.0;
    return dist;
}

int updateDirection(int dir, int angle){
  if (angle >=180) return-1;
  if (angle <= 0) return 1;
  return dir;
}


void servoMove(int angle){
  myServo.write(angle);
}

void loop() {
  dist= sensorScan();
  theta += sweepdir;
  sweepdir = updateDirection(sweepdir, theta);
  servoMove(theta);
  Serial.println(dist);
  delay(60);
}
