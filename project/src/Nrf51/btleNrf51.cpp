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
#include "../include/Nrf51/btleNrf51.hpp"
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

/*=========================================================================
  APPLICATION SETTINGS

      FACTORYRESET_ENABLE       Perform a factory reset when running this sketch
     
                                Enabling this will put your Bluefruit LE module
  in a 'known good' state and clear any config
  data set in previous sketches or projects, so
                                running this at least once is a good idea.
     
                                When deploying your project, however, you will
  want to disable factory reset by setting this
  value to 0.  If you are making changes to your
                                Bluefruit LE device via AT commands, and those
  changes aren't persisting across resets, this
  is the reason why.  Factory reset will erase
  the non-volatile memory where config data is
  stored, setting it back to factory default
  values.
         
                                Some sketches that require you to bond to a
  central device (HID mouse, keyboard, etc.)
  won't work at all with this feature enabled
  since the factory reset will clear all of the
  bonding data stored on the chip, meaning the
  central device won't be able to reconnect.
  MINIMUM_FIRMWARE_VERSION  Minimum firmware version to have some new features
  MODE_LED_BEHAVIOUR        LED activity, valid options are
  "DISABLE" or "MODE" or "BLEUART" or
  "HWUART"  or "SPI"  or "MANUAL"
  -----------------------------------------------------------------------*/
#define FACTORYRESET_ENABLE 1
#define MINIMUM_FIRMWARE_VERSION "0.6.6"
#define MODE_LED_BEHAVIOUR "MODE"
/*=========================================================================*/

/* create the ble object */
Adafruit_BluefruitLE_SPI ble51(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

//*********************************************
//*
//*       Constructor
//*
//*********************************************
btle51Class::btle51Class()
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
void btle51Class::init(char *inputDeviceName)
{
  /* Initialise the module */
  memset(deviceName, 0, BTLE_MAX_DEVICE_NAME);
  strncpy(deviceName, inputDeviceName, BTLE_MAX_DEVICE_NAME - 1);

  Serial.println("begin of btle Init");
  if (!ble51.begin(VERBOSE_MODE))
  {
    Serial.println(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }

  if (FACTORYRESET_ENABLE)
  {
    /* Perform a factory reset to make sure everything is in a known state */
    if (!ble51.factoryReset())
    {
      Serial.println(F("Couldn't factory reset"));
    }
  }

  /* Disable command echo from Bluefruit */
  ble51.echo(false);

  /* Print Bluefruit information */
  ble51.info();
  ble51.verbose(false); // debug info is a little annoying after this point!

  char tmpChar[BTLE_MAX_DEVICE_NAME + 30];

  sprintf(tmpChar, "AT+GAPDEVNAME=%s", deviceName);

  ble51.sendCommandCheckOK(tmpChar);

  Serial.println("wait for connection");
  /* Wait for connection */

  configured = false;
}

//*********************************************
//*
//*       write
//*
//*********************************************
void btle51Class::write(char *data, int dataLength)
{
  if (ble51.isConnected())
  {
    if (configured == false)
    {
      configured = true;
      // LED Activity command is only supported from 0.6.6
      if (ble51.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION))
      {
        // Change Mode LED Activity
        ble51.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
      }
      // Set module to DATA mode
      ble51.setMode(BLUEFRUIT_MODE_DATA);
    }
    ble51.write(data, dataLength);
  }
}

/**************************************************************************/
/*!
  @brief  Constantly poll for new command or response data
*/
/**************************************************************************/
int btle51Class::read(char *command)
{
  if (ble51.isConnected())
  {
    if (configured == false)
    {
      configured = true;
      Serial.println("Btle51 read");
      // LED Activity command is only supported from 0.6.6
      if (ble51.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION))
      {
        // Change Mode LED Activity
        ble51.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
      }

      // Set module to DATA mode
      ble51.setMode(BLUEFRUIT_MODE_DATA);
    }

    // Echo received data
    while (ble51.available())
    {
      char c = (char)ble51.read();
      if (btleBufferInputsIndex < BTLE_MAX_BUFFER_SIZE)
      {
        btleBufferInputs[btleBufferInputsIndex] = c;
        btleBufferInputsIndex++;
      }
      if (c == BTLE_END_OF_CHAR)
      {
        memcpy(command, btleBufferInputs, btleBufferInputsIndex + 1);
        int output = btleBufferInputsIndex;
        btleBufferInputsIndex = 0;
        if (output < BTLE_MAX_BUFFER_SIZE)
        {
          return output;
        }
        else
        {
          return 0;
        }
      }
    }
    return 0;
  }
  else
  {
    return 0;
  }
}
