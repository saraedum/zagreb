#ifndef ALIGN_H
#define ALIGN_H

#include "composition.h"
#include "../module/align_boards.h"

class Align : public Composition {
	private:
		AlignBoards module;
	public:
		Align(Wall* const wall):module(wall){
			main = &module;
		}
};

#endif
