#include "ws2812.h"

#define WS2812_PIN PA7
#define WS2812_NUM 2

Ws2812 pixels = Ws2812(WS2812_NUM,WS2812_PIN);


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  pixels.begin();
  pixels.setPixelColor(0,0,255,0);
  pixels.setPixelColor(1,0,255,0);
  pixels.show();
  
}

// the loop function runs over and over again forever
void loop() {
  ledTest(0);
  ledTest(1);

}

void ledTest(int pixel) {
  
  pixels.setPixelColor(pixel,255,0,0);
  pixels.show();
  delay(500);

  pixels.setPixelColor(pixel,0,255,0);
  pixels.show();
  delay(500);

  pixels.setPixelColor(pixel,0,0,255);
  pixels.show();
  delay(500);

  pixels.setPixelColor(pixel,50,50,50);
  pixels.show();
  delay(500);

  pixels.setPixelColor(pixel,100,100,100);
  pixels.show();
  delay(500);

  for(int i = 0; i < 255; i++) {
    pixels.setPixelColor(pixel, Wheel(i));
    pixels.show();
    delay(10);
  }
}

