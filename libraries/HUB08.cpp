/*--------------------------------------------------------------------------------------


 Note that the HUB08 library uses the SPI port for the fastest, low overhead writing to the
 display. Keep an eye on conflicts if there are any other devices running from the same
 SPI port, and that the chip select on those devices is correctly set to be inactive
 when the HUB08 is being written to.

 ---

 This program is free software: you can redistribute it and/or modify it under the terms
 of the version 3 GNU General Public License as published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with this program.
 If not, see <http://www.gnu.org/licenses/>.

--------------------------------------------------------------------------------------*/
#include "HUB08.h"

/*--------------------------------------------------------------------------------------
 Setup and instantiation of HUB08 library
 Note this currently uses the SPI port for the fastest performance to the HUB08, be
 careful of possible conflicts with other SPI port devices
--------------------------------------------------------------------------------------*/
HUB08::HUB08(byte panelsWide, byte panelsHigh)
{
	afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);
    uint16_t ui;
    DisplaysWide=panelsWide;
    DisplaysHigh=panelsHigh;
    DisplaysTotal=DisplaysWide*DisplaysHigh;  //1

    bHUB08ScreenRAM = (byte *) malloc(DisplaysTotal*HUB08_RAM_SIZE_BYTES);

	pinMode(P_A, OUTPUT);
	pinMode(P_B, OUTPUT);
	pinMode(P_C, OUTPUT);
	pinMode(P_D, OUTPUT);
	pinMode(P_OE, OUTPUT);
	pinMode(P_R1, OUTPUT);
	pinMode(P_R2, OUTPUT);
	pinMode(P_STB, OUTPUT);
	pinMode(P_CLK, OUTPUT);
	
	pinMode(P_G1, OUTPUT);
	pinMode(P_G2, OUTPUT);
	
	pinMode(P_X, INPUT);
	pinMode(P_Y, INPUT);
	pinMode(P_push, INPUT);
	pinMode(OB_Led, OUTPUT);
	
	digitalWrite(P_R1,LOW);
	digitalWrite(P_R2,LOW);
    clearScreen(true);

    // init the scan line/ram pointer to the required start point
    //bHUB08Byte = 0;
}

//HUB08::~HUB08()
//{
//   // nothing needed here
//}

/*--------------------------------------------------------------------------------------
 Set or clear a pixel at the x and y location (0,0 is the top left corner)
--------------------------------------------------------------------------------------*/
void
 HUB08::writePixel(unsigned int bX, unsigned int bY, byte bGraphicsMode, byte bPixel)
{
    unsigned int uiHUB08RAMPointer;
	byte tmpx;
	if (bX >= (HUB08_PIXELS_ACROSS*DisplaysWide) || bY >= (HUB08_PIXELS_DOWN * DisplaysHigh)) {
	    return;
    }
	if((blockString == true)) {
		if ((bX >= blockStartX) && (bX <= blockEndX)){
			return;
		} 		
	}
			
    uiHUB08RAMPointer = bX/8 + (bY * 8 *  DisplaysTotal); //DisplaysWide;//
	tmpx = bX % 8;
    byte lookup = bPixelLookupTable[tmpx & 0x07];

    switch (bGraphicsMode) {
    case GRAPHICS_NORMAL:
	    if (bPixel == false)
		bHUB08ScreenRAM[uiHUB08RAMPointer] &= ~lookup;	// zero bit is pixel on
	    else
		bHUB08ScreenRAM[uiHUB08RAMPointer] |= lookup;	// one bit is pixel off
	    break;
    case GRAPHICS_INVERSE:
	    if (bPixel == true)
		    bHUB08ScreenRAM[uiHUB08RAMPointer] &= ~lookup;	// zero bit is pixel on
	    else
		    bHUB08ScreenRAM[uiHUB08RAMPointer] |= lookup;	// one bit is pixel off
	    break;
    case GRAPHICS_TOGGLE:
	    if (bPixel == false) {
		if ((bHUB08ScreenRAM[uiHUB08RAMPointer] & lookup) == 0)
		    bHUB08ScreenRAM[uiHUB08RAMPointer] |= lookup;	// one bit is pixel off
		else
		    bHUB08ScreenRAM[uiHUB08RAMPointer] &= ~lookup;	// one bit is pixel off
	    }
	    break;
    case GRAPHICS_OR:
	    //only set pixels on
	    if (bPixel == true)
		    bHUB08ScreenRAM[uiHUB08RAMPointer] &= ~lookup;	// zero bit is pixel on
	    break;
    case GRAPHICS_NOR:
	    //only clear on pixels
	    if ((bPixel == true) &&
		    ((bHUB08ScreenRAM[uiHUB08RAMPointer] & lookup) == 0))
		    bHUB08ScreenRAM[uiHUB08RAMPointer] |= lookup;	// one bit is pixel off
	    break;
    }

}

