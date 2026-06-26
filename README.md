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
