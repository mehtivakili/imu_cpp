/*
    MIT License

    Copyright (c) 2018-2019, 2021 Alexey Dynda

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/
/**
 *   Attiny85 PINS
 *             ____
 *   RESET   -|_|  |- 3V
 *   SCL (3) -|    |- (2)
 *   SDA (4) -|    |- (1)
 *   GND     -|____|- (0)
 *
 *   Atmega328 PINS: connect LCD to A4/A5
 */

#include "lcdgfx.h"

DisplaySSD1306_128x64_I2C display(-1); // or (-1,{busId, addr, scl, sda, frequency})
//DisplaySSD1306_128x64_SPI display(-1,{-1, 0, 1, 0, -1, -1); // Use this line for nano pi (RST not used, 0=CE, gpio1=D/C)
//DisplaySSD1306_128x64_SPI display(3,{-1, 4, 5, 0,-1,-1});   // Use this line for Atmega328p (3=RST, 4=CE, 5=D/C)
//DisplaySSD1306_128x64_SPI display(24,{-1, 0, 23, 0,-1,-1}); // Use this line for Raspberry  (gpio24=RST, 0=CE, gpio23=D/C)
//DisplaySSD1306_128x64_SPI display(22,{-1, 5, 21, 0,-1,-1}); // Use this line for ESP32 (VSPI)  (gpio22=RST, gpio5=CE for VSPI, gpio21=D/C)

#ifndef CONFIG_SSD1306_UNICODE_ENABLE
#error "This sketch requires CONFIG_SSD1306_UNICODE_ENABLE to be enabled in UserSettings.h"
#endif

const uint8_t g_customUnicodeFont_6x8[] PROGMEM =
{
    0x01,  // 0x01 means fixed font type with unicode support
    0x06,  // 0x05 = 6 - font width in pixels
    0x08,  // 0x08 = 8 - font height in pixels
    0x00,  // This byte has no meaning for unicode fonts
    // Start of unicode table
    0x00,  // First unicode char in block (LSB)
    0xE4,  // First unicode char in block (MSB)  = 0x00E4
    0x01,  // number of chars encoded in the block
    // 'ä'
    0B00111000,
    0B01000101,
    0B01000100,
    0B00111001,
    0B01000100,
    0B00000000,

    0x00,  // First unicode char in block (LSB)
    0xC4,  // First unicode char in block (MSB)  = 0x00C4
    0x01,  // number of chars encoded in the block
    // 'Ä'
    0B00000000,
    0B11110000,
    0B00101001,
    0B00100100,
    0B00101001,
    0B11110000,

    0x00, 0x00, 0x00, // End of unicode tables
};

void setup()
{
    display.begin();
    display.fill(0x00);

    // First variant of usage: using unicodes with standard ascii font
    display.setFixedFont( ssd1306xled_font6x8, g_customUnicodeFont_6x8 );
    display.printFixed (0,  8,  "Ascii + Ää", STYLE_NORMAL );

    // Second variant of usage: without standard ascii font
    display.setFixedFont( g_customUnicodeFont_6x8 );
    display.printFixed (0,  16,  "ÄäÄäÄä", STYLE_NORMAL );
}


void loop()
{
}




