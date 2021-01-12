#ifndef COLOR_H
#define COLOR_H

class Color{
	public:
		uint8_t r,g,b;
    Color():Color(0) {}
		Color(const uint8_t r, const uint8_t g, const uint8_t b):r(r),g(g),b(b){}
		Color(const uint32_t c):r((c>>16)&0xff),g((c>>8)&0xff),b(c&0xff){}
		void scale(const uint8_t brightness){
			r = ((uint16_t)r*(uint16_t)brightness)>>8;
			g = ((uint16_t)g*(uint16_t)brightness)>>8;
			b = ((uint16_t)b*(uint16_t)brightness)>>8;
		}
		uint32_t color(){
			return (((uint32_t)r)<<16) | (((uint32_t)g)<<8) | (uint32_t)b;
		}
		static Color HSV(double h, double s, double v){
			while (h>=360)
				h-=360;
			while (h<0)
				h+=360;
			if (s<0) s=0;
			if (s>1) s=1;
			if (v<0) v=0;
			if (v>1) v=1;
			double c = v*s;
			double hh = h/60;
			double hhh = hh;
			while (hhh>2) hhh-=2;
			double x = c*(1-abs(hhh-1));
			double r1,g1,b1;
			if (hh<1){
				r1 = c; g1 = x; b1 = 0;
			}else if(hh<2){
				r1 = x; g1 = c; b1 = 0;
			}else if(hh<3){
				r1 = 0; g1 = c; b1 = x;
			}else if(hh<4){
				r1 = 0; g1 = x; b1 = c;
			}else if(hh<5){
				r1 = x; g1 = 0; b1 = c;
			}else{
				r1 = c; g1 = 0; b1 = x;
			}
			double m = v - c;
			uint8_t r = (r1+m)*255.999;
			uint8_t g = (g1+m)*255.999;
			uint8_t b = (b1+m)*255.999;
			return Color(r,g,b);
		}
};

#endif
