#ifndef WallModule_H
#define WallModule_H

#include "delay_module.h"
#include "fps.h"

inline bool draw_stats(uint8_t x, uint8_t y);

uint8_t TEXT[][10] = {
	{
	 0b11111111,
	 0b11111111,
	 0b11000000,
	 0b11000000,
	 0b11111111,
	 0b11111111,
	 0b00000011,
	 0b00000011,
	 0b11111111,
	 0b11111111,
	},
	{
	 0b11111111,
	 0b11111111,
	 0b11000011,
	 0b11000011,
	 0b11000011,
	 0b11000011,
	 0b11000011,
	 0b11000011,
	 0b11111111,
	 0b11111111,
	},
	{
	 0b11000011,
	 0b11000011,
	 0b11000011,
	 0b11000011,
	 0b11000011,
	 0b11000011,
	 0b11000011,
	 0b11000011,
	 0b11111111,
	 0b11111111,
	},
	{
	 0b11000000,
	 0b11000000,
	 0b11000000,
	 0b11000000,
	 0b11000000,
	 0b11000000,
	 0b11000000,
	 0b11000000,
	 0b11111111,
	 0b11111111,
	},
};

template <typename DerivedModule>
class WallModule : public DelayModule {
	protected:
		Wall* const wall;
		uint8_t x=0,y=0;
	private:
		uint32_t last;
		FPS fps;
		const uint8_t delay=HZ(60);

		inline bool pre(uint8_t x, uint8_t y){
			if (y==0 && x < MODES){
				if (abs(now() - STATS_UNTIL) < 1000){
					Color c = Color(0,0,0);
					if (x==BRIGHTNESS_MODE)
						c.r = 255;
					if (x==BRIGHTNESS_DECAY)
						c.g = 255;
					if (x==mode() || is_cycle())
						c.b = 255;
					wall->set(x, y, c);
					return 1;
				}
			}
			return 0;
		}

		inline void post(uint8_t x, uint8_t y){
			if (is_boot())
				return;
			uint8_t c = mbeat()/1000%360;
			if (c < 4){
				if (!(TEXT[c][y]&(128>>x))){
					Color c = wall->get(x,y);
					wall->set(x,y,Color(c.r>>6,c.g>>6,c.b>>6));
				}
			}
		}

	public:
		WallModule(Wall* const wall):wall(wall),last(now()){}
		virtual uint16_t loop_delayed(){
			if (x>=wall->width){
				x=0;
				y++;
			}
			if (y>=wall->height){
				y=0;
				update_now();
				fps.loop();
				wall->show();
				if (last + delay < now())
					return 0;
				return last + delay - now();
			}else if(wall->has(x,y)){
				if (pre(x,y)){}
				else{
					static_cast<DerivedModule*>(this)->draw();
					post(x,y);
				}
			}
			x++;
			return 0;
		}
};

#endif
