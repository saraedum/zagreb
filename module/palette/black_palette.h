#ifndef BLACK_PALETTE_H
#define BLACK_PALETTE_H

#include "palette.h"

class BlackPalette : public Palette {
	private:
		Palette* const inner;
		const uint8_t colors,blacks;
	public:
		BlackPalette(Palette* const inner, uint8_t colors, uint8_t blacks):inner(inner),colors(colors),blacks(blacks){}
		virtual Color color(const uint8_t n){
			if (n%(colors+blacks)<blacks)
				return Color(0);
			return inner->color(n);
		}
};

#endif
