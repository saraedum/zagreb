#ifndef ZAGREB_LIGHTS_STROBE_HPP
#define ZAGREB_LIGHTS_STROBE_HPP

#include <AceRoutine.h>

#include "../outputs/wall.hpp"

#include "../util/color.h"

namespace zagreb::lights {

class Strobe {
  outputs::Wall* wall;

  static uint32_t color(void* data, uint8_t x, uint8_t y) {
    return 0xffffff;
  }

 public:
  Strobe(outputs::Wall* wall) : wall(wall) {}

  void flash() {
    auto brightness = wall->brightness;

    wall->brightness = 255;

    for (int i = 0; i < outputs::Wall::MAX_BOARDS; i++)
      wall->paint(color, nullptr);

    delay(20);

    wall->brightness = brightness;
  }
};

}

#endif


