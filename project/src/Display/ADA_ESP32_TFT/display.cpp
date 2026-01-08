// ******************************************
// * Baah Box Arduino : Sensor BTLE gateway *
// ******************************************

// Copyright (C) 2017 – 2026 Orange SA

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
#include "display.hpp"
#include <Adafruit_MAX1704X.h>

Adafruit_MAX17048 lipo;
int decalage = 120;
int cptDisplayBatt = 0;

extern BBConfigClass config;
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
GFXcanvas16 canvas(240, 135);
//*********************************************
//*
//*       Constructor
//*
//*********************************************
BBDisplay::BBDisplay()
{
}

//*********************************************
//*
//*       Destructor
//*
//*********************************************
BBDisplay::~BBDisplay()
{
}

//*********************************************
//*
//*       Init
//*
//*********************************************
void BBDisplay::init(void)
{
    Serial.println("ESP32S3 TFT  test");

    // turn on backlite
    pinMode(TFT_BACKLITE, OUTPUT);
    digitalWrite(TFT_BACKLITE, HIGH);

    // turn on the TFT / I2C power supply
    pinMode(TFT_I2C_POWER, OUTPUT);
    digitalWrite(TFT_I2C_POWER, HIGH);
    delay(10);

    // initialize TFT
    tft.init(135, 240); // Init ST7789 240x135
    tft.setRotation(3);
    canvas.setTextColor(ST77XX_WHITE);
    canvas.setFont(&FreeSans12pt7b);

    Serial.println(F("Initialized"));
    if (!lipo.begin())
    {
        Serial.println(F("Couldnt find Adafruit MAX17048?\nMake sure a battery is plugged in!"));
        while (1)
            delay(10);
    }
    Serial.print(F("Found MAX17048"));
    Serial.print(F(" with Chip ID: 0x"));
    Serial.println(lipo.getChipID(), HEX);

    for (int index = 0; index < 118; index++)
    {
        tblCapteur1[index] = 0;
        tblCapteur2[index] = 0;
    }
    idxTblCapteur = 0;

    displayMode = 1;
    currentDisplayMode = displayMode;

    pinMode(BUTTON_A, INPUT_PULLDOWN);
    pinMode(BUTTON_B, INPUT_PULLUP);
    pinMode(BUTTON_C, INPUT_PULLUP);
    button_A_pressed = 0;
    button_B_pressed = 0;
    button_C_pressed = 0;

    scheduler = new BBScheduler(millis(), DISPLAY_DELAY);
}

//*********************************************
//*
//*       Display banner
//*
//*********************************************
void BBDisplay::DisplayBanner(void)
{
    canvas.setTextWrap(false);
    canvas.fillScreen(ST77XX_BLACK);

    canvas.setCursor(10, 60);
    canvas.setTextColor(ST77XX_WHITE);
    canvas.setTextSize(2);
    canvas.println(APPLICATION_NAME);
    canvas.setTextSize(1);
    canvas.setCursor(15, 100);
    canvas.println(config.copyright);
    tft.drawRGBBitmap(0, 0, canvas.getBuffer(), 240, 135);
    pinMode(TFT_BACKLITE, OUTPUT);
    digitalWrite(TFT_BACKLITE, HIGH);
}

//*********************************************
//*
//*       isButtonPressed
//*
//*********************************************
int BBDisplay::isButtonPressed(void)
{
    // read displayer buttons
    int button_A = digitalRead(BUTTON_A);
    int button_B = digitalRead(BUTTON_B);
    int button_C = digitalRead(BUTTON_C);

    if (button_A != 0) // not pressed
    {
        if (button_A_pressed == 0)
        {
            Serial.println("Button A pressed");
            button_A_pressed = 1;
        }
    }
    else
    {
        if (button_A_pressed == 1)
        {
            Serial.println("Button A released");
            button_A_pressed = 0;
        }
    }

    if (button_B == 0)
    {
        if (button_B_pressed == 0)
        {
            Serial.println("Button B pressed");
            button_B_pressed = 1;
        }
    }
    else
    {
        if (button_B_pressed == 1)
        {
            Serial.println("Button B released");
            button_B_pressed = 0;
        }
    }

    if (button_C == 0)
    {
        if (button_C_pressed == 0)
        {
            Serial.println("Button C pressed");
            button_C_pressed = 1;
        }
    }
    else
    {
        if (button_C_pressed == 1)
        {
            Serial.println("Button C released");
            button_C_pressed = 0;
        }
    }
    if (button_A_pressed == 1 || button_B_pressed == 1 || button_C_pressed == 1)
    {
        return 1;
    }

    return 0;
}

