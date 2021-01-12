#ifndef ZAGREB_PALETTE_RANDOM_WARM_PALETTE_HPP
#define ZAGREB_PALETTE_RANDOM_WARM_PALETTE_HPP

#include "random_palette.hpp"

namespace zagreb::palette {

class RandomWarmPalette : public RandomPalette {
		double sigma;

	public:
		// the warm colors, i.e., colors with Hue in the range [330,80], are mapped to the range [-1,1]. Setting sigma=1 means that about 70% of the colors are taken from that range.
    RandomWarmPalette(uint32_t seed, double sigma=1):
      RandomPalette(seed),
      sigma(sigma) {
    }

    using RandomPalette::color;

    Color color(Random& rand) {
			double h = rand.gauss_clamp(25,55*sigma,25-180,25+180);
			double s = rand.gauss_clamp(1,.1,0,1);
			double v = rand.gauss_clamp(1,.1,0,1);
			return Color::HSV(h,s,v);
    }
};

}

#endif
