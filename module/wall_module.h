#ifndef WallModule_H
#define WallModule_H

#include "delay_module.h"
#include "fps.h"

template <typename DerivedModule>
class WallModule : public DelayModule {
	protected:
		Wall* const wall;
		uint8_t x=0,y=0;
	private:
		uint32_t last;
		FPS fps;
		const uint8_t delay=HZ(60);
	public:
		WallModule(Wall* const wall):wall(wall),last(NOW){}
		virtual uint16_t loop_delayed(){
			if (x>=wall->width){
				x=0;
				y++;
			}
			if (y>=wall->height){
				y=0;
				NOW = millis();
				fps.loop();
				wall->show();
				if (last + delay < NOW)
					return 0;
				return last + delay - NOW;
			}else if(wall->has(x,y)){
				static_cast<DerivedModule*>(this)->draw();
			}
			x++;
			return 0;
		}
};

#endif
