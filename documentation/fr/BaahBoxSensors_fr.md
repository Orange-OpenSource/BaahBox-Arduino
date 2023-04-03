
# Exemple de capteurs pour la Baah Box

## A. Capteurs myo-éléctriques

Principe de base : les capteurs de muscles delivrent un signal analogique proportionnel à l'influx musculaire exercé sur eux.

![](../img/myoware_muscle.jpg)

Voici deux marques de capteurs de ce type:  
	- https://www.sparkfun.com/products/13723 
	- https://www.seeedstudio.com/Grove-EMG-Detector-p-1737.html


Le positionnement des capteurs sur le bras du patient est assez délicat; sur chaque capteur il y a deux électrodes qu'il faut positionner dans le sens des fibres musculaires, plus une troisième électrode à mettre dans une zone neutre.


![](../img/myowareOnArm.jpg)


### Plan de connexion


![](../img/topSensor.jpg)

On peut voir sur la droite du plan de connexion  les 3 points de connexions que nous utilisons : "+", "-", "sig".


**_NB:_** Lorsque vous utiliserez le capteur, n'oubliez pas de le calibrer avec le petit potentiomètre que l'on voit à gauche en bas sur le plan ("adjustable gain"). 



## Soudure

Pour utiliser un capteur myo-éléctrique avec la Baah box,

![](../img/photoBaahBox_p.jpg)
 
Il faudra relier un jack stéréo au capteur via 3 cables (alimentation, masse et signal), d'environ un mètre de long.


![](../img/connection_jack_male.jpg)

![](../img/connections_myo.jpg)

### Tester les connexions avec des potentiomètres (*sliders*)

Vous pouvez aussi tester (et jouer!) les applications et la connexion avec la Baah Box avec des potentiomètres (*sliders*) !

(Toujours en reliant le jack au potentiomètre en utilisant les broches VCC, GND, et SIG)


![](../img/slider.jpg)



## B. Joystick

Nous utilisons un joystick de borne d'arcade.

![](../img/Arcade_Joystick_400X300.jpeg)


Nous utilisons aussi le cable de connexion fourni avec, 
dont nous coupons une des extrémités pour la souder sur une prise DB9 mâle.

![](../img/db9_male.jpg)

La table ci-dessous montre les connexions à effectuer. 


![](../img/DB9-Joystick.jpg)


On pourra ainsi connecter le joystick avec le boîtier de la BaahBox avec un cable DB9 mâle-femelle.

![](../img/cable_DB9.jpg)


On peut ensuite monter le joystick dans une boîte, 
avec la prise db9 vissée sur le coté.

![](../img/Joystick_box_parts_400x300.jpeg)


![](../img/Joystick_box_assembly_300X300.jpeg)



![](../img/Joystick.jpg)


****
