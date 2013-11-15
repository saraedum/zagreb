#ifndef FADE_H
#define FADE_H

#include "../../util/color.h"
#include "../palette/palette.h"

class Fade {
	protected:
		Palette* const palette;
	public:
		Fade(Palette* const palette):palette(palette){}
		virtual Color color(const uint32_t t) = 0;
};

#endif
