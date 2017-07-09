/*
 *	WS2812 / NeoPixel implementation for STM32F0x microcontrollers.
 *	Assumes a 48MHz clock rate from the internal oscillator / PLL.
 *
 *  Likely to work with other STM32Fxx, provided clock rate is similar
 *  or timing is adjusted to suit.
 *
 *  Based off of the Adafruit NeoPixel library for Arduino.
 *
 *	This is a VERY basic implementation that relies on bit-banging the signal
 *	to the WS2812 LEDs, and the output waveforms are very rough - in some situations
 *	the signal may result in incorrect behaviour.
 *
 *	A better approach would use DMA to write out values to the LEDs - but this is
 *	what I have at the moment, hopefully it helps someone else get started.
 *
 * Example usage (see included example file for full example):
 *
 * 			#define WS2812_NUM 16
 * 			#define WS2812_PIN GPIO_PIN_5
 * 			#define WS2812_PORT GPIOA
 *
 * 			Ws2812 pixels = Ws2812(WS2812_NUM,WS2812_PIN,WS2812_PORT);
 *
 * 			pixels.begin();
 *
 * 			for(uint8_t i=0; i< pixels.numPixels(); i++) {
 *				pixels.setPixelColor(i, 100,100,100);
 *			}
 *
 *	Written by Chris Barr, 2016.
 */

#ifndef __ws2812
#define __ws2812

#include <Arduino.h>
#include <stdint.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

uint32_t Wheel(uint8_t WheelPos);

class Ws2812 {
public:
	Ws2812(uint8_t num, uint16_t pin);

	void begin(void);
	void show(void);
	void setPixelColor(uint8_t pixel, uint8_t red, uint8_t green, uint8_t blue);
	void setPixelColor(uint8_t pixel, uint32_t color);

	//helper functions to deal with entire strip at once
	void setAllColor(uint8_t red, uint8_t green, uint8_t blue);
	void setAllColor(uint32_t color);

	uint8_t numPixels(void) const;

	static uint32_t Color(uint8_t r, uint8_t g, uint8_t b);


private:

	bool begun;
	uint8_t *pixels;
	uint8_t numLEDs;

	uint16_t pin;

	void writeSPI(unsigned long value);

	inline void ws2812_writebit(uint8_t bit);
	inline void ws2812_writebit_high(void);
	inline void ws2812_writebit_low(void);
};

#define BIT0 (1 << 0)
#define BIT1 (1 << 1)
#define BIT2 (1 << 2)
#define BIT3 (1 << 3)
#define BIT4 (1 << 4)
#define BIT5 (1 << 5)
#define BIT6 (1 << 6)
#define BIT7 (1 << 7)
#define BIT8 (1 << 8)
#define BIT9 (1 << 9)
#define BIT10 (1 << 10)
#define BIT11 (1 << 11)
#define BIT12 (1 << 12)
#define BIT13 (1 << 13)
#define BIT14 (1 << 14)
#define BIT15 (1 << 15)
#define BIT16 (1 << 16)
#define BIT17 (1 << 17)
#define BIT18 (1 << 18)
#define BIT19 (1 << 19)
#define BIT20 (1 << 20)
#define BIT21 (1 << 21)
#define BIT22 (1 << 22)
#define BIT23 (1 << 23)
#define BIT24 (1 << 24)
#define BIT25 (1 << 25)
#define BIT26 (1 << 26)
#define BIT27 (1 << 27)
#define BIT28 (1 << 28)
#define BIT29 (1 << 29)
#define BIT30 (1 << 30)
#define BIT31 (1 << 31)

#endif
