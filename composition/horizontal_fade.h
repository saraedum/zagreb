#ifndef HORIZONTAL_FADE_H
#define HORIZONTAL_FADE_H

#include "composition.h"
#include "../module/palette/random_warm_palette.h"
#include "../module/palette/black_palette.h"
#include "../module/fade/linear_fade.h"
#include "../module/dist_fade.h"
#include "../module/dist/horizontal_dist.h"

class HorizontalFade : public Composition {
	private:
		RandomWarmPalette pal;
		BlackPalette pal2;
		LinearFade fade;
		HorizontalDist dist;
		DistFade module;
	public:
		HorizontalFade(Wall* const wall):pal(hwrandom(UNCONNECTED_ANALOG_PIN)), pal2(&pal, 3, 2), fade(&pal2), dist(wall->width, wall->height) , module(wall, &fade, &dist) {
			main = &module;
		}
};

#endif
