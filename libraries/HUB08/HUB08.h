/*--------------------------------------------------------------------------------------

 Note that the HUB08 library uses the SPI port for the fastest, low overhead writing to the
 display. Keep an eye on conflicts if there are any other devices running from the same
 SPI port, and that the chip select on those devices is correctly set to be inactive
 when the HUB08 is being written to.


LED Panel Layout in RAM
                            32 pixels (4 bytes)
        top left  ----------------------------------------
                  |                                      |
         Screen 1 |        512 pixels (64 bytes)         | 16 pixels
                  |                                      |
                  ---------------------------------------- bottom right

 ---
 
 This program is free software: you can redistribute it and/or modify it under the terms
 of the version 3 GNU General Public License as published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with this program.
 If not, see <http://www.gnu.org/licenses/>.

--------------------------------------------------------------------------------------*/
#ifndef HUB08_H_
#define HUB08_H_
#include "Arduino.h"
//Arduino toolchain header, version dependent
#if defined(ARDUINO) && ARDUINO >= 100
	
#else
	#include "WProgram.h"
#endif

//SPI library must be included for the SPI scanning/connection method to the HUB08
//#include "pins_arduino.h"
#include <avr/pgmspace.h>
// #include "Print.h"
//#include <SPI.h>

// ######################################################################################################################
// ######################################################################################################################
#warning CHANGE THESE TO SEMI-ADJUSTABLE PIN DEFS!

// ####################### BRD VER 0.9 ######################################

	
	#define P_A   PB6  //PB13
	#define P_B   PB5  //PB14
	#define P_C   PB4  //PB15
	#define P_D   PB3  //PA12
	#define P_OE  PA15  //PA11
	#define P_R1  PA11  //PA15
	#define P_R2  PA10  //PB3
	#define P_STB PA8  //PB4
	#define P_CLK PB15   //PB5

	#define P_G1  PA12  //PA15
	#define P_G2  PA9   //PB3

	#define P_X   	PB0
	#define P_Y   	PA7
	#define P_push  PA6
	#define OB_Led  PA4   //PA4

	#define pinX 0x0001 //P
	#define pinY 0x0080 //P
	#define pinP 0x0040 //P
	#define pin_OBled  0x0010  //PA4

	#define pinA  0x0040  //PB6
	#define pinB  0x0020  //PB5
	#define pinC  0x0010  //PB4
	#define pinD  0x0008  //PB3
	#define pinOE 0x8000  //PA15
	#define pinR1 0x0800  //PA11
	#define pinR2  0x0400  //PA10
	#define pinSTB 0x0100  //PA8
	#define pinCLK 0x8000  //PB15

	#define pinG1 0x1000  //P
	#define pinG2  0x0200  //P

	//HUB08 I/O pin macros
	#define wA(BIT)      (BIT) ? (GPIOB->regs->BSRR = pinA)   : (GPIOB->regs->BRR = pinA)
	#define wB(BIT)      (BIT) ? (GPIOB->regs->BSRR = pinB)   : (GPIOB->regs->BRR = pinB)
	#define wC(BIT)      (BIT) ? (GPIOB->regs->BSRR = pinC)   : (GPIOB->regs->BRR = pinC)
	#define wD(BIT)      (BIT) ? (GPIOB->regs->BSRR = pinD)   : (GPIOB->regs->BRR = pinD)
	#define wOE(BIT)     (BIT) ? (GPIOA->regs->BSRR = pinOE)  : (GPIOA->regs->BRR = pinOE)
	#define wR1(BIT)     (BIT) ? (GPIOA->regs->BSRR = pinR1)  : (GPIOA->regs->BRR = pinR1)
	#define wR2(BIT)     (BIT) ? (GPIOA->regs->BSRR = pinR2)  : (GPIOA->regs->BRR = pinR2)
	#define wSTB(BIT)    (BIT) ? (GPIOA->regs->BSRR = pinSTB) : (GPIOA->regs->BRR = pinSTB)
	#define wCLK(BIT)    (BIT) ? (GPIOB->regs->BSRR = pinCLK) : (GPIOB->regs->BRR = pinCLK)

	#define wG1(BIT)     (BIT) ? (GPIOA->regs->BSRR = pinG1)  : (GPIOA->regs->BRR = pinG1)
	#define wG2(BIT)     (BIT) ? (GPIOA->regs->BSRR = pinG2)  : (GPIOA->regs->BRR = pinG2)

	#define OBLed(BIT)     (BIT) ? (GPIOA->regs->BSRR = pin_OBled)  : (GPIOA->regs->BRR = pin_OBled)

	#define rotX (GPIOB->regs->IDR & pinX)
	#define rotY (GPIOA->regs->IDR & pinY)
	#define push (GPIOA->regs->IDR & pinP)
// ######################################################################################################################
//Pixel/graphics writing modes (bGraphicsMode)
#define GRAPHICS_NORMAL    0
#define GRAPHICS_INVERSE   1
#define GRAPHICS_TOGGLE    2
#define GRAPHICS_OR        3
#define GRAPHICS_NOR       4

