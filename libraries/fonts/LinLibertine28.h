

/*
 *
 * LinLibertine28
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : Linlibertine28.h
 * Date                : 28.03.2019
 * Font size in bytes  : 6311
 * Font width          : 10
 * Font height         : 25
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

#ifndef LINLIBERTINE28_H
#define LINLIBERTINE28_H

#define LINLIBERTINE28_WIDTH 10
#define LINLIBERTINE28_HEIGHT 25

static const uint8_t LinLibertine28[] PROGMEM = {
    0x18, 0xA7, // size
    0x0A, // width
    0x19, // height
    0x20, // first char
    0x1E, // char count
    
    // char widths
    0x00, 0x03, 0x07, 0x0B, 0x04, 0x0F, 0x12, 0x03, 
    0x06, 0x06, 0x08, 0x0A, 0x03, 0x07, 0x03, 0x07, 
    0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 
    0x0B, 0x0B, 0x04, 0x03, 0x0C, 0x0B, 
    
    // font data
    0xFC, 0xFC, 0xFC, 0x00, 0x3F, 0x00, 0x0E, 0x0E, 0x0E, 0x00, 0x00, 0x00, // 33
    0x38, 0xFC, 0x3C, 0x00, 0x3C, 0xFC, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 34
    0x00, 0x00, 0x00, 0x80, 0x78, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x40, 0x41, 0xC1, 0x7F, 0x41, 0x41, 0xC1, 0xFF, 0x41, 0x41, 0x01, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 35
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 36
    0xC0, 0xE0, 0x30, 0x10, 0x10, 0xE0, 0x20, 0x20, 0x20, 0x20, 0xA0, 0x60, 0x30, 0x00, 0x00, 0x03, 0x0F, 0x08, 0x08, 0x06, 0xC1, 0x20, 0x18, 0x04, 0xC3, 0xE1, 0x70, 0x10, 0x10, 0xE0, 0x00, 0x00, 0x08, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x08, 0x08, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 37
    0x00, 0x00, 0x00, 0x00, 0xF0, 0xF8, 0x8C, 0x04, 0x04, 0xCC, 0xFC, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF0, 0x30, 0x08, 0x04, 0x07, 0x07, 0x1F, 0x39, 0x70, 0xC0, 0x80, 0x60, 0x19, 0x07, 0x03, 0x01, 0x01, 0x03, 0x07, 0x04, 0x0C, 0x08, 0x08, 0x08, 0x08, 0x04, 0x06, 0x03, 0x03, 0x07, 0x0C, 0x08, 0x08, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 38
    0x3C, 0xFC, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 39
    0x00, 0xC0, 0xF0, 0x18, 0x06, 0x03, 0xFE, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x3C, 0x60, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, // 40
    0x03, 0x06, 0x18, 0xF0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFE, 0x00, 0x80, 0x60, 0x3C, 0x0F, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, // 41
    0x08, 0x88, 0xD8, 0x76, 0x3E, 0xF0, 0xD8, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 42
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 43
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8E, 0x4E, 0x3C, 0x00, 0x00, 0x00, // 44
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 45
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x0E, 0x0E, 0x00, 0x00, 0x00, // 46
    0x00, 0x00, 0x00, 0x00, 0xC0, 0x38, 0x0C, 0x00, 0x80, 0x70, 0x0E, 0x01, 0x00, 0x00, 0x1C, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 47
    0x00, 0xC0, 0x70, 0x10, 0x08, 0x08, 0x08, 0x18, 0x70, 0xE0, 0x00, 0x7F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x03, 0x07, 0x0C, 0x08, 0x08, 0x08, 0x04, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 48
    0x00, 0x00, 0x20, 0x20, 0x30, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x0C, 0x0F, 0x0F, 0x0C, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 49
    0x00, 0x60, 0x70, 0x18, 0x08, 0x08, 0x08, 0x18, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x60, 0x30, 0x18, 0x0F, 0x03, 0x00, 0x00, 0x0C, 0x0F, 0x0B, 0x08, 0x08, 0x08, 0x08, 0x0C, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 50
    0x60, 0x70, 0x18, 0x08, 0x08, 0x08, 0x18, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x06, 0x06, 0x05, 0x0D, 0xF8, 0xF0, 0x00, 0x04, 0x0C, 0x08, 0x08, 0x08, 0x08, 0x04, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 51
    0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x20, 0xF0, 0xF8, 0x00, 0x00, 0x60, 0x70, 0x4C, 0x42, 0x41, 0x40, 0x40, 0xFF, 0xFF, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0F, 0x0F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 52
    0x00, 0x80, 0xF8, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0C, 0x00, 0x00, 0x00, 0x07, 0x03, 0x02, 0x02, 0x02, 0x06, 0x0C, 0xFC, 0xF0, 0x00, 0x04, 0x04, 0x0C, 0x08, 0x08, 0x08, 0x0C, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 53
    0x00, 0x00, 0x80, 0xC0, 0x20, 0x10, 0x10, 0x08, 0x08, 0x00, 0x00, 0xFC, 0xFF, 0x07, 0x04, 0x02, 0x02, 0x02, 0x06, 0x0C, 0xFC, 0xF0, 0x00, 0x03, 0x06, 0x0C, 0x08, 0x08, 0x08, 0x0C, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 54
    0x74, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0xE8, 0x38, 0x08, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0x3C, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 55
    0x00, 0xE0, 0xF0, 0x18, 0x08, 0x08, 0x08, 0x18, 0xF0, 0xE0, 0x00, 0xC0, 0xE1, 0x33, 0x1B, 0x0E, 0x0C, 0x0E, 0x1B, 0x39, 0xF0, 0xE0, 0x03, 0x07, 0x06, 0x0C, 0x08, 0x08, 0x08, 0x0C, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 56
    0xC0, 0xE0, 0x30, 0x18, 0x08, 0x08, 0x08, 0x18, 0x70, 0xE0, 0x80, 0x0F, 0x1F, 0x38, 0x30, 0x20, 0x20, 0x20, 0xA0, 0xF0, 0x7F, 0x1F, 0x00, 0x00, 0x08, 0x08, 0x04, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 57
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, // 58
    0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x8E, 0x4E, 0x3C, 0x00, 0x00, 0x00, // 59
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x70, 0x50, 0x50, 0xD8, 0x88, 0x88, 0x8C, 0x04, 0x04, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 60
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // 61
    
};

#endif