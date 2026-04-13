// // // ******************************************
// // // * Baah Box Arduino : Sensor BTLE gateway *
// // // ******************************************

// // // Copyright (C) 2017 – 2025 Orange SA

// // // This program is free software: you can redistribute it and/or modify
// // // it under the terms of the GNU General Public License as published by
// // // the Free Software Foundation, either version 3 of the License, or
// // // (at your option) any later version.

// // // This program is distributed in the hope that it will be useful,
// // // but WITHOUT ANY WARRANTY; without even the implied warranty of
// // // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// // // GNU General Public License for more details.

// // // You should have received a copy of the GNU General Public License
// // // along with this program. If not, see <http://www.gnu.org/licenses/>.
// // /*
// // #include <SPI.h>
// #include "btle.hpp"
// #include <bluefruit.h>
// #include <Adafruit_LittleFS.h>
// #include <InternalFileSystem.h>

//  // BLE Service
//  BLEDfu  bledfu;  // OTA DFU service
//  BLEDis  bledis;  // device information
//  BLEUart bleuart; // uart over ble
//  BLEBas  blebas;  // battery

// // /* create the ble object */

// //*********************************************
// //*
// //*       Constructor
// //*
// //*********************************************
// btleClass::btleClass()
// {
//   btleBufferInputsIndex = 0;
//   for (int i = 0; i < BTLE_MAX_BUFFER_SIZE; i++)
//   {
//     btleBufferInputs[i] = 0;
//   }
// }

// //*********************************************
// //*
// //*       init
// //*
// //*********************************************
//  void btleClass::init(char *inputDeviceName)
// {

// //   /* Initialise the module */
// //   memset(deviceName, 0, BTLE_MAX_DEVICE_NAME);
// //   strncpy(deviceName, inputDeviceName, BTLE_MAX_DEVICE_NAME - 1);

// // Setup the BLE LED to be enabled on CONNECT
//   // Note: This is actually the default behavior, but provided
//   // here in case you want to control this LED manually via PIN 19
//   Bluefruit.autoConnLed(true);

//   // Config the peripheral connection with maximum bandwidth
//   // more SRAM required by SoftDevice
//   // Note: All config***() function must be called before begin()
//   Bluefruit.configPrphBandwidth(BANDWIDTH_MAX);

//   Bluefruit.begin();
//   Bluefruit.setTxPower(4);    // Check bluefruit.h for supported values
//   //Bluefruit.setName(getMcuUniqueID()); // useful testing with multiple central connections
//   Bluefruit.Periph.setConnectCallback(connect_callback);
//   Bluefruit.Periph.setDisconnectCallback(disconnect_callback);

//   // To be consistent OTA DFU should be added first if it exists
//   bledfu.begin();

//   // Configure and Start Device Information Service
//   bledis.setManufacturer("Adafruit Industries");
//   bledis.setModel("Bluefruit Feather52");
//   bledis.begin();

//   // Configure and Start BLE Uart Service
//   bleuart.begin();

//   // Start BLE Battery Service
//   blebas.begin();
//   blebas.write(100);

//   // Set up and start advertising
//   // Advertising packet
//   Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
//   Bluefruit.Advertising.addTxPower();

//   // Include bleuart 128-bit uuid
//   Bluefruit.Advertising.addService(bleuart);

//   // Secondary Scan Response packet (optional)
//   // Since there is no room for 'Name' in Advertising packet
//   Bluefruit.ScanResponse.addName();

//   /* Start Advertising
//    * - Enable auto advertising if disconnected
//    * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
//    * - Timeout for fast mode is 30 seconds
//    * - Start(timeout) with timeout = 0 will advertise forever (until connected)
//    *
//    * For recommended advertising interval
//    * https://developer.apple.com/library/content/qa/qa1931/_index.html
//    */
//   Bluefruit.Advertising.restartOnDisconnect(true);
//   Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
//   Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
//   Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds

//  }

// //*********************************************
// //*
// //*       write
// //*
// //*********************************************
// void btleClass::write(char *data, int dataLength)
// {
//     bleuart.write(data, dataLength);
// }

// // /**************************************************************************/
// // /*!
// //   @brief  Constantly poll for new command or response data
// // */
// // /**************************************************************************/
// // int btleClass::read(char *command)
// // {
// //   if (ble.isConnected())
// //   {
// //     if (configured == false)
// //     {
// //       configured = true;
// //       Serial.println("Btle read");
// //       // LED Activity command is only supported from 0.6.6
// //       if (ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION))
// //       {
// //         // Change Mode LED Activity
// //         ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
// //       }

// //       // Set module to DATA mode
// //       ble.setMode(BLUEFRUIT_MODE_DATA);
// //     }

// //     // Echo received data
// //     while (ble.available())
// //     {
// //       char c = (char)ble.read();
// //       if (btleBufferInputsIndex < BTLE_MAX_BUFFER_SIZE)
// //       {
// //         btleBufferInputs[btleBufferInputsIndex] = c;
// //         btleBufferInputsIndex++;
// //       }
// //       if (c == BTLE_END_OF_CHAR)
// //       {
// //         memcpy(command, btleBufferInputs, btleBufferInputsIndex + 1);
// //         int output = btleBufferInputsIndex;
// //         btleBufferInputsIndex = 0;
// //         if (output < BTLE_MAX_BUFFER_SIZE)
// //         {
// //           return output;
// //         }
// //         else
// //         {
// //           return 0;
// //         }
// //       }
// //     }
// //     return 0;
// //   }
// //   else
// //   {
// //     return 0;
// //   }
// // }
// // */