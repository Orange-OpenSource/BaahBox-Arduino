[Version Française](#francais)

# The Arduino source code

We use 3rd party librairies to make the Feather BLE, the SD wing, as well as the OLED Screen work together with our base code. Please make sure that they are installed with your Arduino IDE 
(please check https://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use).

- ArduinoSD from Sparkfun 
- Adafruit GFX 
- Adafruit BluefruitLE nRF51
- Adafruit SSD1306
- Adafruit FeatherOLED



## First step 
  
* Copy **USER.CFG** et **SYSTEM.CFG** on the **SD card**.

 You can update your Baah Box name  (as it will appear on your smartphone for the BLE pairing) by changing **BTLE\_DEVICE_NAME** in **USER.CFG**. 


**CAUTION**: 
We use the 
* 	Feather M0 BlueFruit from Adafruit as our main board,
* 	and the Feather Wings SD and OLED as its shields.

We have chosen to rely on a M0-based arduino board because we needed more power and memory than what a standard arduino board could provide. A 32U4-based arduino, for example, will not fit. 

You can use an different arduino board and shields. You will have to adapt the code (just a few lines) that we actually use to comply to the M0 microprocessor that ships with the Feather BLE M0. 
You can check the differences in the [Feather M0 BlueFruit documentation from Adafruit](https://learn.adafruit.com/adafruit-feather-m0-bluefruit-le/adapting-sketches-to-m0).


## Etape 3 
 
 Upload the code to your arduino board !





# (French version)

# <a name= "francais">Le code Arduino</a>
## Etape 1
Avant de téléverser le code arduino sur votre carte, vous devez vous assurer d'avoir installé les librairies suivantes: 

- ArduinoSD from Sparkfun 
- Adafruit GFX 
- Adafruit BluefruitLE nRF51
- Adafruit SSD1306
- Adafruit FeatherOLED

Vous pouvez consulter ce tutoriel:  http://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use.


## Etape 2

 Copier les fichiers **USER.CFG** et **SYSTEM.CFG** sur **la carte SD**.
 Vous pouvez modifier le nom de la Baah Box dans le fichier **USER.CFG** (**BTLE\_DEVICE_NAME**). Ce nom apparaîtra sur le smartphone au moment de l'appairage Bluetooth.


**ATTENTION**: Le code actuel correspond aux cartes que nous avons utilisées, à savoir: 
* 	Feather M0 BlueFruit de chez Adafruit,
* 	Les shields (Feather wings) lecteur SD et écran OLED d'Adafruit.

Si vous voulez utiliser une autre carte compatible BTLE, il vous faudra adapter le code à votre carte (notamment la configuration du module BTLE et la syntaxe légèrement differente du standard arduino, due au microprocesseur M0). Vous pouvez consulter la [documentation Feather M0 BlueFruit](https://learn.adafruit.com/adafruit-feather-m0-bluefruit-le/adapting-sketches-to-m0).
 *NB:* Le code arduino nécessite une carte relativement puissante avec plus de mémoire qu'une carte de base. Une arduino à base de 32u4, par exemple, ne suffira pas.
 
 
## Etape 3 
 
 Téléversez le code source sur votre carte Arduino... voilà !

