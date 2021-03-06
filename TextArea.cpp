/*
 * The MIT License
 * 
 * Copyright (c) 2018 gaogoa.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * Handles the text display.
 * Text display supports two lines at the bottom of the screen.
 */
 
#include "TextArea.h"
#include "Graphics.h"

static const uint8_t _fontPattern[] =
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x08, 0x08, 0x08, 0x08, 0x00, 0x08, 0x00, 0x00,
  0x14, 0x14, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x14, 0x14, 0x3e, 0x14, 0x3e, 0x14, 0x14, 0x00,
  0x08, 0x3c, 0x0a, 0x1c, 0x28, 0x1e, 0x08, 0x00,
  0x06, 0x26, 0x10, 0x08, 0x04, 0x32, 0x30, 0x00,
  0x0c, 0x12, 0x0a, 0x04, 0x2a, 0x12, 0x2c, 0x00,
  0x0c, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x10, 0x08, 0x04, 0x04, 0x04, 0x08, 0x10, 0x00,
  0x04, 0x08, 0x10, 0x10, 0x10, 0x08, 0x04, 0x00,
  0x00, 0x08, 0x2a, 0x1c, 0x2a, 0x08, 0x00, 0x00,
  0x00, 0x08, 0x08, 0x3e, 0x08, 0x08, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x10, 0x08,
  0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x00,
  0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00,
  0x1c, 0x22, 0x32, 0x2a, 0x26, 0x22, 0x1c, 0x00,
  0x08, 0x0c, 0x08, 0x08, 0x08, 0x08, 0x1c, 0x00,
  0x1c, 0x22, 0x20, 0x10, 0x08, 0x04, 0x3e, 0x00,
  0x3e, 0x10, 0x08, 0x10, 0x20, 0x22, 0x1c, 0x00,
  0x10, 0x18, 0x14, 0x12, 0x3e, 0x10, 0x10, 0x00,
  0x3e, 0x02, 0x1e, 0x20, 0x20, 0x22, 0x1c, 0x00,
  0x18, 0x04, 0x02, 0x1e, 0x22, 0x22, 0x1c, 0x00,
  0x3e, 0x20, 0x10, 0x08, 0x04, 0x04, 0x04, 0x00,
  0x1c, 0x22, 0x22, 0x1c, 0x22, 0x22, 0x1c, 0x00,
  0x1c, 0x22, 0x22, 0x3c, 0x20, 0x10, 0x0c, 0x00,
  0x00, 0x0c, 0x0c, 0x00, 0x0c, 0x0c, 0x00, 0x00,
  0x00, 0x0c, 0x0c, 0x00, 0x0c, 0x08, 0x04, 0x00,
  0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x00,
  0x00, 0x00, 0x3e, 0x00, 0x3e, 0x00, 0x00, 0x00,
  0x04, 0x08, 0x10, 0x20, 0x10, 0x08, 0x04, 0x00,
  0x1c, 0x22, 0x20, 0x10, 0x08, 0x00, 0x08, 0x00,
  0x1c, 0x22, 0x20, 0x2c, 0x3a, 0x22, 0x1c, 0x00,
  0x08, 0x14, 0x22, 0x22, 0x3e, 0x22, 0x22, 0x00,
  0x1e, 0x22, 0x22, 0x1e, 0x22, 0x22, 0x1e, 0x00,
  0x1c, 0x22, 0x02, 0x02, 0x02, 0x22, 0x1c, 0x00,
  0x0e, 0x12, 0x22, 0x22, 0x22, 0x12, 0x0e, 0x00,
  0x3e, 0x02, 0x02, 0x1e, 0x02, 0x02, 0x3e, 0x00,
  0x3e, 0x02, 0x02, 0x1e, 0x02, 0x02, 0x02, 0x00,
  0x1c, 0x22, 0x02, 0x3a, 0x22, 0x22, 0x3c, 0x00,
  0x22, 0x22, 0x22, 0x3e, 0x22, 0x22, 0x22, 0x00,
  0x1c, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1c, 0x00,
  0x38, 0x10, 0x10, 0x10, 0x10, 0x12, 0x0c, 0x00,
  0x22, 0x12, 0x0a, 0x06, 0x0a, 0x12, 0x22, 0x00,
  0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x3e, 0x00,
  0x22, 0x36, 0x2a, 0x2a, 0x22, 0x22, 0x22, 0x00,
  0x22, 0x22, 0x26, 0x2a, 0x32, 0x22, 0x22, 0x00,
  0x1c, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1c, 0x00,
  0x1e, 0x22, 0x22, 0x1e, 0x02, 0x02, 0x02, 0x00,
  0x1c, 0x22, 0x22, 0x22, 0x2a, 0x12, 0x2c, 0x00,
  0x1e, 0x22, 0x22, 0x1e, 0x0a, 0x12, 0x22, 0x00,
  0x3c, 0x02, 0x02, 0x1c, 0x20, 0x20, 0x1e, 0x00,
  0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00,
  0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1c, 0x00,
  0x22, 0x22, 0x22, 0x22, 0x22, 0x14, 0x08, 0x00,
  0x22, 0x22, 0x22, 0x2a, 0x2a, 0x2a, 0x14, 0x00,
  0x22, 0x22, 0x14, 0x08, 0x14, 0x22, 0x22, 0x00,
  0x22, 0x22, 0x22, 0x14, 0x08, 0x08, 0x08, 0x00,
  0x3e, 0x20, 0x10, 0x08, 0x04, 0x02, 0x3e, 0x00,
};

