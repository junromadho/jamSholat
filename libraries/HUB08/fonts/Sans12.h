

/*
 *
 * Sans12
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : Sans12.h
 * Date                : 23.02.2019
 * Font size in bytes  : 6342
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

#ifndef SANS12_H
#define SANS12_H

#define SANS12_WIDTH 10
#define SANS12_HEIGHT 13

static const uint8_t Sans12[] PROGMEM = {
    0x18, 0xC6, // size
    0x0A, // width
    0x0D, // height
    0x20, // first char
    0x60, // char count
    
    // char widths
    0x00, 0x01, 0x03, 0x07, 0x06, 0x05, 0x06, 0x01, 
    0x02, 0x03, 0x03, 0x05, 0x02, 0x03, 0x01, 0x03, 
    0x05, 0x03, 0x05, 0x05, 0x05, 0x06, 0x05, 0x05, 
    0x06, 0x06, 0x01, 0x01, 0x05, 0x05, 0x05, 0x05, 
    0x0B, 0x08, 0x06, 0x08, 0x07, 0x06, 0x05, 0x08, 
    0x07, 0x01, 0x05, 0x06, 0x05, 0x08, 0x07, 0x09, 
    0x06, 0x09, 0x07, 0x06, 0x06, 0x07, 0x07, 0x0B, 
    0x06, 0x07, 0x07, 0x02, 0x03, 0x02, 0x04, 0x07, 
    0x01, 0x07, 0x05, 0x06, 0x06, 0x06, 0x03, 0x06, 
    0x05, 0x01, 0x02, 0x05, 0x01, 0x08, 0x05, 0x06, 
    0x05, 0x06, 0x03, 0x05, 0x03, 0x05, 0x06, 0x08, 
    0x05, 0x06, 0x05, 0x03, 0x01, 0x03, 0x06, 0x09, 
    
    
    // font data
    0xFE, 0x10, // 33
    0x0E, 0x00, 0x0E, 0x00, 0x00, 0x00, // 34
    0x80, 0x90, 0xFC, 0x90, 0xF0, 0x9C, 0x10, 0x00, 0x18, 0x00, 0x10, 0x08, 0x00, 0x00, // 35
    0x20, 0x10, 0x09, 0x05, 0x03, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 36
    0xFE, 0xDC, 0xF8, 0x70, 0x20, 0x18, 0x08, 0x00, 0x00, 0x00, // 37
    0xC0, 0x2C, 0x32, 0x72, 0x8C, 0x40, 0x08, 0x10, 0x10, 0x10, 0x08, 0x18, // 38
    0x0E, 0x00, // 39
    0xF8, 0x06, 0x18, 0x60, // 40
    0x02, 0x0C, 0xF0, 0x00, 0x70, 0x08, // 41
    0x0C, 0x06, 0x0C, 0x00, 0x00, 0x00, // 42
    0x80, 0x80, 0xE0, 0x80, 0x80, 0x00, 0x00, 0x18, 0x00, 0x00, // 43
    0x00, 0x00, 0x40, 0x30, // 44
    0x40, 0x40, 0x40, 0x00, 0x00, 0x00, // 45
    0x00, 0x10, // 46
    0x80, 0x78, 0x06, 0x18, 0x00, 0x00, // 47
    0xFC, 0x06, 0x02, 0x06, 0xFC, 0x08, 0x18, 0x10, 0x18, 0x08, // 48
    0x08, 0x04, 0xFE, 0x00, 0x00, 0x18, // 49
    0x04, 0x82, 0x42, 0x22, 0x1C, 0x18, 0x10, 0x10, 0x10, 0x10, // 50
    0x04, 0x02, 0x22, 0x22, 0xDC, 0x08, 0x10, 0x10, 0x10, 0x08, // 51
    0xE0, 0x90, 0x8C, 0xFE, 0x80, 0x00, 0x00, 0x00, 0x18, 0x00, // 52
    0x00, 0x3E, 0x12, 0x12, 0x32, 0xE2, 0x08, 0x10, 0x10, 0x10, 0x18, 0x08, // 53
    0xF8, 0x16, 0x12, 0x12, 0xE4, 0x08, 0x18, 0x10, 0x10, 0x08, // 54
    0x02, 0x82, 0x62, 0x1A, 0x06, 0x00, 0x18, 0x00, 0x00, 0x00, // 55
    0xDC, 0x22, 0x22, 0x22, 0x22, 0xDC, 0x08, 0x10, 0x10, 0x10, 0x10, 0x08, // 56
    0x3C, 0x66, 0x42, 0x42, 0x26, 0xFC, 0x08, 0x10, 0x10, 0x10, 0x08, 0x00, // 57
    0x08, 0x10, // 58
    0x10, 0x70, // 59
    0xC0, 0xC0, 0x20, 0x20, 0x10, 0x00, 0x00, 0x08, 0x08, 0x10, // 60
    0x40, 0x40, 0x40, 0x40, 0x40, 0x08, 0x08, 0x08, 0x08, 0x08, // 61
    0x10, 0x20, 0x20, 0xC0, 0xC0, 0x10, 0x08, 0x08, 0x00, 0x00, // 62
    0x04, 0x02, 0xC2, 0x22, 0x1C, 0x00, 0x00, 0x10, 0x00, 0x00, // 63
    0xF0, 0x08, 0x04, 0xE4, 0x1A, 0x0A, 0x8A, 0x72, 0x0C, 0x8C, 0x78, 0x08, 0x18, 0x20, 0x40, 0x48, 0x48, 0x40, 0x48, 0x08, 0x08, 0x00, // 64
    0x00, 0xC0, 0x78, 0x4E, 0x4E, 0x78, 0xC0, 0x00, 0x10, 0x18, 0x00, 0x00, 0x00, 0x00, 0x18, 0x10, // 65
    0xFE, 0x22, 0x22, 0x22, 0x22, 0xDC, 0x18, 0x10, 0x10, 0x10, 0x10, 0x08, // 66
    0xF8, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x84, 0x00, 0x08, 0x10, 0x10, 0x10, 0x10, 0x18, 0x08, // 67
    0xFE, 0x02, 0x02, 0x02, 0x02, 0x04, 0xF8, 0x18, 0x10, 0x10, 0x10, 0x10, 0x08, 0x00, // 68
    0xFE, 0x22, 0x22, 0x22, 0x22, 0x02, 0x18, 0x10, 0x10, 0x10, 0x10, 0x10, // 69
    0xFE, 0x22, 0x22, 0x22, 0x22, 0x18, 0x00, 0x00, 0x00, 0x00, // 70
    0xF8, 0x84, 0x02, 0x02, 0x02, 0x22, 0x22, 0xE4, 0x00, 0x08, 0x10, 0x10, 0x10, 0x10, 0x08, 0x18, // 71
    0xFE, 0x20, 0x20, 0x20, 0x20, 0x20, 0xFE, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, // 72
    0xFE, 0x18, // 73
    0x80, 0x00, 0x00, 0x00, 0xFE, 0x08, 0x10, 0x10, 0x10, 0x08, // 74
    0xFE, 0x20, 0x10, 0x68, 0x84, 0x02, 0x18, 0x00, 0x00, 0x00, 0x00, 0x18, // 75
    0xFE, 0x00, 0x00, 0x00, 0x00, 0x18, 0x10, 0x10, 0x10, 0x10, // 76
    0xFE, 0x0E, 0x70, 0x80, 0x80, 0x70, 0x0E, 0xFE, 0x18, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, // 77
    0xFE, 0x06, 0x18, 0x60, 0xC0, 0x00, 0xFE, 0x18, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, // 78
    0xF8, 0x8C, 0x06, 0x02, 0x02, 0x02, 0x06, 0x8C, 0xF8, 0x00, 0x08, 0x18, 0x10, 0x10, 0x10, 0x18, 0x08, 0x00, // 79
    0xFE, 0x22, 0x22, 0x22, 0x22, 0x1C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, // 80
    0xF8, 0x8C, 0x06, 0x02, 0x02, 0x02, 0x06, 0x8C, 0xF8, 0x00, 0x08, 0x18, 0x10, 0x10, 0x10, 0x18, 0x18, 0x20, // 81
    0xFE, 0x22, 0x22, 0x22, 0x22, 0xDC, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x18, 0x10, // 82
    0x9C, 0x32, 0x22, 0x22, 0x62, 0xC4, 0x08, 0x18, 0x10, 0x10, 0x10, 0x08, // 83
    0x02, 0x02, 0x02, 0xFE, 0x02, 0x02, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, // 84
    0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x08, 0x18, 0x10, 0x10, 0x10, 0x18, 0x08, // 85
    0x02, 0x1E, 0xF0, 0x80, 0x80, 0x70, 0x0E, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, // 86
    0x06, 0x7C, 0xC0, 0x80, 0x78, 0x06, 0x3C, 0xC0, 0x80, 0x7C, 0x06, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, // 87
    0x06, 0x8C, 0x70, 0x70, 0x8C, 0x06, 0x18, 0x00, 0x00, 0x00, 0x08, 0x18, // 88
    0x02, 0x0C, 0x30, 0xE0, 0x30, 0x0C, 0x02, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, // 89
    0x00, 0x82, 0xC2, 0x62, 0x1A, 0x0E, 0x06, 0x10, 0x18, 0x10, 0x10, 0x10, 0x10, 0x10, // 90
    0xFE, 0x02, 0xF8, 0x80, // 91
    0x0E, 0xF0, 0x00, 0x00, 0x00, 0x18, // 92
    0x02, 0xFE, 0x80, 0xF8, // 93
    0x18, 0x06, 0x0C, 0x30, 0x00, 0x00, 0x00, 0x00, // 94
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, // 95
    0x02, 0x00, // 96
    0x90, 0x88, 0x48, 0x48, 0x48, 0xF0, 0x00, 0x08, 0x10, 0x10, 0x10, 0x08, 0x18, 0x10, // 97
    0xFE, 0x18, 0x08, 0x18, 0xF0, 0x18, 0x18, 0x10, 0x18, 0x08, // 98
    0xF0, 0x18, 0x08, 0x08, 0x08, 0x10, 0x08, 0x18, 0x10, 0x10, 0x10, 0x08, // 99
    0xF0, 0x18, 0x08, 0x08, 0x18, 0xFE, 0x08, 0x18, 0x10, 0x10, 0x08, 0x18, // 100
    0xF0, 0x58, 0x48, 0x48, 0x58, 0x70, 0x08, 0x18, 0x10, 0x10, 0x10, 0x08, // 101
    0x08, 0xFE, 0x0A, 0x00, 0x18, 0x00, // 102
    0xF0, 0x18, 0x08, 0x08, 0x10, 0xF8, 0x48, 0x98, 0x90, 0x90, 0xC8, 0x78, // 103
    0xFE, 0x10, 0x08, 0x08, 0xF0, 0x18, 0x00, 0x00, 0x00, 0x18, // 104
    0xFA, 0x18, // 105
    0x00, 0xFA, 0x80, 0xF8, // 106
    0xFE, 0x60, 0x70, 0x98, 0x00, 0x18, 0x00, 0x00, 0x08, 0x10, // 107
    0xFE, 0x18, // 108
    0xF8, 0x08, 0x08, 0xF8, 0x18, 0x08, 0x08, 0xF8, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18, // 109
    0xF8, 0x10, 0x08, 0x08, 0xF0, 0x18, 0x00, 0x00, 0x00, 0x18, // 110
    0xF0, 0x18, 0x08, 0x08, 0x18, 0xF0, 0x08, 0x18, 0x10, 0x10, 0x18, 0x08, // 111
    0xF8, 0x18, 0x08, 0x18, 0xF0, 0x78, 0x18, 0x10, 0x18, 0x08, // 112
    0xF0, 0x18, 0x08, 0x08, 0x10, 0xF8, 0x08, 0x18, 0x10, 0x10, 0x08, 0x78, // 113
    0xF8, 0x10, 0x08, 0x18, 0x00, 0x00, // 114
    0x70, 0x48, 0x48, 0x48, 0x90, 0x08, 0x10, 0x10, 0x10, 0x08, // 115
    0x08, 0xFC, 0x08, 0x00, 0x18, 0x10, // 116
    0xF8, 0x00, 0x00, 0x00, 0xF8, 0x08, 0x10, 0x10, 0x08, 0x18, // 117
    0x08, 0x70, 0x80, 0x80, 0x70, 0x08, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, // 118
    0x18, 0xE0, 0x00, 0xF8, 0x00, 0xE0, 0x18, 0x00, 0x00, 0x00, 0x18, 0x00, 0x18, 0x00, 0x00, 0x00, // 119
    0x08, 0x90, 0xE0, 0x30, 0x08, 0x18, 0x00, 0x00, 0x08, 0x10, // 120
    0x08, 0x70, 0x80, 0x80, 0x70, 0x08, 0x80, 0x80, 0x78, 0x18, 0x00, 0x00, // 121
    0x00, 0x88, 0xC8, 0x28, 0x18, 0x10, 0x18, 0x10, 0x10, 0x10, // 122
    0xC0, 0xFE, 0x02, 0x00, 0xF8, 0x80, // 123
    0xFE, 0x78, // 124
    0x02, 0xFE, 0xC0, 0x80, 0xF8, 0x00, // 125
    0x40, 0x20, 0x20, 0x40, 0x40, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 126
    0xFF, 0x01, 0x05, 0x03, 0xC3, 0x23, 0x1D, 0x01, 0xFF, 0x78, 0x40, 0x40, 0x40, 0x50, 0x40, 0x40, 0x40, 0x78 // 127
    
};

#endif