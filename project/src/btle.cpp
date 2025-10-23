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

#include <SPI.h>
#include "btle.hpp"

// #ifdef USE_NRF51
//     #include "Nrf51/btleNrf51.hpp"
//     btle51Class ble51;
// #endif

/*=========================================================================*/

//*********************************************
//*
//*       Constructor
//*
//*********************************************
btleClass::btleClass()
{
  btleBufferInputsIndex = 0;
  for (int i = 0; i < BTLE_MAX_BUFFER_SIZE; i++)
  {
    btleBufferInputs[i] = 0;
  }
}

//*********************************************
//*
//*       init
//*
//*********************************************
void btleClass::init(char *inputDeviceName)
{
  /* Initialise the module */
  memset(deviceName, 0, BTLE_MAX_DEVICE_NAME);
  strncpy(deviceName, inputDeviceName, BTLE_MAX_DEVICE_NAME - 1);

  Serial.println("begin of btle Init");

  #ifdef USE_NRF51
  ble51.init(inputDeviceName); 
  #endif
}

//*********************************************
//*
//*       write
//*
//*********************************************
void btleClass::write(char *data, int dataLength)
{
  #ifdef USE_NRF51
  ble51.write(data, dataLength); 
  #endif
}

/**************************************************************************/
/*!
  @brief  Constantly poll for new command or response data
*/
/**************************************************************************/
int btleClass::read(char *command)
{
  #ifdef USE_NRF51
  ble51.read(command); 
  #endif
}
