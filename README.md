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
## Day 23 June 2026
### Project 6: Servo Sweep (0-180 degrees), with HC-SR04 distance reading at each angle, printing angle + distance to serial monitor.
### Bugs:
- = vs == inside the if condition.
- pulseIn default timeout causes block 1 second per step. Fixed with 38000 microsecond timeout.
- Unsigned long vs float for pulseIn value.
- Serial Port error (unresolved)

### What i now understand: 
pulseIn was blocking, it freezes the whole program until the echo returns. 
### Next:
Fix the serial port issue. Verify the serial monitor output. 
[View Code](projects/day4-servo-radar/servo_radar.ino)
