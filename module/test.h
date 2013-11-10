#ifndef TEST_H
#define TEST_H

#include "../color.h"
#include "delay_module.h"
#include <Adafruit_NeoPixel.h>

class Test : public DelayModule {
	Adafruit_NeoPixel* const strip;
	uint8_t i;
	const uint32_t RED = COLOR(255,0,0);
	const uint32_t BLACK = COLOR(0,0,0);
	public:
	Test(Adafruit_NeoPixel* const strip):strip(strip),i(0){}
	virtual int loop_delayed(){
		strip->setPixelColor(i, strip->getPixelColor(i)==RED?BLACK:RED);
		strip->show();
		i++;
		i%=strip->numPixels();
		return 100;
	}
};

#endif
