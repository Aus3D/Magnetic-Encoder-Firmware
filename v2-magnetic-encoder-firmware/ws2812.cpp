#include "ws2812.h"
#include "SPI.h"

Ws2812::Ws2812(uint8_t num, uint16_t outputPin) {

	pin = outputPin;
	begun = false;

	if(pixels) free(pixels);

	int numBytes = numLEDs * 3;

	if((pixels = (uint8_t *)malloc(numBytes))) {
	    memset(pixels, 0, numBytes);
		numLEDs = num;
	} else {
	numLEDs = numBytes = 0;
	}

 if((brightness = (uint8_t *)malloc(numLEDs))) {
    memset(brightness, 255, numLEDs);
 }

}

void Ws2812::begin(void) {

	if (pin == 0x00) {
		return;
	}
  SPI.begin();
  SPI.beginTransaction(SPISettings(3000000, MSBFIRST, SPI_MODE1));

	begun = true;
 
}

void Ws2812::show() {
	if(!pixels) return;

  int Index;
  uint32_t Encoding=0;
  uint8_t SPI_Data[numLEDs*9];
  uint32_t SPI_index = 0;
  uint8_t *p, *b;
  uint8_t green;
  uint8_t red;
  uint8_t blue;
  uint32_t colour;
  
	for(int i = 0; i < numLEDs; i++) {

    b = &brightness[i];
    float scale = (float)b[0] / 255;

    p = &pixels[i * 3];
    green = p[0] * scale;
    red   = p[1] * scale;
    blue  = p[2] * scale;
    
    // Process the GREEN byte
    Encoding = SPIEncodedValue(green);
     
    SPI_Data[SPI_index++] = ((Encoding >> 16) & 0xff);
    SPI_Data[SPI_index++] = ((Encoding >> 8) & 0xff);
    SPI_Data[SPI_index++] = (Encoding & 0xff);
    
    // Process the RED byte
    Encoding = SPIEncodedValue(red);
    
    SPI_Data[SPI_index++] = ((Encoding >> 16) & 0xff);
    SPI_Data[SPI_index++] = ((Encoding >> 8) & 0xff);
    SPI_Data[SPI_index++] = (Encoding & 0xff);
    
    // Process the BLUE byte
    Encoding = SPIEncodedValue(blue);
       
    SPI_Data[SPI_index++] = ((Encoding >> 16) & 0xff);
    SPI_Data[SPI_index++] = ((Encoding >> 8) & 0xff);
    SPI_Data[SPI_index++] = (Encoding & 0xff);

	}
  
  // Now send out the 24 (x3) bits to the SPI bus
  SPI.transfer(SPI_Data,(numLEDs*9));

}

uint32_t Ws2812::SPIEncodedValue(uint8_t color) {
    int index = 0;
    uint32_t encoding = 0;
    
    while (index < 8)
    {
        encoding = encoding << 3;
        if (color & BIT7)
        {
            encoding |= 0b110;
        }
        else
        {
            encoding |= 0b100;
        }
        color = color << 1;
        index++;        
    } 

    return encoding;
}

void Ws2812::setPixelColor(uint8_t pixel, uint8_t red, uint8_t green, uint8_t blue) {
	if(pixel < numLEDs) {

		uint8_t *p;

		p = &pixels[pixel * 3];

		p[0] = green;
		p[1] = red;
		p[2] = blue;

	}
}

void Ws2812::setPixelColor(uint8_t pixel, uint32_t color) {
	if(pixel < numLEDs) {

		uint8_t *p,
		  r = (uint8_t)(color >> 16),
		  g = (uint8_t)(color >>  8),
		  b = (uint8_t)color;

		p = &pixels[pixel * 3];

		p[0] = g;
		p[1] = r;
		p[2] = b;

	}
}

void Ws2812::setPixelBrightness(uint8_t pixel, uint8_t bright) {
  if(pixel < numLEDs) {

    uint8_t *b;

    b = &brightness[pixel];

    b[0] = bright;
  }
}

void Ws2812::setAllColor(uint8_t red, uint8_t green, uint8_t blue) {

	for(int i = 0; i < numLEDs; i++) {
		setPixelColor(i,red,green,blue);
	}

}

void Ws2812::setAllColor(uint32_t color) {

	for(int i = 0; i < numLEDs; i++) {
		setPixelColor(i,color);
	}

}

// Convert separate R,G,B into packed 32-bit RGB color.
// Packed format is always RGB, regardless of LED strand color order.
uint32_t Ws2812::Color(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

uint8_t Ws2812::numPixels(void) const {
	return numLEDs;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(uint8_t WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return Ws2812::Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return Ws2812::Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return Ws2812::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}



