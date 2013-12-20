#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include "linear_rotary_encoder.h"

class Brightness : public LinearRotaryEncoder<uint8_t> {
	public:
		Brightness(int pin0, int pin1):LinearRotaryEncoder(pin0, pin1, 0, 255, &BRIGHTNESS, 8){}
	protected:
		virtual void on_change(){
			wall.setBrightness(BRIGHTNESS);
		}
};

#endif
