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

#ifndef config_hpp
#define config_hpp

#include <stdio.h>
#include <Arduino.h>

typedef struct
{
    int maxValue;
    int duration;
    boolean dataAvailable;
} contractionStruct;

//========================
// Main parameters
//========================
#define VERSION_BBox 4.0
#define MAIN_LOOP_DELAY 1
#define DISPLAY_DELAY 20 // timer refresh value for displayer
#define APPLICATION_NAME "Baah Box"
#define COPYRIGHT "(c)2025 Orange SA"

//========================
// BTLE parameters for default
//========================
#define BTLE_DEVICE_NAME "Baah Box"

//========================
// Sensor parameters
//========================

#define NB_DIGITAL_PINS 4
#define NB_ANALOG_SENSORS 2
#define SENSOR_ACQUISITION_PERIOD_IN_MS 50   // timer refresh value for sensor acquisition
#define ANALOG_SENSOR_FILTER 0.5 // time constant for low pass filter on muscle signal

#endif /* config_hpp */
