// ******************************************
// * Baah Box Arduino : Sensor BTLE gateway *
// ******************************************

// Copyright (C) 2017 – 2025 Orange SA

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

#include <Arduino.h>
#include "display.hpp"

//*********************************************
//*
//*       getVbat
//*
//*********************************************
// #define VBATPIN A7
float getVbat(void)
{
  // float measuredvbat = analogRead(VBATPIN);
  // measuredvbat *= 2;    // we divided by 2, so multiply back
  // measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  // measuredvbat /= 1024; // convert to voltage

  // solveButtonConflict();
  return 3.8;
}

// void setup() {
//   Serial.begin(115200);
//   while (!Serial) delay(10);    // wait until serial monitor opens

//   Serial.println(F("\nAdafruit MAX17048 simple demo"));

//   while (!maxlipo.begin()) {
//     Serial.println(F("Couldnt find Adafruit MAX17048?\nMake sure a battery is plugged in!"));
//     delay(2000);
//   }
//   Serial.print(F("Found MAX17048"));
//   Serial.print(F(" with Chip ID: 0x"));
//   Serial.println(maxlipo.getChipID(), HEX);
// }

// void loop() {
//   float cellVoltage = maxlipo.cellVoltage();
//   if (isnan(cellVoltage)) {
//     Serial.println("Failed to read cell voltage, check battery is connected!");
//     delay(2000);
//     return;
//   }
//   Serial.print(F("Batt Voltage: ")); Serial.print(cellVoltage, 3); Serial.println(" V");
//   Serial.print(F("Batt Percent: ")); Serial.print(maxlipo.cellPercent(), 1); Serial.println(" %");
//   Serial.println();

//   delay(2000);  // dont query too often!
// }