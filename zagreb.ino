// vim:syntax=cpp
#include "wall.h"
#include "progmem_board.h"
#include <Adafruit_NeoPixel.h>

//#include "module/test_strip.h"
//#include "module/test_wall.h"
//#include "module/solid_fade.h"
#include "module/fade/linear_fade.h"
#include "module/palette/random_palette.h"
#include "module/palette/black_palette.h"
#include "module/dist/random_dist.h"
#include "module/dist_fade.h"
#include "module/fps.h"
#include "util/now.h"

#define UNCONNECTED_ANALOG_PIN 5

const uint8_t id3[] PROGMEM = { 15, 14, 5, 4,
                                16, 13, 6, 3,
                                17, 12, 7, 2,
                                18, 11, 8, 1,
                                19, 10, 9, 0, };
Adafruit_NeoPixel* const strip3 = new Adafruit_NeoPixel(20, 3, NEO_GRB + NEO_KHZ800);
ProgmemBoard* const board3 = new ProgmemBoard(strip3, 4, 5, id3);

const uint8_t id5[] PROGMEM = { 19, 10, 9, 0,
                                18, 11, 8, 1,
                                17, 12, 7, 2,
                                16, 13, 6, 3,
								15, 14, 5, 4, };
Adafruit_NeoPixel* const strip5 = new Adafruit_NeoPixel(20, 5, NEO_GRB + NEO_KHZ800);
ProgmemBoard* const board5 = new ProgmemBoard(strip5, 4, 5, id5);

const uint8_t id6[] PROGMEM = { 4, 5, 14, 15,
								3, 6, 13, 16,
								2, 7, 12, 17,
								1, 8, 11, 18,
								0, 9, 10, 19, };
Adafruit_NeoPixel* const strip6 = new Adafruit_NeoPixel(20, 6, NEO_GRB + NEO_KHZ800);
ProgmemBoard* const board6 = new ProgmemBoard(strip6, 4, 5, id6);

const uint8_t id9[] PROGMEM = { 8, 9, 10, 11,
								7, 6,  5,  4,
								0, 1,  2,  3, };
Adafruit_NeoPixel* const strip9 = new Adafruit_NeoPixel(12, 9, NEO_GRB + NEO_KHZ800);
ProgmemBoard* const board9 = new ProgmemBoard(strip9, 4, 3, id9);

const uint8_t id10[] PROGMEM = { 0,
								 1,
								 2,
								 3,
								 4,
								 5,
								 6,
								 7,
								 8,
								 9, };
Adafruit_NeoPixel* const strip10 = new Adafruit_NeoPixel(10, 10, NEO_GRB + NEO_KHZ800);
ProgmemBoard* const board10 = new ProgmemBoard(strip10, 1, 10, id10);

const uint8_t id11[] PROGMEM = { 18, 17, 16, 15,
								 11, 12, 13, 14,
								 10,  9,  8,  7,
								  4,  5,  6, NO_PIXEL,
								  3,  2,  1,  0, };
Adafruit_NeoPixel* const strip11 = new Adafruit_NeoPixel(19, 11, NEO_GRB + NEO_KHZ800);
ProgmemBoard* const board11 = new ProgmemBoard(strip11, 4, 5, id11);

Wall wall(13, 10);

void setup() {

	wall.add(board3,0,0);
	wall.add(board5,0,5);
	wall.add(board6,4,0);
	wall.add(board9,8,0);
	wall.add(board10,12,0);
	wall.add(board11,4,5);
	RandomPalette pal(analogRead(UNCONNECTED_ANALOG_PIN));
	BlackPalette pal2(&pal, 3, 2);
	LinearFade fade(&pal2);
	//SolidFade m(&wall, &fade);
	RandomDist dist(wall.height,wall.width,analogRead(UNCONNECTED_ANALOG_PIN));
	DistFade m(&wall, &fade, &dist);
	//TestWall t(&wall);
	//t.setup();
	m.setup();
	FPS fps;
	while(1){
		NOW = millis();
		m.loop();
		fps.loop();
	}
	m.shutdown();
}

void loop() {}
