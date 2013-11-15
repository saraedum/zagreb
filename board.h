#ifndef BOARD_HPP
#define BOARD_HPP

#include <Adafruit_NeoPixel.h>

#include "util/color.h"

#define NO_PIXEL 255

class Board{
	protected:
	Adafruit_NeoPixel* const strip;
	Board(Adafruit_NeoPixel* const strip, const uint8_t width, const uint8_t height):strip(strip),width(width),height(height){
		strip->begin();
		strip->setBrightness(255);
		strip->show();
	}
	virtual uint8_t id(const uint8_t x, const uint8_t y) = 0;
	public:
	const uint8_t width;
	const uint8_t height;

	void set(const uint8_t x, const uint8_t y, const uint32_t color){
		strip->setPixelColor(id(x,y),color);
	}
	void set(const uint8_t x, const uint8_t y, const Color& color){
		strip->setPixelColor(id(x,y),color.r,color.g,color.b);
	}
	uint32_t get(const uint8_t x, const uint8_t y){
		return strip->getPixelColor(id(x,y));
	}
	bool has(const uint8_t x, const uint8_t y){
		return id(x,y)!=NO_PIXEL;
	}
	void show(){
		strip->show();
	}
	void setBrightness(const uint8_t brightness){
		strip->setBrightness(brightness);
	}
	void set(const uint32_t color){
		set(Color(color));
	}
	void set(const Color& color){
		for(uint8_t i=0;i<strip->numPixels();i++)
			strip->setPixelColor(i,color.r,color.g,color.b);
	}
};

#endif
