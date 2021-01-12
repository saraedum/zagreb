#ifndef ZAGREB_PALETTE_RANDOM_PALETTE_HPP
#define ZAGREB_PALETTE_RANDOM_PALETTE_HPP

#include "../../util/hash.h"
#include "../../util/random.h"
#include "../util/color.h"
#include "palette.hpp"

namespace zagreb::palette {

class RandomPalette : public Palette {
    static constexpr uint8_t cache_size = 32;

    uint32_t seed;

		struct {
      uint16_t n;
      Color color;
    } cache[cache_size];


	protected:
		virtual Color color(Random& rand){
			return Color(hash(rand.random()) & 0xffffff);
		}
	public:
		RandomPalette(uint32_t seed):
      seed(seed) {}

		Color color(uint16_t n) override {
      auto& cached = cache[n % cache_size];
      if (cached.n != n) {
        Random rand(seed + n);

        cached.n = n;
        cached.color = color(rand);
      }

      return cached.color;
		}
};

}

#endif