int HUB08::drawString(int bX, int bY, const char *bChars, byte length,
		     byte bGraphicsMode)
{
    if (bX >= (HUB08_PIXELS_ACROSS*DisplaysWide) || bY >= HUB08_PIXELS_DOWN * DisplaysHigh)
	return 0;
    uint8_t height = pgm_read_byte(this->Font + FONT_HEIGHT);
    if (bY+height<0) return 0;

    int strWidth = 0;
	this->drawLine(bX -1 , bY, bX -1 , bY + height, GRAPHICS_INVERSE);

    for (int i = 0; i < length; i++) {
        int charWide = this->drawChar(bX+strWidth, bY, bChars[i], bGraphicsMode);
	    if (charWide > 0) {
	        strWidth += charWide ;
	        this->drawLine(bX + strWidth , bY, bX + strWidth , bY + height, GRAPHICS_INVERSE);
            strWidth++;
        } else if (charWide < 0) {
            return strWidth;
        }
        if ((bX + strWidth) >= HUB08_PIXELS_ACROSS * DisplaysWide || bY >= HUB08_PIXELS_DOWN * DisplaysHigh) return strWidth;
    }
	return strWidth;
}
int HUB08::drawBlockedString(int bX, int bY, int blkSX, int blkEX,  const char *bChars, byte length,
		     byte bGraphicsMode)
{
    if (bX >= (HUB08_PIXELS_ACROSS*DisplaysWide) || bY >= HUB08_PIXELS_DOWN * DisplaysHigh)
	return 0;
    uint8_t height = pgm_read_byte(this->Font + FONT_HEIGHT);
    if (bY+height<0) return 0;
	blockStartX = blkSX;
	blockEndX = blkEX;
	blockString = true;
    int strWidth = 0;
	this->drawLine(bX -1 , bY, bX -1 , bY + height, GRAPHICS_INVERSE);

    for (int i = 0; i < length; i++) {
        int charWide = this->drawChar(bX+strWidth, bY, bChars[i], bGraphicsMode);
	    if (charWide > 0) {
	        strWidth += charWide ;
	        this->drawLine(bX + strWidth , bY, bX + strWidth , bY + height, GRAPHICS_INVERSE);
            strWidth++;
        } else if (charWide < 0) {
			blockString = false;
            return strWidth;
        }
        if ((bX + strWidth) >= HUB08_PIXELS_ACROSS * DisplaysWide || bY >= HUB08_PIXELS_DOWN * DisplaysHigh) {
			blockString = false;
			return strWidth;
		}
    }
	blockString = false;
	return strWidth;
}

void HUB08::drawMarquee(const char *bChars, byte length, int left, int top)
{
    marqueeWidth = 0;
    for (int i = 0; i < length; i++) {
	    marqueeText[i] = bChars[i];
	    marqueeWidth += charWidth(bChars[i]) + 1;
    }
    marqueeHeight=pgm_read_byte(this->Font + FONT_HEIGHT);
    marqueeText[length] = '\0';
    marqueeOffsetY = top;
    marqueeOffsetX = left;
    marqueeLength = length;
    drawString(marqueeOffsetX, marqueeOffsetY, marqueeText, marqueeLength,
	   GRAPHICS_NORMAL);
}

