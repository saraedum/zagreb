#ifndef ENUMERATE_BOARDS_H
#define ENUMERATE_BOARDS_H

#include "delay_module.h"

class EnumerateBoards : public DelayModule {
	private:
		Wall*const wall;
		const uint32_t RED = Color(255,0,0).color();
		const uint32_t BLACK = Color(0,0,0).color();
		uint16_t i=0;
	public:
		EnumerateBoards(Wall* const wall):wall(wall){}
		virtual void loop(){
			update_now();
			DelayModule::loop();
		}
		virtual uint16_t loop_delayed(){
			for (BoardList* current=wall->boards;current!=0;current=current->next){
				Board* board = current->board;
				if (board->strip->numPixels() <= i)
					continue;
				board->strip->setPixelColor(i,board->strip->getPixelColor(i)==RED?BLACK:RED);
				board->strip->show();
			}
			i=(i+1)%32;
			return 100;
		}
};

#endif
