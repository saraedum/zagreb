#ifndef RANDOM_PALETTE_H
#define RANDOM_PALETTE_H

#include "palette.h"
#include "../../util/hash.h"

class RandomPalette : public Palette {
	private:
		const uint32_t seed;
	public:
		RandomPalette(uint32_t seed):seed(seed){}
	protected:
		virtual uint32_t color(uint32_t n){
			return hash(n + seed) & 0xffffff;
		}
};

#endif
