#ifndef COLOR_H
#define COLOR_H

class Color{
	public:
		uint8_t r,g,b;
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
};

#endif
