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
#include "config.hpp"
#include "muscleSensor.hpp"
#include "configSD.hpp"

extern configSDClass config3dHandz;

//*********************************************
//*
//*       Constructor
//*
//*********************************************
muscleSensorClass::muscleSensorClass()
{
}

//*********************************************
//*
//*       Destructor
//*
//*********************************************
muscleSensorClass::~muscleSensorClass()
{
}

//*********************************************
//*
//*       lowpass
//*
//*********************************************
int muscleSensorClass::lowpass(int value, int index)
{
    float factor = config3dHandz.muscleFilterSensor;
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
int muscleSensorClass::init(unsigned long period, btleClass btle)
{
    this->btle = btle;

    for (int i = 0; i < config3dHandz.nbMuscleSensor; i++)
    {
        Serial.print("Pin");
        Serial.print(i);
        Serial.print(":");
        Serial.println(config3dHandz.pinAnalogInputTab[i]);
    }

    // init joystick digital input
    for (int idx=0 ; idx < NB_JOYSTICK_PIN ; idx++){
        pinMode((uint32_t) config3dHandz.joystickDigitalInputTab[idx],INPUT_PULLUP);
    }
    /*
    pinMode(A5, INPUT_PULLUP);
    pinMode(11, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);
    pinMode(13, INPUT_PULLUP);
    */

    // init scheduler
    scheduler = new Scheduler(millis(), MUSCLE_PERIOD_IN_MS);
    Serial.println("muscleClass::init => OK\n");
    return 0;
}

//*********************************************
//*
//*       getValue
//*
//*********************************************
void muscleSensorClass::getValue(int *capteur1, int *capteur2)
{
    *capteur1 = this->storedValues[0];
    *capteur2 = this->storedValues[1];
}

//*********************************************
//*
//*       muscleAcquisition
//*
//*         Fonction waked up périodicly
//*         to read physicals datas
//*         on muscles sensors
//*
//*********************************************
int tmpDisplay = 0;
void muscleSensorClass::muscleAcquisition(void)
{
    char tmp[10];
    char tmp2[2048] = "";
    int index = 0;

    int value[MAX_NB_MUSCLE_SENSOR];

    for (int i = 0; i < config3dHandz.nbMuscleSensor; i++)
    {
        int mapValue = lowpass(analogRead(config3dHandz.pinAnalogInputTab[i]), i);
        storedValues[i] = mapValue;
        int a = mapValue / 32;
        int b = mapValue - (a * 32);
        tmp[index] = a;
        index++;
        tmp[index] = b;
        index++;
    }

    int c =
        (1 - digitalRead(config3dHandz.joystickDigitalInputTab[0])) * 8 +
        (1 - digitalRead(config3dHandz.joystickDigitalInputTab[1])) * 4 +
        (1 - digitalRead(config3dHandz.joystickDigitalInputTab[2])) * 2 + 1 - digitalRead(config3dHandz.joystickDigitalInputTab[3]);

    tmp[index] = c;
    index++;
    tmp[index] = 90;
    index++;

    btle.write(tmp, index);

#ifdef __DEBUG__
    if (tmpDisplay++ > 10)
    {
        sprintf(tmp2, "%d %d %d %d", tmp[0] * 32 + tmp[1], tmp[2] * 32 + tmp[3], tmp[4], tmp[5]);
        Serial.println(tmp2);
        tmpDisplay = 0;
    }
#endif
}
