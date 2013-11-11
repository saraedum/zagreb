#ifndef LINEAR_FADE_H
#define LINEAR_FADE

#include "fade.h"
#include "../../util/color.h"

class LinearFade : public Fade {
	public:
		LinearFade(Palette* const palette):Fade(palette){}
	protected:
		virtual uint32_t color(const uint32_t t){
			const uint32_t color0 = palette->color(t/1000);
			const uint32_t color1 = palette->color(t/1000 + 1);
			const uint32_t red =   ( t%1000 * ((color1 >> 16) & 0xff) + (1000-t%1000) * ((color0 >> 16) & 0xff) )/1000;
			const uint32_t green = ( t%1000 * ((color1 >>  8) & 0xff) + (1000-t%1000) * ((color0 >>  8) & 0xff) )/1000;
			const uint32_t blue =  ( t%1000 * ((color1 >>  0) & 0xff) + (1000-t%1000) * ((color0 >>  0) & 0xff) )/1000;
			return COLOR(red,green,blue);
		}
};

#endif
