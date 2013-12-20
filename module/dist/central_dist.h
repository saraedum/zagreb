#ifndef CENTRAL_DIST_H
#define CENTRAL_DIST_H

#include "dist.h"
#include "../../util/assert.h"

class CentralDist : public Dist {
	public:
		CentralDist(const uint32_t width, const uint32_t height):Dist(width,height){
			compute_max_dist();
		}
		virtual uint32_t dist(const uint8_t x, const uint8_t y){
			return width*2 - x + height*2 - y;
		}
};

#endif