static const uint8_t *fontPattern = _fontPattern;

const int CHAR_WIDTH  = 8;
const int CHAR_HEIGHT = 8;

void TextArea::clear() {
  memset(bitmapBuff, 0, sizeof(bitmapBuff));
}

void TextArea::update() {
  LCD_Update16(bitmapBuff, LCD_HEIGHT - GRAPHIC_BUFF_HEIGHT, GRAPHIC_BUFF_HEIGHT);
}

void TextArea::print(int x, int y, const char *st)
{
  while(*st) {
    printChar(x++, y, *st++);
  }
}

void TextArea::print(int x, int y, int value, int length, char filler)
{  
  char buff[15 + 1];
  memset(buff, filler, sizeof(buff));
  buff[sizeof(buff) - 1] = 0;

  boolean minus = value < 0;
  value = abs(value);

  int wpos = sizeof(buff);
  if(value == 0) {
      buff[--wpos] = '0';
  }
  else {
    while(wpos >= 0 && value != 0) {
      buff[--wpos] = '0' + (value % 10);
      value /= 10;
    }
    if(wpos >= 0 && minus) {
        buff[--wpos] = '-';
    }
  }

  int dpos = length <= 0 ? wpos : (length < sizeof(buff) - 1 ? sizeof(buff) - length : 0);
  print(x, y, buff + dpos);
}

void TextArea::printChar(int x, int y, char ch) {
  if (ch >= ' ' && ch <= 'Z') {
    uint16_t  *wp = bitmapBuff + (x * CHAR_WIDTH) + (y * CHAR_HEIGHT * GRAPHIC_WIDTH);
    const uint8_t *bp = fontPattern + (ch - 0x20) * 8;
    uint8_t bits;
    for (int v = 0; v < CHAR_HEIGHT; v++)
    {
      bits = *bp++;
      for (int h = 0; h < CHAR_WIDTH; h++)
      {
        if (bits & 1) {
          *(wp + h) = 0xffff;
        }
        bits >>= 1;
      }
      wp += GRAPHIC_WIDTH;
    }
  }
}

void TextArea::error(const char *msg) {
  clear();
  print(0, 0, "* ERROR *");
  print(0, 1, msg);
  for (;;) {
    update();
  }
}

