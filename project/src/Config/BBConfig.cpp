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
#include "Config/BBConfig.hpp"

//*********************************************
//*
//*       Constructor
//*
//*********************************************
BBConfigClass::BBConfigClass()
{
  // loadDefaultValues();
}

//*********************************************
//*
//*       init
//*
//*********************************************
void BBConfigClass::init(void)
{
  this->loadDefaultValues();
  Serial.println("Set defaults values for BBox configuration");
  printConfig();
  return;
}

//*********************************************
//*
//*       loadDefaultValues
//*
//*  Initialize the config default Value
//*
//*
//*********************************************
void BBConfigClass::loadDefaultValues(void)
{
  this->btleDeviceName = "Baah Box dans BBconfig";
  this->nbAnalogSensors = NB_ANALOG_SENSORS;
  this->analogInput[0] = A0;
  this->analogInput[1] = A1;
  this->digitalInput[0] = A5;
  this->digitalInput[1] = 11;
  this->digitalInput[2] = 12;
  this->digitalInput[3] = 13;
  this->analogSensorFilter = ANALOG_SENSOR_FILTER;
  this->copyright = COPYRIGHT;
  this->language = "EN";
}

//*********************************************
//*
//*       printConfig
//*
//*********************************************
void BBConfigClass::printConfig(void)
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

  Serial.print("NB_ANALOG_SENSORS = ");
  Serial.println(this->nbAnalogSensors);

  Serial.print("ANALOG_FILTER_FACTOR = ");
  Serial.println(this->analogSensorFilter);

  Serial.print("ANALOG_INPUT_PIN = ");
  for (int i = 0; i < this->nbAnalogSensors; i++)
  {
    Serial.print(this->analogInput[i]);
    Serial.print(" ");
  }
  Serial.println();

  Serial.print("DIGITAL_INPUT_PIN = ");
  for (int i = 0; i < NB_DIGITAL_PINS; i++)
  {
    Serial.print(this->digitalInput[i]);
    Serial.print(" ");
  }
  Serial.println();

  Serial.print("COPYRIGHT = ");
  Serial.println(this->copyright);
  Serial.println("------------------------------");
}