//drawTestPattern Patterns
#define PATTERN_ALT_0     0
#define PATTERN_ALT_1     1
#define PATTERN_STRIPE_0  2
#define PATTERN_STRIPE_1  3
#define DEFAULT_BRIGHTNESS 80

//display screen (and subscreen) sizing
#define HUB08_PIXELS_ACROSS         64      //pixels across x axis (base 2 size expected)
#define HUB08_PIXELS_DOWN           32      //pixels down y axis
#define HUB08_BITSPERPIXEL           1      //1 bit per pixel, use more bits to allow for pwm screen brightness control
#define HUB08_RAM_SIZE_BYTES        ((HUB08_PIXELS_ACROSS*HUB08_BITSPERPIXEL/8)*HUB08_PIXELS_DOWN)
                                  // (32x * 1 / 8) = 4 bytes, * 16y = 64 bytes per screen here.
//lookup table for HUB08::writePixel to make the pixel indexing routine faster
static byte bPixelLookupTable[8] =
{
   0x80,   //0, bit 7
   0x40,   //1, bit 6
   0x20,   //2. bit 5
   0x10,   //3, bit 4
   0x08,   //4, bit 3
   0x04,   //5, bit 2
   0x02,   //6, bit 1
   0x01    //7, bit 0
};

// Font Indices
#define FONT_LENGTH             0
#define FONT_FIXED_WIDTH        2
#define FONT_HEIGHT             3
#define FONT_FIRST_CHAR         4
#define FONT_CHAR_COUNT         5
#define FONT_WIDTH_TABLE        6

typedef uint8_t (*FontCallback)(const uint8_t*);


//The main class of HUB08 library functions
class HUB08 {
  public:
    //Instantiate the HUB08
    HUB08(byte panelsWide, byte panelsHigh);
	//virtual ~HUB08();

  //Set or clear a pixel at the x and y location (0,0 is the top left corner)
  void writePixel( unsigned int bX, unsigned int bY, byte bGraphicsMode, byte bPixel );

  //Draw a string
  int drawString( int bX, int bY, const char* bChars, byte length, byte bGraphicsMode);
  int drawBlockedString(int bX, int bY, int blkSX, int blkEX,  const char *bChars, byte length,
		     byte bGraphicsMode);
  //Select a text font
  void selectFont(const uint8_t* font);

  //Draw a single character
  int drawChar(const int bX, const int bY, const unsigned char letter, byte bGraphicsMode);

  //Find the width of a character
  int charWidth(const unsigned char letter);

  //Draw a scrolling string
  void drawMarquee( const char* bChars, byte length, int left, int top);

  //Move the maquee accross by amount
  boolean stepMarquee( int amountX, int amountY);

  //Clear the screen in HUB08 RAM
  void clearScreen( byte bNormal );

  //Draw or clear a line from x1,y1 to x2,y2
  void drawLine( int x1, int y1, int x2, int y2, byte bGraphicsMode );

  //Draw or clear a circle of radius r at x,y centre
  void drawCircle( int xCenter, int yCenter, int radius, byte bGraphicsMode );

  //Draw or clear a box(rectangle) with a single pixel border
  void drawBox( int x1, int y1, int x2, int y2, byte bGraphicsMode );

  //Draw or clear a filled box(rectangle) with a single pixel border
  void drawFilledBox( int x1, int y1, int x2, int y2, byte bGraphicsMode );

  //Draw the selected test pattern
  void drawTestPattern( byte bPattern );

  //Scan the dot matrix LED panel display, from the RAM mirror out to the display hardware.
  //Call 4 times to scan the whole display which is made up of 4 interleaved rows within the 16 total rows.
  //Insert the calls to this function into the main loop for the highest call rate, or from a timer interrupt
  void scanDisplay(bool riseDown);	
	int countPixelChar(char *str);
	int totalChar;//,totalPixel;
	bool endRow;
		
  private:
    void drawCircleSub( int cx, int cy, int x, int y, byte bGraphicsMode );

    //Mirror of HUB08 pixels in RAM, ready to be clocked out by the main loop or high speed timer calls
    //byte *bHUB08ScreenRAM;
	byte *bHUB08ScreenRAM;

    //Marquee values
    char marqueeText[256];
    byte marqueeLength;
    int marqueeWidth;
    int marqueeHeight;
    int marqueeOffsetX;
    int marqueeOffsetY;

    //Pointer to current font
    const uint8_t* Font;

    //Display information
    byte DisplaysWide;
    byte DisplaysHigh;
    byte DisplaysTotal;
	byte row;//, pulsa;
	bool blockString;
	int blockStartX, blockEndX;
	//int cursorStr;
	//byte grapH;
	
    //scanning pointer into bHUB08ScreenRAM, setup init @ 48 for the first valid scan
    //volatile byte bHUB08Byte;

};

#endif /* HUB08_H_ */
