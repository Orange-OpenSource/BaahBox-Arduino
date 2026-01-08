//******************************************
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

#ifndef COMMON_DISPLAY_HPP
#define COMMON_DISPLAY_HPP

// key for translation
#define KEY_SENSOR 0
#define KEY_ANALOG_INPUTS 1
#define KEY_SETTINGS 2
#define KEY_VERSION 3
#define KEY_BATTERY 4
#define KEY_LICENCE 5

const String EN_Strings[] = {"Sensor ", "Used channels:", "Settings", "Version: ", "Battery: ", "Copyright (c) 2026\nOrange SA\nLicence: GPLv3"};
const String FR_Strings[] = {"Capteur ", "Canaux utilises : ", "Parametres", "Version : ", "Batterie : ", "Copyright (c) 2026\nOrange SA\nLicence: GPLv3"};
const String ES_Strings[] = {"Sensor ", "Canales usados : ", "Configuraciones", "Version: ", "Batería: ", "Copyright (c) 2026\nOrange SA\nLicencia: GPLv3"};

#endif