boolean HUB08::stepMarquee(int amountX, int amountY)
{
    boolean ret=false;
    marqueeOffsetX += amountX;
    marqueeOffsetY += amountY;
    if (marqueeOffsetX < -marqueeWidth) {
	    marqueeOffsetX = HUB08_PIXELS_ACROSS * DisplaysWide;
	    clearScreen(true);
        ret=true;
    } else if (marqueeOffsetX > HUB08_PIXELS_ACROSS * DisplaysWide) {
	    marqueeOffsetX = -marqueeWidth;
	    clearScreen(true);
        ret=true;
    }
    
        
    if (marqueeOffsetY < -marqueeHeight) {
	    marqueeOffsetY = HUB08_PIXELS_DOWN * DisplaysHigh;
	    clearScreen(true);
        ret=true;
    } else if (marqueeOffsetY > HUB08_PIXELS_DOWN * DisplaysHigh) {
	    marqueeOffsetY = -marqueeHeight;
	    clearScreen(true);
        ret=true;
    }

    // Special case horizontal scrolling to improve speed
    if (amountY==0 && amountX==-1) {
        // Shift entire screen one bit
        for (int i=0; i<HUB08_RAM_SIZE_BYTES*DisplaysTotal;i++) {
            if ((i%(DisplaysWide*8)) == (DisplaysWide*8) -1) {
                bHUB08ScreenRAM[i]=(bHUB08ScreenRAM[i]<<1)+1;
            } else {
                bHUB08ScreenRAM[i]=(bHUB08ScreenRAM[i]<<1) + ((bHUB08ScreenRAM[i+1] & 0x80) >>7);
            }
        }

        // Redraw last char on screen
        int strWidth=marqueeOffsetX;
        for (byte i=0; i < marqueeLength; i++) {
            int wide = charWidth(marqueeText[i]);
            if (strWidth + wide >= DisplaysWide*HUB08_PIXELS_ACROSS) {
                drawChar(strWidth, marqueeOffsetY,marqueeText[i],GRAPHICS_NORMAL);
                return ret;
            }
            strWidth += wide+1;
        }
    } else if (amountY==0 && amountX==1) {
        // Shift entire screen one bit
        for (int i=(HUB08_RAM_SIZE_BYTES*DisplaysTotal)-1; i>=0;i--) {
            if ((i%(DisplaysWide*8)) == 0) {
                bHUB08ScreenRAM[i]=(bHUB08ScreenRAM[i]>>1)+256;
            } else {
                bHUB08ScreenRAM[i]=(bHUB08ScreenRAM[i]>>1) + ((bHUB08ScreenRAM[i-1] & 1) <<7);
            }
        }

        // Redraw last char on screen
        int strWidth=marqueeOffsetX;
        for (byte i=0; i < marqueeLength; i++) {
            int wide = charWidth(marqueeText[i]);
            if (strWidth+wide >= 0) {
                drawChar(strWidth, marqueeOffsetY,marqueeText[i],GRAPHICS_NORMAL);
                return ret;
            }
            strWidth += wide+1;
        }
    } else {
        drawString(marqueeOffsetX, marqueeOffsetY, marqueeText, marqueeLength,
	       GRAPHICS_NORMAL);
    }

    return ret;
}


/*--------------------------------------------------------------------------------------
 Clear the screen in HUB08 RAM
--------------------------------------------------------------------------------------*/
void HUB08::clearScreen(byte bNormal)
{
    if (bNormal) // clear all pixels
        memset(bHUB08ScreenRAM,0x00,HUB08_RAM_SIZE_BYTES*DisplaysTotal);
    else // set all pixels
        memset(bHUB08ScreenRAM,0xFF,HUB08_RAM_SIZE_BYTES*DisplaysTotal);
}

