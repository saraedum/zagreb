#ifndef TEST_WALL_H
#define TEST_WALL_H

#include "../util/color.h"
#include "delay_module.h"

class TestWall : public DelayModule {
	Wall* const wall;
	uint8_t x=0,y=0;
	const uint32_t delay;
	const uint32_t RED = COLOR(255,0,0);
	const uint32_t BLACK = COLOR(0,0,0);
	public:
	TestWall(Wall* const wall):wall(wall),delay(delay){}
	virtual void setup(){
		wall->set(BLACK);
	}
	virtual int loop_delayed(){
		if (wall->has(x,y)){
			wall->set(x,y,wall->get(x,y)==RED?BLACK:RED);
		}
		wall->show();

		x++;
		if (x>=wall->width){
			x=0;
			y++;
		}
		y%=wall->height;

		return 10;
	}
};

#endif
