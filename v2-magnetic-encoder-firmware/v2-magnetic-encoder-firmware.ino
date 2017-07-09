/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO 
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN takes care 
  of use the correct LED pin whatever is the board used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products
  
  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
  
  modified 2 Sep 2016
  by Arturo Guadalupi
*/

#include "ws2812.h"

#define WS2812_PIN PA7
#define WS2812_NUM 2

Ws2812 pixels = Ws2812(WS2812_NUM,WS2812_PIN);


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  pixels.begin();
  pixels.setPixelColor(0,255,0,0);    //Red
  pixels.setPixelColor(1,0,255,0);    //Red
  pixels.show();
  delay(1000);
  //pixels.show();
  //pixels.show();
}

// the loop function runs over and over again forever
void loop() {
  for(int i = 0; i < 255 * 5; i++) {
    pixels.setPixelColor(0, Wheel(i));
    pixels.show();
    delay(10);
  }
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  pixels.setPixelColor(0,255,0,0);    //Red
  pixels.setPixelColor(1,0,255,0);    //Red
  pixels.show();
  delay(50);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  pixels.setPixelColor(0,255,0,0);    //Red
  pixels.setPixelColor(1,0,255,0);    //Red
  pixels.show();
  delay(50);                       // wait for a second
}
