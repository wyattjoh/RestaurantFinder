#Restaurant Finder
*Authors: Wyatt Johnson (1230799), Andre Charest (1342401)*


An Arduino program designed for the MEGA 2560 to display a scrollable map to select restaurants from a onboard database.

*NOTE: This project requires special wiring instructions for the Joystick Button as it is attached as an interrupt, denounced using a capacitor denouncing circuit as detailed below. If any complications occur with setup, please ask one of the group members listed above for assistance.*

##Pin Setup

The pin configuration is standard, with the exception of the *Joystick - Button* which is attached to *Digital Pin 21 / Interrupt 2* required to be on the interrupt pin to work.

For the purposes of this document, *# A* will refer to an analogue pin, while *# D* will refer to a digital pin.

###Joystick

* (*0 A*) Joystick - Horizontal
* (*1 A*) Joystick - Vertical
* (*21 D*) Joystick - Button

Joystick Wiring Diagram:

<pre>
GND --- -C1+ --- + --- R1 --- Joystick Button
				 |
			     |
	Interrupt Pin 2 (Digital Pin 21)



C1-> 1 micro Farad capacitor
R1-> 560 Ohm resistor
</pre>

As sourced from [Course Website](http://ugweb.cs.ualberta.ca/~c296/ConcreteComputing/pending-edits/DigitalInputDebounce.txt "Course Website, Pending Edits").

Where the current across the resistor can be defined as:

![http://en.wikipedia.org/wiki/Capacitor](http://upload.wikimedia.org/math/2/c/4/2c407669187a342a314a2b47662df875.png)

For voltage across the resistor (`V_0`), with resistance (`R`) after time (`t`) with (`tou_0`) representing our time constant of the RC circuit which will supplement the circuit with the necessary voltage from the charged capacitor while giving the circuit time to denounce, hence resulting in a clean wave front for use with a software based interrupt. `i(t)` defines the current over time for the given circuit.

###LCD

+ (*8 D*) LCD - Reset
+ (*7 D*) LCD - DC
+ (*5 D*) LCD - CARD_CS
+ (*6 D*) LCD - TFT_CS
+ (*51 D*) LCD - MOSI
+ (*52 D*) LCD - SCK
+ (*50 D*) LCD - MISO

###Using
---
1. Power up the Arduino with the program uploaded
2. Move joystick around until you find a location for which you would like to determine the closest restaurant
3. Click the Joystick to load the restaurants
4. Move the Joystick up and down to scroll through the list of all restaurants sorted by a [comb_sort](http://en.wikipedia.org/wiki/Comb_sort) algorithm.

###Compiling and Uploading
---
The `Makefile` is already configured to compile and upload the Arduino code.

####Compiling
1. `make`

####Uploading
1. `arduino-port-select`
2. `make upload`



###Debug
--------
Debug mode can be enabled from the `debug.h` file. `#define DEBUG 1` indicates that debug mode is on, `#define DEBUG 0` indicates that debug mode is off. There are also various levels of debug, as selected by increasing the debug level up to level 3, which is the maximum debug level.