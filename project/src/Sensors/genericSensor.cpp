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
#include "Config/config.hpp"
#include "Config/BBConfig.hpp"
#include "genericSensor.hpp"

extern BBConfigClass config;

//*********************************************
//*
//*       Constructor
//*
//*********************************************
genericSensorClass::genericSensorClass()
{
}

//*********************************************
//*
//*       Destructor
//*
//*********************************************
genericSensorClass::~genericSensorClass()
{
}

//*********************************************
//*
//*       lowpass
//*
//*********************************************
int genericSensorClass::lowpass(int value, int index)
{
    float factor = config.analogSensorFilter;
    // the equivalent number of value used to calc the out is proportionnal to 1/factor
    // if factor -> 0 ; out -> value
    // if factor -> 1 ; out -> memory[index]
    int out = (int)((float)memory[index] * factor + (1.0f - factor) * (float)value);
    memory[index] = out;
    return out;
}

//*********************************************
//*
//*       init
//*
//*********************************************
int genericSensorClass::init(unsigned long period)
{
    for (int i = 0; i < config.nbAnalogSensors; i++)
    {
        Serial.print("Pin");
        Serial.print(i);
        Serial.print(":");
        Serial.println(config.analogInput[i]);
    }

    // init joystick digital input
    for (int idx = 0; idx < NB_DIGITAL_PINS; idx++)
    {
        pinMode((uint32_t)config.digitalInput[idx], INPUT_PULLUP);
    }
    /*
    pinMode(A5, INPUT_PULLUP);
    pinMode(11, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);
    pinMode(13, INPUT_PULLUP);
    */

    // init scheduler
    scheduler = new BBScheduler(millis(), SENSOR_ACQUISITION_PERIOD_IN_MS);
    Serial.println("muscleClass::init => OK\n");
    return 0;
}

//*********************************************
//*
//*       getAnalogInputs
//*
//*********************************************
void genericSensorClass::getAnalogInputs(int *input1, int *input2)
{
    *input1 = this->storedValues[0];
    *input2 = this->storedValues[1];
}

//*********************************************
//*
//*       sensorAcquisition
//*
//*         Fonction waked up periodicly
//*         to read physicals datas
//*         from sensors and format it
//*
//*********************************************
int tmpDisplay = 0;
int genericSensorClass::sensorAcquisition(char *sensorDataFormatted)
{
    int index = 0;
    // Analog input acquisition
    for (int i = 0; i < config.nbAnalogSensors; i++)
    {
        int mapValue = lowpass(analogRead(config.analogInput[i]), i);
#ifdef __ANALOG__JOYSTICK__
        if (mapValue >= 440 && mapValue <= 550)
        {
            mapValue = 500;
        }
#endif
        storedValues[i] = mapValue;
        int a = mapValue / 32;
        int b = mapValue - (a * 32);
        sensorDataFormatted[index] = a;
        index++;
        sensorDataFormatted[index] = b;
        index++;
    }
    // digital input acquisition
    int c =
        (1 - digitalRead(config.digitalInput[0])) * 8 +
        (1 - digitalRead(config.digitalInput[1])) * 4 +
        (1 - digitalRead(config.digitalInput[2])) * 2 +
        1 - digitalRead(config.digitalInput[3]);

    sensorDataFormatted[index] = c;
    index++;
    sensorDataFormatted[index] = 90;
    index++;

#ifdef __DEBG__
    char tmp2[2048] = "";
    if (tmpDisplay++ > 10)
    {
        sprintf(tmp2, "%d %d %d %d", sensorDataFormatted[0] * 32 + sensorDataFormatted[1], sensorDataFormatted[2] * 32 + sensorDataFormatted[3], sensorDataFormatted[4], sensorDataFormatted[5]);
        Serial.println(tmp2);
        tmpDisplay = 0;
    }
#endif

    return index;
}
