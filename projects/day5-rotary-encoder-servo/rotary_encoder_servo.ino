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
void setup() {
myServo.attach(thetapin);
myServo.write(90);
pinMode(clk, INPUT);
pinMode(dt, INPUT);
pinMode(sw, INPUT_PULLUP);
lastclkstate = digitalRead(clk);
}

void loop() {
clkstate = digitalRead(clk);
if (lastclkstate != clkstate){
  dtstate = digitalRead(dt);
  if (lastclkstate == dtstate){
    theta -= 5;
    if (theta > 180) theta = 180;
    if (theta < 0) theta = 0;
    myServo.write(theta);
    
  } else {
    theta += 5;
    if (theta > 180) theta = 180;
    if (theta < 0) theta = 0;
    myServo.write(theta);
    
  }
  lastclkstate = clkstate;
}
swstate = digitalRead(sw);
if (swstate == 0) {
  theta = 90;
  myServo.write(90);
}

}
