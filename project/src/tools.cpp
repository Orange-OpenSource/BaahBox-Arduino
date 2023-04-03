// ******************************************
// * Baah Box Arduino : Sensor BTLE gateway *
// ******************************************

// Copyright (C) 2017 – 2023 Orange SA

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include <arduino.h>
#include "display.hpp"

//*********************************************
//*
//*       getVbat
//*
//*********************************************
#define VBATPIN A7
float getVbat(void)
{
  float measuredvbat = analogRead(VBATPIN);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024; // convert to voltage
  //Serial.print("VBat: ");
  //Serial.println(measuredvbat);

  // to solve conflict issue between batterie input and BUTTON_A input
  pinMode(BUTTON_A, OUTPUT);
  digitalWrite(BUTTON_A, HIGH);
  pinMode(BUTTON_A, INPUT);
  return measuredvbat;
}