# robotics-journey
A documented record of my path toward mechatronics engineering.

## Day 1 — 17 June 2026
 
### Project 1: Blinking LED
Built the standard blink sketch. Learned pinMode, digitalWrite, delay.
### Project 2: Button-controlled LED
Used a breadboard and switch to toggle an LED. Learned digitalRead and pull-down resistor logic.
### Mistake: Motor brownout
Tried to drive a DC motor directly from pin 13. Arduino reset every time — the motor was pulling more current than the pin could supply. Learned I need an L298N motor driver. 
### Project 3: Binary LED counter
Made a binary counter using a breadboard and 4 LEDs that count from 0 to 15 in binary, on being 1 and off being 0. Followed Paul Mcwhorters Arduino series. The repeated digitalWrite commands for each and every single number proved to be highly tedious to type. Messed up with the delay and had to change it all over again using a variable which i forgot to add the first time.
## Day 19 June 2026
### Project 4: LED Brightness Increment Device
Made a LED brightness increment device. Increases the brightness of the LED every click of the switch. Uses a variable to store the state of the switch and stores it ever iteration of the loop. If the state of the swtich becomes 0, and the last iteration's state was 1 it increases the LED. It uses a previous state variable as to not increment upon just holding the button. It only increments upon clicking once. 
Errors: Wired the LED and switch system together, which ended up not working. Took some help and realised that i have to separate both the systems and use code to unite them. Multple code errors aswell that got fixed with time.
[View code](projects/day2-button-brightness/led_brightness_increment.ino)
## Day 22 June 2026
### Project 5: HC-SR04 Distance Sensor:
Used the HC-SR04 sensor, arduino, and the IDE to measure distance using the sensor. There are 4 pins on the sensor. The VCC which has a 5 volt supply at all times, the trig pin which stays on a LOW signal for 2 microseconds to clear out noise from previous readings, then turns high for 10 microseconds which emits the sonic pulse, and turns LOW instantly, the echo pin then switches to HIGH and stays that way until it recieves the sonic, it measuers how long it stays HIGH and outputs that in microseconds. After running some calculations we are able to find distance in centimeteres. Some times it outputs a 0 reading which is due to the sensor not being able to complete its full cycle before the next pulse fires, thus, we add a delay of 60 milliseconds to give it time to clear the past reading. 
[View Code](projects/day3-hc-sr04/Sonic_Sensor.ino)
## Day 23-25 June 2026
### Project 6: Servo Sweep (0-180 degrees), with HC-SR04 distance reading at each angle, printing angle + distance to serial monitor.
### Bugs:
- = vs == inside the if condition.
- pulseIn default timeout causes block 1 second per step. Fixed with 38000 microsecond timeout.
- Unsigned long vs float for pulseIn value.
- Serial Port error (unresolved)
 
- Serial port and Serial monitor output fixed.

### What i now understand: 
pulseIn was blocking, it freezes the whole program until the echo returns. 
### Next:
Fix the serial port issue. Verify the serial monitor output. 


[View Code](projects/day4-servo-radar/servo_radar.ino)

