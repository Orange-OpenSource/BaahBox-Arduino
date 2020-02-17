
# Build your sensors to use with your Baah Box


## Electromyography (EMG) Sensors



This kind of sensors measure muscle activity by detecting its electric potential.



![](../img/myoware_muscle.jpg)


You will find below two example of such sensors :
	- https://www.sparkfun.com/products/13723 
	- https://www.seeedstudio.com/Grove-EMG-Detector-p-1737.html


You will have to be careful when positioning the electrodes on the muscle:  two of them have to be placed on the muscle (parallel to  the muscle fibers) for which you want to measure the activity.
The third electrode serves as a reference, and has to be placed outside the muscle area.

You will find plenty of links and instructions on the web on how to use those sensors.

![](../img/myowareOnArm.jpg)


### Connection


![](../img/topSensor.jpg)

 You will have to use the 3 pins "+", "-", "sig" (as shown below on to the right of the sensor).


###  Soldering


![](../img/photoBaahBox_p.jpg)
 
You will have to connect the sensor to a 3.5mm stereo male jack, 
using 3 (approx. 1 m long) cables - one for Vcc, one for the Ground, and one for the Signal.


![](../img/connection_jack_male.jpg)

![](../img/connections_myo.jpg)

## Sliders

You can also use one or two sliders to play with the Baah Box. 
always using the same connection  as the myoware sensor.
**(Actually, any analog arduino sensor will do the trick)**


![](../img/slider.jpg)




## Joystick

You can use an Arcade Joystick with its connection cable, like this one.

![](../img/Arcade_Joystick_400X300.jpeg)


And cut one end of the cable to solder it to a male DB9 connector.

![](../img/db9_male.jpg)
 
### Soldering 

The table below shows the connection to the DB9 male connector to the joystick pins.
 
![](../img/DB9-Joystick.jpg)


You will then be able to connect the Baah Box and the joystck with a DB9 male-female cable - and reuse the joystick for another use!

![](../img/cable_DB9.jpg)

### In the box !

The final step is to put the joystick (and the DB9 connector soldered to it)
 in a home-made box, like so : 


![](../img/Joystick_box_parts_400x300.jpeg)


![](../img/Joystick_box_assembly_300X300.jpeg)



![](../img/Joystick.jpg)


