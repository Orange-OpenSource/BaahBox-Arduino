// ******************************************
// * Baah Box Arduino : Sensor BTLE gateway
// * for NRF51 Adafruit boards like FEATHER M0 Bluefruit 
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

#ifndef btle_hpp
#define btle_hpp

#include <stdio.h>
#define BTLE_END_OF_CHAR '#'
#define BTLE_MAX_BUFFER_SIZE 512
#define BTLE_MAX_DEVICE_NAME 128

#include "btleNrf51.hpp"

// COMMON SETTINGS
// ----------------------------------------------------------------------------------------------
// These settings are used in both SW UART, HW UART and SPI mode
// ----------------------------------------------------------------------------------------------
// #define BUFSIZE 128        // Size of the read buffer for incoming data
// #define VERBOSE_MODE false // If set to 'true' enables debug output

/* Btle lib Class*/
class btleClass
{
public:
  btleClass();
  void init(char *inputDeviceName);
  int read(char *command);
  void write(char *data, int dataLength);
  char deviceName[BTLE_MAX_DEVICE_NAME];
  
private:
  bool configured;
  int btleBufferInputsIndex;
  char btleBufferInputs[BTLE_MAX_BUFFER_SIZE];
  btle51Class ble51;

};

#endif /* btle_hpp */
