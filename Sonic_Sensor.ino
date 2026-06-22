int trig = 9;
float dur;
float dist;
int echo = 8;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(trig, OUTPUT);
pinMode(echo, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trig, LOW);
delayMicroseconds(2);
digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);
dur = pulseIn(echo, HIGH);
dist = dur/58;
Serial.println(dist);
delay(60);
}
