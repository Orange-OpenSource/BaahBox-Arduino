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

#ifndef config_hpp
#define config_hpp
#include <stdio.h>
#include <Arduino.h>
#include "configSD.hpp"

typedef struct
{
    int maxValue;
    int duration;
    boolean dataAvailable;
} contractionStruct;

extern configSDClass config3dHandz;

//========================
// Main parameters
//========================
#define VERSION_3DHANDZ 2.0
#define MAIN_LOOP_DELAY 1
#define HAND_TYPE HAND_SERIAL // no used in this version
#define DISPLAY_DELAY 20      // timer refresh value for displayer
#define APPLICATION_NAME "Baah Box"
#define COPYRIGHT "(C) 2022 Orange SA"
#define __DEBUG__ // debug mode (activate log on Serial outpout)

//========================
// BTLE parameters for default
//========================
#define BTLE_DEVICE_NAME "Baah Box"

//========================
// Sensor parameters
//========================
#define NB_MUSCLE_SENSOR 2
#define MUSCLE_PERIOD_IN_MS 50      // timer refresh value for sensor acquisition
#define MUSCLE_FILTER_SENSOR 0.5    // time constant for low pass filter on muscle signal
#define SEUIL_DEBUT_CONTRACTION 600 // 0-1023 value
#define SEUIL_FIN_CONTRACTION 350   // 0-1023 value

#endif /* config_hpp */
