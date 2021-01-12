#ifndef ZAGREB_LIGHTS_RANDOM_FADE_HPP
#define ZAGREB_LIGHTS_RANDOM_FADE_HPP

#include <AceRoutine.h>

#include "../outputs/wall.hpp"
#include "../palette/palette.hpp"
#include "../util/color.h"
#include "../util/hash.h"

namespace zagreb::lights {

class RandomFades : public ace_routine::Coroutine {
  outputs::Wall* wall;
  palette::Palette* palette;

  float pos = 0;

  static uint8_t hash4(uint8_t x, uint8_t y) {
	  uint16_t ret = x;
	  ret += (ret << 10);
	  ret ^= (ret >> 6);
	  ret += y;
    ret += (ret << 3);
    ret ^= (ret >> 11);
    return ret % 4;
  }

  static uint32_t color(void* data, uint8_t x, uint8_t y) {
    const auto& self = *static_cast<RandomFades*>(data);

    const uint16_t n = hash4(x, y) + static_cast<uint16_t>(self.pos);

    Color a = self.palette->color(n);
    Color b = self.palette->color(n + 1);

    float rel = self.pos - floor(self.pos);

    a.scale(255 * (1 - rel));
    b.scale(255 * rel);

    return a.color() + b.color();
  }

 public:
  float speed = .03;

  RandomFades(outputs::Wall* wall, palette::Palette* palette):
    wall(wall),
    palette(palette) {
  }

  int runCoroutine() override {
    COROUTINE_LOOP() {
      // auto a = micros();
      pos += speed;

      wall->paint(RandomFades::color, this);

      // Serial.println(micros() - a);

      COROUTINE_DELAY(wall->FPS16_DELAY);
    }
  }
};

}

#endif
