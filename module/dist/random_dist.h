#ifndef RANDOM_DIST_H
#define RANDOM_DIST_H

#include "dist.h"

class RandomDist : public Dist {
	private:
		uint8_t* d;
	public:
		RandomDist(const uint32_t width, const uint32_t height, const uint32_t seed):Dist(width,height){
			d = (uint8_t*)malloc(sizeof(uint8_t)*width*height);
			Random rand(seed);
			for (uint32_t i=0;i<width*height;i++)
				d[i] = rand.randrange(0,255);
			compute_max_dist();
		}
		virtual uint32_t dist(const uint8_t x, const uint8_t y){
			return d[width*y + x];
		}
};

#endif
