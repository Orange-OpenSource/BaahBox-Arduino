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

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789 display
#include <SPI.h>
#include <Fonts/FreeSans12pt7b.h>

#include "Sensors/genericSensor.hpp"
#include "Config/BBConfig.hpp"
#include "Display/commonDisplay.hpp"

#define TFT_BUTTON_A 0
#define TFT_BUTTON_B 1
#define TFT_BUTTON_C 2

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
  int tblCapteur1[118], tblCapteur2[118]; //62
  int tblCapteur[238]; //126
  int capteur1, capteur2, idxTblCapteur;
  int displayMode;
  int currentDisplayMode;
  int buttonNotReleased;

  int cptRefresh = 0;

  void DisplayBanner(void);
  int isButtonPressed(void);
  void displayAxes(int type);
  void capteurs(int type);
  void displayAnalogInputs(int channel, int type);
  void joystick(void);
  void refreshDisplay(void);
  void displayConfig(void);
  void displayBattery(void);
  void displayLicences(void);
  String getTranslatedString(int key);
};

#endif /* display_hpp */
