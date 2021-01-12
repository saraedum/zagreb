#ifndef ZAGREB_OUTPUTS_WALL_HPP
#define ZAGREB_OUTPUTS_WALL_HPP

#include "board.hpp"

namespace zagreb::outputs {

class Wall {
 public:
  // There can be at most 6 boards, one for each pin exposed on the breakout board.
  static constexpr uint8_t MAX_BOARDS = 6;

 private:
  uint8_t nboards = 0;

  struct {
    Board* board;
    uint8_t x;
    uint8_t y;
  } boards[MAX_BOARDS];

  int progress = 0;

 public:
  uint8_t brightness = 255;

  // Delay between updates to reach about 24 FPS
  uint16_t FPS16_DELAY = 1024 / 24;

  uint8_t width = 0;
  uint8_t height = 0;

  uint8_t pixels = 0;
  
	void add(Board* const board, const uint8_t offset_x, const uint8_t offset_y){
    boards[nboards].board = board;
    boards[nboards].x = offset_x;
    boards[nboards].y = offset_y;
    nboards++;

    FPS16_DELAY = 1024 / 24 / nboards;

    width = max(width, board->width + offset_x);
    height = max(height, board->height + offset_y);
    pixels += board->numPixels();

#ifndef NDEBUG
    for (uint8_t i = 0; i < 1; i++) {
      for (uint8_t X = 0; X <= width; X++) {
        for (uint8_t x = 0; x < width; x++)
          for (uint8_t y = 0; y < height; y++)
            set(x, y, x == X ? 255 : 0, 0, 0);
        show();
        delay(20);
      }
    }

    for (uint8_t i = 0; i < 1; i++) {
      for (uint8_t Y = 0; Y <= height; Y++) {
        for (uint8_t x = 0; x < width; x++)
          for (uint8_t y = 0; y < height; y++)
            set(x, y, y == Y ? 255 : 0, 0, 0);
        show();
        delay(20);
      }
    }
#endif
	}

  void paint(uint32_t (*color)(void*, uint8_t x, uint8_t y), void* data) {
    uint8_t width = boards[progress].board->width;
    uint8_t height = boards[progress].board->height;

    boards[progress].board->setBrightness(brightness);

    for (uint8_t x = 0; x < width; x++)
      for (uint8_t y = 0; y < height; y++)
        boards[progress].board->set(x, y, color(data, x + boards[progress].x, y + boards[progress].y));

    boards[progress].board->show();

    progress++;
    if (progress == nboards) progress = 0;
  }

	void set(const uint8_t x, const uint8_t y, uint8_t r, uint8_t g, uint8_t b){
    for (uint8_t b = 0; b < nboards; b++) {
      uint8_t xx = x - boards[b].x;
      uint8_t yy = y - boards[b].y;
      if (xx < boards[b].board->width && yy < boards[b].board->height) {
        boards[b].board->set(xx, yy, r, g, b);
      }
    }
	}

  void show() {
    for (uint8_t b = 0; b < nboards; b++)
      boards[b].board->show();
  }
};

}

#endif
