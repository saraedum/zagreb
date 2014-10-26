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
uint16_t COLORS512 = 2048; // 4 colors are visible at a time
uint8_t BRIGHTNESS_DECAY = 0;
uint8_t BRIGHTNESS_MODE  = 0;
uint32_t STATS_UNTIL = 0;
uint32_t NEXT_CYCLE = 0;

#define FIRST_NON_BOOT_MODE 3
#define FIRST_NON_BORING_MODE 4
#define MODES 8
#define CYCLE_MASK 0b10000000
#define BOOT_MASK 0b01000000
#define MODE_MASK 0b00111111
#define CYCLE_DELAY 1000
#define CYCLE_INCREASE 8
#define CYCLE_LENGTH 60000L
uint8_t MODE = BOOT_MASK | (MODES-1);
bool is_cycle(){
	return MODE&CYCLE_MASK;
}

bool is_boot(){
	return MODE&BOOT_MASK;
}

uint8_t mode(){
	return MODE&MODE_MASK;
}

Wall wall(8, 8);

#include "module/sound_energy.h"
SoundEnergy sound_energy;
#include "module/sound_brightness.h"
SoundBrightness sound_brightness(sound_energy);
#include "module/brightness.h"
#include "module/linear_rotary_encoder.h"
#include "module/control.h"


const uint8_t id3[] PROGMEM = {
 3, 4,  11,  12,
 2, 5,  10,  13,
 1, 6,  9,  14,
 0, 7,  8,  15
};
Adafruit_NeoPixel* const strip3 = new Adafruit_NeoPixel(16, 3, NEO_GRB + NEO_KHZ800);
ProgmemBoard* const board3 = new ProgmemBoard(strip3, 4, 4, id3);

const uint8_t id5[] PROGMEM = {
 15, 14,  13,  12,
 8, 9,  10,  11,
 7, 6,  5,  4,
 0, 1,  2,  3
};
Adafruit_NeoPixel* const strip5 = new Adafruit_NeoPixel(16, 5, NEO_GRB + NEO_KHZ800);
ProgmemBoard* const board5 = new ProgmemBoard(strip5, 4, 4, id5);


const uint8_t id10[] PROGMEM = {
 3, 4,  11,  12,
 2, 5,  10,  13,
 1, 6,  9,  14,
 0, 7,  8,  15
};
Adafruit_NeoPixel* const strip10 = new Adafruit_NeoPixel(16, 10, NEO_GRB + NEO_KHZ800);
ProgmemBoard* const board10 = new ProgmemBoard(strip10, 4, 4, id10);


const uint8_t id11[] PROGMEM = {
 12, 11,  4,  3,
 13, 10,  5,  2,
 14, 9,  6,  1,
 15, 8,  7,  0
};

Adafruit_NeoPixel* const strip11 = new Adafruit_NeoPixel(16, 11, NEO_GRB + NEO_KHZ800);
ProgmemBoard* const board11 = new ProgmemBoard(strip11, 4, 4, id11);

Control control;
LinearRotaryEncoder<uint16_t> bpm_encoder(BPM_PIN_0, BPM_PIN_1, 1, 1000, &BPM, 1);
//Brightness brightness_encoder(BRIGHTNESS_PIN0, BRIGHTNESS_PIN1);
LinearRotaryEncoder<uint16_t> color_encoder(BRIGHTNESS_PIN0, BRIGHTNESS_PIN1, 128, 512*20, &COLORS512, 128);

void setup() {
	wall.add( board3,   4,  0);
	wall.add( board5,   4,  4);
	wall.add( board10,  0,  0);
	wall.add( board11,  0,  4);	
}

void loop() {
	control.loop();
	Control::main->loop();
	bpm_encoder.loop();
	//brightness_encoder.loop();
	color_encoder.loop();
	if (BRIGHTNESS_MODE){
		sound_energy.loop();
		sound_brightness.loop();
	}
}
