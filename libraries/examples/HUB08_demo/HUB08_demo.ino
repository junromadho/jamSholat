/*--------------------------------------------------------------------------------------

 HUB08_test.cpp 
   Demo and example project for a 512 LED matrix display
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
   into any regular size Arduino Board (Uno, Freetronics Eleven, EtherTen, USBDroid, etc)
  
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
#include "SystemFont5x7.h"
#include "Arial_black_16.h"

//Fire up the HUB08 library as hub08
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
HUB08 hub08(DISPLAYS_ACROSS, DISPLAYS_DOWN);

/*--------------------------------------------------------------------------------------
  Interrupt handler for Timer1 (TimerOne) driven HUB08 refresh scanning, this gets
  called at the period set in Timer1.initialize();
--------------------------------------------------------------------------------------*/
void ScanHUB08()
{ 
  hub08.scanDisplayBySPI();
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

}

/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
--------------------------------------------------------------------------------------*/
void loop(void)
{
   byte b;
   
   // 10 x 14 font clock, including demo of OR and NOR modes for pixels so that the flashing colon can be overlayed
   hub08.clearScreen( true );
   hub08.selectFont(Arial_Black_16);
   hub08.drawChar(  0,  3, '2', GRAPHICS_NORMAL );
   hub08.drawChar(  7,  3, '3', GRAPHICS_NORMAL );
   hub08.drawChar( 17,  3, '4', GRAPHICS_NORMAL );
   hub08.drawChar( 25,  3, '5', GRAPHICS_NORMAL );
   hub08.drawChar( 15,  3, ':', GRAPHICS_OR     );   // clock colon overlay on
   delay( 1000 );
   hub08.drawChar( 15,  3, ':', GRAPHICS_NOR    );   // clock colon overlay off
   delay( 1000 );
   hub08.drawChar( 15,  3, ':', GRAPHICS_OR     );   // clock colon overlay on
   delay( 1000 );
   hub08.drawChar( 15,  3, ':', GRAPHICS_NOR    );   // clock colon overlay off
   delay( 1000 );
   hub08.drawChar( 15,  3, ':', GRAPHICS_OR     );   // clock colon overlay on
   delay( 1000 );

   hub08.drawMarquee("Scrolling Text",14,(32*DISPLAYS_ACROSS)-1,0);
   long start=millis();
   long timer=start;
   boolean ret=false;
   while(!ret){
     if ((timer+30) < millis()) {
       ret=hub08.stepMarquee(-1,0);
       timer=millis();
     }
   }
   // half the pixels on
   hub08.drawTestPattern( PATTERN_ALT_0 );
   delay( 1000 );

   // the other half on
   hub08.drawTestPattern( PATTERN_ALT_1 );
   delay( 1000 );
   
   // display some text
   hub08.clearScreen( true );
   hub08.selectFont(System5x7);
   for (byte x=0;x<DISPLAYS_ACROSS;x++) {
     for (byte y=0;y<DISPLAYS_DOWN;y++) {
       hub08.drawString(  2+(32*x),  1+(16*y), "freet", 5, GRAPHICS_NORMAL );
       hub08.drawString(  2+(32*x),  9+(16*y), "ronic", 5, GRAPHICS_NORMAL );
     }
   }
   delay( 2000 );
   
   // draw a border rectangle around the outside of the display
   hub08.clearScreen( true );
   hub08.drawBox(  0,  0, (32*DISPLAYS_ACROSS)-1, (16*DISPLAYS_DOWN)-1, GRAPHICS_NORMAL );
   delay( 1000 );
   
   for (byte y=0;y<DISPLAYS_DOWN;y++) {
     for (byte x=0;x<DISPLAYS_ACROSS;x++) {
       // draw an X
       int ix=32*x;
       int iy=16*y;
       hub08.drawLine(  0+ix,  0+iy, 11+ix, 15+iy, GRAPHICS_NORMAL );
       hub08.drawLine(  0+ix, 15+iy, 11+ix,  0+iy, GRAPHICS_NORMAL );
       delay( 1000 );
   
       // draw a circle
       hub08.drawCircle( 16+ix,  8+iy,  5, GRAPHICS_NORMAL );
       delay( 1000 );
   
       // draw a filled box
       hub08.drawFilledBox( 24+ix, 3+iy, 29+ix, 13+iy, GRAPHICS_NORMAL );
       delay( 1000 );
     }
   }

   // stripe chaser
   for( b = 0 ; b < 20 ; b++ )
   {
      hub08.drawTestPattern( (b&1)+PATTERN_STRIPE_0 );
      delay( 200 );      
   }
   delay( 200 );      
   
}

