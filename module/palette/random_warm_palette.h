#ifndef RANDOM_WARM_PALETTE_H
#define RANDOM_WARM_PALETTE_H

#include "random_palette.h"

class RandomWarmPalette : public RandomPalette {
	private:
		double sigma;
	protected:
		virtual Color random_color(){
			double h = rand.gauss_clamp(25,55*sigma,25-180,25+180);
			double s = rand.gauss_clamp(1,.1,0,1);
			double v = rand.gauss_clamp(1,.1,0,1);
			return Color::HSV(h,s,v);
		}
	public:
		RandomWarmPalette(uint32_t seed, uint8_t size=32, double sigma=1):RandomPalette(seed, size),sigma(sigma){} // the warm colors, i.e., colors with Hue in the range [330,80], are mapped to the range [-1,1]. Setting sigma=1 means that about 70% of the colors are taken from that range.
};

#endif
