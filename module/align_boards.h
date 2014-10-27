#ifndef ALIGN_BOARDS_H
#define ALIGN_BOARDS_H

#include "wall_module.h"

class AlignBoards : public WallModule<AlignBoards> {
	public:
		AlignBoards(Wall* const wall):WallModule(wall){}
		inline void draw(){
			double x_ = x-wall->width/2.;
			double y_ = y-wall->height/2.;
			double h = atan2(y_,x_)/3.141592/2.*360.;
			x_ = 2*x_/wall->width;
			y_ = 2*y_/wall->height;
			double s = sqrt(x_*x_ + y_*y_);
			Color c = Color::HSV(h, s, 1);
			if (y==mbeat()*wall->width/1000/wall->width % wall->height){
				if (x!=mbeat()*wall->width/1000 % wall->width){
					c = Color(c.r>>4,c.g>>4,c.b>>4);
				}
			}
			wall->set(x, y, c);
		}
};

#endif
