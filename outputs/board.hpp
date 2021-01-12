#ifndef ZAGREB_OUTPUTS_BOARD_HPP
#define ZAGREB_OUTPUTS_BOARD_HPP

#include <avr/pgmspace.h>

#include <Adafruit_NeoPixel.h>

namespace zagreb::outputs {

class Board {
 public:
  const uint8_t width;
  const uint8_t height;

 private:
  const uint8_t* matrix;

  Adafruit_NeoPixel strip;

  uint8_t index(uint8_t x, uint8_t y) {
		return pgm_read_byte(&(matrix[y * width + x]));
  }

 public:
  static constexpr uint8_t LED_MISSING = 255;

  Board(uint8_t pin, uint8_t width, uint8_t height, const uint8_t* matrix): 
    width(width),
    height(height),
    matrix(matrix),
    strip([&](){
      uint8_t length = 0;
      for (uint8_t y = 0; y < height; y++)
        for (uint8_t x = 0; x < width; x++)
          if (has(x, y)) length++;
      return length;
    }(), pin, NEO_GRB + NEO_KHZ800) {
    strip.begin();
    strip.setBrightness(255);
    strip.show();

#ifndef NDEBUG
    for (uint8_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(255, 255, 255));
      strip.show();
      delay(20);
    }

    for (uint8_t channel = 0; channel < 4; channel++) {
      for (uint8_t i = 0; i < strip.numPixels(); i++)
        strip.setPixelColor(i, strip.Color(channel == 0 ? 255 : 0, channel == 1 ? 255 : 0, channel == 2 ? 255 : 0));
      strip.show();
      delay(100);
    }
#endif
  }

  uint8_t numPixels() {
    return strip.numPixels();
  }

	bool has(const uint8_t x, const uint8_t y){
		return index(x, y) != LED_MISSING;
	}

	void set(const uint8_t x, const uint8_t y, const uint32_t color) {
		strip.setPixelColor(index(x, y), color);
	}

	void set(const uint8_t x, const uint8_t y, const uint8_t r, const uint8_t g, const uint8_t b) {
    set(x, y, strip.Color(r, g, b));
	}

	void show(){
		strip.show();
	}

	void setBrightness(const uint8_t brightness){
		strip.setBrightness(brightness);
	}

  /*
	void set(const uint8_t x, const uint8_t y, const Color& color){
		strip->setPixelColor(id(x,y),color.r,color.g,color.b);
	}
	uint32_t get(const uint8_t x, const uint8_t y){
		return strip->getPixelColor(id(x,y));
	}

	void set(const uint32_t color){
		set(Color(color));
	}
	void set(const Color& color){
		for(uint8_t i=0;i<strip->numPixels();i++)
			strip->setPixelColor(i,color.r,color.g,color.b);
	}
  */
};

}

#endif

