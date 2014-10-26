#ifndef RANDOM_PALETTE_H
#define RANDOM_PALETTE_H

#include "../../util/assert.h"
#include "palette.h"
#include "../../util/hash.h"
#include "../../util/random.h"

class RandomPalette : public Palette {
	private:
		Color *palette;
		uint8_t size;
		uint8_t active_size;
		uint8_t oldest_survivor;
	protected:
		Random rand;
		virtual Color random_color(){
			return Color(hash(rand.random()) & 0xffffff);
		}
	public:
		RandomPalette(uint32_t seed, uint8_t size=32):size(size),active_size(size/2),oldest_survivor(0),rand(seed){
			palette = (Color*)malloc(size*sizeof(Color));
			assert(palette);
			//for(uint32_t n=0;n<size;n++)
			//	palette[n] = Color(hash(n + seed) & 0xffffff);
		}
		virtual ~RandomPalette(){
			free(palette);
		}
		virtual Color color(const uint8_t n){
			uint8_t dist = n-oldest_survivor;
			if (dist >= active_size){
				for (uint8_t i=oldest_survivor+active_size;i!=n+1;i++){
					palette[i%size] = random_color();
				}
				oldest_survivor = n-active_size+1;
			}
			return palette[n%size];
		}
};

#endif