//*********************************************
//*
//*       displayAxes
//*
//*********************************************
void BBDisplay::displayAxes(int type)
{
    // type =>
    //  0 : 2 sensors
    //  1 : sensor 1 only
    //  2 : sensor 2 only

    canvas.setTextSize(1);
    canvas.setTextColor(ST77XX_WHITE);
    int PosLegende = 125; 
    int x0 = 0;
    int y0 = 0;
    int x1 = 120; 
    int y1 = 90;

    switch (type)
    {
    case 0:
        // display caption for sensor 1

        canvas.setCursor(5, PosLegende);
        canvas.print(getTranslatedString(KEY_SENSOR));
        canvas.print("1");
        // display caption for sensor 2
        canvas.setCursor(120 + 5, PosLegende);
        canvas.print(getTranslatedString(KEY_SENSOR));
        canvas.print("2");

         canvas.drawLine(x0, y0, x0, y1, ST77XX_WHITE);
        canvas.drawLine(x0, y1, x1 - 2, y1, ST77XX_WHITE);

        canvas.drawLine(x0 + decalage, y0, x0 + decalage, y1, ST77XX_WHITE);
        canvas.drawLine(x0 + decalage, y1, x1 + decalage - 2, y1, ST77XX_WHITE);
        break;
    case 1:
    case 2:
        x1 = 120 + decalage;
        // display caption for selected sensor
        canvas.setCursor(50, PosLegende);
        canvas.print(getTranslatedString(KEY_SENSOR));
        canvas.print(type);
        canvas.drawLine(x0, y0, x0, y1, ST77XX_WHITE);
        canvas.drawLine(x0, y1, x1 - 2, y1, ST77XX_WHITE);
        break;
    }
    tft.drawRGBBitmap(0, 0, canvas.getBuffer(), 240, 135);
}

//*********************************************
//*
//*       capteurs
//*
//*********************************************
void BBDisplay::capteurs(int type)
{
    genericSensor.getAnalogInputs(&capteur1, &capteur2);
    displayAxes(type);
    // int capteur1 = analogRead(config.analogInput[0]);
    // int capteur2 = analogRead(config.analogInput[1]);
    Serial.print(capteur1);
    Serial.print("cap1 cap2");
    Serial.println(capteur2);
   
    switch (type)
    {
    case 0:
        tblCapteur1[idxTblCapteur] = capteur1;
        tblCapteur2[idxTblCapteur] = capteur2;
        if (idxTblCapteur >= 118)
        {
            idxTblCapteur = 0;
        }
        displayAnalogInputs(0, type);
        displayAnalogInputs(1, type);
        break;
    case 1:
        tblCapteur[idxTblCapteur] = capteur1;
        if (idxTblCapteur >= 238)
        {
            idxTblCapteur = 0;
        }
        displayAnalogInputs(0, type);
        break;
    case 2:
        tblCapteur[idxTblCapteur] = capteur2;
        if (idxTblCapteur >= 238)
        {
            idxTblCapteur = 0;
        }
        displayAnalogInputs(1, type);
        break;
    }
    idxTblCapteur++;
}

