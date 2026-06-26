#include <Servo.h>
Servo myServo;
int clk = 2;
int dt = 3;
int sw = 4;
int clkstate;
int dtstate;
int thetapin = 9;
int theta = 90;
int lastclkstate;
int swstate;
int direction;
void setup() {
myServo.attach(thetapin);
myServo.write(90);
pinMode(clk, INPUT);
pinMode(dt, INPUT);
pinMode(sw, INPUT_PULLUP);
lastclkstate = digitalRead(clk);
}

int ReadEncoder(){
  clkstate = digitalRead(clk);
  dtstate = digitalRead(dt);
  if (clkstate != lastclkstate){
    if (dtstate != lastclkstate){
      return 1;
    } else {
      return -1;
    }
  } else {
    return 0;
  }
}

int clampTheta(int theta){
  if (theta > 180) return 180;
  if (theta < 0 ) return 0;
  return theta;
}

void updateServo(){
  swstate = digitalRead(sw);
  if (swstate == 0){
    theta = 90;
  }
  myServo.write(theta);
}

void loop() {
direction = ReadEncoder();
theta += direction * 5;
theta = clampTheta(theta);
updateServo();
lastclkstate = clkstate;

}
