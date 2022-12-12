HuskyTail
-----------
Uses an Arduino and a linear actuator to wag the tail of a Home Depot outdoor husky decoration.

**WATCH [THIS VIDEO](https://youtube.com/shorts/xi_J9zB_G6o?feature=share) TO SEE IT IN ACTION!**

The Home Depot christmas husky decoration *conveniently uses a wire frame that fits within the mounting holes of the Actuonix L16 actuator.* I recommend the [L16-140-35-12-P](https://www.actuonix.com/l16-140-35-12-p) model, which is what I used to test this project.

The Arduino that I used was an old, Uno-compatible SparkFun BlackBoard that I had laying around.

I powered the Arduino with a 12V 1A wall wart power supply, with a standard barrel jack. The actuator's red pin was connected to 12V, the actuator's black pin was connected to GND, and the digital highs and lows for the H-Bridge were
connected to Arduino outputs on pins 9 and 10.

(TODO: Add potentiometer feedback from the actuator to the Arduino)

I used diagonal wire cutters to snip the husky's wire frame, in order to mount the actuator, although it was a bit of a tough job for them.

For libraries, I used the [arduino-timer](https://github.com/contrem/arduino-timer) library. You can install it using the Arduino IDE.