/*--------------------------------------------------------------------------------------
 Draw or clear a line from x1,y1 to x2,y2
--------------------------------------------------------------------------------------*/
void HUB08::drawLine(int x1, int y1, int x2, int y2, byte bGraphicsMode)
{
    int dy = y2 - y1;
    int dx = x2 - x1;
    int stepx, stepy;

    if (dy < 0) {
	    dy = -dy;
	    stepy = -1;
    } else {
	    stepy = 1;
    }
    if (dx < 0) {
	    dx = -dx;
	    stepx = -1;
    } else {
	    stepx = 1;
    }
    dy <<= 1;			// dy is now 2*dy
    dx <<= 1;			// dx is now 2*dx

    writePixel(x1, y1, bGraphicsMode, true);
    if (dx > dy) {
	    int fraction = dy - (dx >> 1);	// same as 2*dy - dx
	    while (x1 != x2) {
	        if (fraction >= 0) {
		        y1 += stepy;
		        fraction -= dx;	// same as fraction -= 2*dx
	        }
	        x1 += stepx;
	        fraction += dy;	// same as fraction -= 2*dy
	        writePixel(x1, y1, bGraphicsMode, true);
	    }
    } else {
	    int fraction = dx - (dy >> 1);
	    while (y1 != y2) {
	        if (fraction >= 0) {
		        x1 += stepx;
		        fraction -= dy;
	        }
	        y1 += stepy;
	        fraction += dx;
	        writePixel(x1, y1, bGraphicsMode, true);
	    }
    }
}

/*--------------------------------------------------------------------------------------
 Draw or clear a circle of radius r at x,y centre
--------------------------------------------------------------------------------------*/
void HUB08::drawCircle(int xCenter, int yCenter, int radius,
		     byte bGraphicsMode)
{
    int x = 0;
    int y = radius;
    int p = (5 - radius * 4) / 4;

    drawCircleSub(xCenter, yCenter, x, y, bGraphicsMode);
    while (x < y) {
	    x++;
	    if (p < 0) {
	        p += 2 * x + 1;
	    } else {
	        y--;
	        p += 2 * (x - y) + 1;
	    }
	    drawCircleSub(xCenter, yCenter, x, y, bGraphicsMode);
    }
}

void HUB08::drawCircleSub(int cx, int cy, int x, int y, byte bGraphicsMode)
{

    if (x == 0) {
	    writePixel(cx, cy + y, bGraphicsMode, true);
	    writePixel(cx, cy - y, bGraphicsMode, true);
	    writePixel(cx + y, cy, bGraphicsMode, true);
	    writePixel(cx - y, cy, bGraphicsMode, true);
    } else if (x == y) {
	    writePixel(cx + x, cy + y, bGraphicsMode, true);
	    writePixel(cx - x, cy + y, bGraphicsMode, true);
	    writePixel(cx + x, cy - y, bGraphicsMode, true);
	    writePixel(cx - x, cy - y, bGraphicsMode, true);
    } else if (x < y) {
	    writePixel(cx + x, cy + y, bGraphicsMode, true);
	    writePixel(cx - x, cy + y, bGraphicsMode, true);
	    writePixel(cx + x, cy - y, bGraphicsMode, true);
	    writePixel(cx - x, cy - y, bGraphicsMode, true);
	    writePixel(cx + y, cy + x, bGraphicsMode, true);
	    writePixel(cx - y, cy + x, bGraphicsMode, true);
	    writePixel(cx + y, cy - x, bGraphicsMode, true);
	    writePixel(cx - y, cy - x, bGraphicsMode, true);
    }
}

/*--------------------------------------------------------------------------------------
 Draw or clear a box(rectangle) with a single pixel border
--------------------------------------------------------------------------------------*/
void HUB08::drawBox(int x1, int y1, int x2, int y2, byte bGraphicsMode)
{
    drawLine(x1, y1, x2, y1, bGraphicsMode);
    drawLine(x2, y1, x2, y2, bGraphicsMode);
    drawLine(x2, y2, x1, y2, bGraphicsMode);
    drawLine(x1, y2, x1, y1, bGraphicsMode);
}

/*--------------------------------------------------------------------------------------
 Draw or clear a filled box(rectangle) with a single pixel border
--------------------------------------------------------------------------------------*/
void HUB08::drawFilledBox(int x1, int y1, int x2, int y2,
			byte bGraphicsMode)
{
    for (int b = x1; b <= x2; b++) {
	    drawLine(b, y1, b, y2, bGraphicsMode);
    }
}

