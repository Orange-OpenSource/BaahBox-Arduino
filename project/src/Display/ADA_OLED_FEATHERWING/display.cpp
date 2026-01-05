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
#include <Wire.h>

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
    oled = Adafruit_SSD1306(128, 32, &WIRE);
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
    Serial.println("OLED FeatherWing test");
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

    Serial.println("OLED begun");

    // Show image buffer on the display hardware.
    // Since the buffer is intialized with an Adafruit splashscreen
    // internally, this will display the splashscreen.
    // display.display();
    delay(1000);

    // Clear the buffer.
    oled.clearDisplay();
    oled.display();

    pinMode(BUTTON_A, INPUT_PULLUP);
    pinMode(BUTTON_B, INPUT_PULLUP);
    pinMode(BUTTON_C, INPUT_PULLUP);

    for (int index = 0; index < 62; index++)
    {
        tblCapteur1[index] = 0;
        tblCapteur2[index] = 0;
    }
    idxTblCapteur = 0;

    displayMode = 1;

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
    oled.setTextSize(2);
    oled.setTextColor(WHITE);
    oled.setCursor(10, 1);
    oled.println(APPLICATION_NAME);
    oled.setTextSize(1);
    oled.setCursor(10, 24);
    oled.println(config.copyright);
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

    if (button_A == 0)
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

    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    int PosLegende = 25;
    int x0 = 0;
    int y0 = 0;
    int x1 = 64;
    int y1 = 23;

    switch (type)
    {
    case 0:
        // display caption for sensor 1
        oled.setCursor(5, PosLegende);
        oled.print(getTranslatedString(KEY_SENSOR));
        oled.print("1");
        // display caption for sensor 2
        oled.setCursor(64 + 5, PosLegende);
        oled.print(getTranslatedString(KEY_SENSOR));
        oled.print("2");

        oled.drawLine(x0, y0, x0, y1, WHITE);
        oled.drawLine(x0, y1, x1 - 2, y1, WHITE);

        oled.drawLine(x0 + decalage, y0, x0 + decalage, y1, WHITE);
        oled.drawLine(x0 + decalage, y1, x1 + decalage - 2, y1, WHITE);
        break;
    case 1:
    case 2:
        x1 = 64 + decalage;
        // display caption for selected sensor
        oled.setCursor(50, PosLegende);
        oled.print(getTranslatedString(KEY_SENSOR));
        oled.print(type);
        oled.drawLine(x0, y0, x0, y1, WHITE);
        oled.drawLine(x0, y1, x1 - 2, y1, WHITE);
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
        displayAnalogInputs(0, type);
        displayAnalogInputs(1, type);
        break;
    case 1:
        tblCapteur[idxTblCapteur] = capteur1;
        if (idxTblCapteur >= 126)
        {
            idxTblCapteur = 0;
        }
        displayAnalogInputs(0, type);
        break;
    case 2:
        tblCapteur[idxTblCapteur] = capteur2;
        if (idxTblCapteur >= 126)
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
            oled.drawPixel(posX, posY, WHITE);
        }
        break;
    case 1:
    case 2:
        for (int index = 0; index < 126; index++)
        {
            posX = index + 1;
            posY = map(tblCapteur[index], 0, 1023, 22, 0);
            oled.drawPixel(posX, posY, WHITE);
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
        oled.display();
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

    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.setCursor(0, 0);

    oled.print(blancs);
    oled.print("   [");
    if (btHaut == 0)
        oled.print("*");
    else
        oled.print(" ");
    oled.println("]");

    oled.print(titre);
    oled.print("[");
    if (btGauche == 0)
        oled.print("*");
    else
        oled.print(" ");
    oled.print("]");
    oled.print("   [");
    if (btDroit == 0)
        oled.print("*");
    else
        oled.print(" ");
    oled.println("]");

    oled.print(blancs);
    oled.print("   [");
    if (btBas == 0)
        oled.print("*");
    else
        oled.print(" ");
    oled.print("]");
}

//*********************************************
//*
//*       displayConfig
//*
//*********************************************
void BBDisplay::displayConfig()
{
    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.setCursor(0, 0);
    oled.println(getTranslatedString(KEY_SETTINGS));
    oled.println("BTLE Name : ");
    oled.println(config.btleDeviceName);
    oled.print(getTranslatedString(KEY_VERSION));
    oled.println(VERSION_BBox);
}

//*********************************************
//*
//*       displayConfig2
//*
//*********************************************
void BBDisplay::displayConfig2()
{
    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.setCursor(0, 0);
    oled.println(getTranslatedString(KEY_SETTINGS));
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
    oled.print("Vbat = ");
    oled.print(tmp);
    oled.print("V (");
    oled.print(charge);
    oled.println("%)");
    oled.print(getTranslatedString(KEY_BATTERY));
    oled.print("[");
    for (int i = 0; i <= 95; i += 12)
    {
        if (i <= charge)
        {
            oled.print("*");
        }
        else
        {
            oled.print(" ");
        }
    }
    oled.println("]");
    oled.display();
}

//*********************************************
//*
//*       displayLicences
//*
//*********************************************
void BBDisplay::displayLicences()
{
    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.setCursor(0, 0);
    oled.println(getTranslatedString(KEY_LICENCE));
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
        oled.clearDisplay();
        DisplayBanner();
        displayMode = 0;
        break;
    case 20:
        displayMode = 21;
        break;
    case 21:
        oled.clearDisplay();
        capteurs(0); // 2 analog inputs
        break;
    case 22:
        displayMode = 23;
        break;
    case 23:
        oled.clearDisplay();
        capteurs(1); // first analog input
        break;
    case 24:
        displayMode = 25;
        break;
    case 25:
        oled.clearDisplay();
        capteurs(2); // second analog input
        break;
    case 26:
        displayMode = 27;
        break;
    case 27:
        oled.clearDisplay();
        joystick(); // 4 digital inputs
        break;
    case 31:
        oled.clearDisplay();
        displayConfig();
        displayMode = 32;
        break;
    case 33:
        oled.clearDisplay();
        displayConfig2();
        cptDisplayBatt = 0;
        displayMode = 34;
        break;
    case 34:
        if (cptDisplayBatt++ > 50)
        {
            oled.clearDisplay();
            displayConfig2();
            cptDisplayBatt = 0;
        }
        break;
    case 35:
        oled.clearDisplay();
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
String EN_Strings[] = {"Sensor ", "Used channels:", "Settings", "Version: ", "Battery: ", "Copyright (c) 2025\nOrange SA\nLicence: GPLv3"};
String FR_Strings[] = {"Capteur ", "Canaux utilises : ", "Parametres", "Version : ", "Batterie : ", "Copyright (c) 2025\nOrange SA\nLicence: GPLv3"};
String ES_Strings[] = {"Sensor ", "Canales usados : ", "Configuraciones", "Version: ", "Batería: ", "Copyright (c) 2025\nOrange SA\nLicencia: GPLv3"};
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
    return EN_Strings[key];
}
