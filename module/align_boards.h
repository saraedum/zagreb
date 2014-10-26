#ifndef ALIGN_BOARDS_H
#define ALIGN_BOARDS_H

#include "wall_module.h"

class AlignBoards : public WallModule<AlignBoards> {
	public:
		AlignBoards(Wall* const wall):WallModule(wall){}
		inline void draw(){
			uint16_t r = (256*x)/wall->width;
			uint16_t g = (256*y)/wall->height;
			uint16_t b = g;
			wall->set(x, y, Color(r, g, b));
		}
};

#endif
