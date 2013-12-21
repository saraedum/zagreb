// vim:syntax=cpp
#include "util/profiler.h"

#include "wall.h"
#include "progmem_board.h"
#include <Adafruit_NeoPixel.h>

#define UNCONNECTED_ANALOG_PIN 5
#define BPM_PIN_0 A0
#define BPM_PIN_1 A1
#define BRIGHTNESS_PIN0 A2
#define BRIGHTNESS_PIN1 A3
#define MIC_PIN 4
#define BUTTON_PIN_0 2
#define BUTTON_PIN_1 4
uint8_t BRIGHTNESS = 255;
bool STROBO = false;
bool SOUND_BRIGHTNESS = true;
	Wall wall(25, 5);

#include "module/sound_energy.h"
SoundEnergy sound_energy;
#include "module/sound_brightness.h"
SoundBrightness sound_brightness(sound_energy);
#include "module/brightness.h"
#include "module/linear_rotary_encoder.h"
#include "module/control.h"

const uint8_t id3[] PROGMEM = {  12, 13,14,15,
                                 11, 10, 9, 8,
                                  4,  5, 6, 7,
                                  3,  2, 1, 0 };
Adafruit_NeoPixel* const strip3 = new Adafruit_NeoPixel(16, 3, NEO_GRB + NEO_KHZ800);
ProgmemBoard* const board3 = new ProgmemBoard(strip3, 4, 4, id3);

const uint8_t id5[] PROGMEM = { 15, 14, 5, 4,
                                16, 13, 6, 3,
                                17, 12, 7, 2,
                                18, 11, 8, 1,
								19, 10, 9, 0, };
Adafruit_NeoPixel* const strip5 = new Adafruit_NeoPixel(20, 5, NEO_GRB + NEO_KHZ800);
ProgmemBoard* const board5 = new ProgmemBoard(strip5, 4, 5, id5);

const uint8_t id6[] PROGMEM = { 15, 14,13,12,
                                 8,  9,10,11,
                                 7,  6, 5, 4,
                                 0,  1, 2, 3, };
Adafruit_NeoPixel* const strip6 = new Adafruit_NeoPixel(16, 6, NEO_GRB + NEO_KHZ800);
ProgmemBoard* const board6 = new ProgmemBoard(strip6, 4, 4, id6);

const uint8_t id9[] PROGMEM = { 4, 5, 14, 15,
								3, 6, 13, 16,
								2, 7, 12, 17,
								1, 8, 11, 18,
								0, 9, 10, 19, };
Adafruit_NeoPixel* const strip9 = new Adafruit_NeoPixel(20, 9, NEO_GRB + NEO_KHZ800);
ProgmemBoard* const board9 = new ProgmemBoard(strip9, 4, 5, id9);

const uint8_t id10[] PROGMEM = { 4, 5, 14, 15,
								3, 6, 13, 16,
								2, 7, 12, 17,
								1, 8, 11, 18,
								0, 9, 10, 19, };
Adafruit_NeoPixel* const strip10 = new Adafruit_NeoPixel(20, 10, NEO_GRB + NEO_KHZ800);
ProgmemBoard* const board10 = new ProgmemBoard(strip10, 4, 5, id10);

const uint8_t id11[] PROGMEM = { 18, 17, 16, 15,
								 11, 12, 13, 14,
								 10,  9,  8,  7,
								  4,  5,  6, NO_PIXEL,
								  3,  2,  1,  0, };
Adafruit_NeoPixel* const strip11 = new Adafruit_NeoPixel(19, 11, NEO_GRB + NEO_KHZ800);
ProgmemBoard* const board11 = new ProgmemBoard(strip11, 4, 5, id11);

Control control;
LinearRotaryEncoder<uint16_t> bpm_encoder(BPM_PIN_0, BPM_PIN_1, 1, 1000, &BPM, 1);
Brightness brightness_encoder(BRIGHTNESS_PIN0, BRIGHTNESS_PIN1);

void setup() {
	wall.add(board3,0,0);
	wall.add(board5,4,0);
	wall.add(board6,21,0);
	wall.add(board9,8,0);
	wall.add(board10,16,0);
	wall.add(board11,12,0);
}

void loop() {
	control.loop();
	Control::main->loop();
	bpm_encoder.loop();
	brightness_encoder.loop();
	if (SOUND_BRIGHTNESS){
		sound_energy.loop();
		sound_brightness.loop();
	}
}
