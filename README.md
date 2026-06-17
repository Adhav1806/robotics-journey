# robotics-journey
A documented record of my path toward mechatronics engineering.

### Project 1: Blinking LED
Built the standard blink sketch. Learned pinMode, digitalWrite, delay.
### Project 2: Button-controlled LED
Used a breadboard and switch to toggle an LED. Learned digitalRead and pull-down resistor logic.
### Mistake: Motor brownout
Tried to drive a DC motor directly from pin 13. Arduino reset every time — the motor was pulling more current than the pin could supply. Learned I need an L298N motor driver. 
