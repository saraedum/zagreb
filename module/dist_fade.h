#ifndef DIST_FADE_H
#define DIST_FADE_H

#include "fade/fade.h"
#include "dist/dist.h"
#include "../wall.h"
#include "wall_module.h"

class DistFade : public WallModule<DistFade> {
	private:
		Fade* const fade;
		Dist* const dist;
		const uint32_t scale;
	public:
		DistFade(Wall* const wall, Fade* const fade, Dist* const dist, uint32_t scale=2000):WallModule(wall),fade(fade),dist(dist),scale(scale){}
		inline void draw(){
			const uint32_t dst = dist->dist(x,y);
			const uint32_t t = (NOW + dst*scale/dist->max_dist)/4;
			Color col = fade->color(t);
			wall->set(x,y,col);
		}
};

#endif
