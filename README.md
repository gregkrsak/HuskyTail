HuskyTail
-----------
Uses an Arduino and a servo to wag the tail of a Home Depot outdoor husky decoration.

**WATCH [THIS VIDEO](https://youtube.com/shorts/xi_J9zB_G6o?feature=share) TO SEE IT IN ACTION!**

The Home Depot christmas husky decoration *conveniently uses a wire frame that fits within the mounting holes of the Actuonix L16 servo.* I recommend the [L16-140-35-6-R](https://www.actuonix.com/l16-140-35-6-r) model, which is what I used to test this project.

The Arduino that I used was an old, Uno-compatible SparkFun BlackBoard that I had laying around.

I powered the Arduino with a 12V 1A wall wart power supply, with a standard barrel jack. The servo's red pin was connected to 5V, the servo's black pin was connected to GND, and the servo's white pin was connected to digital pin 9.

I used diagonal wire cutters to snip the husky's wire frame, in order to mount the servo, although it was a bit of a tough job for them.

For libraries, I used the [arduino-timer](https://github.com/contrem/arduino-timer) and [Servo](https://github.com/arduino-libraries/Servo) libraries. You can install them using the Arduino IDE.
