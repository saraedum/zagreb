#ifndef RANDOM_DIST_FADE_H
#define RANDOM_DIST_FADE_H

#include "composition.h"
#include "../module/palette/random_warm_palette.h"
#include "../module/palette/black_palette.h"
#include "../module/fade/linear_fade.h"
#include "../module/dist_fade.h"
#include "../module/dist/random_dist.h"

class RandomDistFade : public Composition {
	private:
		RandomWarmPalette pal;
		BlackPalette pal2;
		LinearFade fade;
		RandomDist dist;
		DistFade module;
	public:
		RandomDistFade(Wall* const wall):
			pal(hwrandom(UNCONNECTED_ANALOG_PIN)), 
			pal2(&pal, 3, 2), 
			fade(&pal2), 
			dist(wall->width, wall->height, hwrandom(UNCONNECTED_ANALOG_PIN)), 
			module(wall, &fade, &dist) {
			main = &module;
		}
};

#endif
