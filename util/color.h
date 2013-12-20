#ifndef COLOR_H
#define COLOR_H

class Color{
	public:
		uint8_t r,g,b;
		Color(const uint8_t r, const uint8_t g, const uint8_t b):r(r),g(g),b(b){}
		Color(const uint32_t c):r((c>>16)&0xff),g((c>>8)&0xff),b(c&0xff){}
};

#endif
