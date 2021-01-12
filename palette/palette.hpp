#ifndef ZAGREB_PALETTE_PALETTE_HPP
#define ZAGREB_PALETTE_PALETTE_HPP

#include "../util/color.h"

namespace zagreb::palette {

class Palette {
	public:
		virtual Color color(const uint16_t n) = 0;
};

}

#endif