//*********************************************
//*
//*       displayAnalogInputs
//*
//*********************************************
void BBDisplay::displayAnalogInputs(int channel, int type)
{
    int posX, posY;

    switch (type)
    {
    case 0:
        for (int index = 0; index < 118; index++)
        {
            Serial.print(tblCapteur1[index]);
    Serial.print(" :cap1 cap2: ");
    Serial.println(tblCapteur2[index]);
   
            if (channel == 0)
            {
                posX = index + 1;
                posY = map(tblCapteur1[index], 0, 1023, 80, 20);
            }
            else
            {
                posX = index + 1 + decalage;
                posY = map(tblCapteur2[index], 0, 1023, 80, 20);
            }
            tft.drawPixel(posX, posY, ST77XX_BLUE);
        }
        break;
    case 1:
    case 2:
        for (int index = 0; index < 238; index++)
        {
            posX = index + 1;
            posY = map(tblCapteur[index], 0, 1023, 80, 0);
            tft.drawPixel(posX, posY, ST77XX_GREEN);
        }
        break;
    }
}

//*********************************************
//*
//*       refreshDisplay
//*
//*********************************************
void BBDisplay::refreshDisplay()
{
    if (cptRefresh++ > 5)
    {
        // display.display();
        cptRefresh = 0;
    }
}

//*********************************************
//*
//*       joystick
//*
//*********************************************
void BBDisplay::joystick()
{
    int btGauche = digitalRead(config.digitalInput[1]);
    int btDroit = digitalRead(config.digitalInput[0]);
    int btBas = digitalRead(config.digitalInput[2]);
    int btHaut = digitalRead(config.digitalInput[3]);
    // int btGauche = digitalRead(11);
    // int btDroit = digitalRead(A5);
    // int btBas = digitalRead(12);
    // int btHaut = digitalRead(13);

    char blancs[20] = "           ";
    char titre[20] = " Joystick  ";

    canvas.setTextSize(1);
    canvas.setTextColor(ST77XX_WHITE);
    canvas.setCursor(0, 0);

    canvas.print(blancs);
    canvas.print("   [");
    if (btHaut == 0)
        canvas.print("*");
    else
        canvas.print(" ");
    canvas.println("]");

    canvas.print(titre);
    canvas.print("[");
    if (btGauche == 0)
        canvas.print("*");
    else
        canvas.print(" ");
    canvas.print("]");
    canvas.print("   [");
    if (btDroit == 0)
        canvas.print("*");
    else
        canvas.print(" ");
    canvas.println("]");

    canvas.print(blancs);
    canvas.print("   [");
    if (btBas == 0)
        canvas.print("*");
    else
        canvas.print(" ");
    canvas.print("]");
}

//*********************************************
//*
//*       displayConfig
//*
//*********************************************
void BBDisplay::displayConfig()
{
    canvas.setTextSize(1);
    canvas.setTextColor(ST77XX_WHITE);
    canvas.setCursor(0, 30);
    canvas.println(getTranslatedString(KEY_SETTINGS));
    canvas.print("BTLE : ");
    canvas.println(config.btleDeviceName);
    canvas.print(getTranslatedString(KEY_ANALOG_INPUTS));
    canvas.println(config.analogInput[0]); // todo: fix this
    canvas.print(getTranslatedString(KEY_VERSION));
    canvas.println(VERSION_BBox);
    tft.drawRGBBitmap(0, 0, canvas.getBuffer(), 240, 135);
}

//*********************************************
//*
//*       displayBattery
//*
//*********************************************
void BBDisplay::displayBattery()
{
    canvas.setTextSize(2);
    canvas.setTextColor(ST77XX_BLUE);
    canvas.setCursor(0, 45);
    canvas.println(getTranslatedString(KEY_BATTERY));
    canvas.setTextColor(ST77XX_WHITE);
    canvas.setTextSize(2);
    float charge = lipo.cellVoltage();
    canvas.print(charge, 1);
    canvas.print(" V   ");
    canvas.setTextSize(2);
    charge = 4.03;
    if (charge < 3.8)
    {
        canvas.setTextColor(ST77XX_RED);
        canvas.println("(!)");
    }
    else if (charge < 4.0)
    {
        canvas.setTextColor(ST77XX_YELLOW);
        canvas.println("(!)");
    }
    else
    {
        canvas.setTextColor(ST77XX_GREEN);
        canvas.println("(ok)");
    }

    tft.drawRGBBitmap(0, 0, canvas.getBuffer(), 240, 135);
}

