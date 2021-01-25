

/*
 *
 * UbuntuCon13
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : UbuntuCon13.h
 * Date                : 10.04.2019
 * Font size in bytes  : 5081
 * Font width          : 10
 * Font height         : 13
 * Font first char     : 32
 * Font last char      : 128
 * Font used chars     : 96
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

#ifndef UBUNTUCON13_H
#define UBUNTUCON13_H

#define UBUNTUCON13_WIDTH 10
#define UBUNTUCON13_HEIGHT 13

static const uint8_t UbuntuCon13[] PROGMEM = {
    0x13, 0xD9, // size
    0x0A, // width
    0x0D, // height
    0x20, // first char
    0x60, // char count
    
    // char widths
    0x00, 0x01, 0x03, 0x05, 0x04, 0x04, 0x05, 0x02, 
    0x03, 0x03, 0x05, 0x05, 0x02, 0x02, 0x01, 0x04, 
    0x04, 0x04, 0x04, 0x04, 0x05, 0x04, 0x04, 0x04, 
    0x04, 0x04, 0x03, 0x02, 0x04, 0x04, 0x04, 0x04, 
    0x09, 0x07, 0x05, 0x04, 0x05, 0x04, 0x04, 0x05, 
    0x05, 0x01, 0x04, 0x05, 0x03, 0x07, 0x06, 0x06, 
    0x04, 0x06, 0x05, 0x03, 0x05, 0x05, 0x05, 0x07, 
    0x05, 0x05, 0x05, 0x02, 0x04, 0x02, 0x05, 0x05, 
    0x01, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03, 0x04, 
    0x04, 0x01, 0x02, 0x04, 0x02, 0x07, 0x04, 0x04, 
    0x04, 0x04, 0x03, 0x03, 0x03, 0x04, 0x05, 0x07, 
    0x05, 0x04, 0x04, 0x03, 0x01, 0x03, 0x05, 0x05, 
    
    
    // font data
    0xFC, 0x30, // 33
    0x0E, 0x00, 0x0E, 0x00, 0x00, 0x00, // 34
    0x10, 0xFC, 0x10, 0xFC, 0x10, 0x08, 0x38, 0x08, 0x38, 0x08, // 35
    0x18, 0x24, 0x46, 0x84, 0x10, 0x10, 0x70, 0x08, // 36
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 37
    0x80, 0x58, 0x64, 0x98, 0xC0, 0x18, 0x20, 0x20, 0x18, 0x30, // 38
    0x08, 0x06, 0x00, 0x00, // 39
    0xF0, 0x0C, 0x02, 0x18, 0x60, 0x80, // 40
    0x02, 0x0C, 0xF0, 0x80, 0x60, 0x18, // 41
    0x40, 0xA0, 0x5E, 0xA0, 0x40, 0x00, 0x00, 0x78, 0x00, 0x00, // 42
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 43
    0x00, 0x00, 0x80, 0x60, // 44
    0x80, 0x80, 0x00, 0x00, // 45
    0x00, 0x30, // 46
    0x00, 0x80, 0x78, 0x06, 0xC0, 0x38, 0x00, 0x00, // 47
    0xF8, 0x04, 0x04, 0xF8, 0x18, 0x20, 0x20, 0x18, // 48
    0x00, 0x08, 0xFC, 0x00, 0x00, 0x00, 0x38, 0x00, // 49
    0x04, 0x84, 0x44, 0x38, 0x38, 0x20, 0x20, 0x20, // 50
    0x04, 0x44, 0x44, 0xB8, 0x20, 0x20, 0x20, 0x18, // 51
    0xC0, 0x30, 0x08, 0xFC, 0x00, 0x08, 0x08, 0x08, 0x38, 0x08, // 52
    0x3C, 0x24, 0x24, 0xC4, 0x20, 0x20, 0x20, 0x18, // 53
    0xF0, 0x28, 0x24, 0xC4, 0x18, 0x20, 0x20, 0x18, // 54
    0x04, 0x84, 0x64, 0x1C, 0x00, 0x38, 0x00, 0x00, // 55
    0xB8, 0x44, 0x44, 0xB8, 0x18, 0x20, 0x20, 0x18, // 56
    0x78, 0x84, 0x84, 0xF8, 0x20, 0x20, 0x10, 0x08, // 57
    0x00, 0x30, 0x00, 0x00, 0x30, 0x00, // 58
    0x00, 0x18, 0x80, 0x60, // 59
    0x80, 0x40, 0x40, 0x20, 0x00, 0x08, 0x08, 0x10, // 60
    0x20, 0x20, 0x20, 0x20, 0x08, 0x08, 0x08, 0x08, // 61
    0xF0, 0xE0, 0xC0, 0x80, 0x38, 0x18, 0x08, 0x00, // 62
    0x04, 0xC4, 0x24, 0x18, 0x00, 0x30, 0x00, 0x00, // 63
    0xE0, 0x18, 0xC4, 0x24, 0x24, 0xE4, 0x04, 0x08, 0xF0, 0x18, 0x60, 0x88, 0x90, 0x90, 0x98, 0x10, 0x10, 0x08, // 64
    0x00, 0xC0, 0x38, 0x04, 0x38, 0xC0, 0x00, 0x30, 0x08, 0x08, 0x08, 0x08, 0x08, 0x30, // 65
    0xFC, 0x44, 0x44, 0x44, 0xB8, 0x38, 0x20, 0x20, 0x20, 0x18, // 66
    0xF8, 0x04, 0x04, 0x04, 0x18, 0x20, 0x20, 0x20, // 67
    0xFC, 0x04, 0x04, 0x08, 0xF0, 0x38, 0x20, 0x20, 0x10, 0x08, // 68
    0xFC, 0x44, 0x44, 0x44, 0x38, 0x20, 0x20, 0x20, // 69
    0xFC, 0x44, 0x44, 0x44, 0x38, 0x00, 0x00, 0x00, // 70
    0xF0, 0x08, 0x04, 0x44, 0x84, 0x08, 0x10, 0x20, 0x20, 0x38, // 71
    0xFC, 0x40, 0x40, 0x40, 0xFC, 0x38, 0x00, 0x00, 0x00, 0x38, // 72
    0xFC, 0x38, // 73
    0x00, 0x00, 0x00, 0xFC, 0x10, 0x20, 0x20, 0x18, // 74
    0xFC, 0x40, 0xB0, 0x08, 0x04, 0x38, 0x00, 0x08, 0x10, 0x20, // 75
    0xFC, 0x00, 0x00, 0x38, 0x20, 0x20, // 76
    0xFC, 0x1C, 0xE0, 0x00, 0xE0, 0x1C, 0xFC, 0x38, 0x00, 0x00, 0x18, 0x00, 0x00, 0x38, // 77
    0xFC, 0x08, 0x30, 0xC0, 0x00, 0xFC, 0x38, 0x00, 0x00, 0x00, 0x18, 0x38, // 78
    0xF0, 0x08, 0x04, 0x04, 0x08, 0xF0, 0x08, 0x10, 0x20, 0x20, 0x10, 0x08, // 79
    0xFC, 0x84, 0x84, 0x78, 0x38, 0x00, 0x00, 0x00, // 80
    0xF0, 0x08, 0x04, 0x04, 0x08, 0xF0, 0x08, 0x10, 0x20, 0x60, 0x90, 0x88, // 81
    0xFC, 0x84, 0x84, 0x44, 0x38, 0x38, 0x00, 0x00, 0x18, 0x20, // 82
    0x38, 0x44, 0x84, 0x20, 0x20, 0x18, // 83
    0x04, 0x04, 0xFC, 0x04, 0x04, 0x00, 0x00, 0x38, 0x00, 0x00, // 84
    0xFC, 0x00, 0x00, 0x00, 0xFC, 0x18, 0x20, 0x20, 0x20, 0x18, // 85
    0x1C, 0xE0, 0x00, 0xE0, 0x1C, 0x00, 0x18, 0x20, 0x18, 0x00, // 86
    0xFC, 0x00, 0xC0, 0x78, 0xC0, 0x00, 0xFC, 0x18, 0x20, 0x18, 0x00, 0x18, 0x20, 0x18, // 87
    0x04, 0x98, 0x60, 0x98, 0x04, 0x20, 0x18, 0x00, 0x18, 0x20, // 88
    0x0C, 0x30, 0xC0, 0x30, 0x0C, 0x00, 0x00, 0x38, 0x00, 0x00, // 89
    0x04, 0x84, 0x64, 0x14, 0x0C, 0x30, 0x28, 0x20, 0x20, 0x20, // 90
    0x00, 0x00, 0x00, 0x00, // 91
    0x06, 0x78, 0x80, 0x00, 0x00, 0x00, 0x38, 0xC0, // 92
    0x00, 0x00, 0x00, 0x00, // 93
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 94
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, // 95
    0x00, 0x00, // 96
    0x00, 0x90, 0x90, 0xE0, 0x18, 0x20, 0x20, 0x38, // 97
    0xFE, 0x10, 0x10, 0xE0, 0x38, 0x20, 0x20, 0x18, // 98
    0xE0, 0x10, 0x10, 0x10, 0x18, 0x20, 0x20, 0x20, // 99
    0xE0, 0x10, 0x10, 0xFE, 0x18, 0x20, 0x20, 0x38, // 100
    0xE0, 0x90, 0x90, 0xE0, 0x18, 0x20, 0x20, 0x20, // 101
    0xFC, 0x12, 0x12, 0x38, 0x00, 0x00, // 102
    0xE0, 0x10, 0x10, 0xF0, 0x88, 0x90, 0x90, 0x78, // 103
    0xFE, 0x10, 0x10, 0xE0, 0x38, 0x00, 0x00, 0x38, // 104
    0xF4, 0x38, // 105
    0x00, 0xF4, 0x80, 0x78, // 106
    0xFE, 0x80, 0x60, 0x10, 0x38, 0x00, 0x18, 0x20, // 107
    0xFE, 0x00, 0x18, 0x20, // 108
    0xF0, 0x10, 0x10, 0xF0, 0x10, 0x10, 0xE0, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x38, // 109
    0xF0, 0x10, 0x10, 0xE0, 0x38, 0x00, 0x00, 0x38, // 110
    0xE0, 0x10, 0x10, 0xE0, 0x18, 0x20, 0x20, 0x18, // 111
    0xF0, 0x10, 0x10, 0xE0, 0xF8, 0x20, 0x20, 0x18, // 112
    0xE0, 0x10, 0x10, 0xF0, 0x18, 0x20, 0x20, 0xF8, // 113
    0xE0, 0x10, 0x10, 0x38, 0x00, 0x00, // 114
    0x60, 0x90, 0x10, 0x20, 0x20, 0x18, // 115
    0xFC, 0x10, 0x10, 0x18, 0x20, 0x20, // 116
    0xF0, 0x00, 0x00, 0xF0, 0x18, 0x20, 0x20, 0x38, // 117
    0x30, 0xC0, 0x00, 0xC0, 0x30, 0x00, 0x18, 0x20, 0x18, 0x00, // 118
    0xF0, 0x00, 0xC0, 0x30, 0xC0, 0x00, 0xF0, 0x18, 0x20, 0x18, 0x00, 0x18, 0x20, 0x18, // 119
    0x10, 0x60, 0x80, 0x60, 0x10, 0x20, 0x18, 0x00, 0x18, 0x20, // 120
    0x30, 0xC0, 0x00, 0xF0, 0x80, 0x80, 0x78, 0x00, // 121
    0x10, 0x90, 0x50, 0x30, 0x30, 0x28, 0x20, 0x20, // 122
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 123
    0xFE, 0xF8, // 124
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 125
    0x80, 0x40, 0x40, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, // 126
    0xFE, 0x02, 0x02, 0x02, 0xFE, 0x38, 0x20, 0x20, 0x20, 0x38 // 127
    
};

#endif