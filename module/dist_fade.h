#ifndef DIST_FADE_H
#define DIST_FADE_H

#include "delay_module.h"
#include "fade/fade.h"
#include "dist/dist.h"
#include "../wall.h"

class DistFade : public DelayModule {
	private:
		Wall* const wall;
		Fade* const fade;
		Dist* const dist;
		const uint32_t scale;
	public:
		DistFade(Wall* const wall, Fade* const fade, Dist* const dist, uint32_t scale=2000):wall(wall),fade(fade),dist(dist),scale(scale){}
		virtual uint32_t loop_delayed(){
			for (uint8_t y=0;y<wall->height;y++){
				for (uint8_t x=0;x<wall->width;x++){
					if (!wall->has(x,y))
						continue;
					wall->set(x,y,fade->color(NOW + dist->dist(x,y)*scale/dist->max_dist)); // set takes 23µs
				}
			}
			wall->show();
			return HZ(50);
		}
};

#endif
