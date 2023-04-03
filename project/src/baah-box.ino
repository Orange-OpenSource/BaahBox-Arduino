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

#include <arduino.h>
#include "btle.hpp"
#include "config.hpp"
#include "muscleSensor.hpp"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "display.hpp"
#include "configSD.hpp"

btleClass btle;
muscleSensorClass muscleSensor;
handzDisplay display3dhandz;

// SDCard
configSDClass config3dHandz;

// tinyUSB for nrf52
#if defined(USE_TINYUSB)
#include <Adafruit_TinyUSB.h> // for Serial
#endif


//*********************************************
//*
//*       S E T U P
//*
//*********************************************
void setup()
{

#ifdef __DEBUG__
    {
        // initialize serial communication
        Serial.begin(38400);
        int timeoutInitSerial = 100;
        while (timeoutInitSerial-- > 0)
        {
            if (Serial)
                break;
            delay(10);
        }
        Serial.println("Serial initialized");
    }
#endif
    // init SD Card and load parameters
    config3dHandz.init();
    Serial.println("SD Card initialized");

    // initialise BTLE
    char tmpDeviceName[50];
    config3dHandz.btleDeviceName.toCharArray(tmpDeviceName, 50);
    btle.init(tmpDeviceName);
    Serial.print("BTLE initialized => ");
    Serial.println(tmpDeviceName);

    muscleSensor.init(MUSCLE_PERIOD_IN_MS, btle);
    Serial.println("Sensors initialized");

    // init display
    display3dhandz.init();
    Serial.println("Display initialized");

    Serial.println("end of main setup");
}

//*********************************************
//*
//*       L O O P
//*
//*********************************************
void loop()
{
    display3dhandz.checkButtons();

    if (muscleSensor.scheduler->needToBeExecuted())
    {
        // Serial.println("exec read capteurs");
        muscleSensor.muscleAcquisition();
    }

    if (display3dhandz.scheduler->needToBeExecuted())
    {
        // Serial.println("exec display");
        display3dhandz.update();
    }

    delay(MAIN_LOOP_DELAY);
}
