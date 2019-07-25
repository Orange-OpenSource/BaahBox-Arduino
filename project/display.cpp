// ******************************************
// * Baah Box Arduino : Sensor BTLE gateway *
// ******************************************

// Copyright (C) 2017 – 2019 Orange SA

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
#include "display.hpp"
#include "configSD.hpp"

int decalage = 64;
int cptDisplayBatt = 0;

extern configSDClass config3dHandz;

//*********************************************
//*
//*       Constructor
//*
//*********************************************
handzDisplay::handzDisplay()
{
}

//*********************************************
//*
//*       Destructor
//*
//*********************************************
handzDisplay::~handzDisplay()
{
}

//*********************************************
//*
//*       Init
//*
//*********************************************
void handzDisplay::init(void)
{
    Serial.println("OLED FeatherWing test");
    // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 128x32)

    display.clearDisplay();
    display.display();

    for (int index = 0; index < 62; index++)
    {
        tblCapteur1[index] = 0;
        tblCapteur2[index] = 0;
    }
    idxTblCapteur = 0;

    displayMode = 1;

    pinMode(BUTTON_A, INPUT_PULLUP);
    pinMode(BUTTON_B, INPUT_PULLUP);
    pinMode(BUTTON_C, INPUT_PULLUP);
    button_A_pressed = 0;
    button_B_pressed = 0;
    button_C_pressed = 0;

    scheduler = new Scheduler(millis(), DISPLAY_DELAY);
}

//*********************************************
//*
//*       Display banner
//*
//*********************************************
void handzDisplay::DisplayBanner(void)
{
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(10, 1);
    display.println(APPLICATION_NAME);
    display.setTextSize(1);
    display.setCursor(10, 24);
    display.println(config3dHandz.copyright);
}

//*********************************************
//*
//*       isButtonPressed
//*
//*********************************************
int handzDisplay::isButtonPressed(void)
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
void handzDisplay::displayAxes(int type)
{
    // type =>
    //  0 : 2 sensors
    //  1 : sensor 1 only
    //  2 : sensor 2 only

    display.setTextSize(1);
    display.setTextColor(WHITE);
    int PosLegende = 25;
    int x0 = 0;
    int y0 = 0;
    int x1 = 64;
    int y1 = 23;

    switch (type)
    {
    case 0:
        // display caption for sensor 1
        display.setCursor(5, PosLegende);
        display.print(getTranslatedString(KEY_SENSOR));
        display.print("1");
        // display caption for sensor 2
        display.setCursor(64 + 5, PosLegende);
        display.print(getTranslatedString(KEY_SENSOR));
        display.print("2");

        display.drawLine(x0, y0, x0, y1, WHITE);
        display.drawLine(x0, y1, x1 - 2, y1, WHITE);

        display.drawLine(x0 + decalage, y0, x0 + decalage, y1, WHITE);
        display.drawLine(x0 + decalage, y1, x1 + decalage - 2, y1, WHITE);
        break;
    case 1:
    case 2:
        x1 = 64 + decalage;
        // display caption for selected sensor
        display.setCursor(50, PosLegende);
        display.print(getTranslatedString(KEY_SENSOR));
        display.print(type);
        display.drawLine(x0, y0, x0, y1, WHITE);
        display.drawLine(x0, y1, x1 - 2, y1, WHITE);
        break;
    }
}

//*********************************************
//*
//*       capteurs
//*
//*********************************************
void handzDisplay::capteurs(int type)
{
    muscleSensor.getValue(&capteur1, &capteur2);
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
void handzDisplay::displayCapteur(int channel, int type)
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
            display.drawPixel(posX, posY, WHITE);
        }
        break;
    case 1:
    case 2:
        for (int index = 0; index < 126; index++)
        {
            posX = index + 1;
            posY = map(tblCapteur[index], 0, 1023, 22, 0);
            display.drawPixel(posX, posY, WHITE);
        }
        break;
    }
}

