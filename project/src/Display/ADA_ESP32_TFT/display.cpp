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
#include "display.hpp"
#include <Adafruit_MAX1704X.h>

Adafruit_MAX17048 maxlipo;
int decalage = 64;
int cptDisplayBatt = 0;

extern BBConfigClass config;

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
    tft.init(240, 135); // Init ST7789 240x135
    tft.setRotation(3);
    tft.fillScreen(ST77XX_BLACK);

    Serial.println(F("Initialized"));

    //
    // oleddisplay.clearDisplay();
    //  display.display();
    // 128 X 32
    for (int index = 0; index < 62; index++)
    {
        tblCapteur1[index] = 0;
        tblCapteur2[index] = 0;
    }
    idxTblCapteur = 0;

    displayMode = 1;

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
    tft.setTextWrap(false);
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(10, 1);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);
    tft.println(APPLICATION_NAME);
    tft.setTextSize(1);
    tft.setCursor(10, 24);
    tft.println(config.copyright);
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

    tft.setTextSize(1);
    tft.setTextColor(ST77XX_WHITE);
    int PosLegende = 25;
    int x0 = 0;
    int y0 = 0;
    int x1 = 64;
    int y1 = 23;

    switch (type)
    {
    case 0:
        // display caption for sensor 1
        tft.setCursor(5, PosLegende);
        tft.print(getTranslatedString(KEY_SENSOR));
        tft.print("1");
        // display caption for sensor 2
        tft.setCursor(64 + 5, PosLegende);
        tft.print(getTranslatedString(KEY_SENSOR));
        tft.print("2");

        tft.drawLine(x0, y0, x0, y1, ST77XX_WHITE);
        tft.drawLine(x0, y1, x1 - 2, y1, ST77XX_WHITE);

        tft.drawLine(x0 + decalage, y0, x0 + decalage, y1, ST77XX_WHITE);
        tft.drawLine(x0 + decalage, y1, x1 + decalage - 2, y1, ST77XX_WHITE);
        break;
    case 1:
    case 2:
        x1 = 64 + decalage;
        // display caption for selected sensor
        tft.setCursor(50, PosLegende);
        tft.print(getTranslatedString(KEY_SENSOR));
        tft.print(type);
        tft.drawLine(x0, y0, x0, y1, ST77XX_WHITE);
        tft.drawLine(x0, y1, x1 - 2, y1, ST77XX_WHITE);
        break;
    }
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

    switch (type)
    {
    case 0:
        tblCapteur1[idxTblCapteur] = capteur1;
        tblCapteur2[idxTblCapteur] = capteur2;
        if (idxTblCapteur >= 62)
        {
            idxTblCapteur = 0;
        }
        displayCapteur(0, type);
        displayCapteur(1, type);
        break;
    case 1:
        tblCapteur[idxTblCapteur] = capteur1;
        if (idxTblCapteur >= 126)
        {
            idxTblCapteur = 0;
        }
        displayCapteur(0, type);
        break;
    case 2:
        tblCapteur[idxTblCapteur] = capteur2;
        if (idxTblCapteur >= 126)
        {
            idxTblCapteur = 0;
        }
        displayCapteur(1, type);
        break;
    }
    idxTblCapteur++;
}

