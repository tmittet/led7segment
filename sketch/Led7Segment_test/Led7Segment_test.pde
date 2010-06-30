/************************************************************************/
/* 7-Segment LED Display library test sketch, v1.1.                     */
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
/* Written by Thomas Mittet thomas@mittet.nu March 2010.                */
/************************************************************************/

#include <Led7Segment.h>

// displayPanels = 4, clockPin = 3, dataPin = 4, dimPin = 5, reverseDim = false
Led7Segment led7 = Led7Segment(4, 3, 4, 5, false);

void setup()
{ }

void loop()
{
  led7.fade(500, 0);
  led7.displayText((char[4]){ 'T', 'e', 's', 't' });
  led7.fade(500, 255);
  led7.fade(500, 0);
  led7.displayNumber(31.559, true, 2);
  led7.fade(500, 255);
  delay(1000);
}
