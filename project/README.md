[Version Française](#francais)

# The Arduino source code

We use the 
* 	Feather M0 BlueFruit from Adafruit as our main board,
* 	and the Feather Wings SD and OLED as its shields.

Yet you can use an different arduino board and shields. You will have to adapt the code (just a few lines) that we actually use to comply to the M0 microprocessor that ships with the Feather BLE M0. 
You can check the differences in the [Feather M0 BlueFruit documentation from Adafruit](https://learn.adafruit.com/adafruit-feather-m0-bluefruit-le/adapting-sketches-to-m0).
## Step 1 - Configure your Arduino IDE

Most people compile and upload the code using the standard Arduino IDE ( In this case, we strongly recommend that you use the latest 2.x version : https://www.arduino.cc/en/software).

We also provide a set up for PlatformIO (https://platformio.org/).

### A. Arduino IDE 

Copy the content of the _**src**_  and **_include_** directory in a single directory on your computer and open the `baah-box.ino` with the Arduino IDE.

We use 3rd party librairies to make the Feather BLE, the SD wing, as well as the OLED Screen work together with our base code. _Please make sure that they are installed with your Arduino IDE_
(Check https://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use).

- ArduinoSD from Sparkfun 
- Adafruit GFX 
- Adafruit BluefruitLE nRF51
- Adafruit SSD1306
- Adafruit FeatherOLED

### B. PlatformIO (with VSCode)
The libraries are already listed in the config file - `platformio.ini`.

Open the **_project_** directory with PlatformIO and you're done ! 

## Step 2 - (Optional) Customize your BaahBox with the SD card
  
* Copy **USER.CFG** et **SYSTEM.CFG** on the **SD card**.

 You can update your Baah Box name  (as it will appear on your smartphone for the BLE pairing) by changing **BTLE\_DEVICE_NAME** in **USER.CFG**. 

_Note:_ Your BaahBox comes with a default configuration in case you do not use a SD card.



## Step 3 - Upload the code to your arduino board !



 
# (French version)

# <a name= "francais">Le code Arduino</a>

Le code actuel correspond aux cartes (compatibles Arduino) que nous avons utilisées, à savoir: 
* 	Feather M0 BlueFruit de chez Adafruit,
* 	Les shields (Feather wings) lecteur SD et écran OLED d'Adafruit.

Si vous voulez utiliser une autre carte compatible BTLE, il vous faudra adapter le code à votre carte (notamment la configuration du module BTLE et la syntaxe légèrement differente du standard arduino, due au microprocesseur M0). Vous pouvez consulter la [documentation Feather M0 BlueFruit](https://learn.adafruit.com/adafruit-feather-m0-bluefruit-le/adapting-sketches-to-m0).

## Etape 1 - Configuration du projet selon votre IDE

La pratique la plus courante consiste à compiler et télécharger le code arduino sur votre carte en utilisant l'IDE ARDUINO (dans ce cas nous vous conseillons de prendre la dernière version: https://www.arduino.cc/en/software).

Nous proposons par défaut une arborescence de projet 
PlatformIO (https://platformio.org/).


### A. l'IDE ARDUINO

Copiez le contenu des répertoires  _**src**_  and **_include_**   dans un seul répertoire sur votre ordinateur et ouvrez le fichier the `baah-box.ino` avec l'IDE Arduino.

Avant de téléverser le code arduino sur votre carte, vous devez vous assurer d'avoir installé les librairies suivantes: 

- ArduinoSD from Sparkfun 
- Adafruit GFX 
- Adafruit BluefruitLE nRF51
- Adafruit SSD1306
- Adafruit FeatherOLED

Vous pouvez consulter ce tutoriel:  http://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use.


### B. PlatformIO (avec VSCode)
Les librairies sont déjà listées dans le fichier `platformio.ini` du répetoire **_project_**.
Il ne vous reste plus qu'à ouvrir le répertoire **_project_** avec  PlatformIO ! 

 

## Etape 2 - (Optionel) Configurez votre BaahBox avec les fichiers sur la carte SD 

 Copier les fichiers **USER.CFG** et **SYSTEM.CFG** sur **la carte SD**.
 Vous pouvez modifier le nom de la Baah Box dans le fichier **USER.CFG** (**BTLE\_DEVICE_NAME**). Ce nom apparaîtra sur le smartphone au moment de l'appairage Bluetooth.

 _Note:_ vous pouvez vous passer de carte SD, la BaahBox a une configuration par défaut... et elle sera vue sous le nom de `BaahBox` sur votre application mobile.

 
## Etape 3 Téléversez le code source sur votre carte Arduino

... et voilà !
 