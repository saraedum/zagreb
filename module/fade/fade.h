#ifndef FADE_H
#define FADE_H

#include "../palette/palette.h"

class Fade {
	protected:
		Palette* const palette;
	public:
		Fade(Palette* const palette):palette(palette){}
		virtual uint32_t color(const uint32_t t) = 0;
};

#endif
