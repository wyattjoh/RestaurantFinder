Restraunt Finder
=================
An Arduino program designed for the MEGA 2560 to display a scrollable map to select restraunts from a onboard database.

###Pin Setup
-------------
####Joystick

+ (0A) Joystick - Horizontal
+ (1A) Joystick - Vertical
+ (9D) Joystick - Button

####Potentialometer

+ (2A) Potentialometer - Zoom

####LCD

+ (8D) LCD - Reset
+ (7D) LCD - DC
+ (5D) LCD - CARD_CS
+ (6D) LCD - TFT_CS
+ (51D) LCD - MOSI
+ (52D) LCD - SCK
+ (50D) LCD - MISO

###Compiling and Uploading
--------------------------
The `Makefile` is already configured to compile and upload the arduino code.

####Compiling
1. `make`

####Uploading
1. `arduino-port-select`
2. `make upload`




###Debug
--------
Debug mode can be enabled from the `debug.h` file. `#define DEBUG 1` indicates that debug mode is on, `#define DEBUG 0` indicates that debug mode is off.