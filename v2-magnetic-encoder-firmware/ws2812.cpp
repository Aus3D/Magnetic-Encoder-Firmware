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

}

void Ws2812::begin(void) {

	if (pin == 0x00) {
		return;
	}
  SPI.begin();
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));

  //pinMode(pin, OUTPUT);

	begun = true;

}

void Ws2812::show() {
	if(!pixels) return;

  int Index;
  uint32_t Encoding=0;
  uint8_t SPI_Data[numLEDs*10];
  uint32_t SPI_index = 0;
  
	for(int i = 0; i < numLEDs; i++) {

    uint8_t *p;

    p = &pixels[i * 3];

    uint8_t green = p[0];//10;//p[0];
    uint8_t red = p[1];//10;//p[1];
    uint8_t blue = p[2];//244;//p[2];

    uint32_t colour = ((green << 16) + (red << 8) + blue);
    
    // Process the GREEN byte
    Index=0;
    Encoding=0;
    while (Index < 8)
    {
        Encoding = Encoding << 3;
        if (colour & BIT23)
        {
            Encoding |= 0b110;
        }
        else
        {
            Encoding |= 0b100;
        }
        colour = colour << 1;
        Index++;
        
    }    
    SPI_Data[SPI_index++] = ((Encoding >> 16) & 0xff);
    SPI_Data[SPI_index++] = ((Encoding >> 8) & 0xff);
    SPI_Data[SPI_index++] = (Encoding & 0xff);
    
    // Process the RED byte
    Index=0;
    Encoding=0;
    while (Index < 8)
    {
        Encoding = Encoding << 3;
        if (colour & BIT23)
        {
            Encoding |= 0b110;
        }
        else
        {
            Encoding |= 0b100;
        }
        colour = colour << 1;
        Index++;
        
    }    
    SPI_Data[SPI_index++] = ((Encoding >> 16) & 0xff);
    SPI_Data[SPI_index++] = ((Encoding >> 8) & 0xff);
    SPI_Data[SPI_index++] = (Encoding & 0xff);
    
    // Process the BLUE byte
    Index=0;
    Encoding=0;
    while (Index < 8)
    {
        Encoding = Encoding << 3;
        if (colour & BIT23)
        {
            Encoding |= 0b110;
        }
        else
        {
            Encoding |= 0b100;
        }
        colour = colour << 1;
        Index++;
        
    }    
    SPI_Data[SPI_index++] = ((Encoding >> 16) & 0xff);
    SPI_Data[SPI_index++] = ((Encoding >> 8) & 0xff);
    SPI_Data[SPI_index++] = (Encoding & 0xff);

	}

  // Now send out the 24 (x3) bits to the SPI bus
  SPI.transfer(SPI_Data,numLEDs*9);

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

#pragma GCC push_options
#pragma GCC optimize ("O0")

inline void Ws2812::ws2812_writebit(uint8_t bit) {
	if(bit == 1) {
		ws2812_writebit_high();
	}
	else {
		ws2812_writebit_low();
	}
}

inline void Ws2812::ws2812_writebit_high() {

	digitalWrite(pin, HIGH);


	//all delays found by trial-and-error, should be improved with proper delay function / timer
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");

	digitalWrite(pin, LOW);

	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
}

inline void Ws2812::ws2812_writebit_low() {

	digitalWrite(pin, HIGH);

	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");

	digitalWrite(pin, LOW);

	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
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



