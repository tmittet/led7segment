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

#ifndef Led7Segment_h
#define Led7Segment_h

#include "Arduino.h"

// ASCII characters 33 to 96
const uint8_t ascii[64] =
{
  0x61, //  !
  0x44, //  "
  0x92, //  #
  0x6C, //  $ = ||
  0xB4, //  %
  0xFF, //  & = 8.
  0x04, //  '
  0x9C, //  (
  0xF0, //  )
  0x62, //  *
  0x0E, //  +
  0x08, //  , = i <<
  0x02, //  -
  0x01, //  .
  0x4A, //  /
  0xFC, //  0
  0X60, //  1
  0xDA, //  2
  0xF2, //  3
  0x66, //  4
  0xB6, //  5
  0xBE, //  6
  0xE0, //  7
  0xFE, //  8
  0xF6, //  9
  0x41, //  :
  0x50, //  ;
  0x1A, //  <
  0x12, //  =
  0x32, //  >
  0xCB, //  ?
  0x3B, //  @
  0xEE, //  A
  0x3E, //  B
  0x9C, //  C
  0x7A, //  D
  0x9E, //  E
  0x8E, //  F
  0xBE, //  G
  0x6E, //  H
  0x60, //  I
  0x70, //  J
  0x1E, //  K
  0x1C, //  L
  0xEC, //  M
  0x2A, //  N
  0x3A, //  O
  0xCE, //  P
  0xE6, //  Q
  0x0A, //  R
  0xB6, //  S
  0x1E, //  T
  0x7C, //  U
  0x38, //  V
  0x38, //  W
  0x6E, //  X
  0x76, //  Y
  0xDA, //  Z
  0x9C, //  [
  0x26, /*  \ */
  0xF0, //  ]
  0xC4, //  ^
  0x10, //  _
  0x40, // `
};


class Led7Segment
{

public:
  Led7Segment(uint8_t displayPanels, uint8_t clockPin, uint8_t dataPin, uint8_t dimPin, bool reverseDim);

  void displayText(char text[]);
  void displayNumber(float number, uint8_t decimals, bool leadingZero);
  void displayNumber(float number, uint8_t decimals, bool leadingZero, uint8_t padLeft, uint8_t padRight);
  void displayCharacter(char character, bool dot);
  void on();
  void off();
  void clear();
  void clear(char character);
  void fade(uint16_t ms, uint8_t value);

private:
  uint8_t charToPattern(char character);
  void updateBrightness();
  uint8_t displayPanels, clockPin, dataPin, dimPin, brightness;
  bool reverseDim;
};

#endif