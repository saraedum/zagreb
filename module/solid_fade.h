#ifndef SOLID_FADE_H
#define SOLID_FADE_H

#include "fade/fade.h"
#include "wall_module.h"

class SolidFade : public WallModule<SolidFade> {
	private:
		Fade* const fade;
	public:
		SolidFade(Wall* const wall, Fade* const fade):WallModule(wall),fade(fade){}
		virtual void draw(){
			Color color = fade->color(millis());
			if (SOUND_BRIGHTNESS)
				color.scale(sound_brightness.brightness);
			wall->set(x,y,color);
		}
};

#endif
