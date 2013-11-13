#ifndef BLACK_PALETTE_H
#define BLACK_PALETTE_H

#include "palette.h"

class BlackPalette : public Palette {
	private:
		Palette* const inner;
		const uint8_t colors,blacks;
	public:
		BlackPalette(Palette* const inner, uint8_t colors, uint8_t blacks):inner(inner),colors(colors),blacks(blacks){}
		virtual uint32_t color(uint32_t n){
			if (n%(colors+blacks)<blacks)
				return 0;
			return inner->color(n);
		}
};

#endif
