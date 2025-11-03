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

#include "btle.hpp"
#include <string.h>


// Callback pour recevoir la commande
class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string rxValue = pCharacteristic->getValue();
    if (rxValue == "CALIBRATE") {
      //Serial.println("Commande CALIBRATE reçue");
    }
  }
};
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
  BLEDevice::init(inputDeviceName);
  pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  // Caractéristique pour recevoir la commande (écriture)
  pCommandCharacteristic = pService->createCharacteristic(
                                CHAR_COMMAND_UUID,
                                BLECharacteristic::PROPERTY_WRITE
                              );
  pCommandCharacteristic->setCallbacks(new MyCallbacks());

  // Caractéristique pour envoyer la position (notification)
  pSensorDataCharacteristic = pService->createCharacteristic(
                                CHAR_POSITION_UUID,
                                BLECharacteristic::PROPERTY_NOTIFY
                              );
  pSensorDataCharacteristic->addDescriptor(new BLE2902());

  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->start();
}

/*********************************************
//*
//*       write
//*
//*********************************************/
void btleClass::write(char *data, int dataLength)
{
  std::string str;
// Manually push characters from char* to string
    for (int i = 0; data[i] != '\0'; i++) {
        str.push_back(data[i]);
    }
// quid du 90 ?


  pSensorDataCharacteristic->setValue(str);
  pSensorDataCharacteristic->notify();
}
/**************************************************************************/
/*!
  @brief  Constantly poll for new command or response data
*/
/**************************************************************************/
int btleClass::read(char *command)
{

}

