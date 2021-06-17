/**

     GPIO  0 - Button right / D3
     GPIO  1 - D10
     GPIO  2 - LED blue (LED_BUILTIN) / D4
     GPIO  3 - D9
     GPIO  4 - OLED SCL
     GPIO  5 - OLED SDA
     GPIO 12 - Button down
     GPIO 13 - Button up
     GPIO 14 - Button push
     GPIO 15 - D8
     GPIO 16 - LED green
     GPIO A0 - ADC

**/

#include "SSD1306Brzo.h"            // Include OLED Library

SSD1306Brzo  display(0x3c, 5, 4);   // Initialize OLED display

int blueLed = LED_BUILTIN;          // Blue LED is on GPIO 2 (LED_BUILTIN)
int greenLed = 16;                  // Green LED is on GPIO 16

int analogPin = A0;                 // Analog input is A0
int analogValue = 0;

volatile byte state = LOW;
String button = "Waiting...";

void setup() {
  display.init();   // Initialise the display

  pinMode(blueLed, OUTPUT);   // Initialize digital pin LED_BUILTIN as an output.
  pinMode(greenLed, OUTPUT);  // initialize digital pin 16 as an output.

  pinMode(0, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(0), interrupt0, HIGH);    // Right
  pinMode(12, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(12), interrupt12, HIGH);  // Down
  pinMode(13, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(13), interrupt13, HIGH);  // Up
  pinMode(14, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(14), interrupt14, HIGH);  // Push
}

void drawText() { // Fuction to draw the text
  display.setTextAlignment(TEXT_ALIGN_LEFT);

  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Button:");
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 16, button);                          // Print button press

  display.setFont(ArialMT_Plain_16);
  analogValue = analogRead(analogPin);
  display.drawString(0, 48, "ADC: " + String(analogValue));   // Print value of analog input

}

void interrupt0() // Right
{
  button = "Right";
  blink();
}

void interrupt12() // Down
{
  button = "Down";
  blink();
}

void interrupt13() // Up
{
  button = "Up";
  blink();
}

void interrupt14() // Push
{
  button = "Push";
  blink();
}

void blink() {
  state = !state;   // Reverse LED state
}

void loop() {
  display.clear();      // Clear OLED display
  drawText();           // Draw the text
  display.display();    // Write the buffer to the display

  digitalWrite(blueLed, state);      // Turn the blue LED on/off
  digitalWrite(greenLed, !state);    // Turn the green LED on/off
}
