#ifndef LINEAR_FADE_H
#define LINEAR_FADE_H

#include "fade.h"
#include "../../util/color.h"

class LinearFade : public Fade {
	private:
		inline uint8_t mix(uint8_t c1, uint8_t c2, uint8_t lambda){ // weighted average of two bytes without overflow
			return (c1>c2)?
				(((c1-c2)>>4) * (lambda>>4) + c2):
				(((c2-c1)>>4) * ((0xff-lambda)>>4) + c1);
		}
	public:
		LinearFade(Palette* const palette):Fade(palette){}
		virtual Color color(const uint32_t t){
			const uint8_t slot = (t>>8)&0xff;
			const Color color0 = palette->color(slot);
			const Color color1 = palette->color(slot + 1);
			return Color(mix(color1.r,color0.r,t),
					     mix(color1.g,color0.g,t),
						 mix(color1.b,color0.b,t));
		}
};

#endif
