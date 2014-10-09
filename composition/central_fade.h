#ifndef CENTRAL_FADE_H
#define CENTRAL_FADE_H

#include "composition.h"
#include "../module/palette/random_palette.h"
#include "../module/palette/black_palette.h"
#include "../module/fade/linear_fade.h"
#include "../module/dist_fade.h"
#include "../module/dist/central_dist.h"

class CentralFade : public Composition {
	private:
		RandomPalette pal;
		BlackPalette pal2;
		LinearFade fade;
		CentralDist dist;
		DistFade module;
	public:
		CentralFade(Wall* const wall):pal(hwrandom(UNCONNECTED_ANALOG_PIN)), pal2(&pal, 3, 2), fade(&pal2), dist(wall->height, wall->width) , module(wall, &fade, &dist) {
			main = &module;
		}
};

#endif