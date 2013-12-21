#ifndef WHITE_H
#define WHITE_H

#include "composition.h"
#include "../module/solid_fade.h"
#include "../module/fade/no_fade.h"

class White : public Composition {
	private:
		NoFade white_fade;
		SolidFade module;
	public:
		White(Wall* const wall):white_fade(Color(255,255,255)), module(wall, &white_fade){
			main = &module;
		}
};

#endif
