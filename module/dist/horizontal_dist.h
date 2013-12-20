#ifndef HORIZONTAL_DIST_H
#define HORIZONTAL_DIST_H

#include "dist.h"
#include "../../util/assert.h"

class HorizontalDist : public Dist {
	public:
		HorizontalDist(const uint32_t width, const uint32_t height):Dist(width,height){
			compute_max_dist();
		}
		virtual uint32_t dist(const uint8_t x, const uint8_t y){
			return x+1;
		}
};

#endif
