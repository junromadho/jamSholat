HUB08 library
--------------

A library for driving the 512 pixel dot matrix LED display "HUB08", a 64 x 32 layout.

Includes:
- High speed display connection straight to GPIO port and pins.
- A full 5 x 7 pixel font set and character routines for display.
- A numerical and symbol 6 x 16 font set with a colon especially for clocks and other fun large displays.
- Special graphics modes: Normal, Inverse, Toggle, OR and NOR!
- Clear screen with all pixels off or on.
- Point to point line drawing.
- Circle drawing.
- Box (rectangle) drawing, border and filled versions.
- Test pattern generation.


USAGE NOTES
-----------

- Place the HUB08 library folder into the "arduino/libraries/" folder of your Arduino installation.
- Get the TimerOne library from here: http://code.google.com/p/arduino-timerone/downloads/list
  or download the local copy from the HUB08 library page (which may be older but was used for this creation)
  and place the TimerOne library folder into the "arduino/libraries/" folder of your Arduino installation.
- Restart the IDE.
- In the Arduino IDE, you can open File > Examples > HUB08 > HUB08_demo, or HUB08_clock_readout, and get it
  running straight away!

* The HUB08 comes with a pre-made data cable and HUB08CON connector board so you can plug-and-play straight
  into any regular size Arduino Board (Uno, EtherTen, USBDroid, etc)
  
* Please note that the Mega boards have SPI on different pins, so this library does not currently support
  the HUB08CON connector board for direct connection to Mega's, please jumper the HUB08CON pins to the
  matching SPI pins on the other header on the Mega boards.

