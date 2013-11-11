#ifndef RANDOM_PALETTE_H
#define RANDOM_PALETTE_H

#include "palette.h"
#include "../../util/random.h"

class RandomPalette : public Palette {
	private:
		const uint32_t seed;
	public:
		RandomPalette(uint32_t seed):seed(seed){}
	protected:
		virtual uint32_t color(uint32_t n){
			Random random(seed);
			random.skip(n-1);
			return random.randrange(0,0x1000000);
		}
};

#endif
