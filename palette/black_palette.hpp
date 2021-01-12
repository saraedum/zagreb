#ifndef ZAGREB_PALETTE_BLACK_PALETTE_HPP
#define ZAGREB_PALETTE_BLACK_PALETTE_HPP

#include "palette.hpp"

namespace zagreb::palette {

template <uint8_t colors = 1, uint8_t blacks = 1>
class BlackPalette : public Palette {
	private:
		Palette* const inner;
	public:
		BlackPalette(Palette* const inner):
      inner(inner) {
    }

		Color color(const uint16_t n) override {
			if (n%(colors+blacks)<blacks)
				return Color();
			return inner->color(n);
		}
};

}

#endif
