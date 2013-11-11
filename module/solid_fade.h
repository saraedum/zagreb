#ifndef SOLID_FADE_H
#define SOLID_FADE_H

#include "delay_module.h"
#include "fade/fade.h"
#include "../wall.h"

class SolidFade : public DelayModule {
	private:
		Wall* const wall;
		Fade* const fade;
	public:
		SolidFade(Wall* const wall, Fade* const fade):wall(wall),fade(fade){}
		virtual uint32_t loop_delayed(){
			wall->set(fade->color(millis()));
			wall->show();
			return 20;
		}
};

#endif
