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

#include <Arduino.h>
#include "configSD.hpp"
#include "config.hpp"

//*********************************************
//*
//*       Constructor
//*
//*********************************************
configSDClass::configSDClass()
{
  // init SD Card
  loadDefaultValues();
}

//*********************************************
//*
//*       init
//*
//*********************************************
void configSDClass::init(void)
{
  Serial.print("\nInitializing SD card...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!SD.begin(CHIP_SELECT_SD_PIN))
  {
    Serial.println("Card failed, or not present");
    this->loadDefaultValues();
    Serial.println("Set defaults Init Values");
    printConfig();
    return;
  }
  Serial.println("card initialized.\n");

  Serial.println("Initialize config file for BaahBox...");

  root = SD.open("/");

  analyseConfigFile(userConfigFileName);
  analyseConfigFile(systemConfigFileName);
  Serial.println("Read config on SD card OK");

  printConfig();
}

//*********************************************
//*
//*       loadDefaultValues
//*
//*  Initialize the config default Value
//*       if SDCard not present
//*
//*********************************************
void configSDClass::loadDefaultValues(void)
{
  this->btleDeviceName = "Baah Box";
  this->nbMuscleSensor = NB_MUSCLE_SENSOR;
  //Serial.print("Default values for sensors : ");
  this->pinAnalogInputTab[0] = 0;
  this->pinAnalogInputTab[1] = 1;
  this->joystickDigitalInputTab[0] = A5;
  this->joystickDigitalInputTab[1] = 11;
  this->joystickDigitalInputTab[2] = 12;
  this->joystickDigitalInputTab[3] = 13;
  this->muscleFilterSensor = MUSCLE_FILTER_SENSOR;
  this->copyright = COPYRIGHT;
  this->language = "EN";
}

//*********************************************
//*
//*       analyseConfigFile
//*
//*  analyse the config file :
//*  - filter bad lines
//*  - extract value from lines
//*
//*********************************************
void configSDClass::analyseConfigFile(String configFileName)
{
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open(configFileName, FILE_READ);
  Serial.print("Analyze config file : ");
  Serial.println(configFileName);

  // if the file is available, read to it:
  if (dataFile)
  {
    String line;
    char car;
    int index;
    while (dataFile.available())
    {
      line = "";
      while ((car = dataFile.read()) != '\n')
      {
        line.concat(car);
      }

      index = isValidLine(line);
      if (index != -1)
      {
        // set value of parameter
        String key = line.substring(0, index);
        key.trim();
        String value = line.substring(index + 1, line.length());
        value.trim();
        key.toUpperCase();
        if (key.equals("BTLE_DEVICE_NAME"))
        {
          this->btleDeviceName = value;
        }
        else if (key.equals("NB_MUSCLE_SENSOR"))
        {
          this->nbMuscleSensor = value.toInt();
        }
        else if (key.equals("MUSCLE_FILTER_FACTOR"))
        {
          this->muscleFilterSensor = value.toFloat();
        }
        else if (key.equals("JOYSTICK_DIGITAL_INPUT_PIN"))
        {
          char tmp[20];
          this->joystickDigitalInputs = value;
          value.toCharArray(tmp, 20);
          char *p = strtok(tmp, ",");
          int idx = 0;
          while (p != nullptr && idx < NB_JOYSTICK_PIN)
          {
            if (atoi(p) != 0){
              joystickDigitalInputTab[idx] = atoi(p);
              Serial.print("affectation pin joystick : ");
              Serial.print(atoi(p));
              Serial.println();

            }else {
              if (strcmp(p, "A5") == 0) joystickDigitalInputTab[idx] = A5;
              Serial.print("affectation pin joystick A5 : ");
              Serial.print(A5);
              Serial.println();
            }
            p = strtok(NULL, ",");
            Serial.print("joystickDigitalInputTab[idx] : ");
            Serial.print(joystickDigitalInputTab[idx]);
            Serial.println();
            idx++;
          }
        }
        else if (key.equals("MUSCLE_ANALOG_INPUT_PIN"))
        {
          char tmp[20];
          this->pinAnalogInputs = value;
          value.toCharArray(tmp, 20);
          char *p = strtok(tmp, ",");
          int idx = 0;
          while (p != nullptr && idx < NB_JOYSTICK_PIN)
          {
            switch (atoi(p))
            {
            case 0:
              this->pinAnalogInputTab[idx++] = A0;
              break;
            case 1:
              this->pinAnalogInputTab[idx++] = A1;
              break;
            case 2:
              this->pinAnalogInputTab[idx++] = A2;
              break;
            case 3:
              this->pinAnalogInputTab[idx++] = A3;
              break;
            case 4:
              this->pinAnalogInputTab[idx++] = A4;
              break;
            case 5:
              this->pinAnalogInputTab[idx++] = A5;
              break;
            default:
              Serial.println("ERROR : analog input pin invalid");
            }
            p = strtok(NULL, ",");
          }
        }
        else if (key.equals("LANGUAGE"))
        {

          if (value.equals("FR"))
          {
            Serial.println("Selection de la langue francaise");
          }
          else if (value.equals("EN"))
          {
            Serial.println("English language selected");
          }
          else if (value.equals("ES"))
          {
            Serial.println("Idioma español seleccionado");
          }
          else if (value.equals("DE"))
          {
            Serial.println("Spanische Sprache ausgewählt");
          }
          else
          {
            Serial.println("Default english language selected");
            value = "EN";
          }
          this->language = value;
        }
        else
        {
          Serial.print("Unknown key : ");
          Serial.println(key);
        }
      }
    }
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else
  {
    Serial.print("error opening ");
    Serial.println(configFileName);
  }
}
//*********************************************
//*
//*       isValidLine
//*
//*********************************************
int configSDClass::isValidLine(String line)
{
  if (line.indexOf("#") == 0)
    return -1;
  return line.indexOf('=');
}

//*********************************************
//*
//*       printConfig
//*
//*********************************************
void configSDClass::printConfig(void)
{
  Serial.println("------------------------------");
  Serial.println(" User Configuration :");
  Serial.println("------------------------------");
  Serial.print("BTLE_DEVICE_NAME = ");
  Serial.println(this->btleDeviceName);

  Serial.print("LANGUAGE = ");
  Serial.println(this->language);

  Serial.println("------------------------------");
  Serial.println(" System Configuration :");
  Serial.println("------------------------------");

  Serial.print("NB_MUSCLE_SENSOR = ");
  Serial.println(this->nbMuscleSensor);

  Serial.print("MUSCLE_FILTER_FACTOR = ");
  Serial.println(this->muscleFilterSensor);

  Serial.print("MUSCLE_ANALOG_INPUT_PIN = ");
  for (int i = 0; i < this->nbMuscleSensor; i++)
  {
    Serial.print(this->pinAnalogInputTab[i]);
    Serial.print(" ");
  }
  Serial.println();

  Serial.print("JOYSTICK_DIGITAL_INPUT_PIN = ");
  for (int i = 0; i < NB_JOYSTICK_PIN; i++)
  {
    Serial.print(this->joystickDigitalInputTab[i]);
    Serial.print(" ");
  }
  Serial.println();

  Serial.print("COPYRIGHT = ");
  Serial.println(this->copyright);
  Serial.println("------------------------------");
}
