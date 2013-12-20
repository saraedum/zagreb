#ifndef VERTICAL_FADE_H
#define VERTICAL_FADE_H

#include "composition.h"
#include "../module/palette/random_palette.h"
#include "../module/palette/black_palette.h"
#include "../module/fade/linear_fade.h"
#include "../module/dist_fade.h"
#include "../module/dist/vertical_dist.h"

class VerticalFade : public Composition {
	private:
		RandomPalette pal;
		BlackPalette pal2;
		LinearFade fade;
		VerticalDist dist;
		DistFade module;
	public:
		VerticalFade(Wall* const wall):pal(hwrandom(UNCONNECTED_ANALOG_PIN)), pal2(&pal, 3, 2), fade(&pal2), dist(wall->height, wall->width) , module(wall, &fade, &dist) {
			main = &module;
		}
};

#endif