//*********************************************
//*
//*       displayLicences
//*
//*********************************************
void BBDisplay::displayLicences()
{
    canvas.setTextSize(1);
    canvas.setTextColor(ST77XX_WHITE);
    canvas.setCursor(0, 30);
    canvas.println(getTranslatedString(KEY_LICENCE));
    tft.drawRGBBitmap(0, 0, canvas.getBuffer(), 240, 135);
}

//*********************************************
//*
//*       update
//*
//*********************************************
void BBDisplay::update(void)
{
    switch (displayMode)
    {
    case 0:
    case 30:
    case 32:
    case 36:
        // nothing to display
        break;
    case 1:
       // if (displayMode != currentDisplayMode)
        //{
            //DisplayBanner();
            capteurs(0); 
            displayMode = 0;
        //}
        break;
    case 20:
        displayMode = 21;
        break;
    case 21:
        capteurs(0);
        break;
    case 22:
        displayMode = 23;
        break;
    case 23:
        // canvas.fillScreen(ST77XX_BLACK);
        capteurs(1);
        break;
    case 24:
        displayMode = 25;
        break;
    case 25:
        // canvas.fillScreen(ST77XX_BLACK);
        capteurs(2);
        break;
    case 26:
        displayMode = 27;
        break;
    case 27:
        // canvas.fillScreen(ST77XX_BLACK);
        joystick();
        break;
    case 31:
        // canvas.fillScreen(ST77XX_BLACK);
        displayConfig();
        displayMode = 32;
        break;
    case 33:
        // canvas.fillScreen(ST77XX_BLACK);
        displayBattery();
        cptDisplayBatt = 0;
        displayMode = 34;
        break;
    case 34:
        if (cptDisplayBatt++ > 50)
        {
            // canvas.fillScreen(ST77XX_BLACK);
            displayBattery();
            cptDisplayBatt = 0;
        }
        break;
    case 35:
        // canvas.fillScreen(ST77XX_BLACK);
        displayLicences();
        displayMode = 36;
        break;
    default:
        Serial.println("Unknown display mode");
        displayMode = 0;
    }
    currentDisplayMode = displayMode;
    refreshDisplay();
}

//*********************************************
//*
//*       chackButtons
//*
//*********************************************
void BBDisplay::checkButtons(void)
{
    int buttonPressed = isButtonPressed();

    if (buttonPressed != 0)
    {
        if (buttonNotReleased == 0)
        {
            switch (displayMode)
            {
            }
            if (button_A_pressed == 1)
            {
                displayMode = 1;
                Serial.println("Banner screen");
            }
            if (button_B_pressed == 1)
            {
                switch (displayMode)
                {
                case 21: // Display capteur 1 curve
                    displayMode = 22;
                    break;
                case 23: // Display capteur 2 curve
                    displayMode = 24;
                    break;
                case 25: // Display joystick
                    displayMode = 26;
                    break;
                default: // Display 2 capteurs curves
                    displayMode = 20;
                }
            }
            if (button_C_pressed == 1)
            {
                switch (displayMode)
                {
                case 31: // nothing to do
                case 33: // nothing to do
                case 35: // nothing to do
                    break;
                case 32: // display 1st screen (Parameters)
                    displayMode = 33;
                    break;
                case 34: // display 2nd screen (Battery)
                    displayMode = 35;
                    break;
                case 36: // display 3rd screen (Licences)
                    displayMode = 31;
                    break;
                default: // first press of C button
                    displayMode = 31;
                    break;
                }
            }
            buttonNotReleased = 1;
        }
    }
    else
    {
        buttonNotReleased = 0;
    }
}

//
//*
//*       getTranslatedString
//*
//*********************************************
String BBDisplay::getTranslatedString(int key)
{
    // get the translated value of string identified by the key
    String language = config.language;
    if (language.equals("FR"))
    {
        return FR_Strings[key];
    }
    else if (language.equals("EN"))
    {
        return EN_Strings[key];
    }
    else if (language.equals("ES"))
    {
        return ES_Strings[key];
    }
    return EN_Strings[key];
}
