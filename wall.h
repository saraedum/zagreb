#ifndef WALL_HPP
#define WALL_HPP

#include "board.h"

class BoardList {
	private:
	public:
		BoardList(Board*const board, const uint8_t offset_x, const uint8_t offset_y):board(board),offset_x(offset_x),offset_y(offset_y){}
		Board* const board;
		const uint8_t offset_x,offset_y;
		BoardList* next=0;
};

class Wall {
	private:
	BoardList* getBoard(const uint8_t x, const uint8_t y){
		BoardList *next = boards;
		while(next){
			if (x >= next->offset_x && 
				x < next->offset_x + next->board->width &&
				y >= next->offset_y &&
				y < next->offset_y + next->board->height)
				return next;
			next = next->next;
		}
		return 0;
	}
	BoardList* boards = 0;
	public:
	Wall(const uint8_t width, const uint8_t height):width(width),height(height){}
	const uint8_t width;
	const uint8_t height;

	void add(Board* const board, const uint8_t offset_x, const uint8_t offset_y){
		if (boards){
			BoardList* next = boards;
			while(next->next)
				next = next->next;
			next->next = new BoardList(board, offset_x, offset_y);
		}else{
			boards = new BoardList(board, offset_x, offset_y);
		}
	}
	void set(const uint8_t x, const uint8_t y, const uint32_t color){
		BoardList* board = getBoard(x,y);
		if (board)
			board->board->set(x-board->offset_x, y-board->offset_y, color);
	}
	uint32_t get(const uint8_t x, const uint8_t y){
		BoardList* board = getBoard(x,y);
		if (board)
			return board->board->get(x-board->offset_x, y-board->offset_y);
		return 0;
	}
	bool has(const uint8_t x, const uint8_t y){
		return getBoard(x,y)!=0;
	}
	void show(){
		BoardList* next = boards;
		while(next){
			next->board->show();
			next = next->next;
		}
	}
	void setBrightness(uint8_t brightness){
		BoardList* next = boards;
		while(next){
			next->board->setBrightness(brightness);
			next = next->next;
		}
	}
	void set(const uint32_t color){
		BoardList* next = boards;
		while(next){
			next->board->set(color);
			next = next->next;
		}
	}
};

#endif