/*--------------------------------------------------------------------------------------
 Draw the selected test pattern
--------------------------------------------------------------------------------------*/
void HUB08::drawTestPattern(byte bPattern)
{
    unsigned int ui;

    int numPixels=DisplaysTotal * HUB08_PIXELS_ACROSS * HUB08_PIXELS_DOWN;
    int pixelsWide=HUB08_PIXELS_ACROSS*DisplaysWide;
    for (ui = 0; ui < numPixels; ui++) {
	    switch (bPattern) {
	    case PATTERN_ALT_0:	// every alternate pixel, first pixel on
		    if ((ui & pixelsWide) == 0)
		        //even row
		        writePixel((ui & (pixelsWide-1)), ((ui & ~(pixelsWide-1)) / pixelsWide), GRAPHICS_NORMAL, ui & 1);
		    else
		        //odd row
		        writePixel((ui & (pixelsWide-1)), ((ui & ~(pixelsWide-1)) / pixelsWide), GRAPHICS_NORMAL, !(ui & 1));
		    break;
	    case PATTERN_ALT_1:	// every alternate pixel, first pixel off
		    if ((ui & pixelsWide) == 0)
		        //even row
		        writePixel((ui & (pixelsWide-1)), ((ui & ~(pixelsWide-1)) / pixelsWide), GRAPHICS_NORMAL, !(ui & 1));
		    else
		        //odd row
		        writePixel((ui & (pixelsWide-1)), ((ui & ~(pixelsWide-1)) / pixelsWide), GRAPHICS_NORMAL, ui & 1);
		    break;
	    case PATTERN_STRIPE_0:	// vertical stripes, first stripe on
		    writePixel((ui & (pixelsWide-1)), ((ui & ~(pixelsWide-1)) / pixelsWide), GRAPHICS_NORMAL, ui & 1);
		    break;
	    case PATTERN_STRIPE_1:	// vertical stripes, first stripe off
		    writePixel((ui & (pixelsWide-1)), ((ui & ~(pixelsWide-1)) / pixelsWide), GRAPHICS_NORMAL, !(ui & 1));
		    break;
        }
    }
}

/*--------------------------------------------------------------------------------------
 Scan the dot matrix LED panel display, from the RAM mirror out to the display hardware.
 Call 4 times to scan the whole display which is made up of 4 interleaved rows within the 16 total rows.
 Insert the calls to this function into the main loop for the highest call rate, or from a timer interrupt
--------------------------------------------------------------------------------------*/
void HUB08::scanDisplay(bool riseDown)
{
	byte dataR1,dataR2, dataG1, dataG2;
	switch (riseDown){
		case true:			
			//for (row=0;row<16;row++) {
			for (int8_t j=0;j<(8*DisplaysTotal);j++) {
				dataR1 = bHUB08ScreenRAM[j+(row*8*DisplaysTotal)];
				// dataG1 = bHUB08ScreenRAM[j+(row*8*DisplaysTotal)];
				// dataG1 = dataR1;
				dataR2 = bHUB08ScreenRAM[j+(row*8*DisplaysTotal)+(128*DisplaysTotal)];
				// dataG2 = bHUB08ScreenRAM[j+(row*8*DisplaysTotal)+(128*DisplaysTotal)];
				// dataG2 = dataR2;
				for (int8_t bit=7; bit >= 0; bit--) {
					wR1((dataR1 >> bit) & 0x01);
					wR2((dataR2 >> bit) & 0x01);
					//wR1(0);
					//wR2(0);
					// wG1((dataG1 >> bit) & 0x01);
					// wG2((dataG2 >> bit) & 0x01);
					wCLK(1);
					wCLK(0);			
				}			
			}
			wOE(1);			
			wSTB(1);
			wSTB(0);		
			wA(row & 0x01);
			wB((row>>1) & 0x01);
			wC((row>>2) & 0x01);
			wD((row>>3) & 0x01);
			row++;
			if (row >= 16){
				endRow = true;
				row = 0;
			}
			//else if(row == 1){
			//	endRow = false;
			//}
		break;
		case false:
			wOE(0);			
		break;
	}
}

