#ifndef PROGMEM_BOARD_HPP
#define PROGMEM_BOARD_HPP

#include "board.h"
#include <Adafruit_NeoPixel.h>
#include <avr/pgmspace.h>

class ProgmemBoard : public Board {
	private:
	const uint8_t* ids;
	protected:
	virtual uint8_t id(const uint8_t x, const uint8_t y){
		return pgm_read_byte(&(ids[y*width+x]));
	}
	public:
	ProgmemBoard(Adafruit_NeoPixel* const strip, const uint8_t width, const uint8_t height, const uint8_t* ids) : Board(strip, width, height), ids(ids){
	}
};

#endif
