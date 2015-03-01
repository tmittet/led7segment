/************************************************************************/
/* 7-Segment LED Display library, for 74HC series chips, v1.1.          */
/*                                                                      */
/* This library is free software: you can redistribute it and/or modify */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation, either version 3 of the License, or    */
/* (at your option) any later version.                                  */
/*                                                                      */
/* This library is distributed in the hope that it will be useful, but  */
/* WITHOUT ANY WARRANTY; without even the implied warranty of           */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU     */
/* General Public License for more details.                             */
/*                                                                      */
/* You should have received a copy of the GNU General Public License    */
/* along with this library. If not, see <http://www.gnu.org/licenses/>. */
/*                                                                      */
/* Written by Thomas Mittet (code@lookout.no) March 2010.               */
/************************************************************************/

#include "Led7Segment.h"

Led7Segment::Led7Segment(uint8_t displayPanels, uint8_t clockPin, uint8_t dataPin, uint8_t dimPin, bool reverseDim)
{
  this->displayPanels = displayPanels;
  this->clockPin = clockPin;
  this->dataPin = dataPin;
  this->dimPin = dimPin;
  this->reverseDim = reverseDim;
  brightness = reverseDim ? 0 : 255;
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(dimPin,OUTPUT);
  off();
  clear();
}

//////////////////////////////
/// Public
//////////////////////////////

void Led7Segment::displayText(char text[])
{
  off();
  for(int8_t i = displayPanels; i >= 0; i--)
  {
    displayCharacter(text[i], false);
  }
  on();
}

void Led7Segment::displayNumber(float number, uint8_t decimals, bool leadingZero)
{
  displayNumber(number, decimals, leadingZero, 0, 0);
}

void Led7Segment::displayNumber(float number, uint8_t decimals, bool leadingZero, uint8_t padLeft, uint8_t padRight)
{
  off();
  bool negative = number < 0;
  uint32_t real = round(abs(number) * pow(10, decimals));
  uint8_t digits = 0;
  for(uint8_t i = 0; i < padRight; i++)
  {
    displayCharacter(' ', 0);
  }
  while((real > 0 || digits < decimals + 1) && displayPanels + decimals > digits)
  {
    shiftOut(dataPin, clockPin, LSBFIRST, ascii[(real % 10) + 15] + (decimals && digits == decimals));
    real /= 10;
    digits++;
  }
  if(real == 0)
  {
    while(digits < displayPanels || (negative && digits - decimals < displayPanels))
    {
      if(negative && (!leadingZero || digits >= displayPanels - 1))
      {
        displayCharacter('-', 0);
        negative = 0;
      }
      else if(digits < displayPanels - padLeft - padRight)
      {
        displayCharacter(leadingZero ? '0' : ' ', 0);
      }
      else if(digits >= displayPanels - padLeft)
      {
        displayCharacter(' ', 0);
      }
      digits++;
    }
  }
  // Overflow, real isn't zero
  else
  {
    clear('-');
  }
  on();
}

void Led7Segment::displayCharacter(char character, bool dot)
{
  shiftOut(dataPin, clockPin, LSBFIRST, charToPattern(character) + dot);
}

void Led7Segment::on()
{
  updateBrightness();
}

void Led7Segment::off()
{
  digitalWrite(dimPin, LOW);
}

void Led7Segment::clear()
{
  clear(' ');
}

void Led7Segment::clear(char character)
{
  off();
  for(int i = 0; i < displayPanels; i++) displayCharacter(character, 0);
  on();
}

void Led7Segment::fade(uint16_t ms, uint8_t value)
{
  if(brightness != value)
  {
    if(ms == 0)
    {
      brightness = value;
      updateBrightness();
    }
    else
    {
      uint8_t factor = brightness > value ? -1 : 1;
      while(brightness != value)
      {
        brightness += factor;
        updateBrightness();
        delayMicroseconds(ms * 4);
      }
    }
  }
}

//////////////////////////////
/// Private
//////////////////////////////

uint8_t Led7Segment::charToPattern(char character)
{
  if(character < 33) return 0;
  return ascii[character - (character > 96 ? 65 : 33)];
}

void Led7Segment::updateBrightness()
{
  analogWrite(dimPin, reverseDim ? 255 - brightness : brightness);
}