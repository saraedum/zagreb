#ifndef RANDOM_PALETTE_H
#define RANDOM_PALETTE_H

#include "palette.h"
#include "../../util/hash.h"

class RandomPalette : public Palette {
	private:
		uint32_t *palette;
		uint8_t size;
	public:
		RandomPalette(uint32_t seed, uint8_t size=256):size(size){
			palette = (uint32_t*)malloc(size*sizeof(uint32_t));
			for(uint32_t n=0;n<size;n++)
				palette[n] = hash(n + seed) & 0xffffff;
		}
		~RandomPalette(){
			free(palette);
		}
		virtual uint32_t color(const uint8_t n){
			return palette[n%size];
		}
};

#endif
