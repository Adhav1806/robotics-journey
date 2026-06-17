# robotics-journey
A documented record of my path toward mechatronics engineering.

## Day 1 — 17 June 2026
 
### Project 1: Blinking LED
Built the standard blink sketch. Learned pinMode, digitalWrite, delay.
### Project 2: Button-controlled LED
Used a breadboard and switch to toggle an LED. Learned digitalRead and pull-down resistor logic.
### Mistake: Motor brownout
Tried to drive a DC motor directly from pin 13. Arduino reset every time — the motor was pulling more current than the pin could supply. Learned I need an L298N motor driver. 
### Project 3:
Made a binary counter using a breadboard and 4 LEDs that count from 0 to 15 in binary, on being 1 and off being 0. Followed Paul Mcwhorters Arduino series. The repeated digitalWrite commands for each and every single number proved to be highly tedious to type. Messed up with the delay and had to change it all over again using a variable which i forgot to add the first time.
