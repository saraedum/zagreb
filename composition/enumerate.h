#ifndef ENUMERATE_H
#define ENUMERATE_H

#include "composition.h"
#include "../module/enumerate_boards.h"

class Enumerate : public Composition {
	private:
		EnumerateBoards module;
	public:
		Enumerate(Wall* const wall):module(wall){
			main = &module;
		}
};

#endif
