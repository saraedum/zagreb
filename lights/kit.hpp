#ifndef ZAGREB_LIGHTS_KIT_HPP
#define ZAGREB_LIGHTS_KIT_HPP

#include <AceRoutine.h>

#include "../outputs/wall.hpp"

#include "../util/color.h"

namespace zagreb::lights {

class Kit : public ace_routine::Coroutine {
  outputs::Wall* wall;

  float angle = 0;
  float pos = 0;

  static uint32_t color(void* data, uint8_t x, uint8_t y) {
    const auto& self = *static_cast<Kit*>(data);

    Color c(self.fill);
    c.scale(255 * max(0, 1 - abs(x - self.pos)));
    return c.color();
  }

 public:
  float speed = .03;

  Color fill = 0xff0000;

  Kit(outputs::Wall* wall) : wall(wall) {}

  int runCoroutine() override {
    COROUTINE_LOOP() {
      angle += speed;

      pos = (sin(angle) + 1) / 2 * (wall->width - 1);

      wall->paint(Kit::color, this);

      COROUTINE_DELAY(wall->FPS16_DELAY);
    }
  }

  unsigned char temperature = 207;
};

}

#endif

