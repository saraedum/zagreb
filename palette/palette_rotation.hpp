#ifndef ZAGREB_PALETTE_PALETTE_ROTATION_HPP
#define ZAGREB_PALETTE_PALETTE_ROTATION_HPP

#include <AceRoutine.h>

#include "ace_routine/Coroutine.h"
#include "random_warm_palette.hpp"

namespace zagreb::palette {

class PaletteRotation : public ace_routine::Coroutine {
  RandomWarmPalette* palette;
  Color* value;

  int16_t n = 0;

 public:
  PaletteRotation(RandomWarmPalette* palette, Color* value):
    palette(palette),
    value(value) {}

  int runCoroutine() override {
    COROUTINE_LOOP() {
      *value = palette->color(n++);

      COROUTINE_DELAY(1000);
    }
  }
};

}

#endif
