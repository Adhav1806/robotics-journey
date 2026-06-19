int readval;
int pinno = 2;
int oppin = 3;
float brighti = 5;
int prevstate;
void setup() {
pinMode(oppin, OUTPUT);
pinMode(pinno, INPUT_PULLUP);
Serial.begin(9600);
}

void loop() {
  readval = digitalRead(pinno); 
  if (prevstate == 1 && prevstate != readval){
    brighti += 45;
    
  }
  if (brighti > 255){
    brighti = 0;
  }
  analogWrite(oppin, brighti);
  delay(500);
  prevstate = readval;
}



