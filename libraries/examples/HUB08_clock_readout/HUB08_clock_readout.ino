/*--------------------------------------------------------------------------------------

 HUB08_clock_readout.cpp 
   Example clock readout project for the 512 LED matrix display
   panel arranged in a 32 x 16 layout.

 Note that the HUB08 library uses the SPI port for the fastest, low overhead writing to the
 display. Keep an eye on conflicts if there are any other devices running from the same
 SPI port, and that the chip select on those devices is correctly set to be inactive
 when the HUB08 is being written to.

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

 This example code is in the public domain.
 The HUB08 library is open source (GPL), for more see HUB08.cpp and HUB08.h

--------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
  Includes
--------------------------------------------------------------------------------------*/
#include <SPI.h>        //SPI.h must be included as HUB08 is written by SPI (the IDE complains otherwise)
#include <HUB08.h>        //
#include <TimerOne.h>   //
#include "Arial_black_16.h"

//Fire up the HUB08 library as hub08
HUB08 hub08(1,1);

/*--------------------------------------------------------------------------------------
  Interrupt handler for Timer1 (TimerOne) driven HUB08 refresh scanning, this gets
  called at the period set in Timer1.initialize();
--------------------------------------------------------------------------------------*/
void ScanHUB08()
{ 
  hub08.scanDisplayBySPI();
}

/*--------------------------------------------------------------------------------------
  Show clock numerals on the screen from a 4 digit time value, and select whether the
  flashing colon is on or off
--------------------------------------------------------------------------------------*/
void ShowClockNumbers( unsigned int uiTime, byte bColonOn )
{
   hub08.clearScreen(true);
   hub08.drawChar(  1,  3,'0'+((uiTime%10000)/1000), GRAPHICS_NORMAL );   // thousands
   hub08.drawChar(  8,  3, '0'+((uiTime%1000) /100),  GRAPHICS_NORMAL );   // hundreds
   hub08.drawChar( 17,  3, '0'+((uiTime%100)  /10),   GRAPHICS_NORMAL );   // tens
   hub08.drawChar( 25,  3, '0'+ (uiTime%10),          GRAPHICS_NORMAL );   // units
   if( bColonOn )
      hub08.drawChar( 15,  3, ':', GRAPHICS_OR     );   // clock colon overlay on
   else
      hub08.drawChar( 15,  3, ':', GRAPHICS_NOR    );   // clock colon overlay off
}

/*--------------------------------------------------------------------------------------
  setup
  Called by the Arduino architecture before the main loop begins
--------------------------------------------------------------------------------------*/
void setup(void)
{
   
   //initialize TimerOne's interrupt/CPU usage used to scan and refresh the display
   Timer1.initialize( 5000 );           //period in microseconds to call ScanHUB08. Anything longer than 5000 (5ms) and you can see flicker.
   Timer1.attachInterrupt( ScanHUB08 );   //attach the Timer1 interrupt to ScanHUB08 which goes to hub08.scanDisplayBySPI()

   //clear/init the HUB08 pixels held in RAM
   hub08.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
   hub08.selectFont(Arial_Black_16);

}

/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
--------------------------------------------------------------------------------------*/
void loop(void)
{
   unsigned int ui;
   
   // 10 x 14 font clock, including demo of OR and NOR modes for pixels so that the flashing colon can be overlayed
   ui = 1234;
   ShowClockNumbers( ui, true );
   delay( 1000 );
   ShowClockNumbers( ui, false );
   delay( 1000 );
   ShowClockNumbers( ui, true );
   delay( 1000 );
   ShowClockNumbers( ui, false );
   delay( 1000 );

   ui = 2345;
   ShowClockNumbers( ui, true );
   delay( 1000 );
   ShowClockNumbers( ui, false );
   delay( 1000 );
   ShowClockNumbers( ui, true );
   delay( 1000 );
   ShowClockNumbers( ui, false );
   delay( 1000 );
}
