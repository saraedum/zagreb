#ifndef PALETTE_H
#define PALETTE_H

#include "../../util/color.h"

class Palette {
	public:
		virtual Color color(const uint8_t n) = 0;
};

#endif