[Demo Video](https://youtu.be/ClaX6ihR6sw)

## Day 26 June 2026
### Project 7: Rotary Encoder linked with Servo.
Used the rotary encoder to turn the servo. Every unit turn turns the servo by 5 degrees. The CLK pin on the rotary encoder sends a pulse every turn of the knob. The DT pin sends another pulse slightly out of sync with the CLK pin. Comparing CLK output to the DT output gives us the direction of the turn. If CLK and DT are equal, then the knob has been turned left, and if they are not equal, it has been turned right. The SW pin acts as the button of the encoder knob. Pressing the knob sends a LOW signal to the rotary encoder. We use this to reset the servo's position back to 90 degrees. The servo starts at 90 degrees and turns by increments of 5 every unit turn of the knob. Upon pressing the knob, the servo resets to 90 degrees.
### Bugs: 
- After coding the SW pin to reset the servo position to 90 degrees, the mechanism would stop working entirely, occassionally jittering. This happened due to the pin floating between HIGH and LOW. The fix for this was to use INPUT_PULLUP which used the internal pullup resistor pulls the pin firmly to HIGH or LOW and doenst float.
- The servo has a limit of 180 degrees of rotation. The starting position of the servo is 90 degrees in this project. If the knob is turned even after the servo hits 180 or 0 degrees, the servo would not move but the theta value in the code would keep incrementing. For example, if we turned the knob 5 units after it reached 180 or 0 degrees, we have to turn 5 units in the opposite direction to have it move again. We solve this issue by clamping theta to 180 or 0 if it reaches the limit, even if it is rotated beyond.

### What I now understand:
- INPUT_PULLUP is important so that the value doenst hover between HIGH and LOW.
- Learnt how to use the rotary encoder.

[View Code](projects/day5-rotary-encoder-servo/rotary_encoder_servo.ino)
[Demo Video](https://youtu.be/sYo4ep5gtlI)

## Day 26: Refactoring Code For Two Projects:
### Project 6 Refactor:
### What it does:
- Same as previous. A servo spins with a HR-SR04 mounted on it (unmounted currently). The sensor then prints the distance readings, also easily visualised through the serial plotter.
## Refactor: Before and After

**Before — all logic in `loop()`:**
```cpp
void loop() {
  for (int theta = 0; theta <= 180; theta++) {
    myServo.write(theta);
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    dur = pulseIn(echo, HIGH, 38000);
    dist = dur / 58;
    if (dur > 0) {
    Serial.println(dist);
    }
    delay(100);
  }
  for (int theta = 180; theta >= 0; theta--) {
    myServo.write(theta);
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    dur = pulseIn(echo, HIGH, 38000);
    dist = dur / 58;
    if (dur > 0) {
    Serial.println(dist);
    }
    delay(100);
  }
}
```

**After — functions only:**
```cpp
void loop() {
  dist= sensorScan();
  theta += sweepdir;
  sweepdir = updateDirection(sweepdir, theta);
  servoMove(theta);
  Serial.println(dist);
  delay(60);
}
```
### Reasons for Refactoring:
-Previously, all logic sat inside loop(), making it inconvenient and difficult to isolate which part of the code controlled what. Refactoring using functions means each responsibility has a name. Debugging is much simpler and is targetted.

### Project 7 Refactor;
### What it Does:
- Same as before. Turning the knob of the rotary encoder turned the servo by 5 degrees every unit turn. Pressing down on the rotary encoder reset the servo
position back to 90 degrees.

### Refactor: Before and After

**Before — all logic in `loop()`:**
```cpp
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
```

**After — functions only:**
```cpp
void loop() {
direction = ReadEncoder();
theta += direction * 5;
theta = clampTheta(theta);
updateServo();
lastclkstate = clkstate;

}
```
### Reasons for Refactor:
- Previous loop() was messy and unordered. New code has named functions which make it easy for debugging.
- Understood Scope and State Sequencing. In my current code there are two kinds of scope. Global and Local Scope. Global is declared outside the functions. Every function can see them and modify them freely. Local scope only exists within the function and only exists then the function runs. In clampTheta, the parameter 'theta' is a local copy. Changing it inside the function doesnt affect the Global theta unless we assign the return value back. State sequencing is when certain variables exist to remember what previously happened. Usually to compare it with the current state. This is useful in the LED dimming project aswell as the rotary encoder project. One good example within the rotary encoder project is when we use lastclkstate that exists to compare it with clkstate. If they are not equal, then it has turned. 

## Day 27 June 2026
### Project 8: Servo and photoresistor mechanism;
- Two photoresistors are connected a certain distance apart from each other in a voltage divider. The analog readings output values from 0-1023, based on amount of voltage. The photoresistor changes resistancce based on amount of light hitting it.The servo stays in a neutral position of 90 degrees pointing at nothing until there is a difference in light hitting the photoresistors. More light, less resistance and vice versa. A servo is then connected to this mechanism and through code, the servo points the photoresistor that is receiving more light.
- Learnt the map() function today. It rescales a value from one range to another. In this project, the map function rescaled the analog readings of the photoresistor to angles for the servo motor. 
### Bugs and Issues:
- Tried powering the servo through pin 13. The GPIO pins dont supply enough current for a servo. This could have caused a brown-out or damaged the servo.
- Header pin broke and got stuck inside the servo pin slot. Removed it using a needle.
- Confused myServo.write() with myServo.attach().

[View Code]()
