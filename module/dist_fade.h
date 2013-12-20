#ifndef DIST_FADE_H
#define DIST_FADE_H

#include "fade/fade.h"
#include "dist/dist.h"
#include "../wall.h"
#include "wall_module.h"
#include "../util/bpm.h"

class DistFade : public WallModule<DistFade> {
	private:
		Fade* const fade;
		Dist* const dist;
	public:
		DistFade(Wall* const wall, Fade* const fade, Dist* const dist):WallModule(wall),fade(fade),dist(dist){}
		inline void draw(){
			const uint32_t dst = dist->dist(x,y);
			const uint32_t t = (now() + dst*2000/dist->max_dist)*BPM/60;
			Color col = fade->color(t);
			wall->set(x,y,col);
		}
};

#endif
