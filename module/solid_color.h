#ifndef SOLID_COLOR_H
#define SOLID_COLOR_H

#include "wall_module.h"

class SolidColor : public WallModule<SolidColor> {
	private:
		const Color color;
	public:
		SolidColor(Wall* const wall, const Color color):WallModule(wall),color(color){}
		virtual void draw(){
			Color color = this->color;
			if (SOUND_BRIGHTNESS)
				color.scale(sound_brightness.brightness);
			wall->set(x,y,color);
		}
};

#endif