void HUB08::selectFont(const uint8_t * font)
{
    this->Font = font;
}


int HUB08::drawChar(const int bX, const int bY, const unsigned char letter, byte bGraphicsMode)
{
    if (bX > (HUB08_PIXELS_ACROSS*DisplaysWide) || bY > (HUB08_PIXELS_DOWN*DisplaysHigh) ) return -1;
    unsigned char c = letter;
    uint8_t height = pgm_read_byte(this->Font + FONT_HEIGHT);
    if (c == ' ') {
	    int charWide = charWidth(' ');
	    this->drawFilledBox(bX, bY, bX + charWide, bY + height, GRAPHICS_INVERSE);
	    return charWide;
    }
    uint8_t width = 0;
    uint8_t bytes = (height + 7) / 8;

    uint8_t firstChar = pgm_read_byte(this->Font + FONT_FIRST_CHAR);
    uint8_t charCount = pgm_read_byte(this->Font + FONT_CHAR_COUNT);

    uint16_t index = 0;

    if (c < firstChar || c >= (firstChar + charCount)) return 0;
    c -= firstChar;

    if (pgm_read_byte(this->Font + FONT_LENGTH) == 0
	    && pgm_read_byte(this->Font + FONT_LENGTH + 1) == 0) {
	    // zero length is flag indicating fixed width font (array does not contain width data entries)
	    width = pgm_read_byte(this->Font + FONT_FIXED_WIDTH);
	    index = c * bytes * width + FONT_WIDTH_TABLE;
    } else {
	    // variable width font, read width data, to get the index
	    for (uint8_t i = 0; i < c; i++) {
	        index += pgm_read_byte(this->Font + FONT_WIDTH_TABLE + i);
	    }
	    index = index * bytes + charCount + FONT_WIDTH_TABLE;
	    width = pgm_read_byte(this->Font + FONT_WIDTH_TABLE + c);
    }
    if (bX < -width || bY < -height) return width;

    // last but not least, draw the character
    for (uint8_t j = 0; j < width; j++) { // Width
	    for (uint8_t i = bytes - 1; i < 254; i--) { // Vertical Bytes
	        uint8_t data = pgm_read_byte(this->Font + index + j + (i * width));
		    int offset = (i * 8);
		    if ((i == bytes - 1) && bytes > 1) {
		        offset = height - 8;
            }
	        for (uint8_t k = 0; k < 8; k++) { // Vertical bits
		        if ((offset+k >= i*8) && (offset+k <= height)) {
		            if (data & (1 << k)) {
						writePixel(bX + j, bY + offset + k, bGraphicsMode, true);						
		            } else {
			            writePixel(bX + j, bY + offset + k, bGraphicsMode, false);
		            }
		        }
	        }
	    }
    }
    return width;
}

int HUB08::countPixelChar(char *str){	
	int totalPixel = 0;
	//int j=0;
	totalChar = 0; 
    while (*str) {
		int wide = charWidth(*str++);
		totalPixel = totalPixel + wide+1 ;
		totalChar++; //j++;
    }	
	//totalChar = j;
	return (totalPixel);
}

int HUB08::charWidth(const unsigned char letter)
{
    unsigned char c = letter;
    // Space is often not included in font so use width of 'n'
    if (c == ' ') c = 'n';
    uint8_t width = 0;

    uint8_t firstChar = pgm_read_byte(this->Font + FONT_FIRST_CHAR);
    uint8_t charCount = pgm_read_byte(this->Font + FONT_CHAR_COUNT);

    uint16_t index = 0;

    if (c < firstChar || c >= (firstChar + charCount)) {
	    return 0;
    }
    c -= firstChar;

    if (pgm_read_byte(this->Font + FONT_LENGTH) == 0
	&& pgm_read_byte(this->Font + FONT_LENGTH + 1) == 0) {
	    // zero length is flag indicating fixed width font (array does not contain width data entries)
	    width = pgm_read_byte(this->Font + FONT_FIXED_WIDTH);
    } else {
	    // variable width font, read width data
	    width = pgm_read_byte(this->Font + FONT_WIDTH_TABLE + c);
    }
    return width;
}

