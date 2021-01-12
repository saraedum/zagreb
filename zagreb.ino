#define UNCONNECTED_ANALOG_PIN 5

#include <Adafruit_NeoPixel.h>
#include <AceRoutine.h>

#include <avr/power.h>

#include "inputs/linear_rotary_encoder.hpp"
#include "inputs/button.hpp"
#include "lights/white.hpp"
#include "lights/kit.hpp"
#include "lights/random_fades.hpp"
#include "lights/strobe.hpp"
#include "outputs/board.hpp"
#include "outputs/wall.hpp"
#include "palette/palette_rotation.hpp"
#include "palette/random_warm_palette.hpp"
#include "palette/black_palette.hpp"

const uint8_t pin3BoardLayout[] PROGMEM = {
  19, 18, 17, 16, 15,
  10, 11, 12, 13, 14,
   9,  8,  7,  6,  5,
   0,  1,  2,  3,  4,
};
const uint8_t pin5BoardLayout[] PROGMEM = {
  11, 10,  9,  8,
   4,  5,  6,  7,
   3,  2,  1,  0,
};
const uint8_t pin6BoardLayout[] PROGMEM = {
  19, 18, 17, 16, 15,
  10, 11, 12, 13, 14,
   9,  8,  7,  6,  5,
   0,  1,  2,  3,  4,
};
const uint8_t pin9BoardLayout[] PROGMEM = {
   0,  1,  2,  3,  4,
   9,  8,  7,  6,  5,
  10, 11, 12, 13, 14,
  19, 18, 17, 16, 15,
};
const uint8_t pin10BoardLayout[] PROGMEM = {
   0,  7,  8, 15,
   1,  6,  9, 14,
   2,  5, 10, 13,
   3,  4, 11, 12,
};
const uint8_t pin11BoardLayout[] PROGMEM = {
   0,  1,  2,  3,
   7,  6,  5,  4,
   8,  9, 10, 11,
  15, 14, 13, 12,
};

using namespace zagreb;

void runCoroutines() {}

template <typename Head, typename ...Tail>
void runCoroutines(Head& head, Tail&... tail) {
  head.runCoroutine();
  runCoroutines(tail...);
}

void setup(){
  Serial.begin(57600);
  outputs::Board pin3Board(3, 5, 4, pin3BoardLayout);
  outputs::Board pin5Board(5, 4, 3, pin5BoardLayout);
  outputs::Board pin6Board(6, 5, 4, pin6BoardLayout);
  outputs::Board pin9Board(9, 5, 4, pin9BoardLayout);
  outputs::Board pin10Board(10, 4, 4, pin10BoardLayout);
  outputs::Board pin11Board(11, 4, 4, pin11BoardLayout);

  outputs::Wall wall;
  wall.add(&pin3Board,  5, 0);
  wall.add(&pin5Board,  0, 0);
  wall.add(&pin6Board, 15, 0);
  wall.add(&pin9Board, 10, 0);
  wall.add(&pin10Board, 13, 4);
  wall.add(&pin11Board, 13, 8);

  inputs::LinearRotaryEncoder<uint8_t> brightness(A2, A3, 0, 255, &wall.brightness, 4);

  uint8_t MODE = 0;

  auto onModeSwitch = [](void* data) {
    uint8_t& mode = *static_cast<uint8_t*>(data);
    mode++;
  };

  inputs::Button modeSwitch(2, onModeSwitch, &MODE);

  while(true){ 
    switch(MODE) {
      case 0:
        {
          lights::White white(&wall);

          inputs::LinearRotaryEncoder<uint8_t> temperature(A0, A1, 0, 255, &white.temperature, 4);

          while(MODE == 0) runCoroutines(modeSwitch, white, temperature, brightness);
        }
        break;
      case 1:
        {
          lights::Kit kit(&wall);

          lights::Strobe strobe(&wall);

          auto onStrobeSwitch = [](void* data) {
            lights::Strobe& strobe = *static_cast<lights::Strobe*>(data);
            strobe.flash();
          };

          inputs::Button strobeSwitch(4, onStrobeSwitch, &strobe);

          inputs::LinearRotaryEncoder<float> speed(A0, A1, 0, .2, &kit.speed, .001);

          while(MODE == 1) runCoroutines(modeSwitch, kit, brightness, strobeSwitch, speed);
        }
        break;
      case 2:
        {
          lights::Kit kit(&wall);

          lights::Strobe strobe(&wall);

          auto onStrobeSwitch = [](void* data) {
            lights::Strobe& strobe = *static_cast<lights::Strobe*>(data);
            strobe.flash();
          };

          inputs::Button strobeSwitch(4, onStrobeSwitch, &strobe);

          inputs::LinearRotaryEncoder<float> speed(A0, A1, 0, .2, &kit.speed, .001);

          palette::RandomWarmPalette palette(hwrandom(UNCONNECTED_ANALOG_PIN));
          palette::PaletteRotation rotation(&palette, &kit.fill);

          while(MODE == 2) runCoroutines(modeSwitch, kit, brightness, strobeSwitch, speed, rotation);
        }
        break;
      case 3:
        {
          palette::RandomWarmPalette palette(hwrandom(UNCONNECTED_ANALOG_PIN));
          palette::BlackPalette<2, 1> black(&palette);

          lights::RandomFades fades(&wall, &black); 

          lights::Strobe strobe(&wall);

          auto onStrobeSwitch = [](void* data) {
            lights::Strobe& strobe = *static_cast<lights::Strobe*>(data);
            strobe.flash();
          };

          inputs::Button strobeSwitch(4, onStrobeSwitch, &strobe);

          inputs::LinearRotaryEncoder<float> speed(A0, A1, 0, .2, &fades.speed, .001);

          while(MODE == 3) runCoroutines(modeSwitch, fades, brightness, strobeSwitch, speed);
        }
        break;
      default:
        MODE = 0;
        break;
    }
  }
}

void loop() {}
