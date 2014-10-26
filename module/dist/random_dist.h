#ifndef RANDOM_DIST_H
#define RANDOM_DIST_H

#include "dist.h"
#include "../../util/random.h"
#include "../../util/assert.h"

class RandomDist : public Dist {
	private:
		uint8_t* d;
	public:
		RandomDist(const uint8_t width, const uint8_t height, const uint32_t seed):Dist(width,height){
			d = (uint8_t*)malloc(sizeof(uint8_t)*(uint16_t)width*(uint16_t)height);
			assert(d);
			Random rand(seed);
			for (uint32_t i=0;i<(uint16_t)width*(uint16_t)height;i++)
				d[i] = rand.randrange((uint32_t)0,(uint32_t)256);
			compute_max_dist();
		}
		virtual ~RandomDist(){
			free(d);
		}
		virtual uint32_t dist(const uint8_t x, const uint8_t y){
			return d[width*y + x];
		}
};

#endif
