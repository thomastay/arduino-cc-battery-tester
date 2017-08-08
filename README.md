# arduino-cc-battery-tester
Constant current circuit to test 18650 batteries.

## Introduction
18650 batteries need to be tested under load to know their capacity. It is possible to plot a discharge curve of the battery, but a constant current load gives you more useful data as you will be using the 18650 battery to draw a certain amount of current in your circuit anyway. 

The circuit diagram can be seen in "BJT CC.sch". Basically, the op-amp and the transistor (a TIP120 is used here, but any power Darlington would work too) act as a constant-current load, keeping the current at 1 amp through the 1ohm power resistor. 

The important part of the circuit is that it is controlled by an Arduino. The Arduino senses the battery voltage and switches off the transistor once it reaches a set cutoff point as an over-discharge protection. This is crucial since we are dealing with unprotected 18650 batteries. 

## Important variables

The most important variable is "const float currentSet", which sets the current in Amps. Set it to 1.0 to test your battery under 1A. 

## Usage
Set the variable currentSet and upload the code to your arduino. Then, connect the wires to your Arduino as shown in the schematic. You can monitor your Arduino from the serial monitor, or you can use a program like PLX-DAQ, which logs the serial monitor data to an Excel file.

When the battery is under load, the LED will turn on. After the battery is discharged, the battery cuts off and the LED will blink once a second, indicating that the discharge is done.

Here's how to calculate the capacity of the battery: Take the time in hours that the battery works under load, and multiply it by 1000 to get the capacity in mAh. This is the capacity of your battery under a 1A load.

## LED indicator

1 blink every 5 seconds --> No battery connected

2 blinks every second, for 3 seconds, followed by 2 second delay --> Battery undercharged

3 blinks every second, for 3 seconds, followed by 2 second delay --> Battery overcharged

1 blink every second --> Battery finished discharging

LED fully on --> Battery under load. 

## Credits:
I was heavily inspired by GreatScott's video, and my circuit is almost identical to his. Check out his video here: https://www.youtube.com/watch?v=8uBcywBUTkw