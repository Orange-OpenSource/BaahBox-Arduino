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


#ifndef genericSensor_hpp
#define genericSensor_hpp

#ifdef USE_NRF51
#include "./BLE/Nrf51/btle.hpp"
#endif

#ifdef USE_NRF52
#include "./BLE/Nrf52/btle.hpp"
#endif

#ifdef USE_ESP32S3
#include "./BLE/ESP32S3/btle.hpp"
#endif

#include "Config/BBConfig.hpp"
#include "../BBScheduler.hpp"

class genericSensorClass
{

public:
  genericSensorClass(void);
  ~genericSensorClass();

  int init(unsigned long period, btleClass btle);
  int memory[NB_ANALOG_SENSORS] = {};
  void getAnalogInputs(int *input1, int *input2);
  void sensorAcquisition(void);

  btleClass btle;
  int storedValues[NB_ANALOG_SENSORS];
  BBScheduler *scheduler;

private:
  int lowpass(int value, int index);
};

#endif /* muscleSensor_hpp */
