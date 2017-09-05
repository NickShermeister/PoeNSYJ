/* Blink without Delay

 Turns on and off a light emitting diode (LED) connected to a digital
 pin, without using the delay() function.  This means that other code
 can run at the same time without being interrupted by the LED code.

 The circuit:
 * LED attached from pin 13 to ground.
 * Note: on most Arduinos, there is already an LED on the board
 that's attached to pin 13, so no hardware is needed for this example.

 created 2005
 by David A. Mellis
 modified 8 Feb 2010
 by Paul Stoffregen
 modified 11 Nov 2013
 by Scott Fitzgerald


 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
 */

// constants won't change. Used here to set a pin number :
const int buttonPin = 10;     // the number of the pushbutton pin
const int ledPin3 =  13;      // the number of the LED pin
const int ledPin2 =  12;      // the number of the LED pin
const int ledPin1 =  11;      // the number of the LED pin

// Variables will change :
bool ledState1;             // ledState used to set the LED
bool ledState2;             // ledState used to set the LED
bool ledState3;             // ledState used to set the LED
int buttonState;            // Saves the button state (HIHG/LOW)
int buttonSetting;          // Saves what setting the button is on for our diffferent modes.
int tick;                   // Saves what tick the button is on (to differentiate the different lights for each setting)

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis;        // will store last time LED was updated

// constants won't change :
const unsigned long interval = 500;           // interval at which to blink (milliseconds)

void setup() {
 // initialize the LED pin as an output:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  // Set variables' startings states
  ledState1 = HIGH;             
  ledState2 = LOW;            
  ledState3 = HIGH;           
  buttonState = 0;
  buttonSetting = 0;
  tick = 0;
  previousMillis = 0;
  Serial.begin(9600);
}

void loop() {
  // Get the current time in milliseconds.
  unsigned long currentMillis = millis();

  // Read the button state
  buttonState = digitalRead(buttonPin);

  // If the button is down, change the setting (having it bounded between 0 and 4)
  if (buttonState == HIGH) {
      buttonSetting = (buttonSetting + 1) % 5;
      delay(500);
    }

  // If there is a large enough gap since the last LED update
  if ((currentMillis - previousMillis) >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // Increment the tick you're on every loop
    tick += 1;

    //Set the first button state (all on)
    if (buttonSetting == 0){
      ledState1 = HIGH;
      ledState2 = HIGH;
      ledState3 = HIGH;
    }

    //Set second button state (all flashing)
    else if (buttonSetting == 1){
      if (tick % 2 == 0) {
        ledState1 = HIGH;
        ledState2 = HIGH;
        ledState3 = HIGH;
      }
      else {
        ledState1 = LOW;
        ledState2 = LOW;
        ledState3 = LOW;
      }
    }

    //Set the third button state (bouncing lights)
    else if (buttonSetting == 2){
      if (tick % 3 == 0){
        ledState1 = HIGH;
        ledState2 = LOW;
        ledState3 = LOW;
      }

      else if (tick % 3== 1) {
        ledState1 = LOW;
        ledState2 = HIGH;
        ledState3 = LOW;
      }
      else {
        ledState1 = LOW;
        ledState2 = LOW;
        ledState3 = HIGH;
      }
      
    }

    //Set the fourth button state (hopscotch)
    else if (buttonSetting == 3){
      if (tick % 2 == 0) {
        ledState1 = HIGH;
        ledState2 = LOW;
        ledState3 = HIGH;
      }
      else {
        ledState1 = LOW;
        ledState2 = HIGH;
        ledState3 = LOW;
      }
    }

    //Set the fifth button state (all off)
    else if (buttonSetting == 4){
      ledState1 = LOW;
      ledState2 = LOW;
      ledState3 = LOW;
    }

  // set the LED states:
    digitalWrite(ledPin1, ledState1);
    digitalWrite(ledPin2, ledState2);
    digitalWrite(ledPin3, ledState3);  
  }
  //Delay so the Arduino doesn't run at max speed all the time.
  delay(5);
  
}

