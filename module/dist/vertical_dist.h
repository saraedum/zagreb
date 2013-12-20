#ifndef VERTICAL_DIST_H
#define VERTICAL_DIST_H

#include "dist.h"
#include "../../util/assert.h"

class VerticalDist : public Dist {
	public:
		VerticalDist(const uint32_t width, const uint32_t height):Dist(width,height){
			compute_max_dist();
		}
		virtual uint32_t dist(const uint8_t x, const uint8_t y){
			return y+1;
		}
};

#endif
