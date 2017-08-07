//This sketch controls a Op-amp to deliver a constant current circuit

/*User defined variables
   currentSet is in Amps, and has a maximum of 2 amps
   resistance is the load resistance. Calibrate according to your testing.
*/
const float noBatt = 0.8;
const float lowBatt = 2.6;
const float highBatt = 4.3;
const float battCutoff = 3.0;
const float currentSet = 0.2;
const float resistance = 1.05;      //Resistance of 1.0+10% ohm resistor, measured with my multimeter

//Program variables - DO NOT TOUCH
unsigned long milli_time = 0.0;
float batteryVoltage = 0.0;
float desiredVoltage = 0.0;
const int LEDIndicator = 8;
const int voltageSet = 9;
const int voltageIn = A0;

void setup() {
  Serial.begin(9600);
  pinMode(LEDIndicator, OUTPUT);
  pinMode(voltageSet, OUTPUT);
  digitalWrite(voltageSet, LOW);
  desiredVoltage = int(currentSet * resistance / 5.0 * 256.0);
  Serial.println("CLEARDATA");         //This string is defined as a commmand
  //for the Excel VBA to clear all the rows and columns

  Serial.println("LABEL,Computer Time,Time (Milli Sec.),Volt"); //LABEL command creates label
  //for columns in the first row
  //with bold font
}

void flashIndicator(float indication) {
  if (indication == noBatt) {
    //'flash LED once every 5 seconds'
    digitalWrite(LEDIndicator, HIGH);
    delay(200);
    digitalWrite(LEDIndicator, LOW);
    delay(4800);
  }
  else if (indication == lowBatt) {
    //'flash LED 2 time a second for 3 seconds, then delay for 2 seconds'
    for (int seconds = 0; seconds < 3; seconds++) {
      for (int timesPerSecond = 0; timesPerSecond < 2; timesPerSecond++) {
        digitalWrite(LEDIndicator, HIGH);
        delay(200);
        digitalWrite(LEDIndicator, LOW);
        delay(200);
      }
      delay(200);
    }
    delay(2000);
  }
  else if (indication == highBatt) {
    //'flash LED 3 times a second for 3 seconds, then delay for 2 seconds'
    for (int seconds = 0; seconds < 3; seconds++) {
      for (int timesPerSecond = 0; timesPerSecond < 3; timesPerSecond++) {
        digitalWrite(LEDIndicator, HIGH);
        delay(100);
        digitalWrite(LEDIndicator, LOW);
        delay(100);
      }
      delay(400);
    }
    delay(2000);
  }

  else if (indication == battCutoff) {
    //'flash LED 1 times a second'
    digitalWrite(LEDIndicator, HIGH);
    delay(200);
    digitalWrite(LEDIndicator, LOW);
    delay(800);
  }
}
void loop() {
  batteryVoltage = analogRead(voltageIn);
  //TO DO!: Take 20 readings and average them

  batteryVoltage = batteryVoltage*5.0/1023.0;
  Serial.println(batteryVoltage);  //For debugging only!
  
  if (batteryVoltage < noBatt) {
    digitalWrite(voltageSet, LOW);
    Serial.println("no battery detected");
    flashIndicator(noBatt);
  }
  else if (batteryVoltage < lowBatt) {
    digitalWrite(voltageSet, LOW);
    Serial.println("Battery attached but overdischarged!");
    flashIndicator(lowBatt);
  }
  else if (batteryVoltage > highBatt) {
    digitalWrite(voltageSet, LOW);
    Serial.println("Battery attached but overcharged!");
    flashIndicator(highBatt);
  }
  else if (batteryVoltage <= battCutoff) {
    Serial.println("Battery is finished draining");
    digitalWrite(voltageSet, LOW);
    while (1) {
      flashIndicator(battCutoff);
    }
  }

  else {                                        //Battery testing starts here
    digitalWrite(LEDIndicator, HIGH);
    Serial.println(desiredVoltage);
    analogWrite(voltageSet, desiredVoltage);    //Sets the Voltage on the + terminal
                                                //of the Op-amp
    milli_time = millis();
    Serial.print("DATA,TIME,");
    Serial.print(milli_time);
    Serial.print(",");
    Serial.println(batteryVoltage);

    delay(5000); //delay of 5s
  }
}

