/* Larson scanner

  Starting with the same LED wiring as before, on digital pins 2 - 6
  and hopefully using a pot on a0 to vary the speed with
  
  This version uses digital pins, which means they can only be on or off,
  so you don't get that nice trailing effect with the slow decay.
  But its a start.
  
*/

// these constants won't change:
const int analogPin = A0;   // the pin that the potentiometer is attached to
const int ledCount = 5;    // the number of LEDs in the bar graph

int dbg_lastSensorReading = 0;

int ledPins[] = { 
   6, 5, 4, 3, 2 // i have it wired in reverse, easier to connect now
  };

#define NUMBER_OF_LEDS (sizeof(ledPins)/sizeof(int))

/*
  This copies a simple design I found elsewhere, where each "frame" is 
  defined beforehand, and the code just loops through the frames.
  (simpler than trying to calculate the back-and-forth scan for a small number)
*/
boolean larson[][NUMBER_OF_LEDS] = {
{ HIGH, LOW, LOW, LOW, LOW},
{ LOW, HIGH, LOW, LOW, LOW},
{ LOW, LOW, HIGH, LOW, LOW},
{ LOW, LOW, LOW, HIGH, LOW},
{ LOW, LOW, LOW, LOW, HIGH},
{ LOW, LOW, LOW, HIGH, LOW},
{ LOW, LOW, HIGH, LOW, LOW},
{ LOW, HIGH, LOW, LOW, LOW},
};

#define FRAMES (sizeof(larson)/(sizeof(larson[0])))

int currentLed = 3; // start at the middle
int scanSpeed = 50;

void setup() {
  
    // loop over the pin array and set them all to output:
   for (int led=0; led < NUMBER_OF_LEDS; ++led) {
     pinMode(ledPins[led], OUTPUT);
}
  
  Serial.begin(9600);
  Serial.println("Larson Scanner LED Test ");
};

void loop() {
     
 long time = millis();

  for (int frame=0; frame < FRAMES; frame++) {
    for (int led=0; led < NUMBER_OF_LEDS; led++) {
      digitalWrite(ledPins[led], larson[frame][led]);
    }
    
    //  play with this to enable speed control
    int sensorValue = map(analogRead(analogPin), 0, 1023, 0, 1000);
    while (sensorValue >= (millis() - time)) {
      sensorValue = analogRead(analogPin);
    }
    
    time = millis();
  }

};