//*********************************************
//*
//*       refreshDisplay
//*
//*********************************************
void handzDisplay::refreshDisplay()
{
    if (cptRefresh++ > 5)
    {
        display.display();
        cptRefresh = 0;
    }
}

//*********************************************
//*
//*       joystick
//*
//*********************************************
void handzDisplay::joystick()
{
    int btGauche = digitalRead(config3dHandz.joystickDigitalInputTab[1]);
    int btDroit = digitalRead(config3dHandz.joystickDigitalInputTab[0]);
    int btBas = digitalRead(config3dHandz.joystickDigitalInputTab[2]);
    int btHaut = digitalRead(config3dHandz.joystickDigitalInputTab[3]);
    //int btGauche = digitalRead(11);
    //int btDroit = digitalRead(A5);
    //int btBas = digitalRead(12);
    //int btHaut = digitalRead(13);

    char blancs[20] = "           ";
    char titre[20] = " Joystick  ";

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);

    display.print(blancs);
    display.print("   [");
    if (btHaut == 0)
        display.print("*");
    else
        display.print(" ");
    display.println("]");

    display.print(titre);
    display.print("[");
    if (btGauche == 0)
        display.print("*");
    else
        display.print(" ");
    display.print("]");
    display.print("   [");
    if (btDroit == 0)
        display.print("*");
    else
        display.print(" ");
    display.println("]");

    display.print(blancs);
    display.print("   [");
    if (btBas == 0)
        display.print("*");
    else
        display.print(" ");
    display.print("]");
}

//*********************************************
//*
//*       displayConfig
//*
//*********************************************
void handzDisplay::displayConfig()
{
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(getTranslatedString(KEY_SETTINGS));
    display.print("BTLE : ");
    display.println(config3dHandz.btleDeviceName);
    display.print(getTranslatedString(KEY_ANALOG_INPUTS));
    display.println(config3dHandz.pinAnalogInputs);
    display.print(getTranslatedString(KEY_VERSION));
    display.println(VERSION_3DHANDZ);
}

//*********************************************
//*
//*       displayConfig2
//*
//*********************************************
void handzDisplay::displayConfig2()
{
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(getTranslatedString(KEY_SETTINGS));
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
    display.print("Vbat = ");
    display.print(tmp);
    display.print("V (");
    display.print(charge);
    display.println("%)");
    display.print(getTranslatedString(KEY_BATTERY));
    display.print("[");
    for (int i = 0; i <= 95; i += 12)
    {
        if (i <= charge)
        {
            display.print("*");
        }
        else
        {
            display.print(" ");
        }
    }
    display.println("]");
    display.display();
}

//*********************************************
//*
//*       displayLicences
//*
//*********************************************
void handzDisplay::displayLicences()
{
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(getTranslatedString(KEY_LICENCE));
}

//*********************************************
//*
//*       update
//*
//*********************************************
void handzDisplay::update(void)
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
        display.clearDisplay();
        DisplayBanner();
        displayMode = 0;
        break;
    case 20:
        displayMode = 21;
        break;
    case 21:
        display.clearDisplay();
        capteurs(0);
        break;
    case 22:
        displayMode = 23;
        break;
    case 23:
        display.clearDisplay();
        capteurs(1);
        break;
    case 24:
        displayMode = 25;
        break;
    case 25:
        display.clearDisplay();
        capteurs(2);
        break;
    case 26:
        displayMode = 27;
        break;
    case 27:
        display.clearDisplay();
        joystick();
        break;
    case 31:
        display.clearDisplay();
        displayConfig();
        displayMode = 32;
        break;
    case 33:
        display.clearDisplay();
        displayConfig2();
        cptDisplayBatt = 0;
        displayMode = 34;
        break;
    case 34:
        if (cptDisplayBatt++ > 50)
        {
            display.clearDisplay();
            displayConfig2();
            cptDisplayBatt = 0;
        }
        break;
    case 35:
        display.clearDisplay();
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
void handzDisplay::checkButtons(void)
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
String handzDisplay::getTranslatedString(int key)
{
    // get the translated value of string identified by the key
    String language = config3dHandz.language;
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
