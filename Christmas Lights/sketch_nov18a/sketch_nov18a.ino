#include <FastLED.h>
#define NUM_LEDS 500
#define DATA_PIN 6
#define BUTTON_PIN 2
CRGB leds[NUM_LEDS];

enum LightMode {
  CHRISTMAS,q
  HANNUKAH,
  WARM
};

LightMode currentMode = CHRISTMAS;

int counter = 0;
int buttonState = LOW;

int lastButtonState = LOW;     // the previous state of the button
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup() { 
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); 
    pinMode(BUTTON_PIN, INPUT);
}


void loop() {

int reading = digitalRead(BUTTON_PIN);

  // check if the button state has changed
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // if the button state has changed and the change has lasted for longer than the debounce delay, change the mode
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // only change the currentMode if the new button state is HIGH
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        Serial.println(counter);
        counter++;

        if (counter % 3 == 0) {
          currentMode = CHRISTMAS;
        } else if (counter % 3 == 1) {
          currentMode = HANNUKAH;
        } else {
          currentMode = WARM;
        }
      }
    }
  }

  lastButtonState = reading;

  switch(currentMode) {
    case CHRISTMAS:
      christmas();
      break;
    case HANNUKAH:
      hannukah();
      break;
    case WARM:
      warm();
      break;
  }
    
  // delay(1000);
  // christmasColors();
  // delay(1000);

  // warmAll();
  // delay(1000);
  // christmasColors();
      // delay(1000);

}



void warm() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(80, 255,0);
  }
  FastLED.show();
}

void hannukah() {
  for (int i = 0; i< NUM_LEDS; i++) {
    if (i % 2) {
      leds[i] = CRGB::White;
    } else {
      leds[i] = CRGB(0,0,255);
    }
  }
  FastLED.show();
}


void christmas() {
  for(int i = 0; i < NUM_LEDS; i++) {
        // Cycle through Red, Blue, Yellow, Green for each LED
        if(i % 4 == 0) {
            leds[i] = CRGB(0, 255,0);
        } else if(i % 4 == 1) {
            leds[i] = CRGB(0,0,50);
        } else if(i % 4 == 2) {
            leds[i] = CRGB(80, 255,0);
        } else {
            leds[i] = CRGB(50,0,0);
        }
    }
    FastLED.show();
}