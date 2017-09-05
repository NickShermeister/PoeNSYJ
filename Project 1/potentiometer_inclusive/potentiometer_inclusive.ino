// constants won't change. Used here to set a pin number :
const int buttonPin = 3;     // the number of the pushbutton pin
const int ledPin3 =  13;      // the number of the LED pin
const int ledPin2 =  12;      // the number of the LED pin
const int ledPin1 =  11;      // the number of the LED pin
const int potentPin = 0;

// Variables will change :
bool ledState1;             // ledState used to set the LED
bool ledState2;             // ledState used to set the LED
bool ledState3;             // ledState used to set the LED
int buttonState;            // Saves the button state (HIGH/LOW)
int lastButtonState;        // Saves last button state (HIGH/LOW)
int buttonSetting;          // Saves what setting the button is on for our diffferent modes.
int lastButtonSetting;      // Saves the last button setting.
int tick;                   // Saves what tick the button is on (to differentiate the different lights for each setting)
int potentValue;            // Saves the current potentiometer value
int lightInterval;

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillisLight;        // will store last time LED was updated
unsigned long previousMillisButton;       // store last time the button was checked to see if it was being pressed

// constants won't change :
const unsigned long buttonInterval = 10;          // interval at which to check to see if the button is pressed
const int minBlinkFrequency = 100;
const int maxBlinkFrequency = 1000;

void setup() {
 // initialize the LED pin as an output:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  
  // initialize the pushbutton pin as an input and attach an interrupt
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonUpdate, CHANGE);

  // Initialize the potentiometerPin as an input
  pinMode(potentPin, INPUT);

  // Set variables' startings states
  ledState1 = HIGH;             
  ledState2 = LOW;            
  ledState3 = HIGH;           
  buttonState = 0;
  lastButtonState = 0;
  buttonSetting = 0;
  lastButtonSetting = 4;
  tick = 0;
  previousMillisButton = 0;
  previousMillisLight = 0;
  potentValue = -1;
  Serial.begin(9600);
  lightInterval = 1;
}

void loop() {
  interrupts();
  // Get the current time in milliseconds.
  unsigned long currentMillis = millis();

  // Get the current potentiometer value
  potentValue = analogRead(potentPin);

  //Set the light interval at which it will blink.
  lightInterval = 100 + potentValue;
  
  // Read the button state
  buttonState = digitalRead(buttonPin);

  // If there is a large enough gap since the last LED update
  if ((currentMillis - previousMillisLight) >= lightInterval) {
    
    // save the last time you blinked the LED
    previousMillisLight = currentMillis;
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
  delay(50);
}


void buttonUpdate() {
  //Get current time
  long unsigned currentMillis = millis();
  
  //Check to see if there is a large enough gap since the last button update
  if ((currentMillis - previousMillisButton) >= buttonInterval){
    //Make sure there was a change in button state and that the current button state is high
    if (buttonState == HIGH && lastButtonState != HIGH) {
          lastButtonSetting = buttonSetting;
          buttonSetting = (buttonSetting + 1) % 5;
      } 
        
    //Upkeep of variables
    previousMillisButton = currentMillis;    
    lastButtonState = buttonState;
  }

}

