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

#ifndef BBConfig_hpp
#define BBConfig_hpp

#include "Config/config.hpp"

class BBConfigClass
{
public:
  BBConfigClass();
  void init();

  String btleDeviceName;
  int nbAnalogSensors;
  int analogInput[NB_ANALOG_SENSORS];
  int digitalInput[NB_DIGITAL_PINS];
  float analogSensorFilter;
  String copyright;
  String language;

private:
  void printConfig(void);
  void loadDefaultValues(void);
};

#endif /* BBConfig_hpp */
