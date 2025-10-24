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

#include "../Config/config.hpp"

#ifndef configSD_hpp
#define configSD_hpp

#include <SPI.h>
#if !(USE_ESP32S3)
  #include <SD.h>
#endif

#define MAX_NB_MUSCLE_SENSOR 5
#define FILENAME_SIZE 50
#define NB_JOYSTICK_PIN 4

// change this to match your SD shield or module;
// Adafruit SD shields and modules: pin 10

/* Btle lib Class*/
class configSDClass
{
public:
  float muscleFilterSensor;
  String pinAnalogInputs;
  String joystickDigitalInputs;
  int pinAnalogInputTab[MAX_NB_MUSCLE_SENSOR];
  int joystickDigitalInputTab[NB_JOYSTICK_PIN];
  int nbMuscleSensor;
  String btleDeviceName;
  String language;
  String copyright;
  configSDClass();
  void init();

private:
  #if !(USE_ESP32S3)
  File root;
  File dataFile;

  String userConfigFileName = "USER.CFG";
  String systemConfigFileName = "SYSTEM.CFG";
  int isValidLine(String line);
  void analyseConfigFile(String filename);
  #endif
  void printConfig(void);
  void loadDefaultValues(void);
};

extern configSDClass config3dHandz;
#endif /* configSD_hpp */
