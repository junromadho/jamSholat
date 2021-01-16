

/*
 *
 * DjvSans24
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : DjvSans24.h
 * Date                : 19.03.2019
 * Font size in bytes  : 6174
 * Font width          : 10
 * Font height         : 22
 * Font first char     : 32
 * Font last char      : 62
 * Font used chars     : 30
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef DJVSANS24_H
#define DJVSANS24_H

#define DJVSANS24_WIDTH 10
#define DJVSANS24_HEIGHT 22

static const uint8_t DjvSans24[] PROGMEM = {
    0x18, 0x1E, // size
    0x0A, // width
    0x16, // height
    0x20, // first char
    0x1E, // char count
    
    // char widths
    0x00, 0x02, 0x06, 0x10, 0x04, 0x14, 0x10, 0x02, 
    0x05, 0x05, 0x0B, 0x10, 0x03, 0x06, 0x02, 0x08, 
    0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 
    0x0C, 0x0C, 0x04, 0x03, 0x0F, 0x0F, 
    
    // font data
    0xFF, 0xFF, 0x8F, 0x8F, 0x0C, 0x0C, // 33
    0x7F, 0x7F, 0x00, 0x00, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 34
    0x00, 0x60, 0x60, 0x60, 0x60, 0xE0, 0xFF, 0x6F, 0x60, 0x60, 0xE0, 0xFE, 0x7F, 0x60, 0x60, 0x60, 0x18, 0x18, 0x18, 0xF8, 0xFE, 0x1F, 0x18, 0x18, 0xD8, 0xFC, 0x1F, 0x19, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x04, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 35
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 36
    0xFC, 0xFE, 0x03, 0x01, 0x01, 0x03, 0xFE, 0xFC, 0x00, 0x00, 0xC0, 0xF0, 0x78, 0x1E, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x02, 0x02, 0x83, 0xE1, 0x78, 0x3C, 0x0F, 0x03, 0x00, 0xFC, 0xFE, 0x03, 0x01, 0x01, 0x03, 0xFE, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0C, 0x08, 0x08, 0x0C, 0x04, 0x00, // 37
    0x00, 0x00, 0x7C, 0xFE, 0xC7, 0x83, 0x03, 0x03, 0x03, 0x03, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xFE, 0xC7, 0x83, 0x01, 0x03, 0x07, 0x0E, 0x9C, 0xB8, 0xF0, 0xE0, 0xF8, 0x9E, 0x06, 0x00, 0x00, 0x00, 0x04, 0x04, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x04, 0x00, 0x00, 0x04, 0x0C, 0x0C, 0x08, // 38
    0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, // 39
    0xC0, 0xF8, 0x3E, 0x07, 0x01, 0x7F, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x0C, 0x3C, 0x70, 0x40, // 40
    0x01, 0x07, 0x3E, 0xF8, 0x80, 0x00, 0x00, 0x80, 0xFF, 0x7F, 0x40, 0x70, 0x3C, 0x0C, 0x00, // 41
    0x84, 0xCC, 0x48, 0x78, 0x30, 0xFF, 0x30, 0x78, 0x48, 0xCC, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 42
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0xFF, 0xFF, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 43
    0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x60, 0x7C, 0x1C, // 44
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 45
    0x00, 0x00, 0x80, 0x80, 0x0C, 0x0C, // 46
    0x00, 0x00, 0x00, 0x00, 0xE0, 0xFE, 0x1F, 0x03, 0x00, 0x80, 0xF8, 0x7F, 0x0F, 0x01, 0x00, 0x00, 0x30, 0x3C, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, // 47
    0xE0, 0xFC, 0x1E, 0x06, 0x03, 0x03, 0x03, 0x03, 0x06, 0x1E, 0xFC, 0xE0, 0x1F, 0xFF, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xFF, 0x1F, 0x00, 0x00, 0x04, 0x04, 0x0C, 0x0C, 0x0C, 0x0C, 0x04, 0x04, 0x00, 0x00, // 48
    0x00, 0x06, 0x06, 0x03, 0x03, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x00, // 49
    0x06, 0x06, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x8E, 0xFC, 0x78, 0x00, 0x00, 0x80, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x07, 0x03, 0x01, 0x00, 0x00, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x00, // 50
    0x00, 0x06, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x86, 0xFE, 0x78, 0x00, 0x80, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x87, 0x86, 0xFC, 0x78, 0x04, 0x04, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x04, 0x04, 0x00, 0x00, // 51
    0x00, 0x00, 0x80, 0xC0, 0xF0, 0x38, 0x0E, 0x03, 0xFF, 0xFF, 0x00, 0x00, 0x38, 0x3E, 0x37, 0x31, 0x30, 0x30, 0x30, 0x30, 0xFF, 0xFF, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00, 0x00, // 52
    0x00, 0xFF, 0xFF, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0x83, 0x03, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0xC3, 0xFF, 0x7E, 0x00, 0x04, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x04, 0x04, 0x00, 0x00, 0x00, // 53
    0xE0, 0xF8, 0x1C, 0x8E, 0xC6, 0xC3, 0xC3, 0xC3, 0xC3, 0x83, 0x06, 0x00, 0x3F, 0xFF, 0xFF, 0xC3, 0x81, 0x00, 0x00, 0x00, 0x81, 0xC3, 0xFF, 0x7E, 0x00, 0x00, 0x04, 0x04, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x04, 0x00, 0x00, // 54
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x83, 0xF3, 0x7F, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF0, 0x7E, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0C, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 55
    0x78, 0xFE, 0x86, 0x07, 0x03, 0x03, 0x03, 0x03, 0x87, 0x86, 0xFE, 0x78, 0x78, 0xFC, 0x87, 0x87, 0x03, 0x03, 0x03, 0x03, 0x87, 0x87, 0xFC, 0x78, 0x00, 0x04, 0x04, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x04, 0x04, 0x00, // 56
    0xF8, 0xFC, 0x0E, 0x07, 0x03, 0x03, 0x03, 0x07, 0x0E, 0xFE, 0xFC, 0xF0, 0x01, 0x83, 0x07, 0x0E, 0x0C, 0x0C, 0x0C, 0x8E, 0xC7, 0xE3, 0x7F, 0x1F, 0x00, 0x04, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x04, 0x04, 0x00, 0x00, 0x00, // 57
    0x00, 0xE0, 0xE0, 0x00, 0x00, 0xC0, 0xC0, 0x00, 0x00, 0x04, 0x04, 0x00, // 58
    0x00, 0xC0, 0xC0, 0x00, 0x81, 0x81, 0x60, 0x7C, 0x1C, // 59
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0x60, 0x60, 0x60, 0x30, 0x0E, 0x0E, 0x0E, 0x1B, 0x1B, 0x3B, 0x31, 0x31, 0x71, 0x60, 0x60, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, // 60
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // 61
    
};

#endif