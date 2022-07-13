// ******************************************
// * Baah Box Arduino : Sensor BTLE gateway *
// ******************************************

// Copyright (C) 2017 – 2019 Orange SA

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

// COMMON SETTINGS
// ----------------------------------------------------------------------------------------------
// These settings are used in both SW UART, HW UART and SPI mode
// ----------------------------------------------------------------------------------------------
#define BUFSIZE 128        // Size of the read buffer for incoming data
#define VERBOSE_MODE false // If set to 'true' enables debug output

// SOFTWARE UART SETTINGS
// ----------------------------------------------------------------------------------------------
// The following macros declare the pins that will be used for 'SW' serial.
// You should use this option if you are connecting the UART Friend to an UNO
// ----------------------------------------------------------------------------------------------
#define BLUEFRUIT_SWUART_RXD_PIN 9  // Required for software serial!
#define BLUEFRUIT_SWUART_TXD_PIN 10 // Required for software serial!
#define BLUEFRUIT_UART_CTS_PIN 11   // Required for software serial!
#define BLUEFRUIT_UART_RTS_PIN -1   // Optional, set to -1 if unused

// HARDWARE UART SETTINGS
// ----------------------------------------------------------------------------------------------
// The following macros declare the HW serial port you are using. Uncomment
// this line if you are connecting the BLE to Leonardo/Micro or Flora
// ----------------------------------------------------------------------------------------------
#ifdef Serial1 // this makes it not complain on compilation if there's no Serial1
#define BLUEFRUIT_HWSERIAL_NAME Serial1
#endif

// SHARED UART SETTINGS
// ----------------------------------------------------------------------------------------------
// The following sets the optional Mode pin, its recommended but not required
// ----------------------------------------------------------------------------------------------
#define BLUEFRUIT_UART_MODE_PIN 12 // Set to -1 if unused

// SHARED SPI SETTINGS
// ----------------------------------------------------------------------------------------------
// The following macros declare the pins to use for HW and SW SPI communication.
// SCK, MISO and MOSI should be connected to the HW SPI pins on the Uno when
// using HW SPI.  This should be used with nRF51822 based Bluefruit LE modules
// that use SPI (Bluefruit LE SPI Friend).
// ----------------------------------------------------------------------------------------------
#define BLUEFRUIT_SPI_CS 8
#define BLUEFRUIT_SPI_IRQ 7
#define BLUEFRUIT_SPI_RST 4 // Optional but recommended, set to -1 if unused

// SOFTWARE SPI SETTINGS
// ----------------------------------------------------------------------------------------------
// The following macros declare the pins to use for SW SPI communication.
// This should be used with nRF51822 based Bluefruit LE modules that use SPI
// (Bluefruit LE SPI Friend).
// ----------------------------------------------------------------------------------------------
#define BLUEFRUIT_SPI_SCK 13
#define BLUEFRUIT_SPI_MISO 12
#define BLUEFRUIT_SPI_MOSI 11

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
};

#endif /* btle_hpp */
