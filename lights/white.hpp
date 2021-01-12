#ifndef ZAGREB_LIGHTS_WHITE_HPP
#define ZAGREB_LIGHTS_WHITE_HPP

#include <AceRoutine.h>

#include "../outputs/wall.hpp"

namespace zagreb::lights {

class White : public ace_routine::Coroutine {
  outputs::Wall* wall;

  static uint32_t color(void* data, uint8_t x, uint8_t y) {
    const auto& self = *static_cast<White*>(data);
    const int32_t FF = 255;
    return (FF << 16) | ((FF - self.temperature / 3) << 8) | (FF - self.temperature);
  }

 public:
  White(outputs::Wall* wall) : wall(wall) {}

  int runCoroutine() override {
    COROUTINE_LOOP() {
      wall->paint(White::color, this);

      COROUTINE_DELAY(wall->FPS16_DELAY);
    }
  }

  unsigned char temperature = 207;
};

}


#endif
