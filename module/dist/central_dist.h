#ifndef CENTRAL_DIST_H
#define CENTRAL_DIST_H

#include "dist.h"
#include "../../util/assert.h"

class CentralDist : public Dist {
	private:
		uint32_t offset;
	public:
		CentralDist(const uint32_t width, const uint32_t height):Dist(width,height),offset(width*width+height*height){
			compute_max_dist();
		}
		virtual uint32_t dist(const uint8_t x, const uint8_t y){
			int16_t x_ = width - 1 - (int16_t)2*x;
			int16_t y_ = height - 1 - (int16_t)2*y;
			return offset - x_*x_ - y_*y_;
		}
};

#endif
