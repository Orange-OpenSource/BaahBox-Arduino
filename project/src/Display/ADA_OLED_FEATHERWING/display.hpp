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

#ifndef __DISPLAY_HPP
#define __DISPLAY_HPP

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Sensors/genericSensor.hpp"
#include "Config/BBConfig.hpp"
#include "Display/commonDisplay.hpp"

#include "tools.hpp"

extern Adafruit_SSD1306 display;

#if defined(ESP8266)
#define BUTTON_A 0
#define BUTTON_B 16
#define BUTTON_C 2
#define LED 0

#elif defined(ESP32)
#define BUTTON_A 15
#define BUTTON_B 32
#define BUTTON_C 14
#define LED 13
#elif defined(ARDUINO_STM32F2_FEATHER)
#define BUTTON_A PA15
#define BUTTON_B PC7
#define BUTTON_C PC5
#define LED PB5
#elif defined(TEENSYDUINO)
#define BUTTON_A 4
#define BUTTON_B 3
#define BUTTON_C 8
#define LED 13
#elif defined(ARDUINO_FEATHER52)
#define BUTTON_A 31
#define BUTTON_B 30
#define BUTTON_C 27
#define LED 17
#else // 32u4, M0, M4, and 328p
#define BUTTON_A 9
#define BUTTON_B 6
#define BUTTON_C 5
#define LED 13
#endif

#if (SSD1306_LCDHEIGHT != 32)
#error ("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
#define WIRE Wire

extern genericSensorClass genericSensor;

class BBDisplay
{
public:
  BBDisplay(void);
  ~BBDisplay();
  void init(void);
  void checkButtons(void);
  void update(void);
  BBScheduler *scheduler;

private:
  int button_A_pressed;
  int button_B_pressed;
  int button_C_pressed;
  int tblCapteur1[62], tblCapteur2[62];
  int tblCapteur[126];
  int capteur1, capteur2, idxTblCapteur;
  int displayMode;
  int buttonNotReleased;

  int cptRefresh = 0;

  Adafruit_SSD1306 oled;

  void DisplayBanner(void);
  int isButtonPressed(void);
  void displayAxes(int type);
  void capteurs(int type);
  void displayAnalogInputs(int channel, int type);
  void joystick(void);
  void refreshDisplay(void);
  void displayConfig(void);
  void displayConfig2(void);
  void displayLicences(void);
  String getTranslatedString(int key);
};

#endif /* display_hpp */