//*********************************************
//*
//*       displayCapteur
//*
//*********************************************
void BBDisplay::displayCapteur(int channel, int type)
{
    int posX, posY;

    switch (type)
    {
    case 0:
        for (int index = 0; index < 62; index++)
        {
            if (channel == 0)
            {
                posX = index + 1;
                posY = map(tblCapteur1[index], 0, 1023, 22, 0);
            }
            else
            {
                posX = index + 1 + decalage;
                posY = map(tblCapteur2[index], 0, 1023, 22, 0);
            }
            tft.drawPixel(posX, posY, ST77XX_WHITE);
        }
        break;
    case 1:
    case 2:
        for (int index = 0; index < 126; index++)
        {
            posX = index + 1;
            posY = map(tblCapteur[index], 0, 1023, 22, 0);
            tft.drawPixel(posX, posY, ST77XX_WHITE);
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

    tft.setTextSize(1);
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(0, 0);

    tft.print(blancs);
    tft.print("   [");
    if (btHaut == 0)
        tft.print("*");
    else
        tft.print(" ");
    tft.println("]");

    tft.print(titre);
    tft.print("[");
    if (btGauche == 0)
        tft.print("*");
    else
        tft.print(" ");
    tft.print("]");
    tft.print("   [");
    if (btDroit == 0)
        tft.print("*");
    else
        tft.print(" ");
    tft.println("]");

    tft.print(blancs);
    tft.print("   [");
    if (btBas == 0)
        tft.print("*");
    else
        tft.print(" ");
    tft.print("]");
}

//*********************************************
//*
//*       displayConfig
//*
//*********************************************
void BBDisplay::displayConfig()
{
    tft.setTextSize(1);
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(0, 0);
    tft.println(getTranslatedString(KEY_SETTINGS));
    tft.print("BTLE : ");
    tft.println(config.btleDeviceName);
    tft.print(getTranslatedString(KEY_ANALOG_INPUTS));
    tft.println(config.analogInput[0]); // todo: fix this
    tft.print(getTranslatedString(KEY_VERSION));
    tft.println(VERSION_BBox);
}

//*********************************************
//*
//*       displayConfig2
//*
//*********************************************
void BBDisplay::displayConfig2()
{
    tft.setTextSize(1);
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(0, 0);
    tft.println(getTranslatedString(KEY_SETTINGS));
    float tmp = getVbat();
    // map batterie level between 3,7V and 4,2V to %
    int charge = map(tmp * 100, 370, 420, 0, 100);
    if (charge > 100)
    {
        charge = 100;
    }
    else if (charge < 0)
    {
        charge = 0;
    }
    tft.print("Vbat = ");
    tft.print(tmp);
    tft.print("V (");
    tft.print(charge);
    tft.println("%)");
    tft.print(getTranslatedString(KEY_BATTERY));
    tft.print("[");
    for (int i = 0; i <= 95; i += 12)
    {
        if (i <= charge)
        {
            tft.print("*");
        }
        else
        {
            tft.print(" ");
        }
    }
    tft.println("]");
    // tft.display();
}

//*********************************************
//*
//*       displayLicences
//*
//*********************************************
void BBDisplay::displayLicences()
{
    tft.setTextSize(1);
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(0, 0);
    tft.println(getTranslatedString(KEY_LICENCE));
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
        tft.fillScreen(ST77XX_BLACK);
        DisplayBanner();
        displayMode = 0;
        break;
    case 20:
        displayMode = 21;
        break;
    case 21:
        tft.fillScreen(ST77XX_BLACK);
        capteurs(0);
        break;
    case 22:
        displayMode = 23;
        break;
    case 23:
        tft.fillScreen(ST77XX_BLACK);
        capteurs(1);
        break;
    case 24:
        displayMode = 25;
        break;
    case 25:
        tft.fillScreen(ST77XX_BLACK);
        capteurs(2);
        break;
    case 26:
        displayMode = 27;
        break;
    case 27:
        tft.fillScreen(ST77XX_BLACK);
        joystick();
        break;
    case 31:
        tft.fillScreen(ST77XX_BLACK);
        displayConfig();
        displayMode = 32;
        break;
    case 33:
        tft.fillScreen(ST77XX_BLACK);
        displayConfig2();
        cptDisplayBatt = 0;
        displayMode = 34;
        break;
    case 34:
        if (cptDisplayBatt++ > 50)
        {
            tft.fillScreen(ST77XX_BLACK);
            ;
            displayConfig2();
            cptDisplayBatt = 0;
        }
        break;
    case 35:
        tft.fillScreen(ST77XX_BLACK);
        ;
        displayLicences();
        displayMode = 36;
        break;
    default:
        Serial.println("Unknown display mode");
        displayMode = 0;
    }
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

// key are defined in display.hpp
String EN_Strings[] = {"Sensor ", "Used channels:", "Settings", "Version: ", "Battery: ", "Licence"};
String FR_Strings[] = {"Capteur ", "Canaux utilises : ", "Parametres", "Version : ", "Batterie : ", "Licence"};
String ES_Strings[] = {"Sensor ", "Canales usados : ", "Configuraciones", "Version: ", "Batería: ", "Licencia"};
String DE_Strings[] = {"Sensor ", "Benutzte Kanäle : ", "Parameter", "Version: ", "Batterie: ", "Lizenz"};
//*********************************************
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
    else if (language.equals("DE"))
    {
        return DE_Strings[key];
    }
    return EN_Strings[key];
}
